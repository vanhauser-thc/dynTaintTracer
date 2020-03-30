// ********* we start here *********** //

/*
    case OP_push:
        handle_push(drcontext, tag, ilist, where);
        break;

    case OP_pop:
        handle_pop(drcontext, tag, ilist, where);
        break;
*/

case OP_vld1_16:
case OP_vld1_32:
case OP_vld1_64:
case OP_vld1_8:
case OP_ldmia:
case OP_ldmdb:
case OP_ldmib:
case OP_ldmda:
DRREG_RESTORE_APP_VALUE(drcontext, ilist, where, instr_get_src(where, 0), { dr_insert_clean_call(drcontext, ilist, where, (void *)process_multiload, false, 1, OPND_CREATE_INTPTR(instr_get_app_pc(where))); });

break;

case OP_vst1_16:
case OP_vst1_32:
case OP_vst1_64:
case OP_vst1_8:
case OP_stmia:
case OP_stmdb:
case OP_stmib:
case OP_stmda:
DRREG_RESTORE_APP_VALUE(drcontext, ilist, where, instr_get_dst(where, 0), { dr_insert_clean_call(drcontext, ilist, where, (void *)process_multistore, false, 1, OPND_CREATE_INTPTR(instr_get_app_pc(where))); });

break;

case OP_vldr:
case OP_ldr:
case OP_ldrb:
case OP_ldrd:
case OP_ldrh:
case OP_ldrsh:
case OP_ldrsb:
case OP_ldrex: {
  handle_load(drcontext, tag, ilist, where);
  break;
}

case OP_vstr:
case OP_str:
case OP_strb:
case OP_strd:
case OP_strh:
case OP_strex: {
  handle_store(drcontext, tag, ilist, where);
  break;
}

case OP_mov:
case OP_mvn:
case OP_mvns:
case OP_movw:
case OP_movt:
case OP_movs:
case OP_rrx:
case OP_rrxs: {
  handle_mov(drcontext, tag, ilist, where);
  break;
}

case OP_sbfx:
case OP_ubfx:
case OP_uxtb:
case OP_uxth:
case OP_sxtb:
case OP_sxth:
case OP_rev:
case OP_rev16: {
  // These aren't mov's per se, but they only accept 1 source and 1 reg dest
  handle_mov(drcontext, tag, ilist, where);
  break;
}

case OP_sel:
case OP_clz: {
  // These aren't mov's per se, but they only accept 1 reg source and 1 dest
  // if (opnd_is_reg(instr_get_src(where, 0)))
  handle_mov(drcontext, tag, ilist, where);
  break;
}

case OP_adc:
case OP_adcs:
case OP_add:
case OP_adds:
case OP_addw:
case OP_rsb:
case OP_rsbs:
case OP_rsc:
case OP_sbc:
case OP_sbcs:
case OP_sub:
case OP_subw:
case OP_subs:
case OP_and:
case OP_ands:
case OP_bic:
case OP_bics:
case OP_eor:
case OP_eors:
case OP_mul:
case OP_muls:
case OP_orr:
case OP_ror:
case OP_orrs:
case OP_lsl:
case OP_lsls:
case OP_lsr:
case OP_lsrs:
case OP_asr:
case OP_asrs:
case OP_orn:
case OP_uadd8:
case OP_uqsub8: {
  // Some of these also write to eflags. If we taint eflags we should do it here.
  // BUG FIXME TODO
  handle_mov(drcontext, tag, ilist, where);
  break;
}

case OP_smull:
case OP_umull:
handle_mov(drcontext, tag, ilist, where);
// handle_umull(drcontext, tag, ilist, where);
break;

case OP_mla:
case OP_mls:
handle_mov(drcontext, tag, ilist, where);
// handle_mla(drcontext, tag, ilist, where);
break;

case OP_bl:
case OP_blx:
case OP_blx_ind:
case OP_bxj:
case OP_bx:
case OP_b:
case OP_b_short: {
  /* could have register destination */
  if (opnd_is_reg(instr_get_src(where, 0))) {
    handle_indirect(drcontext, tag, ilist, where);
  } else if (trace_inst) {
    dr_insert_clean_call(drcontext, ilist, where, (void *)process_trace_inst, false, 1, OPND_CREATE_INTPTR(instr_get_app_pc(where)));
  }
  break;
}

case OP_cbz:
case OP_cbnz:
// same same?
case OP_cmn:
case OP_cmp:
case OP_tst:
case OP_it: {
  // TODO FIXME BUG: handle eflags
  if (trace_inst)
    dr_insert_clean_call(drcontext, ilist, where, (void *)process_trace_inst, false, 1, OPND_CREATE_INTPTR(instr_get_app_pc(where)));
  break;
}

case OP_LABEL:
case OP_svc:
case OP_ldc:
case OP_mcr:
case OP_mrc:
case OP_nop:
case OP_pld:
case OP_dmb: {
  if (trace_inst)
    dr_insert_clean_call(drcontext, ilist, where, (void *)process_trace_inst, false, 1, OPND_CREATE_INTPTR(instr_get_app_pc(where)));
  break;
}

case OP_bfi:
case OP_bfc:
case OP_teq: {
  if (trace_inst)
    dr_insert_clean_call(drcontext, ilist, where, (void *)process_trace_inst, false, 1, OPND_CREATE_INTPTR(instr_get_app_pc(where)));
  break;
}
