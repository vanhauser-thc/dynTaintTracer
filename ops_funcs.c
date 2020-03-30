#ifdef __cplusplus
extern "C" {
#endif
class drreg_reservation {
public:
  drreg_reservation(instrlist_t *ilist, instr_t *where);
  ~drreg_reservation();
  operator reg_id_t() const { return reg_; }
private:
  instrlist_t *ilist_;
  instr_t *where_;
  reg_id_t reg_;
  void *drcontext_;
};

void unimplemented_opcode(instr_t *where);

void instrlist_meta_preinsert_xl8(instrlist_t *ilist, instr_t *where, instr_t *insert);
#ifdef __cplusplus
}
#endif
drreg_reservation::drreg_reservation(instrlist_t *ilist, instr_t *where) : drcontext_(dr_get_current_drcontext()), ilist_(ilist), where_(where) {
  if (drreg_reserve_register(drcontext_, ilist_, where_, NULL, &reg_) != DRREG_SUCCESS)
    throw std::exception();
}

drreg_reservation::~drreg_reservation() { drreg_unreserve_register(drcontext_, ilist_, where_, reg_); }

void unimplemented_opcode(instr_t *where) { /* N/A */ }

void instrlist_meta_preinsert_xl8(instrlist_t *ilist, instr_t *where, instr_t *insert) { instrlist_meta_preinsert(ilist, where, INSTR_XL8(insert, instr_get_app_pc(where))); }

// ******************************************************************************

#define DRREG_RESTORE_APP_VALUE(drcontext, ilist, where, opnd, cb)                                                                                                                                                                                                                                                                                                                                                                                                                                                             \
  do {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         \
    reg_id_t swap = DR_REG_NULL;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               \
    drreg_restore_app_values(drcontext, ilist, where, opnd, &swap);                                                                                                                                                                                                                                                                                                                                                                                                                                                            \
    cb;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        \
    if (swap != DR_REG_NULL)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   \
      drreg_unreserve_register(drcontext, ilist, where, swap);                                                                                                                                                                                                                                                                                                                                                                                                                                                                 \
  } while (false);

typedef enum { DB, IA, DA, IB } stack_dir_t;

stack_dir_t opcode2dir(int opcode) {
#ifdef AARCHXX
  if (opcode == OP_stmdb || opcode == OP_ldmdb)
    return DB;
  if (opcode == OP_stmib || opcode == OP_ldmib)
    return IB;
  if (opcode == OP_stmda || opcode == OP_ldmda)
    return DA;
#endif
  return IA;
}

// ******************************************************************************

static void process_regptr2reg(int src, int dst, int mem, uintptr_t imm, uintptr_t addr, int op) {
  dr_mcontext_t mc = {sizeof(mc), DR_MC_ALL};
  size_t val;

  dr_get_mcontext(dr_get_current_drcontext(), &mc);
  val = getRegValue(&mc, mem);
  // if (addr == 0xb6b51374 || addr == 0xb6b5136c)
  if (debug)
    fprintf(stderr, "%p mem2reg %s %d=%s <= [%d=%s+???]=[%d=%s]=%p + %p\n", (void *)addr, decode_opcode_name(op), dst, num2reg[dst], src, num2reg[src], mem, num2reg[mem], (void *)val, (void *)imm);
  if (checkTaintReg(src) == true) {
    addTaintReg(dst);
    dr_mutex_lock(mutexL);
    fprintf(trace, "TAINT %p  %s %s, [%s] ; [%p]\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src], (void *)val);
    dr_mutex_unlock(mutexL);
  } else {
    if (checkTaintMem(val) == true || (imm != 0 && (checkTaintMem(imm) || checkTaintMem(val + imm) == true))) {
      addTaintReg(dst);
      dr_mutex_lock(mutexL);
      fprintf(trace, "TAINT %p  %s %s, [%s] ; %p\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src], (void *)val);
      dr_mutex_unlock(mutexL);
    } else if (checkTaintReg(dst) == true) {
      removeTaintReg(dst);
      if (untaint) {
        dr_mutex_lock(mutexL);
        fprintf(trace, "UNTAINT %p  %s %s, [%s] ; %p\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src], (void *)val);
        dr_mutex_unlock(mutexL);
      }
    } else if (trace_inst) {
      dr_mutex_lock(mutexL);
      fprintf(trace, "COLOUR %p  %s %s, [%s] ; %p\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src], (void *)val);
      dr_mutex_unlock(mutexL);
    }
  }
}

static void process_regptr2regreg(int src, int dst1, int dst2, int mem, uintptr_t addr, int op) {
  dr_mcontext_t mc = {sizeof(mc), DR_MC_ALL};
  uintptr_t val, didtaint = 0, diduntaint = 0;

  dr_get_mcontext(dr_get_current_drcontext(), &mc);
  val = getRegValue(&mc, mem);
  // if (addr == 0xb6b51374 || addr == 0xb6b5136c)
  if (debug)
    fprintf(stderr, "%p mem2reg %s [%d=%s+???]=[%d=%s]=%p => %d=%s + %d=%s\n", (void *)addr, decode_opcode_name(op), src, num2reg[src], mem, num2reg[mem], (void *)val, dst1, num2reg[dst1], dst2, num2reg[dst2]);
  if (checkTaintReg(src) == true) {
    addTaintReg(dst1);
    addTaintReg(dst2);
    didtaint = 3;
  } else {
    if (checkTaintMem(val) == true) {
      addTaintReg(dst1);
      didtaint = 1;
    }
    if (checkTaintMem(val + sizeof(uintptr_t)) == true) {
      addTaintReg(dst2);
      didtaint += 2;
    }
  }
  if ((didtaint & 1) == 0 && checkTaintReg(dst1) == true) {
    removeTaintReg(dst1);
    diduntaint = 1;
  }
  if ((didtaint & 2) == 0 && checkTaintReg(dst2) == true) {
    removeTaintReg(dst2);
    diduntaint += 2;
  }
  if (didtaint) {
    dr_mutex_lock(mutexL);
    fprintf(trace, "TAINT %p  %s %s, %s, [%s] ; %p\n", (void *)addr, decode_opcode_name(op), num2reg[dst1], num2reg[dst2], num2reg[src], (void *)val);
    dr_mutex_unlock(mutexL);
  } else {
    if (untaint && diduntaint != 0) {
      dr_mutex_lock(mutexL);
      fprintf(trace, "UNTAINT %p  %s %s, %s, [%s] ; %p\n", (void *)addr, decode_opcode_name(op), num2reg[dst1], num2reg[dst2], num2reg[src], (void *)val);
      dr_mutex_unlock(mutexL);
    } else if (trace_inst) {
      dr_mutex_lock(mutexL);
      fprintf(trace, "COLOUR %p  %s %s, %s, [%s] ; %p\n", (void *)addr, decode_opcode_name(op), num2reg[dst1], num2reg[dst2], num2reg[src], (void *)val);
      dr_mutex_unlock(mutexL);
    }
  }
}

static void process_reg2regptr(int src, int dst, int mem, uintptr_t addr, int op) {
  dr_mcontext_t mc = {sizeof(mc), DR_MC_ALL};
  uintptr_t val;

  dr_get_mcontext(dr_get_current_drcontext(), &mc);
  val = getRegValue(&mc, mem);
  // if (addr == 0xb6b51374 || addr == 0xb6b5136c)
  if (debug)
    fprintf(stderr, "%p reg2mem %s [%d=%s+???]=[%d=%s]=%p <= %d=%s\n", (void *)addr, decode_opcode_name(op), dst, num2reg[dst], mem, num2reg[mem], (void *)val, src, num2reg[src]);
  if (checkTaintReg(src) == true) {
    addTaintMem(val);
    dr_mutex_lock(mutexL);
    fprintf(trace, "TAINT %p  %s %s, [%s] ; %p\n", (void *)addr, decode_opcode_name(op), num2reg[src], num2reg[dst], (void *)val);
    dr_mutex_unlock(mutexL);
  } else {
    if (checkTaintReg(dst) == true) {
      addTaintMem(val);
      dr_mutex_lock(mutexL);
      fprintf(trace, "TAINT %p  %s %s, [%s] ; [%p]\n", (void *)addr, decode_opcode_name(op), num2reg[src], num2reg[dst], (void *)val);
      dr_mutex_unlock(mutexL);
    } else if (checkTaintMem(val) == true) {
      removeTaintMem(val);
      if (untaint) {
        dr_mutex_lock(mutexL);
        fprintf(trace, "UNTAINT %p  %s %s, [%s] ; %p\n", (void *)addr, decode_opcode_name(op), num2reg[src], num2reg[dst], (void *)val);
        dr_mutex_unlock(mutexL);
      } else if (trace_inst) {
        dr_mutex_lock(mutexL);
        fprintf(trace, "COLOUR %p  %s %s, [%s] ; %p\n", (void *)addr, decode_opcode_name(op), num2reg[src], num2reg[dst], (void *)val);
        dr_mutex_unlock(mutexL);
      }
    } else if (trace_inst) {
      dr_mutex_lock(mutexL);
      fprintf(trace, "COLOUR %p  %s %s, [%s] ; %p\n", (void *)addr, decode_opcode_name(op), num2reg[src], num2reg[dst], (void *)val);
      dr_mutex_unlock(mutexL);
    }
  }
}

static void process_regreg2regptr(int src1, int src2, int dst, int mem, uintptr_t addr, int op) {
  dr_mcontext_t mc = {sizeof(mc), DR_MC_ALL};
  uintptr_t val, didtaint = 0, diduntaint = 0;

  dr_get_mcontext(dr_get_current_drcontext(), &mc);
  val = getRegValue(&mc, mem);
  // if (addr == 0xb6b51374 || addr == 0xb6b5136c)
  if (debug)
    fprintf(stderr, "%p reg2mem %s [%d=%s+???]=[%d=%s]=%p <= %d=%s + %d=%s\n", (void *)addr, decode_opcode_name(op), dst, num2reg[dst], mem, num2reg[mem], (void *)val, src1, num2reg[src1], src2, num2reg[src2]);
  if (checkTaintReg(dst) == true) {
    addTaintMem(val);
    addTaintMem(val + sizeof(uintptr_t));
    didtaint = 3;
  } else {
    if (checkTaintReg(src1) == true) {
      addTaintMem(val);
      didtaint = 1;
    }
    if (checkTaintReg(src2) == true) {
      addTaintMem(val + sizeof(uintptr_t));
      didtaint += 2;
    }
  }
  if ((didtaint & 1) == 0 && checkTaintMem(val) == true) {
    removeTaintMem(val);
    diduntaint = 1;
  }
  if ((didtaint & 2) == 0 && checkTaintMem(val + sizeof(uintptr_t)) == true) {
    removeTaintMem(val + sizeof(uintptr_t));
    diduntaint += 2;
  }
  if (didtaint) {
    dr_mutex_lock(mutexL);
    fprintf(trace, "TAINT %p  %s %s, %s, [%s] ; %p\n", (void *)addr, decode_opcode_name(op), num2reg[src1], num2reg[src2], num2reg[dst], (void *)val);
    dr_mutex_unlock(mutexL);
  } else {
    if (untaint && diduntaint != 0) {
      dr_mutex_lock(mutexL);
      fprintf(trace, "UNTAINT %p  %s %s, %s, [%s] ; %p\n", (void *)addr, decode_opcode_name(op), num2reg[src1], num2reg[src2], num2reg[dst], (void *)val);
      dr_mutex_unlock(mutexL);
    } else if (trace_inst) {
      dr_mutex_lock(mutexL);
      fprintf(trace, "COLOUR %p  %s %s, %s, [%s] ; %p\n", (void *)addr, decode_opcode_name(op), num2reg[src1], num2reg[src2], num2reg[dst], (void *)val);
      dr_mutex_unlock(mutexL);
    }
  }
}

static void process_pop_reg(int dst, uintptr_t addr, int op) {
  dr_mcontext_t mc = {sizeof(mc), DR_MC_ALL};
  dr_get_mcontext(dr_get_current_drcontext(), &mc);
  uintptr_t val = getRegValue(&mc, DR_REG_SP) - sizeof(intptr_t);

  if (checkTaintMem(val) == true) {
    addTaintReg(dst);
    dr_mutex_lock(mutexL);
    fprintf(trace, "TAINT %p  %s %s ; %p\n", (void *)addr, decode_opcode_name(op), num2reg[dst], (void *)val);
    dr_mutex_unlock(mutexL);
  } else {
    if (checkTaintReg(dst) == true) {
      removeTaintReg(dst);
      if (untaint) {
        dr_mutex_lock(mutexL);
        fprintf(trace, "UNTAINT %p  %s %s ; %p\n", (void *)addr, decode_opcode_name(op), num2reg[dst], (void *)val);
        dr_mutex_unlock(mutexL);
      } else if (trace_inst) {
        dr_mutex_lock(mutexL);
        fprintf(trace, "COLOUR %p  %s %s ; %p\n", (void *)addr, decode_opcode_name(op), num2reg[dst], (void *)val);
        dr_mutex_unlock(mutexL);
      }
    } else if (trace_inst) {
      dr_mutex_lock(mutexL);
      fprintf(trace, "COLOUR %p  %s %s ; %p\n", (void *)addr, decode_opcode_name(op), num2reg[dst], (void *)val);
      dr_mutex_unlock(mutexL);
    }
  }
}

static void process_push_reg(int src, uintptr_t addr, int op) {
  dr_mcontext_t mc = {sizeof(mc), DR_MC_ALL};
  dr_get_mcontext(dr_get_current_drcontext(), &mc);
  uintptr_t val = getRegValue(&mc, DR_REG_SP);

  if (checkTaintReg(src) == true) {
    addTaintMem(val);
    dr_mutex_lock(mutexL);
    fprintf(trace, "TAINT %p  %s %s ; %p\n", (void *)addr, decode_opcode_name(op), num2reg[src], (void *)val);
    dr_mutex_unlock(mutexL);
  } else {
    if (checkTaintMem(val) == true) {
      removeTaintMem(val);
      if (untaint) {
        dr_mutex_lock(mutexL);
        fprintf(trace, "UNTAINT %p  %s %s ; %p\n", (void *)addr, decode_opcode_name(op), num2reg[src], (void *)val);
        dr_mutex_unlock(mutexL);
      } else if (trace_inst) {
        dr_mutex_lock(mutexL);
        fprintf(trace, "COLOUR %p  %s %s ; %p\n", (void *)addr, decode_opcode_name(op), num2reg[src], (void *)val);
        dr_mutex_unlock(mutexL);
      }
    } else if (trace_inst) {
      dr_mutex_lock(mutexL);
      fprintf(trace, "COLOUR %p  %s %s ; %p\n", (void *)addr, decode_opcode_name(op), num2reg[src], (void *)val);
      dr_mutex_unlock(mutexL);
    }
  }
}

static void process_push_imm(uintptr_t src, uintptr_t addr, int op) {
  dr_mcontext_t mc = {sizeof(mc), DR_MC_ALL};
  dr_get_mcontext(dr_get_current_drcontext(), &mc);
  uintptr_t val = getRegValue(&mc, DR_REG_SP);

  if (checkTaintMem(src) == true) {
    addTaintMem(val);
    dr_mutex_lock(mutexL);
    fprintf(trace, "TAINT %p  %s %p ; %p\n", (void *)addr, decode_opcode_name(op), (void *)src, (void *)val);
    dr_mutex_unlock(mutexL);
  } else {
    if (checkTaintMem(val) == true) {
      removeTaintMem(val);
      if (untaint) {
        dr_mutex_lock(mutexL);
        fprintf(trace, "UNTAINT %p  %s %p ; %p\n", (void *)addr, decode_opcode_name(op), (void *)src, (void *)val);
        dr_mutex_unlock(mutexL);
      } else if (trace_inst) {
        dr_mutex_lock(mutexL);
        fprintf(trace, "COLOUR %p  %s %p ; %p\n", (void *)addr, decode_opcode_name(op), (void *)src, (void *)val);
        dr_mutex_unlock(mutexL);
      }
    } else if (trace_inst) {
      dr_mutex_lock(mutexL);
      fprintf(trace, "COLOUR %p  %s %p ; %p\n", (void *)addr, decode_opcode_name(op), (void *)src, (void *)val);
      dr_mutex_unlock(mutexL);
    }
  }
}

static void process_reg2reg(int src, int dst, uintptr_t addr, int op) {
  // fprintf(stderr, "%p reg2reg [%d=%s] <= %d=%s\n", (void*)addr, decode_opcode_name(op), dst, num2reg[dst], src, num2reg[src]);
  if (checkTaintReg(src) == true) {
    addTaintReg(dst);
    dr_mutex_lock(mutexL);
    fprintf(trace, "TAINT %p  %s %s, %s ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src]);
    dr_mutex_unlock(mutexL);
  } else {
    if (checkTaintReg(dst) == true) {
      removeTaintReg(dst);
      if (untaint) {
        dr_mutex_lock(mutexL);
        fprintf(trace, "UNTAINT %p  %s %s, %s ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src]);
        dr_mutex_unlock(mutexL);
      } else if (trace_inst) {
        dr_mutex_lock(mutexL);
        fprintf(trace, "COLOUR %p  %s %s, %s ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src]);
        dr_mutex_unlock(mutexL);
      }
    } else if (trace_inst) {
      dr_mutex_lock(mutexL);
      fprintf(trace, "COLOUR %p  %s %s, %s ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src]);
      dr_mutex_unlock(mutexL);
    }
  }
}

static void process_imm2reg(uintptr_t src, int dst, uintptr_t addr, int op) {
  // fprintf(stderr, "%p reg2reg [%d=%s] <= %d=%s\n", (void*)addr, decode_opcode_name(op), dst, num2reg[dst], src, num2reg[src]);
  if (checkTaintMem(src) == true) {
    addTaintReg(dst);
    dr_mutex_lock(mutexL);
    fprintf(trace, "TAINT %p  %s %s, %p ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], (void *)src);
    dr_mutex_unlock(mutexL);
  } else {
    if (checkTaintReg(dst) == true) {
      removeTaintReg(dst);
      if (untaint) {
        dr_mutex_lock(mutexL);
        fprintf(trace, "UNTAINT %p  %s %s, %p ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], (void *)src);
        dr_mutex_unlock(mutexL);
      } else if (trace_inst) {
        dr_mutex_lock(mutexL);
        fprintf(trace, "COLOUR %p  %s %s, %p ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], (void *)src);
        dr_mutex_unlock(mutexL);
      }
    } else if (trace_inst) {
      dr_mutex_lock(mutexL);
      fprintf(trace, "COLOUR %p  %s %s, %p ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], (void *)src);
      dr_mutex_unlock(mutexL);
    }
  }
}

static void process_regreg2reg(int src1, int src2, int dst, uintptr_t addr, int op) {
  // fprintf(stderr, "%p reg2reg [%d=%s] <= %d=%s\n", (void*)addr, decode_opcode_name(op), dst, num2reg[dst], src, num2reg[src]);
  if (checkTaintReg(src1) == true || checkTaintReg(src2) == true) {
    addTaintReg(dst);
    dr_mutex_lock(mutexL);
    fprintf(trace, "TAINT %p  %s %s, %s, %s ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src1], num2reg[src2]);
    dr_mutex_unlock(mutexL);
  } else {
    if (checkTaintReg(dst) == true) {
      removeTaintReg(dst);
      if (untaint) {
        dr_mutex_lock(mutexL);
        fprintf(trace, "UNTAINT %p  %s %s, %s, %s ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src1], num2reg[src2]);
        dr_mutex_unlock(mutexL);
      } else if (trace_inst) {
        dr_mutex_lock(mutexL);
        fprintf(trace, "COLOUR %p  %s %s, %s, %s ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src1], num2reg[src2]);
        dr_mutex_unlock(mutexL);
      }
    } else if (trace_inst) {
      dr_mutex_lock(mutexL);
      fprintf(trace, "COLOUR %p  %s %s, %s, %s ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src1], num2reg[src2]);
      dr_mutex_unlock(mutexL);
    }
  }
}

static void process_regreg2regreg(int src1, int src2, int dst1, int dst2, uintptr_t addr, int op) {
  // fprintf(stderr, "%p reg2reg [%d=%s] <= %d=%s\n", (void*)addr, decode_opcode_name(op), dst, num2reg[dst], src, num2reg[src]);
  if (checkTaintReg(src1) == true || checkTaintReg(src2) == true) {
    addTaintReg(dst1);
    addTaintReg(dst2);
    dr_mutex_lock(mutexL);
    fprintf(trace, "TAINT %p  %s %s, %s, %s, %s ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst1], num2reg[src2], num2reg[src1], num2reg[src2]);
    dr_mutex_unlock(mutexL);
  } else {
    if (checkTaintReg(dst1) == true || checkTaintReg(dst2) == true) {
      removeTaintReg(dst1);
      removeTaintReg(dst2);
      if (untaint) {
        dr_mutex_lock(mutexL);
        fprintf(trace, "UNTAINT %p  %s %s, %s, %s, %s ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst1], num2reg[src2], num2reg[src1], num2reg[src2]);
        dr_mutex_unlock(mutexL);
      } else if (trace_inst) {
        dr_mutex_lock(mutexL);
        fprintf(trace, "COLOUR %p  %s %s, %s, %s, %s ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst1], num2reg[src2], num2reg[src1], num2reg[src2]);
        dr_mutex_unlock(mutexL);
      }
    } else if (trace_inst) {
      dr_mutex_lock(mutexL);
      fprintf(trace, "COLOUR %p  %s %s, %s, %s, %s ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst1], num2reg[src2], num2reg[src1], num2reg[src2]);
      dr_mutex_unlock(mutexL);
    }
  }
}

static void process_regimm2regreg(int src1, uintptr_t src2, int dst1, int dst2, uintptr_t addr, int op) {
  // fprintf(stderr, "%p reg2reg [%d=%s] <= %d=%s\n", (void*)addr, decode_opcode_name(op), dst, num2reg[dst], src, num2reg[src]);
  if (checkTaintReg(src1) == true || checkTaintMem(src2) == true) {
    addTaintReg(dst1);
    addTaintReg(dst2);
    dr_mutex_lock(mutexL);
    fprintf(trace, "TAINT %p  %s %s, %s, %s, %p ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst1], num2reg[src2], num2reg[src1], (void *)src2);
    dr_mutex_unlock(mutexL);
  } else {
    if (checkTaintReg(dst1) == true || checkTaintReg(dst2) == true) {
      removeTaintReg(dst1);
      removeTaintReg(dst2);
      if (untaint) {
        dr_mutex_lock(mutexL);
        fprintf(trace, "UNTAINT %p  %s %s, %s, %s, %p ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst1], num2reg[src2], num2reg[src1], (void *)src2);
        dr_mutex_unlock(mutexL);
      } else if (trace_inst) {
        dr_mutex_lock(mutexL);
        fprintf(trace, "COLOUR %p  %s %s, %s, %s, %p ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst1], num2reg[src2], num2reg[src1], (void *)src2);
        dr_mutex_unlock(mutexL);
      }
    } else if (trace_inst) {
      dr_mutex_lock(mutexL);
      fprintf(trace, "COLOUR %p  %s %s, %s, %s, %p ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst1], num2reg[src2], num2reg[src1], (void *)src2);
      dr_mutex_unlock(mutexL);
    }
  }
}

static void process_regregreg2reg(int src1, int src2, int src3, int dst, uintptr_t addr, int op) {
  // fprintf(stderr, "%p reg2reg [%d=%s] <= %d=%s\n", (void*)addr, decode_opcode_name(op), dst, num2reg[dst], src, num2reg[src]);
  if (checkTaintReg(src1) == true || checkTaintReg(src2) == true || checkTaintReg(src3) == true) {
    addTaintReg(dst);
    dr_mutex_lock(mutexL);
    fprintf(trace, "TAINT %p  %s %s, %s, %s, %s ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src1], num2reg[src2], num2reg[src3]);
    dr_mutex_unlock(mutexL);
  } else {
    if (checkTaintReg(dst) == true) {
      removeTaintReg(dst);
      if (untaint) {
        dr_mutex_lock(mutexL);
        fprintf(trace, "UNTAINT %p  %s %s, %s, %s, %s ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src1], num2reg[src2], num2reg[src3]);
        dr_mutex_unlock(mutexL);
      } else if (trace_inst) {
        dr_mutex_lock(mutexL);
        fprintf(trace, "COLOUR %p  %s %s, %s, %s, %s ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src1], num2reg[src2], num2reg[src3]);
        dr_mutex_unlock(mutexL);
      }
    } else if (trace_inst) {
      dr_mutex_lock(mutexL);
      fprintf(trace, "COLOUR %p  %s %s, %s, %s, %s ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src1], num2reg[src2], num2reg[src3]);
      dr_mutex_unlock(mutexL);
    }
  }
}

static void process_regregimm2reg(int src1, int src2, uintptr_t src3, int dst, uintptr_t addr, int op) {
  // fprintf(stderr, "%p reg2reg [%d=%s] <= %d=%s\n", (void*)addr, decode_opcode_name(op), dst, num2reg[dst], src, num2reg[src]);
  if (checkTaintReg(src1) == true || checkTaintReg(src2) == true || checkTaintMem(src3) == true) {
    addTaintReg(dst);
    dr_mutex_lock(mutexL);
    fprintf(trace, "TAINT %p  %s %s, %s, %s, %p ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src1], num2reg[src2], (void *)src3);
    dr_mutex_unlock(mutexL);
  } else {
    if (checkTaintReg(dst) == true) {
      removeTaintReg(dst);
      if (untaint) {
        dr_mutex_lock(mutexL);
        fprintf(trace, "UNTAINT %p  %s %s, %s, %s, %p ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src1], num2reg[src2], (void *)src3);
        dr_mutex_unlock(mutexL);
      } else if (trace_inst) {
        dr_mutex_lock(mutexL);
        fprintf(trace, "COLOUR %p  %s %s, %s, %s, %p ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src1], num2reg[src2], (void *)src3);
        dr_mutex_unlock(mutexL);
      }
    } else if (trace_inst) {
      dr_mutex_lock(mutexL);
      fprintf(trace, "COLOUR %p  %s %s, %s, %s, %p ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src1], num2reg[src2], (void *)src3);
      dr_mutex_unlock(mutexL);
    }
  }
}

static void process_regimm2reg(int src1, uintptr_t src2, int dst, uintptr_t addr, int op) {
  // fprintf(stderr, "%p reg2reg [%d=%s] <= %d=%s\n", (void*)addr, decode_opcode_name(op), dst, num2reg[dst], src, num2reg[src]);
  if (checkTaintReg(src1) == true || checkTaintMem(src2) == true) {
    addTaintReg(dst);
    dr_mutex_lock(mutexL);
    fprintf(trace, "TAINT %p  %s %s, %s, %p ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src1], (void *)src2);
    dr_mutex_unlock(mutexL);
  } else {
    if (checkTaintReg(dst) == true) {
      removeTaintReg(dst);
      if (untaint) {
        dr_mutex_lock(mutexL);
        fprintf(trace, "UNTAINT %p  %s %s, %s, %p ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src1], (void *)src2);
        dr_mutex_unlock(mutexL);
      } else if (trace_inst) {
        dr_mutex_lock(mutexL);
        fprintf(trace, "COLOUR %p  %s %s, %s, %p ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src1], (void *)src2);
        dr_mutex_unlock(mutexL);
      }
    } else if (trace_inst) {
      dr_mutex_lock(mutexL);
      fprintf(trace, "COLOUR %p  %s %s, %s, %p ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src1], (void *)src2);
      dr_mutex_unlock(mutexL);
    }
  }
}

static void process_immimm2reg(uintptr_t src1, uintptr_t src2, int dst, uintptr_t addr, int op) {
  // fprintf(stderr, "%p reg2reg [%d=%s] <= %d=%s\n", (void*)addr, decode_opcode_name(op), dst, num2reg[dst], src, num2reg[src]);
  if (checkTaintMem(src1) == true || checkTaintMem(src2) == true || checkTaintMem(src1 + src2) == true) {
    addTaintReg(dst);
    dr_mutex_lock(mutexL);
    fprintf(trace, "TAINT %p  %s %s, %p, %p ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], (void *)src1, (void *)src2);
    dr_mutex_unlock(mutexL);
  } else {
    if (checkTaintReg(dst) == true) {
      removeTaintReg(dst);
      if (untaint) {
        dr_mutex_lock(mutexL);
        fprintf(trace, "UNTAINT %p  %s %s, %p, %p ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], (void *)src1, (void *)src2);
        dr_mutex_unlock(mutexL);
      } else if (trace_inst) {
        dr_mutex_lock(mutexL);
        fprintf(trace, "COLOUR %p  %s %s, %p, %p ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], (void *)src1, (void *)src2);
        dr_mutex_unlock(mutexL);
      }
    } else if (trace_inst) {
      dr_mutex_lock(mutexL);
      fprintf(trace, "COLOUR %p  %s %s, %p, %p ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], (void *)src1, (void *)src2);
      dr_mutex_unlock(mutexL);
    }
  }
}

static void process_untaint_reg(int dst, uintptr_t addr, int op) {
  if (checkTaintReg(dst) == true) {
    removeTaintReg(dst);
    if (untaint) {
      dr_mutex_lock(mutexL);
      fprintf(trace, "UNTAINT %p  %s %s, %s ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[dst]);
      dr_mutex_unlock(mutexL);
    } else if (trace_inst) {
      dr_mutex_lock(mutexL);
      fprintf(trace, "COLOUR %p  %s %s, %s ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[dst]);
      dr_mutex_unlock(mutexL);
    }
  } else if (trace_inst) {
    dr_mutex_lock(mutexL);
    fprintf(trace, "COLOUR %p  %s %s, %s ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[dst]);
    dr_mutex_unlock(mutexL);
  }
}

static void process_check_taint_reg(int dst, uintptr_t addr, int op) {
  if (checkTaintReg(dst) == true) {
    dr_mutex_lock(mutexL);
    fprintf(trace, "TAINT %p  %s %s ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst]);
    dr_mutex_unlock(mutexL);
  } else if (trace_inst) {
    dr_mutex_lock(mutexL);
    fprintf(trace, "COLOUR %p  %s %s ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst]);
    dr_mutex_unlock(mutexL);
  }
}

static void process_check_taint_mem(uintptr_t dst, uintptr_t addr, int op) {
  if (checkTaintMem(dst) == true) {
    dr_mutex_lock(mutexL);
    fprintf(trace, "TAINT %p  %s %p ;\n", (void *)addr, decode_opcode_name(op), (void *)dst);
    dr_mutex_unlock(mutexL);
  } else if (trace_inst) {
    dr_mutex_lock(mutexL);
    fprintf(trace, "COLOUR %p  %s %p ;\n", (void *)addr, decode_opcode_name(op), (void *)dst);
    dr_mutex_unlock(mutexL);
  }
}

static void process_reg4reg(int src, int dst, uintptr_t addr, int op) {
  // fprintf(stderr, "%p reg4reg [%d=%s] <= %d=%s\n", (void*)addr, decode_opcode_name(op), dst, num4reg[dst], src, num4reg[src]);
  if (checkTaintReg(dst) == true) {
    dr_mutex_lock(mutexL);
    fprintf(trace, "TAINT %p  %s %s, %s ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src]);
    dr_mutex_unlock(mutexL);
    return;
  }
  if (checkTaintReg(src) == true) {
    addTaintReg(dst);
    dr_mutex_lock(mutexL);
    fprintf(trace, "TAINT %p  %s %s, %s ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src]);
    dr_mutex_unlock(mutexL);
  } else if (trace_inst) {
    dr_mutex_lock(mutexL);
    fprintf(trace, "COLOUR %p  %s %s, %s ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src]);
    dr_mutex_unlock(mutexL);
  }
}

static void process_imm4reg(uintptr_t src, int dst, uintptr_t addr, int op) {
  // fprintf(stderr, "%p reg4reg [%d=%s] <= %d=%s\n", (void*)addr, decode_opcode_name(op), dst, num4reg[dst], src, num4reg[src]);
  if (checkTaintReg(dst) == true) {
    dr_mutex_lock(mutexL);
    fprintf(trace, "TAINT %p  %s %s, %p ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], (void *)src);
    dr_mutex_unlock(mutexL);
    return;
  }
  if (checkTaintMem(src) == true) {
    addTaintReg(dst);
    dr_mutex_lock(mutexL);
    fprintf(trace, "TAINT %p  %s %s, %p ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], (void *)src);
    dr_mutex_unlock(mutexL);
  } else if (trace_inst) {
    dr_mutex_lock(mutexL);
    fprintf(trace, "COLOUR %p  %s %s, %p ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], (void *)src);
    dr_mutex_unlock(mutexL);
  }
}

static void process_regreg4reg(int src1, int src2, int dst, uintptr_t addr, int op) {
  // fprintf(stderr, "%p reg2reg [%d=%s] <= %d=%s\n", (void*)addr, decode_opcode_name(op), dst, num2reg[dst], src, num2reg[src]);
  if (checkTaintReg(dst) == true) {
    dr_mutex_lock(mutexL);
    fprintf(trace, "TAINT %p  %s %s, %s, %s ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src1], num2reg[src2]);
    dr_mutex_unlock(mutexL);
    return;
  }
  if (checkTaintReg(src1) == true || checkTaintReg(src2) == true) {
    addTaintReg(dst);
    dr_mutex_lock(mutexL);
    fprintf(trace, "TAINT %p  %s %s, %s, %s ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src1], num2reg[src2]);
    dr_mutex_unlock(mutexL);
  } else if (trace_inst) {
    dr_mutex_lock(mutexL);
    fprintf(trace, "COLOUR %p  %s %s, %s, %s ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src1], num2reg[src2]);
    dr_mutex_unlock(mutexL);
  }
}

static void process_regimm4reg(int src1, uintptr_t src2, int dst, uintptr_t addr, int op) {
  // fprintf(stderr, "%p reg2reg [%d=%s] <= %d=%s\n", (void*)addr, decode_opcode_name(op), dst, num2reg[dst], src, num2reg[src]);
  if (checkTaintReg(dst) == true) {
    dr_mutex_lock(mutexL);
    fprintf(trace, "TAINT %p  %s %s, %s, %p ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src1], (void *)src2);
    dr_mutex_unlock(mutexL);
    return;
  }
  if (checkTaintReg(src1) == true || checkTaintMem(src2) == true) {
    addTaintReg(dst);
    dr_mutex_lock(mutexL);
    fprintf(trace, "TAINT %p  %s %s, %s, %p ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src1], (void *)src2);
    dr_mutex_unlock(mutexL);
  } else if (trace_inst) {
    dr_mutex_lock(mutexL);
    fprintf(trace, "COLOUR %p  %s %s, %s, %p ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], num2reg[src1], (void *)src2);
    dr_mutex_unlock(mutexL);
  }
}

static void process_immimm4reg(uintptr_t src1, uintptr_t src2, int dst, uintptr_t addr, int op) {
  // fprintf(stderr, "%p reg2reg [%d=%s] <= %d=%s\n", (void*)addr, decode_opcode_name(op), dst, num2reg[dst], src, num2reg[src]);
  if (checkTaintMem(src1) == true || checkTaintMem(src2) == true || checkTaintMem(src1 + src2) == true) {
    addTaintReg(dst);
    dr_mutex_lock(mutexL);
    fprintf(trace, "TAINT %p  %s %s, %p, %p ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], (void *)src1, (void *)src2);
    dr_mutex_unlock(mutexL);
  } else {
    if (checkTaintReg(dst) == true) {
      removeTaintReg(dst);
      if (untaint) {
        dr_mutex_lock(mutexL);
        fprintf(trace, "UNTAINT %p  %s %s, %p, %p ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], (void *)src1, (void *)src2);
        dr_mutex_unlock(mutexL);
      } else if (trace_inst) {
        dr_mutex_lock(mutexL);
        fprintf(trace, "COLOUR %p  %s %s, %p, %p ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], (void *)src1, (void *)src2);
        dr_mutex_unlock(mutexL);
      }
    } else if (trace_inst) {
      dr_mutex_lock(mutexL);
      fprintf(trace, "COLOUR %p  %s %s, %p, %p ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst], (void *)src1, (void *)src2);
      dr_mutex_unlock(mutexL);
    }
  }
}

static void process_multiload(void *addr) {
  void *drcontext = dr_get_current_drcontext();
  instr_t *where = instr_create(drcontext);

  decode(drcontext, (byte *)addr, where);
  int size, didtaint = 0, diduntaint = 0, i, opcode = instr_get_opcode(where), type = opcode2dir(opcode);

  dr_mcontext_t mc = {
      sizeof(mc),
      DR_MC_ALL,
  };
  dr_get_mcontext(drcontext, &mc);
  int dstreg, srcreg = opnd_get_base(instr_get_src(where, 0));
  uintptr_t val = getRegValue(&mc, srcreg);

  if (debug) {
    fprintf(stderr, "DEBUG %p ", addr);
    instr_disassemble(drcontext, where, STDERR);
    fprintf(stderr, " ; %d %d - %s %p\n", instr_num_srcs(where), instr_num_dsts(where), num2reg[srcreg], (void *)val);
  }

  switch (opcode) {
  OP_vld1_8:
    size = 1;
    break;
  OP_vld1_16:
    size = 2;
    break;
  OP_vld1_32:
    size = 4;
    break;
  OP_vld1_64:
    size = 8;
    break;
  }
  if (size == 0)
    size = (int)sizeof(uintptr_t);
  else {
    per_thread_t *data = (per_thread_t *)drmgr_get_cls_field(drcontext, tcls_idx);
    if (data->neon == 1) {
      if (problem || debug)
        fprintf(stderr, "PROBLEM %p vld ; more than one load before store\n", (void *)addr);
    } else
      data->neon = 1;
  }

  for (i = 0; i < instr_num_dsts(where); ++i) {
    if (type == IB)
      val += size;
    else if (type == DB)
      val -= size;
    dstreg = opnd_get_reg(instr_get_dst(where, i));
    if (dstreg == srcreg)
      break;
    if (debug)
      fprintf(stderr, " reg %s <= %p\n", num2reg[dstreg], (void *)val);
    if (dstreg != DR_REG_PC && dstreg != DR_REG_LR && dstreg != DR_REG_SP) {
      if (checkTaintMem(val) == true) {
        addTaintReg(dstreg);
        didtaint++;
      } else if (checkTaintReg(dstreg) == true) {
        removeTaintReg(dstreg);
        diduntaint++;
      }
    }
    if (type == IA)
      val += size;
    else if (type == DA)
      val -= size;
  }
  if (didtaint) {
    dr_mutex_lock(mutexL);
    fprintf(trace, "TAINT %p  %s %s!, {%d regs} ;\n", (void *)addr, decode_opcode_name(opcode), num2reg[srcreg], instr_num_dsts(where) - 1);
    dr_mutex_unlock(mutexL);
  } else if (untaint && diduntaint) {
    dr_mutex_lock(mutexL);
    fprintf(trace, "UNTAINT %p  %s %s!, {%d regs} ;\n", (void *)addr, decode_opcode_name(opcode), num2reg[srcreg], instr_num_dsts(where) - 1);
    dr_mutex_unlock(mutexL);
  } else if (trace_inst) {
    dr_mutex_lock(mutexL);
    fprintf(trace, "COLOUR %p  %s %s!, {%d regs} ;\n", (void *)addr, decode_opcode_name(opcode), num2reg[srcreg], instr_num_dsts(where) - 1);
    dr_mutex_unlock(mutexL);
    dr_mutex_unlock(mutexL);
  }
  instr_destroy(drcontext, where);
}

static void process_multistore(void *addr) {
  void *drcontext = dr_get_current_drcontext();
  instr_t *where = instr_create(drcontext);

  decode(drcontext, (byte *)addr, where);
  int size, didtaint = 0, diduntaint = 0, i, opcode = instr_get_opcode(where), type = opcode2dir(opcode);

  dr_mcontext_t mc = {
      sizeof(mc),
      DR_MC_ALL,
  };
  dr_get_mcontext(drcontext, &mc);
  int srcreg, dstreg = opnd_get_base(instr_get_dst(where, 0));
  uintptr_t val = getRegValue(&mc, dstreg);

  if (debug) {
    fprintf(stderr, "DEBUG %p ", addr);
    instr_disassemble(drcontext, where, STDERR);
    fprintf(stderr, " ; %d %d - %s %p\n", instr_num_srcs(where), instr_num_dsts(where), num2reg[dstreg], (void *)val);
  }

  switch (opcode) {
  OP_vst1_8:
    size = 1;
    break;
  OP_vst1_16:
    size = 2;
    break;
  OP_vst1_32:
    size = 4;
    break;
  OP_vst1_64:
    size = 8;
    break;
  }
  if (size == 0)
    size = (int)sizeof(uintptr_t);
  else {
    per_thread_t *data = (per_thread_t *)drmgr_get_cls_field(drcontext, tcls_idx);
    data->neon = 0;
  }

  for (i = 0; i < instr_num_srcs(where); ++i) {
    if (type == IB)
      val += size;
    else if (type == DB)
      val -= size;
    srcreg = opnd_get_reg(instr_get_src(where, i));
    if (dstreg == srcreg)
      break;
    if (debug)
      fprintf(stderr, " reg %s => %p\n", num2reg[srcreg], (void *)val);
    if (dstreg != DR_REG_PC && dstreg != DR_REG_LR && dstreg != DR_REG_SP) {
      if (checkTaintReg(srcreg) == true) {
        addTaintMem(val);
        didtaint++;
      } else if (checkTaintMem(val) == true) {
        removeTaintMem(val);
        diduntaint++;
      }
    }
    if (type == IA)
      val += size;
    else if (type == DA)
      val -= size;
  }
  if (didtaint) {
    dr_mutex_lock(mutexL);
    fprintf(trace, "TAINT %p  %s %s!, {%d regs} ;\n", (void *)addr, decode_opcode_name(opcode), num2reg[srcreg], instr_num_dsts(where) - 1);
    dr_mutex_unlock(mutexL);
  } else if (untaint && diduntaint) {
    dr_mutex_lock(mutexL);
    fprintf(trace, "UNTAINT %p  %s %s!, {%d regs} ;\n", (void *)addr, decode_opcode_name(opcode), num2reg[srcreg], instr_num_dsts(where) - 1);
    dr_mutex_unlock(mutexL);
  } else if (trace_inst) {
    dr_mutex_lock(mutexL);
    fprintf(trace, "COLOUR %p  %s %s!, {%d regs} ;\n", (void *)addr, decode_opcode_name(opcode), num2reg[srcreg], instr_num_dsts(where) - 1);
    dr_mutex_unlock(mutexL);
  }
  instr_destroy(drcontext, where);
}

static void process_trace_inst(void *addr) {
  void *drcontext = dr_get_current_drcontext();
  instr_t *where = instr_create(drcontext);

  decode(drcontext, (byte *)addr, where);
  char buf[64];

  instr_disassemble_to_buffer(drcontext, where, buf, sizeof(buf));
  dr_mutex_lock(mutexL);
  fprintf(trace, "COLOUR %p %s ; %d %d\n", addr, buf, instr_num_srcs(where), instr_num_dsts(where));
  dr_mutex_unlock(mutexL);
}

static void process_indirect(int dst, uintptr_t addr, int op) {
  if (checkTaintReg(dst) == true) {
    dr_mutex_lock(mutexL);
    fprintf(trace, "TAINT %p  %s %s ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst]);
    dr_mutex_unlock(mutexL);
  } else if (trace_inst) {
    dr_mutex_lock(mutexL);
    fprintf(trace, "COLOUR %p  %s %s ;\n", (void *)addr, decode_opcode_name(op), num2reg[dst]);
    dr_mutex_unlock(mutexL);
  }
  if (indirect) {
    dr_mcontext_t mc = {sizeof(mc), DR_MC_ALL};
    size_t val;

    dr_get_mcontext(dr_get_current_drcontext(), &mc);
    val = getRegValue(&mc, dst);
    if ((val & 1) == 1) {
      dr_mutex_lock(mutexL);
      fprintf(trace, "INDIRECT call/jmp from %p to %p ; %s %s THUMB\n", (void *)addr, (void *)(val & (~(uintptr_t)1)), decode_opcode_name(op), num2reg[dst]);
      dr_mutex_unlock(mutexL);
    } else {
      dr_mutex_lock(mutexL);
      fprintf(trace, "INDIRECT call/jmp from %p to %p ; %s %s\n", (void *)addr, (void *)val, decode_opcode_name(op), num2reg[dst]);
      dr_mutex_unlock(mutexL);
    }
  }
}

// ***************************************************************

static void debug_dump_opnds(instr_t *where) {
  int i;
  opnd_t o;

  fprintf(stderr, "sources: %d\n", instr_num_srcs(where));
  if (instr_num_srcs(where) > 0)
    for (i = 0; i < instr_num_srcs(where); i++) {
      o = instr_get_src(where, i);
      fprintf(stderr, " %d is_reg:%d is_absaddr:%d is_base:%d is_disp_enc0:%d is_disp_force:%d is_disp_short:%d is_reladdr:%d is_inst:%d is_memref:%d is_pc:%d is_imm:%d is_float:%d is_null:%d is_vsib:%d\n", i, opnd_is_reg(o), opnd_is_abs_addr(o), opnd_is_base_disp(o), opnd_is_disp_encode_zero(o), opnd_is_disp_force_full(o), opnd_is_disp_short_addr(o), opnd_is_rel_addr(o), opnd_is_instr(o), opnd_is_memory_reference(o), opnd_is_pc(o), opnd_is_immed(o), opnd_is_immed_float(o), opnd_is_null(o),
              opnd_is_mem_instr(o));
      fprintf(stderr, " => %s ", (opnd_is_reg(o) == true ? num2reg[opnd_get_reg(o)] : (opnd_is_base_disp(o) == true ? num2reg[opnd_get_base(o)] : "unknown")));
      fprintf(stderr, "getaddr %p, ", opnd_get_addr(o));
      fprintf(stderr, "getbase %u, ", opnd_get_base(o));
      fprintf(stderr, "getdisp %x, ", opnd_get_disp(o));
      fprintf(stderr, "getimm %p, ", (void *)opnd_get_immed_int(o));
      fprintf(stderr, "getindex %x, ", opnd_get_index(o));
      fprintf(stderr, "getreg %u, ", opnd_get_reg(o));
      fprintf(stderr, "regscale %d, ", opnd_get_scale(o));
      fprintf(stderr, "getseg %u, ", opnd_get_segment(o));
      fprintf(stderr, "getdiscpl %d, ", opnd_get_mem_instr_disp(o));
      fprintf(stderr, "getpc %p, ", opnd_get_pc(o));
      fprintf(stderr, "\n");
    }
  fprintf(stderr, "destinations: %d\n", instr_num_dsts(where));
  if (instr_num_dsts(where) > 0)
    for (i = 0; i < instr_num_dsts(where); i++) {
      o = instr_get_dst(where, i);
      fprintf(stderr, " %d is_reg:%d is_absaddr:%d is_base:%d is_disp_enc0:%d is_disp_force:%d is_disp_short:%d is_reladdr:%d is_inst:%d is_memref:%d is_pc:%d is_imm:%d is_float:%d is_null:%d is_vsib:%d\n", i, opnd_is_reg(o), opnd_is_abs_addr(o), opnd_is_base_disp(o), opnd_is_disp_encode_zero(o), opnd_is_disp_force_full(o), opnd_is_disp_short_addr(o), opnd_is_rel_addr(o), opnd_is_instr(o), opnd_is_memory_reference(o), opnd_is_pc(o), opnd_is_immed(o), opnd_is_immed_float(o), opnd_is_null(o),
              opnd_is_mem_instr(o));
      fprintf(stderr, " => %s ", (opnd_is_reg(o) == true ? num2reg[opnd_get_reg(o)] : (opnd_is_base_disp(o) == true ? num2reg[opnd_get_base(o)] : "unknown")));
      fprintf(stderr, "getaddr %p, ", opnd_get_addr(o));
      fprintf(stderr, "getbase %u, ", opnd_get_base(o));
      fprintf(stderr, "getdisp 0x%x, ", opnd_get_disp(o));
      fprintf(stderr, "getimm 0x" _MYS ", ", opnd_get_immed_int(o));
      fprintf(stderr, "getindex %u, ", opnd_get_index(o));
      fprintf(stderr, "getreg %u, ", opnd_get_reg(o));
      fprintf(stderr, "regscale %d, ", opnd_get_scale(o));
      fprintf(stderr, "getseg %u, ", opnd_get_segment(o));
      fprintf(stderr, "getdiscpl %d, ", opnd_get_mem_instr_disp(o));
      fprintf(stderr, "getpc %p, ", opnd_get_pc(o));
      fprintf(stderr, "\n");
    }
}

static void handle_multistore(void *drcontext, void *tag, instrlist_t *ilist, instr_t *where) {
  opnd_t addr = OPND_CREATE_INTPTR(instr_get_app_pc(where));
  dr_insert_clean_call(drcontext, ilist, where, (void *)process_multistore, false, 1, addr);
}

static void handle_multiload(void *drcontext, void *tag, instrlist_t *ilist, instr_t *where) {
  opnd_t addr = OPND_CREATE_INTPTR(instr_get_app_pc(where));
  dr_insert_clean_call(drcontext, ilist, where, (void *)process_multiload, false, 1, addr);
}

static void handle_load(void *drcontext, void *tag, instrlist_t *ilist, instr_t *where) {
  int dstreg = opnd_get_reg(instr_get_dst(where, 0));

  if (dstreg == DR_REG_LR) // otherwise dynamorio can end up in an endless loop :(
    return;
  opnd_t dst = OPND_CREATE_INT32(dstreg);
  opnd_t mem1 = instr_get_src(where, 0);
  opnd_t src = OPND_CREATE_INT32(opnd_get_base(mem1));
  opnd_t imm;

  if (instr_num_srcs(where) == 1 || opnd_get_immed_int(mem1) != 0)
    imm = OPND_CREATE_INTPTR(0);
  else
    imm = OPND_CREATE_INTPTR(opnd_get_immed_int(instr_get_src(where, 1)));
  opnd_t addr = OPND_CREATE_INTPTR(instr_get_app_pc(where));

  if (debug) {
    fprintf(stderr, "DEBUG %p ", instr_get_app_pc(where));
    instr_disassemble(drcontext, where, STDERR);
    fprintf(stderr, " ; %d %d\n", instr_num_srcs(where), instr_num_dsts(where));
    if (instr_num_srcs(where) != 1 || instr_num_dsts(where) != 1)
      debug_dump_opnds(where);
  }
  auto sreg1 = drreg_reservation{ilist, where};
  auto sapp2 = drreg_reservation{ilist, where};
  drutil_insert_get_mem_addr(drcontext, ilist, where, mem1, sapp2, sreg1);
  opnd_t mem = OPND_CREATE_INT32(sapp2);
  int opcode = instr_get_opcode(where);
  opnd_t op = OPND_CREATE_INT32(opcode);

  switch (opcode) {
  OP_ldrd : {
    opnd_t dst2 = OPND_CREATE_INT32(opnd_get_reg(instr_get_dst(where, 1)));

    dr_insert_clean_call(drcontext, ilist, where, (void *)process_regptr2regreg, false, 6, src, dst, dst2, mem, addr, op);
    break;
  }
    //    OP_ldrex: {
    //      break;
    //    }
  default:
    dr_insert_clean_call(drcontext, ilist, where, (void *)process_regptr2reg, false, 6, src, dst, mem, imm, addr, op);
  }
}

static void handle_store(void *drcontext, void *tag, instrlist_t *ilist, instr_t *where) {
  int srcreg = opnd_get_reg(instr_get_src(where, 0));

  if (srcreg == DR_REG_LR) // otherwise dynamorio can end up in an endless loop :(
    return;
  opnd_t src = OPND_CREATE_INT32(srcreg);
  opnd_t mem1 = instr_get_dst(where, 0);
  opnd_t dst = OPND_CREATE_INT32(opnd_get_base(mem1));
  opnd_t addr = OPND_CREATE_INTPTR(instr_get_app_pc(where));

  if (debug) {
    fprintf(stderr, "DEBUG %p ", instr_get_app_pc(where));
    instr_disassemble(drcontext, where, STDERR);
    fprintf(stderr, " ; %d %d\n", instr_num_srcs(where), instr_num_dsts(where));
    debug_dump_opnds(where);
  }
  auto sreg1 = drreg_reservation{ilist, where};
  auto sapp2 = drreg_reservation{ilist, where};
  drutil_insert_get_mem_addr(drcontext, ilist, where, mem1, sapp2, sreg1);
  opnd_t mem = OPND_CREATE_INT32(sapp2);
  int opcode = instr_get_opcode(where);
  opnd_t op = OPND_CREATE_INT32(opcode);

  switch (opcode) {
#ifdef AARCHXX
  case OP_strd: {
    opnd_t src2 = OPND_CREATE_INT32(opnd_get_reg(instr_get_src(where, 1)));

    dr_insert_clean_call(drcontext, ilist, where, (void *)process_regreg2regptr, false, 6, src, src2, dst, mem, addr, op);
    break;
  }
  case OP_strex: {
    if (workaround) {
      dr_insert_clean_call(drcontext, ilist, instr_get_next(where), (void *)process_reg2regptr, false, 5, src, dst, mem, addr, op);
    } else if (problem) {
      char buf[256];
      dr_mutex_lock(mutexL);
      instr_disassemble_to_buffer(drcontext, where, buf, sizeof(buf));
      fprintf(trace, "PROBLEM %p %s ; can not handle strex as dynamorio sometimes endlessly loops. you can try -workaround\n", instr_get_app_pc(where), buf);
      dr_mutex_unlock(mutexL);
    }
    return; // TODO BUGME FIX
  }         // fall through
#endif
  default:
    dr_insert_clean_call(drcontext, ilist, where, (void *)process_reg2regptr, false, 5, src, dst, mem, addr, op);
  }
}

static void handle_indirect(void *drcontext, void *tag, instrlist_t *ilist, instr_t *where) {
  if (debug) {
    fprintf(stderr, "DEBUG %p ", instr_get_app_pc(where));
    instr_disassemble(drcontext, where, STDERR);
    fprintf(stderr, " ; %d %d\n", instr_num_srcs(where), instr_num_dsts(where));
    if (instr_num_srcs(where) != 1 || instr_num_dsts(where) != 0)
      debug_dump_opnds(where);
  }
  int srcreg = opnd_get_reg(instr_get_src(where, 0));
  if (srcreg == DR_REG_LR || srcreg == DR_REG_PC)
    return;
  opnd_t op = OPND_CREATE_INT32(instr_get_opcode(where));
  opnd_t src = OPND_CREATE_INT32(srcreg);
  opnd_t addr = OPND_CREATE_INTPTR(instr_get_app_pc(where));
  // fprintf(stderr, "XXX %d %d %p\n", instr_get_opcode(where), srcreg, instr_get_app_pc(where));

  dr_insert_clean_call(drcontext, ilist, where, (void *)process_indirect, false, 3, src, addr, op);
}

static void handle_mov(void *drcontext, void *tag, instrlist_t *ilist, instr_t *where) {
  if (debug) {
    fprintf(stderr, "DEBUG %p ", instr_get_app_pc(where));
    instr_disassemble(drcontext, where, STDERR);
    fprintf(stderr, " ; %d %d\n", instr_num_srcs(where), instr_num_dsts(where));
    if (instr_num_srcs(where) != 1 || instr_num_dsts(where) != 1)
      debug_dump_opnds(where);
  }
  if (instr_num_dsts(where) == 0 || instr_num_srcs(where) == 0)
    return;
  int regsrc[4] = {0, 0, 0, 0}, srcno = 0, i, memreg = 0, memoff = 0;
  int regdst[3] = {0, 0, 0}, immsrc[3] = {0, 0, 0}, dstno = 0, immno = 0;
  for (i = 0; i < instr_num_srcs(where); i++) {
    if (opnd_is_memory_reference(instr_get_src(where, i)) == true) {
      DR_ASSERT_MSG(memreg == 0, "two mem refs");
      memreg = opnd_get_reg(instr_get_src(where, i));
      memoff = opnd_get_immed_int(instr_get_src(where, i));
      // i++;
    }
    if (opnd_is_reg(instr_get_src(where, i)) == true)
      regsrc[srcno++] = opnd_get_reg(instr_get_src(where, i));
    else if (opnd_is_immed(instr_get_src(where, i)) == true) {
      immsrc[immno] = opnd_get_immed_int(instr_get_src(where, i));
      if (immsrc[immno] >= 0x1000)
        immno++;
    } else {
      fprintf(stderr, "Error: no reg not imm: src %d\n", i);
      DR_ASSERT(false);
    }
  }
  if (srcno = 0 && immno == 0)
    return;
  DR_ASSERT_MSG(memreg == 0, "memref not handled");
  DR_ASSERT_MSG(srcno < 4, "too many src");
  DR_ASSERT_MSG(immno < 2, "too many imm");
  for (i = 0; i < instr_num_dsts(where); i++) {
    if (opnd_is_reg(instr_get_dst(where, i)) == true)
      regdst[dstno++] = opnd_get_reg(instr_get_dst(where, i));
    else {
      fprintf(stderr, "Error: no reg in dst: src %d\n", i);
      DR_ASSERT(false);
    }
  }
  if (dstno == 1 && srcno == 1 && immno == 0 && regsrc[0] == regdst[0]) {
    if (debug)
      fprintf(stderr, "DEBUG: skipping function that only has src same as dst\n");
    return;
  }
  DR_ASSERT_MSG(dstno < 3, "too many dst");
  opnd_t op = OPND_CREATE_INT32(instr_get_opcode(where));
  opnd_t addr = OPND_CREATE_INTPTR(instr_get_app_pc(where));
  opnd_t dst1 = OPND_CREATE_INT32(regdst[0]);

  if (dstno == 2) {
    opnd_t src1 = OPND_CREATE_INT32(regsrc[0]);
    opnd_t dst2 = OPND_CREATE_INT32(regdst[1]);

    if (immno && immsrc[0] >= 0x1000) {
      opnd_t imm = OPND_CREATE_INTPTR(immsrc[0]);
      dr_insert_clean_call(drcontext, ilist, where, (void *)process_regimm2regreg, false, 6, src1, imm, dst1, dst2, addr, op);
    } else {
      opnd_t src2 = OPND_CREATE_INT32(regsrc[1]);
      dr_insert_clean_call(drcontext, ilist, where, (void *)process_regreg2regreg, false, 6, src1, src2, dst1, dst2, addr, op);
    }
  } else {
    if (immno == 0) {
      opnd_t src1 = OPND_CREATE_INT32(regsrc[0]);
      if (srcno == 1) {
        dr_insert_clean_call(drcontext, ilist, where, (void *)process_reg2reg, false, 4, src1, dst1, addr, op);
        return;
      }
      opnd_t src2 = OPND_CREATE_INT32(regsrc[1]);
      if (srcno == 2) {
        dr_insert_clean_call(drcontext, ilist, where, (void *)process_reg2reg, false, 5, src1, src2, dst1, addr, op);
        return;
      }
      opnd_t src3 = OPND_CREATE_INT32(regsrc[2]);
      dr_insert_clean_call(drcontext, ilist, where, (void *)process_regregreg2reg, false, 6, src1, src2, src3, dst1, addr, op);
    } else {
      opnd_t imm = OPND_CREATE_INTPTR(immsrc[0]);
      if (srcno == 0) {
        dr_insert_clean_call(drcontext, ilist, where, (void *)process_imm2reg, false, 4, imm, dst1, addr, op);
        return;
      }
      opnd_t src1 = OPND_CREATE_INT32(regsrc[0]);
      if (srcno == 1) {
        dr_insert_clean_call(drcontext, ilist, where, (void *)process_regimm2reg, false, 5, src1, imm, dst1, addr, op);
        return;
      }
      opnd_t src2 = OPND_CREATE_INT32(regsrc[1]);
      DR_ASSERT_MSG(srcno == 2, "too many src with 1 imm");
      dr_insert_clean_call(drcontext, ilist, where, (void *)process_regregimm2reg, false, 6, src1, src2, imm, dst1, addr, op);
    }
  }
}

static void handle_push(void *drcontext, void *tag, instrlist_t *ilist, instr_t *where) {
  if (debug) {
    fprintf(stderr, "DEBUG %p ", instr_get_app_pc(where));
    instr_disassemble(drcontext, where, STDERR);
    fprintf(stderr, " ; %d %d\n", instr_num_srcs(where), instr_num_dsts(where));
  }
  if (opnd_is_reg(instr_get_src(where, 0)) == true) {
    int srcreg = opnd_get_reg(instr_get_src(where, 0));

    if (srcreg != DR_REG_LR) {
      opnd_t src = OPND_CREATE_INT32(srcreg);
      opnd_t op = OPND_CREATE_INT32(instr_get_opcode(where));
      opnd_t addr = OPND_CREATE_INTPTR(instr_get_app_pc(where));

      dr_insert_clean_call(drcontext, ilist, where, (void *)process_push_reg, false, 3, src, addr, op);
    }
  } else {
    uintptr_t srcimm = opnd_get_immed_int(instr_get_src(where, 0));

    if (srcimm < 0x1000)
      return;
    opnd_t imm = OPND_CREATE_INTPTR(srcimm);
    opnd_t op = OPND_CREATE_INT32(instr_get_opcode(where));
    opnd_t addr = OPND_CREATE_INTPTR(instr_get_app_pc(where));

    dr_insert_clean_call(drcontext, ilist, where, (void *)process_push_imm, false, 3, imm, addr, op);
  }
}

static void handle_pop(void *drcontext, void *tag, instrlist_t *ilist, instr_t *where) {
  if (debug) {
    fprintf(stderr, "DEBUG %p ", instr_get_app_pc(where));
    instr_disassemble(drcontext, where, STDERR);
    fprintf(stderr, " ; %d %d\n", instr_num_srcs(where), instr_num_dsts(where));
  }
  int dstreg = opnd_get_reg(instr_get_dst(where, 0));

  if (dstreg != DR_REG_LR) {
    opnd_t dst = OPND_CREATE_INT32(dstreg);
    opnd_t op = OPND_CREATE_INT32(instr_get_opcode(where));
    opnd_t addr = OPND_CREATE_INTPTR(instr_get_app_pc(where));

    dr_insert_clean_call(drcontext, ilist, where, (void *)process_push_reg, false, 3, dst, addr, op);
  }
}

static void my_debug(void *drcontext, void *tag, instr_t *where) {
  fprintf(stderr, "DEBUG %p ", instr_get_app_pc(where));
  instr_disassemble(drcontext, where, STDERR);
  fprintf(stderr, " ; %d %d\n", instr_num_srcs(where), instr_num_dsts(where));
  debug_dump_opnds(where);
}

/*
event_app_instruction(void *drcontext, void *tag, instrlist_t *ilist, instr_t *where, ... {
  ...
    if (instr_is_simd(where)) {
        unimplemented_opcode(where);
        return DR_EMIT_DEFAULT;
    }

    if (instr_handle_constant_func(drcontext, tag, ilist, where))
        return DR_EMIT_DEFAULT;

    // We define a routine to make it easier to call drreg_restore_app_value() in
    // the case that we have to swap a register out to make space for the stolen reg
*/

/*
 event_post_syscall(void *drcontext, int sysnum) {
  ...
    // clear taint for system calls with an OUT memarg param
    if (drsys_iterate_memargs(drcontext, drsys_iter_cb, drcontext) !=
        DRMF_SUCCESS)
        DR_ASSERT(false);
}
*/
