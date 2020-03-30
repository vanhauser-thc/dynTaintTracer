#ifdef X86
case DR_REG_RAX:
case DR_REG_EAX:
if (data->regsTainted[DR_REG_EAX] == 1)
  return true;
case DR_REG_AX: {
  if (data->regsTainted[DR_REG_AX] == 1)
    return true;
  if (data->regsTainted[DR_REG_AH] == 1)
    return true;
  if (data->regsTainted[DR_REG_AL] == 1)
    return true;
  break;
}
case DR_REG_AH:
if (data->regsTainted[DR_REG_AH] == 1)
  return true;
break;
case DR_REG_AL:
if (data->regsTainted[DR_REG_AH] == 1)
  return true;
break;
case DR_REG_RBX:
case DR_REG_EBX:
if (data->regsTainted[DR_REG_EBX] == 1)
  return true;
case DR_REG_BX: {
  if (data->regsTainted[DR_REG_BX] == 1)
    return true;
  if (data->regsTainted[DR_REG_BH] == 1)
    return true;
  if (data->regsTainted[DR_REG_BL] == 1)
    return true;
  break;
}
case DR_REG_BH:
if (data->regsTainted[DR_REG_BH] == 1)
  return true;
break;
case DR_REG_BL:
if (data->regsTainted[DR_REG_BH] == 1)
  return true;
break;
case DR_REG_RCX:
case DR_REG_ECX:
if (data->regsTainted[DR_REG_ECX] == 1)
  return true;
case DR_REG_CX: {
  if (data->regsTainted[DR_REG_CX] == 1)
    return true;
  if (data->regsTainted[DR_REG_CH] == 1)
    return true;
  if (data->regsTainted[DR_REG_CL] == 1)
    return true;
  break;
}
case DR_REG_CH:
if (data->regsTainted[DR_REG_CH] == 1)
  return true;
break;
case DR_REG_CL:
if (data->regsTainted[DR_REG_CH] == 1)
  return true;
break;
case DR_REG_RDX:
case DR_REG_EDX:
if (data->regsTainted[DR_REG_EDX] == 1)
  return true;
case DR_REG_DX: {
  if (data->regsTainted[DR_REG_DX] == 1)
    return true;
  if (data->regsTainted[DR_REG_DH] == 1)
    return true;
  if (data->regsTainted[DR_REG_DL] == 1)
    return true;
  break;
}
case DR_REG_DH:
if (data->regsTainted[DR_REG_DH] == 1)
  return true;
break;
case DR_REG_DL:
if (data->regsTainted[DR_REG_DH] == 1)
  return true;
break;
case DR_REG_RBP:
case DR_REG_EBP:
if (data->regsTainted[DR_REG_EBP] == 1)
  return true;
case DR_REG_BP:
if (data->regsTainted[DR_REG_BP] == 1)
  return true;
case DR_REG_BPL:
if (data->regsTainted[DR_REG_BPL] == 1)
  return true;
break;
case DR_REG_RDI:
case DR_REG_EDI:
if (data->regsTainted[DR_REG_EDI] == 1)
  return true;
case DR_REG_DI:
if (data->regsTainted[DR_REG_DI] == 1)
  return true;
case DR_REG_DIL:
if (data->regsTainted[DR_REG_DIL] == 1)
  return true;
break;
case DR_REG_RSI:
case DR_REG_ESI:
if (data->regsTainted[DR_REG_ESI] == 1)
  return true;
case DR_REG_SI:
if (data->regsTainted[DR_REG_SI] == 1)
  return true;
case DR_REG_SIL:
if (data->regsTainted[DR_REG_SIL] == 1)
  return true;
break;
case DR_REG_R8:
case DR_REG_R8D:
if (data->regsTainted[DR_REG_R8D] == 1)
  return true;
case DR_REG_R8W:
if (data->regsTainted[DR_REG_R8W] == 1)
  return true;
case DR_REG_R8L:
if (data->regsTainted[DR_REG_R8L] == 1)
  return true;
break;
case DR_REG_R9:
case DR_REG_R9D:
if (data->regsTainted[DR_REG_R9D] == 1)
  return true;
case DR_REG_R9W:
if (data->regsTainted[DR_REG_R9W] == 1)
  return true;
case DR_REG_R9L:
if (data->regsTainted[DR_REG_R9L] == 1)
  return true;
break;
case DR_REG_R10:
case DR_REG_R10D:
if (data->regsTainted[DR_REG_R10D] == 1)
  return true;
case DR_REG_R10W:
if (data->regsTainted[DR_REG_R10W] == 1)
  return true;
case DR_REG_R10L:
if (data->regsTainted[DR_REG_R10L] == 1)
  return true;
break;
case DR_REG_R11:
case DR_REG_R11D:
if (data->regsTainted[DR_REG_R11D] == 1)
  return true;
case DR_REG_R11W:
if (data->regsTainted[DR_REG_R11W] == 1)
  return true;
case DR_REG_R11L:
if (data->regsTainted[DR_REG_R11L] == 1)
  return true;
break;
case DR_REG_R12:
case DR_REG_R12D:
if (data->regsTainted[DR_REG_R12D] == 1)
  return true;
case DR_REG_R12W:
if (data->regsTainted[DR_REG_R12W] == 1)
  return true;
case DR_REG_R12L:
if (data->regsTainted[DR_REG_R12L] == 1)
  return true;
break;
case DR_REG_R13:
case DR_REG_R13D:
if (data->regsTainted[DR_REG_R13D] == 1)
  return true;
case DR_REG_R13W:
if (data->regsTainted[DR_REG_R13W] == 1)
  return true;
case DR_REG_R13L:
if (data->regsTainted[DR_REG_R13L] == 1)
  return true;
break;
case DR_REG_R14:
case DR_REG_R14D:
if (data->regsTainted[DR_REG_R14D] == 1)
  return true;
case DR_REG_R14W:
if (data->regsTainted[DR_REG_R14W] == 1)
  return true;
case DR_REG_R14L:
if (data->regsTainted[DR_REG_R14L] == 1)
  return true;
break;
case DR_REG_R15:
case DR_REG_R15D:
if (data->regsTainted[DR_REG_R15D] == 1)
  return true;
case DR_REG_R15W:
if (data->regsTainted[DR_REG_R15W] == 1)
  return true;
case DR_REG_R15L:
if (data->regsTainted[DR_REG_R15L] == 1)
  return true;
break;
case DR_REG_XMM0:
if (data->regsTainted[DR_REG_XMM0] == 1)
  return true;
break;
case DR_REG_XMM1:
if (data->regsTainted[DR_REG_XMM1] == 1)
  return true;
break;
case DR_REG_XMM2:
if (data->regsTainted[DR_REG_XMM2] == 1)
  return true;
break;
case DR_REG_XMM3:
if (data->regsTainted[DR_REG_XMM3] == 1)
  return true;
break;
case DR_REG_XMM4:
if (data->regsTainted[DR_REG_XMM4] == 1)
  return true;
break;
case DR_REG_XMM5:
if (data->regsTainted[DR_REG_XMM5] == 1)
  return true;
break;
case DR_REG_XMM6:
if (data->regsTainted[DR_REG_XMM6] == 1)
  return true;
break;
case DR_REG_XMM7:
if (data->regsTainted[DR_REG_XMM7] == 1)
  return true;
break;
case DR_REG_XMM8:
if (data->regsTainted[DR_REG_XMM8] == 1)
  return true;
break;
case DR_REG_XMM9:
if (data->regsTainted[DR_REG_XMM9] == 1)
  return true;
break;
case DR_REG_XMM10:
if (data->regsTainted[DR_REG_XMM10] == 1)
  return true;
break;
case DR_REG_XMM11:
if (data->regsTainted[DR_REG_XMM11] == 1)
  return true;
break;
case DR_REG_XMM12:
if (data->regsTainted[DR_REG_XMM12] == 1)
  return true;
break;
case DR_REG_XMM13:
if (data->regsTainted[DR_REG_XMM13] == 1)
  return true;
break;
case DR_REG_XMM14:
if (data->regsTainted[DR_REG_XMM14] == 1)
  return true;
break;
case DR_REG_XMM15:
if (data->regsTainted[DR_REG_XMM15] == 1)
  return true;
break;
case DR_REG_YMM0:
if (data->regsTainted[DR_REG_YMM0] == 1)
  return true;
break;
case DR_REG_YMM1:
if (data->regsTainted[DR_REG_YMM1] == 1)
  return true;
break;
case DR_REG_YMM2:
if (data->regsTainted[DR_REG_YMM2] == 1)
  return true;
break;
case DR_REG_YMM3:
if (data->regsTainted[DR_REG_YMM3] == 1)
  return true;
break;
case DR_REG_YMM4:
if (data->regsTainted[DR_REG_YMM4] == 1)
  return true;
break;
case DR_REG_YMM5:
if (data->regsTainted[DR_REG_YMM5] == 1)
  return true;
break;
case DR_REG_YMM6:
if (data->regsTainted[DR_REG_YMM6] == 1)
  return true;
break;
case DR_REG_YMM7:
if (data->regsTainted[DR_REG_YMM7] == 1)
  return true;
break;
case DR_REG_YMM8:
if (data->regsTainted[DR_REG_YMM8] == 1)
  return true;
break;
case DR_REG_YMM9:
if (data->regsTainted[DR_REG_YMM9] == 1)
  return true;
break;
case DR_REG_YMM10:
if (data->regsTainted[DR_REG_YMM10] == 1)
  return true;
break;
case DR_REG_YMM11:
if (data->regsTainted[DR_REG_YMM11] == 1)
  return true;
break;
case DR_REG_YMM12:
if (data->regsTainted[DR_REG_YMM12] == 1)
  return true;
break;
case DR_REG_YMM13:
if (data->regsTainted[DR_REG_YMM13] == 1)
  return true;
break;
case DR_REG_YMM14:
if (data->regsTainted[DR_REG_YMM14] == 1)
  return true;
break;
case DR_REG_YMM15:
if (data->regsTainted[DR_REG_YMM15] == 1)
  return true;
break;
case DR_REG_MM0:
if (data->regsTainted[DR_REG_MM0] == 1)
  return true;
break;
case DR_REG_MM1:
if (data->regsTainted[DR_REG_MM1] == 1)
  return true;
break;
case DR_REG_MM2:
if (data->regsTainted[DR_REG_MM2] == 1)
  return true;
break;
case DR_REG_MM3:
if (data->regsTainted[DR_REG_MM3] == 1)
  return true;
break;
case DR_REG_MM4:
if (data->regsTainted[DR_REG_MM4] == 1)
  return true;
break;
case DR_REG_MM5:
if (data->regsTainted[DR_REG_MM5] == 1)
  return true;
break;
case DR_REG_MM6:
if (data->regsTainted[DR_REG_MM6] == 1)
  return true;
break;
case DR_REG_MM7:
if (data->regsTainted[DR_REG_MM7] == 1)
  return true;
break;
#else
#ifdef AARCHXX
case DR_REG_R0:
#ifdef AARCH64
case DR_REG_W0:
#endif
if (data->regsTainted[DR_REG_R0] == 1)
  return true;
break;
case DR_REG_R1:
#ifdef AARCH64
case DR_REG_W1:
#endif
if (data->regsTainted[DR_REG_R1] == 1)
  return true;
break;
case DR_REG_R2:
#ifdef AARCH64
case DR_REG_W2:
#endif
if (data->regsTainted[DR_REG_R2] == 1)
  return true;
break;
case DR_REG_R3:
#ifdef AARCH64
case DR_REG_W3:
#endif
if (data->regsTainted[DR_REG_R3] == 1)
  return true;
break;
case DR_REG_R4:
#ifdef AARCH64
case DR_REG_W4:
#endif
if (data->regsTainted[DR_REG_R4] == 1)
  return true;
break;
case DR_REG_R5:
#ifdef AARCH64
case DR_REG_W5:
#endif
if (data->regsTainted[DR_REG_R5] == 1)
  return true;
break;
case DR_REG_R6:
#ifdef AARCH64
case DR_REG_W6:
#endif
if (data->regsTainted[DR_REG_R6] == 1)
  return true;
break;
case DR_REG_R7:
#ifdef AARCH64
case DR_REG_W7:
#endif
if (data->regsTainted[DR_REG_R7] == 1)
  return true;
break;
case DR_REG_R8:
#ifdef AARCH64
case DR_REG_W8:
#endif
if (data->regsTainted[DR_REG_R8] == 1)
  return true;
break;
case DR_REG_R9:
#ifdef AARCH64
case DR_REG_W9:
#endif
if (data->regsTainted[DR_REG_R9] == 1)
  return true;
break;
case DR_REG_R10:
#ifdef AARCH64
case DR_REG_W10:
#endif
if (data->regsTainted[DR_REG_R10] == 1)
  return true;
break;
case DR_REG_R11:
#ifdef AARCH64
case DR_REG_W11:
#endif
if (data->regsTainted[DR_REG_R11] == 1)
  return true;
break;
case DR_REG_R12:
#ifdef AARCH64
case DR_REG_W12:
#endif
if (data->regsTainted[DR_REG_R12] == 1)
  return true;
break;
case DR_REG_R13:
#ifdef AARCH64
case DR_REG_W13:
#endif
if (data->regsTainted[DR_REG_R13] == 1)
  return true;
break;
case DR_REG_R14:
#ifdef AARCH64
case DR_REG_W14:
#endif
if (data->regsTainted[DR_REG_R14] == 1)
  return true;
break;
case DR_REG_R15:
#ifdef AARCH64
case DR_REG_W15:
#endif
if (data->regsTainted[DR_REG_R15] == 1)
  return true;
break;
#ifdef AARCH64
case DR_REG_R16:
case DR_REG_W16:
if (data->regsTainted[DR_REG_R16] == 1)
  return true;
break;
case DR_REG_R17:
case DR_REG_W17:
if (data->regsTainted[DR_REG_R17] == 1)
  return true;
break;
case DR_REG_R18:
case DR_REG_W18:
if (data->regsTainted[DR_REG_R18] == 1)
  return true;
break;
case DR_REG_R19:
case DR_REG_W19:
if (data->regsTainted[DR_REG_R19] == 1)
  return true;
break;
case DR_REG_R20:
case DR_REG_W20:
if (data->regsTainted[DR_REG_R20] == 1)
  return true;
break;
case DR_REG_R21:
case DR_REG_W21:
if (data->regsTainted[DR_REG_R21] == 1)
  return true;
break;
case DR_REG_R22:
case DR_REG_W22:
if (data->regsTainted[DR_REG_R22] == 1)
  return true;
break;
case DR_REG_R23:
case DR_REG_W23:
if (data->regsTainted[DR_REG_R23] == 1)
  return true;
break;
case DR_REG_R24:
case DR_REG_W24:
if (data->regsTainted[DR_REG_R24] == 1)
  return true;
break;
case DR_REG_R25:
case DR_REG_W25:
if (data->regsTainted[DR_REG_R25] == 1)
  return true;
break;
case DR_REG_R26:
case DR_REG_W26:
if (data->regsTainted[DR_REG_R26] == 1)
  return true;
break;
case DR_REG_R27:
case DR_REG_W27:
if (data->regsTainted[DR_REG_R27] == 1)
  return true;
break;
case DR_REG_R28:
case DR_REG_W28:
if (data->regsTainted[DR_REG_R28] == 1)
  return true;
break;
case DR_REG_R29:
case DR_REG_W29:
if (data->regsTainted[DR_REG_R29] == 1)
  return true;
break;
case DR_REG_R30:
case DR_REG_W30:
if (data->regsTainted[DR_REG_R30] == 1)
  return true;
break;
#endif
case DR_REG_Q0:
case DR_REG_D0:
if (data->regsTainted[DR_REG_D0] == 1)
  return true;
case DR_REG_S0:
if (data->regsTainted[DR_REG_S0] == 1)
  return true;
case DR_REG_H0:
if (data->regsTainted[DR_REG_H0] == 1)
  return true;
case DR_REG_B0:
if (data->regsTainted[DR_REG_B0] == 1)
  return true;
break;
case DR_REG_Q1:
case DR_REG_D1:
if (data->regsTainted[DR_REG_D1] == 1)
  return true;
case DR_REG_S1:
if (data->regsTainted[DR_REG_S1] == 1)
  return true;
case DR_REG_H1:
if (data->regsTainted[DR_REG_H1] == 1)
  return true;
case DR_REG_B1:
if (data->regsTainted[DR_REG_B1] == 1)
  return true;
break;
case DR_REG_Q2:
case DR_REG_D2:
if (data->regsTainted[DR_REG_D2] == 1)
  return true;
case DR_REG_S2:
if (data->regsTainted[DR_REG_S2] == 1)
  return true;
case DR_REG_H2:
if (data->regsTainted[DR_REG_H2] == 1)
  return true;
case DR_REG_B2:
if (data->regsTainted[DR_REG_B2] == 1)
  return true;
break;
case DR_REG_Q3:
case DR_REG_D3:
if (data->regsTainted[DR_REG_D3] == 1)
  return true;
case DR_REG_S3:
if (data->regsTainted[DR_REG_S3] == 1)
  return true;
case DR_REG_H3:
if (data->regsTainted[DR_REG_H3] == 1)
  return true;
case DR_REG_B3:
if (data->regsTainted[DR_REG_B3] == 1)
  return true;
break;
case DR_REG_Q4:
case DR_REG_D4:
if (data->regsTainted[DR_REG_D4] == 1)
  return true;
case DR_REG_S4:
if (data->regsTainted[DR_REG_S4] == 1)
  return true;
case DR_REG_H4:
if (data->regsTainted[DR_REG_H4] == 1)
  return true;
case DR_REG_B4:
if (data->regsTainted[DR_REG_B4] == 1)
  return true;
break;
case DR_REG_Q5:
case DR_REG_D5:
if (data->regsTainted[DR_REG_D5] == 1)
  return true;
case DR_REG_S5:
if (data->regsTainted[DR_REG_S5] == 1)
  return true;
case DR_REG_H5:
if (data->regsTainted[DR_REG_H5] == 1)
  return true;
case DR_REG_B5:
if (data->regsTainted[DR_REG_B5] == 1)
  return true;
break;
case DR_REG_Q6:
case DR_REG_D6:
if (data->regsTainted[DR_REG_D6] == 1)
  return true;
case DR_REG_S6:
if (data->regsTainted[DR_REG_S6] == 1)
  return true;
case DR_REG_H6:
if (data->regsTainted[DR_REG_H6] == 1)
  return true;
case DR_REG_B6:
if (data->regsTainted[DR_REG_B6] == 1)
  return true;
break;
case DR_REG_Q7:
case DR_REG_D7:
if (data->regsTainted[DR_REG_D7] == 1)
  return true;
case DR_REG_S7:
if (data->regsTainted[DR_REG_S7] == 1)
  return true;
case DR_REG_H7:
if (data->regsTainted[DR_REG_H7] == 1)
  return true;
case DR_REG_B7:
if (data->regsTainted[DR_REG_B7] == 1)
  return true;
break;
case DR_REG_Q8:
case DR_REG_D8:
if (data->regsTainted[DR_REG_D8] == 1)
  return true;
case DR_REG_S8:
if (data->regsTainted[DR_REG_S8] == 1)
  return true;
case DR_REG_H8:
if (data->regsTainted[DR_REG_H8] == 1)
  return true;
case DR_REG_B8:
if (data->regsTainted[DR_REG_B8] == 1)
  return true;
break;
case DR_REG_Q9:
case DR_REG_D9:
if (data->regsTainted[DR_REG_D9] == 1)
  return true;
case DR_REG_S9:
if (data->regsTainted[DR_REG_S9] == 1)
  return true;
case DR_REG_H9:
if (data->regsTainted[DR_REG_H9] == 1)
  return true;
case DR_REG_B9:
if (data->regsTainted[DR_REG_B9] == 1)
  return true;
break;
case DR_REG_Q10:
case DR_REG_D10:
if (data->regsTainted[DR_REG_D10] == 1)
  return true;
case DR_REG_S10:
if (data->regsTainted[DR_REG_S10] == 1)
  return true;
case DR_REG_H10:
if (data->regsTainted[DR_REG_H10] == 1)
  return true;
case DR_REG_B10:
if (data->regsTainted[DR_REG_B10] == 1)
  return true;
break;
case DR_REG_Q11:
case DR_REG_D11:
if (data->regsTainted[DR_REG_D11] == 1)
  return true;
case DR_REG_S11:
if (data->regsTainted[DR_REG_S11] == 1)
  return true;
case DR_REG_H11:
if (data->regsTainted[DR_REG_H11] == 1)
  return true;
case DR_REG_B11:
if (data->regsTainted[DR_REG_B11] == 1)
  return true;
break;
case DR_REG_Q12:
case DR_REG_D12:
if (data->regsTainted[DR_REG_D12] == 1)
  return true;
case DR_REG_S12:
if (data->regsTainted[DR_REG_S12] == 1)
  return true;
case DR_REG_H12:
if (data->regsTainted[DR_REG_H12] == 1)
  return true;
case DR_REG_B12:
if (data->regsTainted[DR_REG_B12] == 1)
  return true;
break;
case DR_REG_Q13:
case DR_REG_D13:
if (data->regsTainted[DR_REG_D13] == 1)
  return true;
case DR_REG_S13:
if (data->regsTainted[DR_REG_S13] == 1)
  return true;
case DR_REG_H13:
if (data->regsTainted[DR_REG_H13] == 1)
  return true;
case DR_REG_B13:
if (data->regsTainted[DR_REG_B13] == 1)
  return true;
break;
case DR_REG_Q14:
case DR_REG_D14:
if (data->regsTainted[DR_REG_D14] == 1)
  return true;
case DR_REG_S14:
if (data->regsTainted[DR_REG_S14] == 1)
  return true;
case DR_REG_H14:
if (data->regsTainted[DR_REG_H14] == 1)
  return true;
case DR_REG_B14:
if (data->regsTainted[DR_REG_B14] == 1)
  return true;
break;
case DR_REG_Q15:
case DR_REG_D15:
if (data->regsTainted[DR_REG_D15] == 1)
  return true;
case DR_REG_S15:
if (data->regsTainted[DR_REG_S15] == 1)
  return true;
case DR_REG_H15:
if (data->regsTainted[DR_REG_H15] == 1)
  return true;
case DR_REG_B15:
if (data->regsTainted[DR_REG_B15] == 1)
  return true;
break;
case DR_REG_Q16:
case DR_REG_D16:
if (data->regsTainted[DR_REG_D16] == 1)
  return true;
case DR_REG_S16:
if (data->regsTainted[DR_REG_S16] == 1)
  return true;
case DR_REG_H16:
if (data->regsTainted[DR_REG_H16] == 1)
  return true;
case DR_REG_B16:
if (data->regsTainted[DR_REG_B16] == 1)
  return true;
break;
case DR_REG_Q17:
case DR_REG_D17:
if (data->regsTainted[DR_REG_D17] == 1)
  return true;
case DR_REG_S17:
if (data->regsTainted[DR_REG_S17] == 1)
  return true;
case DR_REG_H17:
if (data->regsTainted[DR_REG_H17] == 1)
  return true;
case DR_REG_B17:
if (data->regsTainted[DR_REG_B17] == 1)
  return true;
break;
case DR_REG_Q18:
case DR_REG_D18:
if (data->regsTainted[DR_REG_D18] == 1)
  return true;
case DR_REG_S18:
if (data->regsTainted[DR_REG_S18] == 1)
  return true;
case DR_REG_H18:
if (data->regsTainted[DR_REG_H18] == 1)
  return true;
case DR_REG_B18:
if (data->regsTainted[DR_REG_B18] == 1)
  return true;
break;
case DR_REG_Q19:
case DR_REG_D19:
if (data->regsTainted[DR_REG_D19] == 1)
  return true;
case DR_REG_S19:
if (data->regsTainted[DR_REG_S19] == 1)
  return true;
case DR_REG_H19:
if (data->regsTainted[DR_REG_H19] == 1)
  return true;
case DR_REG_B19:
if (data->regsTainted[DR_REG_B19] == 1)
  return true;
break;
case DR_REG_Q20:
case DR_REG_D20:
if (data->regsTainted[DR_REG_D20] == 1)
  return true;
case DR_REG_S20:
if (data->regsTainted[DR_REG_S20] == 1)
  return true;
case DR_REG_H20:
if (data->regsTainted[DR_REG_H20] == 1)
  return true;
case DR_REG_B20:
if (data->regsTainted[DR_REG_B20] == 1)
  return true;
break;
case DR_REG_Q21:
case DR_REG_D21:
if (data->regsTainted[DR_REG_D21] == 1)
  return true;
case DR_REG_S21:
if (data->regsTainted[DR_REG_S21] == 1)
  return true;
case DR_REG_H21:
if (data->regsTainted[DR_REG_H21] == 1)
  return true;
case DR_REG_B21:
if (data->regsTainted[DR_REG_B21] == 1)
  return true;
break;
case DR_REG_Q22:
case DR_REG_D22:
if (data->regsTainted[DR_REG_D22] == 1)
  return true;
case DR_REG_S22:
if (data->regsTainted[DR_REG_S22] == 1)
  return true;
case DR_REG_H22:
if (data->regsTainted[DR_REG_H22] == 1)
  return true;
case DR_REG_B22:
if (data->regsTainted[DR_REG_B22] == 1)
  return true;
break;
case DR_REG_Q23:
case DR_REG_D23:
if (data->regsTainted[DR_REG_D23] == 1)
  return true;
case DR_REG_S23:
if (data->regsTainted[DR_REG_S23] == 1)
  return true;
case DR_REG_H23:
if (data->regsTainted[DR_REG_H23] == 1)
  return true;
case DR_REG_B23:
if (data->regsTainted[DR_REG_B23] == 1)
  return true;
break;
case DR_REG_Q24:
case DR_REG_D24:
if (data->regsTainted[DR_REG_D24] == 1)
  return true;
case DR_REG_S24:
if (data->regsTainted[DR_REG_S24] == 1)
  return true;
case DR_REG_H24:
if (data->regsTainted[DR_REG_H24] == 1)
  return true;
case DR_REG_B24:
if (data->regsTainted[DR_REG_B24] == 1)
  return true;
break;
case DR_REG_Q25:
case DR_REG_D25:
if (data->regsTainted[DR_REG_D25] == 1)
  return true;
case DR_REG_S25:
if (data->regsTainted[DR_REG_S25] == 1)
  return true;
case DR_REG_H25:
if (data->regsTainted[DR_REG_H25] == 1)
  return true;
case DR_REG_B25:
if (data->regsTainted[DR_REG_B25] == 1)
  return true;
break;
case DR_REG_Q26:
case DR_REG_D26:
if (data->regsTainted[DR_REG_D26] == 1)
  return true;
case DR_REG_S26:
if (data->regsTainted[DR_REG_S26] == 1)
  return true;
case DR_REG_H26:
if (data->regsTainted[DR_REG_H26] == 1)
  return true;
case DR_REG_B26:
if (data->regsTainted[DR_REG_B26] == 1)
  return true;
break;
case DR_REG_Q27:
case DR_REG_D27:
if (data->regsTainted[DR_REG_D27] == 1)
  return true;
case DR_REG_S27:
if (data->regsTainted[DR_REG_S27] == 1)
  return true;
case DR_REG_H27:
if (data->regsTainted[DR_REG_H27] == 1)
  return true;
case DR_REG_B27:
if (data->regsTainted[DR_REG_B27] == 1)
  return true;
break;
case DR_REG_Q28:
case DR_REG_D28:
if (data->regsTainted[DR_REG_D28] == 1)
  return true;
case DR_REG_S28:
if (data->regsTainted[DR_REG_S28] == 1)
  return true;
case DR_REG_H28:
if (data->regsTainted[DR_REG_H28] == 1)
  return true;
case DR_REG_B28:
if (data->regsTainted[DR_REG_B28] == 1)
  return true;
break;
case DR_REG_Q29:
case DR_REG_D29:
if (data->regsTainted[DR_REG_D29] == 1)
  return true;
case DR_REG_S29:
if (data->regsTainted[DR_REG_S29] == 1)
  return true;
case DR_REG_H29:
if (data->regsTainted[DR_REG_H29] == 1)
  return true;
case DR_REG_B29:
if (data->regsTainted[DR_REG_B29] == 1)
  return true;
break;
case DR_REG_Q30:
case DR_REG_D30:
if (data->regsTainted[DR_REG_D30] == 1)
  return true;
case DR_REG_S30:
if (data->regsTainted[DR_REG_S30] == 1)
  return true;
case DR_REG_H30:
if (data->regsTainted[DR_REG_H30] == 1)
  return true;
case DR_REG_B30:
if (data->regsTainted[DR_REG_B30] == 1)
  return true;
break;
case DR_REG_Q31:
case DR_REG_D31:
if (data->regsTainted[DR_REG_D31] == 1)
  return true;
case DR_REG_S31:
if (data->regsTainted[DR_REG_S31] == 1)
  return true;
case DR_REG_H31:
if (data->regsTainted[DR_REG_H31] == 1)
  return true;
case DR_REG_B31:
if (data->regsTainted[DR_REG_B31] == 1)
  return true;
break;
#endif
#endif
