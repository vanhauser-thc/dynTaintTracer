#include <asm/unistd.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#ifdef UNIX
#if defined(MACOS) || defined(ANDROID)
#include <sys/syscall.h>
#else
#include <syscall.h>
#endif
#endif
#include "dr_api.h"
#include "dr_ir_macros.h"
#include "dr_ir_opnd.h"
#include "drmgr.h"
#include "droption.h"
#include "drreg.h"
#include "drsyms.h"
#include "drutil.h"
#include "drwrap.h"
#include "drx.h"
#include <cstring>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unordered_set>

#include "num2reg.h"
#include "num2syscall.h"

#define DEBUG

#ifndef __NR_recv
#define __NR_recv 1073
#endif
#ifndef __NR_open
#define __NR_open 99999 // then we do not need it
#endif

#if defined(AARCH64) || defined(X64)
#define _MYS "%lu"
#else
#define _MYS "%u"
#endif

static droption_t<bool> doworkaround(DROPTION_SCOPE_CLIENT, "workaround", false, "work around a bug in dynamorio concerning strex", "work around a bug in dynamorio concerning strex");
static droption_t<bool> reportdebug(DROPTION_SCOPE_CLIENT, "report-debug", false, "debug output", "debug output");
static droption_t<bool> reportunknown(DROPTION_SCOPE_CLIENT, "report-unknown", false, "report unknown instructions", "report unknown instructions");
static droption_t<bool> reportproblem(DROPTION_SCOPE_CLIENT, "report-problem", false, "report problems", "report problems");
static droption_t<bool> reportuntaint(DROPTION_SCOPE_CLIENT, "report-untaint", false, "report untainting instructions", "report untainting instructions");
static droption_t<bool> traceinst(DROPTION_SCOPE_CLIENT, "trace-inst", false, "report all instructions when there is taint", "report all instructions when there is taint");
static droption_t<bool> tracebb(DROPTION_SCOPE_CLIENT, "trace-bb", false, "report all basic blocks when there is taint", "report all basic blocks when there is taint");
static droption_t<bool> traceindirect(DROPTION_SCOPE_CLIENT, "trace-indirect", false, "report all indirect call/jmp when there is taint", "report all indirect call/jmp when there is taint");
static droption_t<bool> taintaccept(DROPTION_SCOPE_CLIENT, "taint-accept", false, "taint accept() and recvfrom()", "taint accept() and recvfrom()");
static droption_t<bool> taintconnect(DROPTION_SCOPE_CLIENT, "taint-connect", false, "taint connect() sendto()", "taint connect() and recvfrom()");
static droption_t<bool> taintstdin(DROPTION_SCOPE_CLIENT, "taint-stdin", false, "taint stdin", "taint stdin");
static droption_t<bool> taintsslread(DROPTION_SCOPE_CLIENT, "taint-sslread", false, "taint SSL_read()", "taint SSL_read()");
static droption_t<std::string> taintfile(DROPTION_SCOPE_CLIENT, "taint-file", "", "taint data from inputfile (or '*' from all)", "taint data from inputfile (or '*' from all)");
static droption_t<std::string> outfile(DROPTION_SCOPE_CLIENT, "outfile", "", "output file (default: stderr)", "output file (default: stderr)");

#ifdef X86
#define RAX DR_REG_XAX
#define DR_REG_LR 0
#define DR_REG_PC 0
#else
#define RAX DR_REG_R0
#endif
#ifdef WINDOWS
#define SYS_MAX_ARGS 9
#else
#define SYS_MAX_ARGS 3
#endif

#define MAX_NUM_MEM_REFS 4096
#define MEM_BUF_SIZE (sizeof(mem_ref_t) * MAX_NUM_MEM_REFS)
#define REG_LAST DR_REG_LAST_VALID_ENUM
#define UNSET64 0xffffffffffffffff
#define UNSET32 0xffffffff
#define FIRST_REG 1
#define FIRST_MEM 2
#define FLAGS_IGNORE 0
#define FLAGS_READ 1
#define FLAGS_UPDATE 2
#define FLAGS_OVERWRITE FLAGS_UPDATE
#define ARG_IGNORE 0
#define ARG_READ 1
#define ARG_UPDATE 2
#define ARG_OVERWRITE 3

static std::list<uint64_t> addressTainted;
static std::vector<int64_t> watchedFds;
static uint8_t regsClean[REG_LAST];
static FILE *trace = stderr;
static int tcls_idx, we_have_taint = 0, we_have_reg_taint = 0, dump_next_inst = 0;
static int indirect = 0, trace_inst = 0, trace_bb = 0, problem = 0, unknown = 0, untaint = 0, debug = 0, workaround = 0;
static int taint_connect = 0, taint_accept = 0;
static void *mutexM, *mutexF, *mutexL;

static const char *sslreads[] = {"SSL_read", "_SSL_read", "gnutls_record_recv", "_gnutls_record_recv", NULL};
static const char *endfuncs[] = {"abort", "_abort", "exit", "_exit", NULL};

typedef struct {
  reg_t param[16];
#ifdef WINDOWS
  reg_t xcx;
#endif
  uint8_t regsTainted[16384];
  int32_t syscall;
  int32_t neon;
  uintptr_t syscall_param;
  uintptr_t bufptr;
  uint64_t bufsize;
} per_thread_t;

typedef struct _mem_ref_t {
  app_pc addr; /* mem ref addr */
} mem_ref_t;

static void log_trace(void *drcontext, instrlist_t *bb, instr_t *inst, app_pc addr, int type, int info, char *string) {
  reg_id_t reg, reg2;
  char buf[64];

  if (!we_have_taint && type != 1 && type != 3)
    return;

  dr_mutex_lock(mutexL);
  switch (type) {
  case 0: {
    if (trace_inst)
      fprintf(trace, "COLOUR %p ", addr);
    break;
  }
  case 1: {
    fprintf(trace, "TAINT %p ", addr);
    break;
  }
  case 2: {
    if (untaint)
      fprintf(trace, "UNTAINT %p ", addr);
    break;
  }
  case 3: {
    fprintf(trace, "TAINT %p ", addr);
    break;
  }
  default:
    fprintf(stderr, "Error: invalid log_trace type %d\n", type);
  }
  if (inst == NULL) {
    fprintf(trace, " syscall(%s) ;%s\n", num2syscall[info], string);
  } else {
    instr_disassemble_to_buffer(drcontext, inst, buf, sizeof(buf));
    fprintf(trace, "%s ;%s\n", buf, string);
  }
  dr_mutex_unlock(mutexL);
}

bool checkTaintMem(uint64_t addr) {
  std::list<uint64_t>::iterator i;
  if (addressTainted.size() == 0)
    return false;
  dr_mutex_lock(mutexM);
  for (i = addressTainted.begin(); i != addressTainted.end(); i++) {
    if (addr == *i) {
      dr_mutex_unlock(mutexM);
      return true;
    }
  }
  dr_mutex_unlock(mutexM);
  return false;
}

void removeTaintMem(uint64_t addr) {
  if (addressTainted.size() == 0)
    return;
  if (debug) {
    if (checkTaintMem(addr) == false)
      return;
    if (debug)
      fprintf(trace, "DEBUG: %p is now untainted\n", (char *)addr);
  }
  dr_mutex_lock(mutexM);
  addressTainted.remove(addr);
  if (addressTainted.size() == 0) {
    if (debug)
      fprintf(trace, "DEBUG: address taint is empty now!\n");
    per_thread_t *data = (per_thread_t *)drmgr_get_cls_field(dr_get_current_drcontext(), tcls_idx);

    if (memcmp(regsClean, data->regsTainted, REG_LAST) == 0)
      we_have_taint = 0;
  }
  dr_mutex_unlock(mutexM);
}

void addTaintMem(uint64_t addr) {
  if (addr == UNSET64 || addr == 0)
    return;
  dr_mutex_lock(mutexM);
  if (!we_have_taint)
    we_have_taint = 1;
  addressTainted.push_back(addr);
  if (debug)
    fprintf(trace, "DEBUG: %p is now tainted\n", (char *)addr);
  dr_mutex_unlock(mutexM);
}

void printTaintMem() {
  std::list<uint64_t>::iterator i;
  fprintf(stderr, "DEBUG: current tainted memory addresses (" _MYS "):", addressTainted.size());
  dr_mutex_lock(mutexM);
  if (addressTainted.size() > 0)
    for (i = addressTainted.begin(); i != addressTainted.end(); ++i)
      fprintf(stderr, " %p", (char *)*i);
  fprintf(stderr, "\n");
  dr_mutex_unlock(mutexM);
}

bool checkTaintReg(reg_id_t reg) {
  if (reg < 0 || reg > REG_LAST || reg == DR_REG_INVALID || we_have_reg_taint == 0)
    return false;
  per_thread_t *data = (per_thread_t *)drmgr_get_cls_field(dr_get_current_drcontext(), tcls_idx);
  switch (reg) {
#include "regs_checktaint.c"
  default:
    return false;
  }
  return false;
}

void addTaintReg(int reg) {
  if (reg <= 0 || reg > REG_LAST || reg == DR_REG_INVALID
#ifdef REG_RSP
      || reg == REG_RSP
#endif
#ifdef REG_ESP
      || reg == REG_ESP
#endif
#ifdef AARCHXXX
      || reg == REG_R11 || reg == REG_R13 || reg == REG_R14 || reg == REG_R15
#endif
#ifdef DR_REG_XZR
      || reg == DR_REG_XZR || reg == DR_REG_XSP || reg == DR_REG_WSP || reg == DR_REG_WZR
#endif
      /*       */)
    return;
  per_thread_t *data = (per_thread_t *)drmgr_get_cls_field(dr_get_current_drcontext(), tcls_idx);

  // due how we do it we do not have to check if its already tainted
  switch (reg) {
#include "regs_taint.c"
  default:
    if (unknown || problem)
      fprintf(stderr, "PROBLEM 0x0000 ; can not taint register %s\n", ((reg <= REG_LAST) ? num2reg[reg] : "UNKNOWN"));
    return;
  }
  if (!we_have_reg_taint)
    we_have_reg_taint = 1;
  if (!we_have_taint)
    we_have_taint = 1;
  if (debug)
    fprintf(stderr, "DEBUG: register %s is now tainted\n", ((reg <= REG_LAST) ? num2reg[reg] : "UNKNOWN"));
}

void removeTaintReg(reg_id_t reg) {
  if (reg <= 0 || reg > REG_LAST || reg == DR_REG_INVALID || we_have_reg_taint == 0)
    return;
  if (debug && checkTaintReg(reg))
    fprintf(stderr, "DEBUG: register %s is now untainted\n", ((reg <= REG_LAST) ? num2reg[reg] : "UNKNOWN"));
  per_thread_t *data = (per_thread_t *)drmgr_get_cls_field(dr_get_current_drcontext(), tcls_idx);
  switch (reg) {
#include "regs_untaint.c"
  default:
    return;
  }
  if (memcmp(regsClean, data->regsTainted, REG_LAST) == 0) {
    we_have_reg_taint = 0;
    if (debug)
      fprintf(stderr, "DEBUG: register taint is empty now!\n");
    if (addressTainted.size() == 0)
      we_have_taint = 0;
  }
}

void printTaintReg() {
  int i;
  per_thread_t *data = (per_thread_t *)drmgr_get_cls_field(dr_get_current_drcontext(), tcls_idx);

  fprintf(stderr, "DEBUG: current tainted registers:");
  for (i = 0; i < REG_LAST; i++)
    if (data->regsTainted[i] == 1)
      fprintf(stderr, " %s", ((i <= REG_LAST) ? num2reg[i] : "UNKNOWN"));
  fprintf(stderr, "\n");
}

#include "regs_getvalue.c"

#include "ops_funcs.c"

static dr_emit_flags_t event_instruction(void *drcontext, void *tag, instrlist_t *ilist, instr_t *where, bool for_trace, bool translating, void *user_data) {
  if (we_have_taint == 0)
    return DR_EMIT_DEFAULT;
  if (trace_bb) {
    if (drmgr_is_first_instr(drcontext, where) == true) {
      dr_mutex_lock(mutexL);
      fprintf(trace, "BB %p ;\n", tag);
      dr_mutex_unlock(mutexL);
    }
  }
  switch (instr_get_opcode(where)) {
#include "ops.c"
  default:
    if (unknown || debug)
      fprintf(stderr, "UNKNOWN %p ", instr_get_app_pc(where));
    instr_disassemble(drcontext, where, STDERR);
    fprintf(stderr, " ; unknown instruction %d\n", instr_get_opcode(where));
    if (debug)
      debug_dump_opnds(where);
  }
  /*
    if (trace_inst)
      log_trace(drcontext, ilist, where, (app_pc)tag, 0, 0, (char*)"");
  */
  return DR_EMIT_DEFAULT;
}

static bool event_pre_syscall(void *drcontext, int sysnum) {
  int sysok = -1, type = 0;
  int64_t fd;
  std::vector<int64_t>::iterator cfd;
  char buf[64] = {0};
  switch (sysnum) {
  case __NR_openat: {
    if (taintfile.get_value().length() > 0) {
      char *filename = (char *)dr_syscall_get_param(drcontext, 1);
      if (strncmp(taintfile.get_value().c_str(), "*", 1) == 0 || strcmp(filename, taintfile.get_value().c_str()) == 0) {
        per_thread_t *data = (per_thread_t *)drmgr_get_cls_field(drcontext, tcls_idx);
        data->syscall = sysnum;
        type = 1;
      } else if (debug)
        fprintf(stderr, "DEBUG: openat(%s) is not matching\n", filename);
    }
    break;
  }
  case __NR_open: {
    if (taintfile.get_value().length() > 0) {
      char *filename = (char *)dr_syscall_get_param(drcontext, 0);
      if (strncmp(taintfile.get_value().c_str(), "*", 1) == 0 || strcmp(filename, taintfile.get_value().c_str()) == 0) {
        per_thread_t *data = (per_thread_t *)drmgr_get_cls_field(drcontext, tcls_idx);
        data->syscall = sysnum;
        type = 1;
      } else if (debug)
        fprintf(stderr, "DEBUG: open(%s) is not matching\n", filename);
    }
    break;
  }
  case __NR_close: {
    if (watchedFds.size() < 1)
      return true;
    fd = (int64_t)dr_syscall_get_param(drcontext, 0);
    dr_mutex_lock(mutexF);
    cfd = watchedFds.begin();
    for (; cfd != watchedFds.end();)
      if (fd == *cfd) {
        cfd = watchedFds.erase(cfd);
        if (debug)
          fprintf(stderr, "DEBUG: untainting fd %d\n", (int)fd);
        type = 2;
      } else
        cfd++;
    dr_mutex_unlock(mutexF);
    break;
  }
  case __NR_recvfrom: // fall through, we ignore the option and addr parameter
  case __NR_recv:     // fall through, we ignore the option parameter
  case __NR_pread64:  // fall through, we ignore the offset parameter
  case __NR_read: {
    uintptr_t bufptr = (uintptr_t)dr_syscall_get_param(drcontext, 1);
    if (__NR_recvfrom == sysnum && (taint_accept || taint_connect)) {
      per_thread_t *data = (per_thread_t *)drmgr_get_cls_field(drcontext, tcls_idx);
      data->syscall = sysnum;
      data->syscall_param = bufptr;
      type = 1;
      sprintf(buf, " %p", (void *)bufptr);
      break;
    } else {
      fd = (int64_t)dr_syscall_get_param(drcontext, 0);
      dr_mutex_lock(mutexF);
      cfd = watchedFds.begin();
      for (; cfd != watchedFds.end(); cfd++)
        if (fd == *cfd) {
          per_thread_t *data = (per_thread_t *)drmgr_get_cls_field(drcontext, tcls_idx);
          data->syscall = sysnum;
          data->syscall_param = bufptr;
          sprintf(buf, " %p", (void *)bufptr);
          type = 1;
          break;
        }
      dr_mutex_unlock(mutexF);
      if (checkTaintMem(bufptr) == true) { // we need to untaint
        uint64_t size, i;
        size = (uint64_t)dr_syscall_get_param(drcontext, 2);
        sprintf(buf, " %p", (void *)bufptr);
        for (i = 0; i < size; i++)
          removeTaintMem(bufptr + i);
      }
    }
    if (type == 1) {
      dr_mcontext_t mc = {
          sizeof(mc),
          DR_MC_INTEGER,
      };
      dr_get_mcontext(drcontext, &mc);
      int olddeb = debug;
      debug = 1;
#include "regs_searchvalue.c"
      debug = olddeb;
    }
    break;
  }
#ifdef __NR_socketcall
#warning "we have to implement syscall socketcall"
#endif
#ifdef __NR_accept4
  case __NR_accept4:
#endif
  case __NR_accept: {
    if (taint_accept) {
      per_thread_t *data = (per_thread_t *)drmgr_get_cls_field(drcontext, tcls_idx);
      data->syscall = sysnum;
      type = 1;
    }
    break;
  }
  case __NR_connect: {
    if (taint_connect) {
      per_thread_t *data = (per_thread_t *)drmgr_get_cls_field(drcontext, tcls_idx);
      data->syscall = sysnum;
      type = 1;
    }
    break;
  }
#ifdef __NR_mmap
  case __NR_mmap:
#endif
#ifdef __NR_mmap2
  case __NR_mmap2:
#endif
  {
    fd = (int64_t)dr_syscall_get_param(drcontext, 0);
    dr_mutex_lock(mutexF);
    cfd = watchedFds.begin();
    for (; cfd != watchedFds.end(); cfd++) {
      if (fd == *cfd) {
        per_thread_t *data = (per_thread_t *)drmgr_get_cls_field(drcontext, tcls_idx);
        data->syscall = sysnum;
        data->syscall_param = (uintptr_t)dr_syscall_get_param(drcontext, 1);
        type = 1;
        break;
      }
    }
    dr_mutex_unlock(mutexF);
    break;
  }
  case __NR_munmap: {
    uint64_t addr = (uint64_t)dr_syscall_get_param(drcontext, 0);
    if (checkTaintMem(addr) == true) {
      uint64_t i, size = (uint64_t)dr_syscall_get_param(drcontext, 1);
      type = 2;
      for (i = 0; i < size; i++)
        removeTaintMem(addr + i);
    }
    break;
  }
  case __NR_mremap: {
    uint64_t old = (uint64_t)dr_syscall_get_param(drcontext, 0);
    if (checkTaintMem(old) == true) {
      uint64_t i, size = (uint64_t)dr_syscall_get_param(drcontext, 1);
      for (i = 0; i < size; i++)
        removeTaintMem(old + i);
      per_thread_t *data = (per_thread_t *)drmgr_get_cls_field(drcontext, tcls_idx);
      data->syscall = sysnum;
      data->syscall_param = (uintptr_t)dr_syscall_get_param(drcontext, 2);
      type = 1;
    }
    break;
  }
  default:
    if (addressTainted.size() > 0) {
      uintptr_t tmp;
      for (fd = 0; fd < SYS_MAX_ARGS; fd++) {
        tmp = (uintptr_t)dr_syscall_get_param(drcontext, fd);
        if (tmp >= 0x1000 && tmp < 0x8000000000000000 && checkTaintMem(tmp) == true) {
          if (debug)
            fprintf(stderr, "DEBUG: syscall(%s[%d]) accessing tainted memory %p\n", ((sysnum <= MAX_SC_NO) ? num2syscall[sysnum] : "UNKNOWN"), sysnum, (char *)tmp);
          type = 3;
        }
      }
    }
  }
  if (trace_inst || type == 1 || (type == 2 && untaint) || (type == 3 && (problem || unknown || debug))) {
    dr_mcontext_t mc = {sizeof(mc), DR_MC_CONTROL /*only need xsp*/};
    dr_get_mcontext(drcontext, &mc);
    log_trace(drcontext, NULL, NULL, (app_pc)mc.xsp, type, sysnum, buf);
  }
  removeTaintReg(RAX);
  return true;
}

static void event_post_syscall(void *drcontext, int sysnum) {
  per_thread_t *data = (per_thread_t *)drmgr_get_cls_field(drcontext, tcls_idx);

  if (data->syscall == UNSET32)
    return;
  if (data->syscall == sysnum) {
    uint64_t i;
    dr_syscall_result_info_t info = {
        sizeof(info),
    };
    dr_syscall_get_result_ex(drcontext, &info);
    if (info.succeeded == true) {
      switch (data->syscall) {
      case __NR_connect:
      case __NR_accept:
      case __NR_openat:
      case __NR_open: {
        if (info.value >= 0) {
          dr_mutex_lock(mutexF);
          watchedFds.push_back(info.value);
          dr_mutex_unlock(mutexF);
          addTaintReg(RAX);
          if (debug)
            fprintf(stderr, "DEBUG: tainting fd " _MYS "\n", info.value);
        }
        break;
      }
      case __NR_recvfrom: // fall through, we ignore the option and addr parameter
      case __NR_recv:     // fall through, we ignore the option parameter
      case __NR_pread64:  // fall through, we ignore the offset parameter
      case __NR_read: {
        if (info.value > 0) {
          for (i = 0; i < info.value; i++)
            addTaintMem(data->syscall_param + i);
          addTaintReg(RAX);
          if (debug)
            fprintf(stderr, "DEBUG: read() tainting " _MYS " bytes at %p\n", info.value, (char *)data->syscall_param);
        }
        break;
      }
#ifdef __NR_mmap
      case __NR_mmap:
#endif
#ifdef __NR_mmap2
      case __NR_mmap2:
#endif
      case __NR_mremap: {
        if (info.value != 0 && info.value != -1) {
          for (i = 0; i < data->syscall_param; i++)
            addTaintMem(info.value + i);
          if (debug)
            fprintf(stderr, "DEBUG: mmap() tainting " _MYS " bytes at %p\n", data->syscall_param, (char *)info.value);
        }
        break;
      }
      default:
        fprintf(stderr, "TAINT ERROR: syscall not implemented: %d\n", sysnum);
        return;
      }
    }
  } else
    fprintf(stderr, "ERROR TAINT: syscall %d != %d\n", data->syscall, sysnum);
  data->syscall = UNSET32;
}

static bool event_filter_syscall(void *drcontext, int sysnum) { return true; }

static void event_thread_context_init(void *drcontext, bool new_depth) {
  per_thread_t *data;

  if (new_depth) {
    data = (per_thread_t *)dr_thread_alloc(drcontext, sizeof(per_thread_t));
    drmgr_set_cls_field(drcontext, tcls_idx, data);
    if (debug)
      fprintf(stderr, "Debug: new thread %d\n", dr_get_thread_id(drcontext));
  } else {
    if (debug)
      fprintf(stderr, "Debug: really new thread %d ?\n", dr_get_thread_id(drcontext));
    data = (per_thread_t *)drmgr_get_cls_field(drcontext, tcls_idx);
  }
  memset(data, 0, sizeof(*data));
  data->syscall = UNSET32;
}

static void event_thread_context_exit(void *drcontext, bool thread_exit) {
  if (thread_exit) {
    if (debug) {
      printTaintReg();
      fprintf(stderr, "Debug: thread %d exit\n", dr_get_thread_id(drcontext));
    }
    per_thread_t *data = (per_thread_t *)drmgr_get_cls_field(drcontext, tcls_idx);
    dr_thread_free(drcontext, data, sizeof(per_thread_t));
    drmgr_set_cls_field(drcontext, tcls_idx, NULL);
  }
}

static void wrap_pre_SSL_read(void *wrapcxt, OUT void **user_data) {
  per_thread_t *data = (per_thread_t *)drmgr_get_cls_field(drwrap_get_drcontext(wrapcxt), tcls_idx);

  data->bufptr = (uintptr_t)drwrap_get_arg(wrapcxt, 1);
  // data->bufsize = (uint64_t) drwrap_get_arg(wrapcxt, 2);
}

static void wrap_pre_abort(void *wrapcxt, OUT void **user_data) { we_have_taint = 0; }

static void wrap_post_SSL_read(void *wrapcxt, void *user_data) {
  int i, actual_read = (int)(ptr_int_t)drwrap_get_retval(wrapcxt);
  per_thread_t *data = (per_thread_t *)drmgr_get_cls_field(drwrap_get_drcontext(wrapcxt), tcls_idx);

  if (data->bufptr == 0 || actual_read < 1)
    return;
  for (i = 0; i < actual_read; i++)
    addTaintMem(data->bufptr + i);
  // addTaintReg(REG_EAX);
  // addTaintReg(REG_R0);
  if (debug)
    fprintf(stderr, "DEBUG: SSL_read(buf = %p) = %d\n", (void *)data->bufptr, actual_read);
}

static void module_load_event(void *drcontext, const module_data_t *mod, bool loaded) {
  app_pc addr;
  uint32_t i = 0;

  if (taintsslread.get_value() == true)
    while (sslreads[i] != NULL) {
      if ((addr = (app_pc)dr_get_proc_address(mod->handle, (char *)sslreads[i])) != 0) {
        if (debug)
          fprintf(stderr, "DEBUG: wrapped %s in %s\n", sslreads[i], dr_module_preferred_name(mod));
        drwrap_wrap(addr, wrap_pre_SSL_read, wrap_post_SSL_read);
      }
      i++;
    }

  i = 0;
  while (endfuncs[i] != NULL) {
    if ((addr = (app_pc)dr_get_proc_address(mod->handle, (char *)endfuncs[i])) != 0) {
      if (debug)
        fprintf(stderr, "DEBUG: wrapped %s in %s\n", endfuncs[i], dr_module_preferred_name(mod));
      drwrap_wrap(addr, wrap_pre_abort, NULL);
    }
    i++;
  }

  if (debug)
    fprintf(stderr, "DEBUG: loaded %s\n", dr_module_preferred_name(mod));
}

static void event_exit(void) {
  if (debug) {
    printTaintMem();
  }
  fprintf(trace, "[dynTainterTracer] done\n");
  dr_mutex_destroy(mutexM);
  drmgr_unregister_cls_field(event_thread_context_init, event_thread_context_exit, tcls_idx);
  drx_exit();
  drwrap_exit();
  drsym_exit();
  drmgr_exit();
  if (outfile.get_value().length() > 0)
    fclose(trace);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {
  std::string parse_err;
  dr_set_client_name("Running DynamoRIO tainter", "https://mh-sec.de/");
  if (droption_parser_t::parse_argv(DROPTION_SCOPE_CLIENT, argc, argv, &parse_err, NULL) != 1) {
    std::cout << "afl-dynamorio (c) 2018 by Marc \"van Hauser\" Heuse <mh@mh-sec.de> AGPL 3.0" << std::endl;
    std::cout << "===========================================================================" << std::endl;
    std::cout << droption_parser_t::usage_long(DROPTION_SCOPE_ALL, "", "", " (", ")", "  ", "\n");
    dr_abort();
  }

  drreg_options_t drreg_ops = {sizeof(drreg_ops), 3, false};
  auto drreg_ret = drreg_init(&drreg_ops);
  DR_ASSERT(drreg_ret == DRREG_SUCCESS);

  if (reportdebug.get_value() == true)
    debug = 1;
  if (reportunknown.get_value() == true)
    unknown = 1;
  if (reportproblem.get_value() == true)
    problem = 1;
  if (reportuntaint.get_value() == true)
    untaint = 1;
  if (traceinst.get_value() == true)
    trace_inst = 1;
  if (tracebb.get_value() == true)
    trace_bb = 1;
  if (traceindirect.get_value() == true)
    indirect = 1;
  if (taintaccept.get_value() == true)
    taint_accept = 1;
  if (taintconnect.get_value() == true)
    taint_connect = 1;
  if (taintstdin.get_value() == true) {
    watchedFds.push_back(0); // taint fd 0
    if (debug)
      fprintf(stderr, "DEBUG: tainted stdin fd 0\n");
  }
  if (doworkaround.get_value() == true)
    workaround = 1;

  memset(regsClean, 0, REG_LAST);
  mutexM = dr_mutex_create();
  mutexF = dr_mutex_create();
  mutexL = dr_mutex_create();

  if (!drmgr_init() || !drx_init() || !drwrap_init())
    DR_ASSERT(false);

  if (strlen(outfile.get_value().c_str()) > 0) {
    if ((trace = fopen(outfile.get_value().c_str(), "w")) == NULL)
      DR_ASSERT_MSG(false, "can not write -outputfile");
  }
  fprintf(trace, "[dynTainterTracer] begin\n");
  if (workaround)
    fprintf(trace, "INFO workaround activated\n");
#ifdef AARCHXX
  else
    fprintf(trace, "INFO workaround NOT activated\n");
#endif

  if (debug)
    fprintf(stderr, "DEBUG: Running with:"
#ifdef AARCHXX
                    " AARCHXX"
#endif
#ifdef AARCH64
                    " AARCH64"
#endif
#ifdef X86
                    " X86"
#endif
#ifdef X64
                    " X64"
#endif
                    "\n");

  tcls_idx = drmgr_register_cls_field(event_thread_context_init, event_thread_context_exit);
  DR_ASSERT_MSG(tcls_idx != -1, "memory problems");

  disassemble_set_syntax(DR_DISASM_INTEL);

  dr_register_exit_event(event_exit);
  drmgr_register_module_load_event(module_load_event);
  if (!drmgr_register_bb_instrumentation_event(NULL, event_instruction, NULL))
    DR_ASSERT_MSG(false, "can not register instrument cb");
  drmgr_register_pre_syscall_event(event_pre_syscall);
  drmgr_register_post_syscall_event(event_post_syscall);
  dr_register_filter_syscall_event(event_filter_syscall);
  drsym_init(0);
}
