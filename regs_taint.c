#ifdef X86
case DR_REG_RAX:
case DR_REG_EAX:
data->regsTainted[DR_REG_EAX] = 1;
case DR_REG_AX: {
  data->regsTainted[DR_REG_AX] = 1;
  data->regsTainted[DR_REG_AH] = 1;
  data->regsTainted[DR_REG_AL] = 1;
  break;
}
case DR_REG_AH:
data->regsTainted[DR_REG_AH] = 1;
break;
case DR_REG_AL:
data->regsTainted[DR_REG_AH] = 1;
break;
case DR_REG_RBX:
case DR_REG_EBX:
data->regsTainted[DR_REG_EBX] = 1;
case DR_REG_BX: {
  data->regsTainted[DR_REG_BX] = 1;
  data->regsTainted[DR_REG_BH] = 1;
  data->regsTainted[DR_REG_BL] = 1;
  break;
}
case DR_REG_BH:
data->regsTainted[DR_REG_BH] = 1;
break;
case DR_REG_BL:
data->regsTainted[DR_REG_BH] = 1;
break;
case DR_REG_RCX:
case DR_REG_ECX:
data->regsTainted[DR_REG_ECX] = 1;
case DR_REG_CX: {
  data->regsTainted[DR_REG_CX] = 1;
  data->regsTainted[DR_REG_CH] = 1;
  data->regsTainted[DR_REG_CL] = 1;
  break;
}
case DR_REG_CH:
data->regsTainted[DR_REG_CH] = 1;
break;
case DR_REG_CL:
data->regsTainted[DR_REG_CH] = 1;
break;
case DR_REG_RDX:
case DR_REG_EDX:
data->regsTainted[DR_REG_EDX] = 1;
case DR_REG_DX: {
  data->regsTainted[DR_REG_DX] = 1;
  data->regsTainted[DR_REG_DH] = 1;
  data->regsTainted[DR_REG_DL] = 1;
  break;
}
case DR_REG_DH:
data->regsTainted[DR_REG_DH] = 1;
break;
case DR_REG_DL:
data->regsTainted[DR_REG_DH] = 1;
break;
case DR_REG_RBP:
case DR_REG_EBP:
data->regsTainted[DR_REG_EBP] = 1;
case DR_REG_BP:
data->regsTainted[DR_REG_BP] = 1;
case DR_REG_BPL:
data->regsTainted[DR_REG_BPL] = 1;
break;
case DR_REG_RDI:
case DR_REG_EDI:
data->regsTainted[DR_REG_EDI] = 1;
case DR_REG_DI:
data->regsTainted[DR_REG_DI] = 1;
case DR_REG_DIL:
data->regsTainted[DR_REG_DIL] = 1;
break;
case DR_REG_RSI:
case DR_REG_ESI:
data->regsTainted[DR_REG_ESI] = 1;
case DR_REG_SI:
data->regsTainted[DR_REG_SI] = 1;
case DR_REG_SIL:
data->regsTainted[DR_REG_SIL] = 1;
break;
case DR_REG_R8:
case DR_REG_R8D:
data->regsTainted[DR_REG_R8D] = 1;
case DR_REG_R8W:
data->regsTainted[DR_REG_R8W] = 1;
case DR_REG_R8L:
data->regsTainted[DR_REG_R8L] = 1;
break;
case DR_REG_R9:
case DR_REG_R9D:
data->regsTainted[DR_REG_R9D] = 1;
case DR_REG_R9W:
data->regsTainted[DR_REG_R9W] = 1;
case DR_REG_R9L:
data->regsTainted[DR_REG_R9L] = 1;
break;
case DR_REG_R10:
case DR_REG_R10D:
data->regsTainted[DR_REG_R10D] = 1;
case DR_REG_R10W:
data->regsTainted[DR_REG_R10W] = 1;
case DR_REG_R10L:
data->regsTainted[DR_REG_R10L] = 1;
break;
case DR_REG_R11:
case DR_REG_R11D:
data->regsTainted[DR_REG_R11D] = 1;
case DR_REG_R11W:
data->regsTainted[DR_REG_R11W] = 1;
case DR_REG_R11L:
data->regsTainted[DR_REG_R11L] = 1;
break;
case DR_REG_R12:
case DR_REG_R12D:
data->regsTainted[DR_REG_R12D] = 1;
case DR_REG_R12W:
data->regsTainted[DR_REG_R12W] = 1;
case DR_REG_R12L:
data->regsTainted[DR_REG_R12L] = 1;
break;
case DR_REG_R13:
case DR_REG_R13D:
data->regsTainted[DR_REG_R13D] = 1;
case DR_REG_R13W:
data->regsTainted[DR_REG_R13W] = 1;
case DR_REG_R13L:
data->regsTainted[DR_REG_R13L] = 1;
break;
case DR_REG_R14:
case DR_REG_R14D:
data->regsTainted[DR_REG_R14D] = 1;
case DR_REG_R14W:
data->regsTainted[DR_REG_R14W] = 1;
case DR_REG_R14L:
data->regsTainted[DR_REG_R14L] = 1;
break;
case DR_REG_R15:
case DR_REG_R15D:
data->regsTainted[DR_REG_R15D] = 1;
case DR_REG_R15W:
data->regsTainted[DR_REG_R15W] = 1;
case DR_REG_R15L:
data->regsTainted[DR_REG_R15L] = 1;
break;
case DR_REG_XMM0:
data->regsTainted[DR_REG_XMM0] = 1;
break;
case DR_REG_XMM1:
data->regsTainted[DR_REG_XMM1] = 1;
break;
case DR_REG_XMM2:
data->regsTainted[DR_REG_XMM2] = 1;
break;
case DR_REG_XMM3:
data->regsTainted[DR_REG_XMM3] = 1;
break;
case DR_REG_XMM4:
data->regsTainted[DR_REG_XMM4] = 1;
break;
case DR_REG_XMM5:
data->regsTainted[DR_REG_XMM5] = 1;
break;
case DR_REG_XMM6:
data->regsTainted[DR_REG_XMM6] = 1;
break;
case DR_REG_XMM7:
data->regsTainted[DR_REG_XMM7] = 1;
break;
case DR_REG_XMM8:
data->regsTainted[DR_REG_XMM8] = 1;
break;
case DR_REG_XMM9:
data->regsTainted[DR_REG_XMM9] = 1;
break;
case DR_REG_XMM10:
data->regsTainted[DR_REG_XMM10] = 1;
break;
case DR_REG_XMM11:
data->regsTainted[DR_REG_XMM11] = 1;
break;
case DR_REG_XMM12:
data->regsTainted[DR_REG_XMM12] = 1;
break;
case DR_REG_XMM13:
data->regsTainted[DR_REG_XMM13] = 1;
break;
case DR_REG_XMM14:
data->regsTainted[DR_REG_XMM14] = 1;
break;
case DR_REG_XMM15:
data->regsTainted[DR_REG_XMM15] = 1;
break;
case DR_REG_YMM0:
data->regsTainted[DR_REG_YMM0] = 1;
break;
case DR_REG_YMM1:
data->regsTainted[DR_REG_YMM1] = 1;
break;
case DR_REG_YMM2:
data->regsTainted[DR_REG_YMM2] = 1;
break;
case DR_REG_YMM3:
data->regsTainted[DR_REG_YMM3] = 1;
break;
case DR_REG_YMM4:
data->regsTainted[DR_REG_YMM4] = 1;
break;
case DR_REG_YMM5:
data->regsTainted[DR_REG_YMM5] = 1;
break;
case DR_REG_YMM6:
data->regsTainted[DR_REG_YMM6] = 1;
break;
case DR_REG_YMM7:
data->regsTainted[DR_REG_YMM7] = 1;
break;
case DR_REG_YMM8:
data->regsTainted[DR_REG_YMM8] = 1;
break;
case DR_REG_YMM9:
data->regsTainted[DR_REG_YMM9] = 1;
break;
case DR_REG_YMM10:
data->regsTainted[DR_REG_YMM10] = 1;
break;
case DR_REG_YMM11:
data->regsTainted[DR_REG_YMM11] = 1;
break;
case DR_REG_YMM12:
data->regsTainted[DR_REG_YMM12] = 1;
break;
case DR_REG_YMM13:
data->regsTainted[DR_REG_YMM13] = 1;
break;
case DR_REG_YMM14:
data->regsTainted[DR_REG_YMM14] = 1;
break;
case DR_REG_YMM15:
data->regsTainted[DR_REG_YMM15] = 1;
break;
case DR_REG_MM0:
data->regsTainted[DR_REG_MM0] = 1;
break;
case DR_REG_MM1:
data->regsTainted[DR_REG_MM1] = 1;
break;
case DR_REG_MM2:
data->regsTainted[DR_REG_MM2] = 1;
break;
case DR_REG_MM3:
data->regsTainted[DR_REG_MM3] = 1;
break;
case DR_REG_MM4:
data->regsTainted[DR_REG_MM4] = 1;
break;
case DR_REG_MM5:
data->regsTainted[DR_REG_MM5] = 1;
break;
case DR_REG_MM6:
data->regsTainted[DR_REG_MM6] = 1;
break;
case DR_REG_MM7:
data->regsTainted[DR_REG_MM7] = 1;
break;
#else
#ifdef AARCHXX
case DR_REG_R0:
#ifdef AARCH64
case DR_REG_W0:
#endif
data->regsTainted[DR_REG_R0] = 1;
break;
case DR_REG_R1:
#ifdef AARCH64
case DR_REG_W1:
#endif
data->regsTainted[DR_REG_R1] = 1;
break;
case DR_REG_R2:
#ifdef AARCH64
case DR_REG_W2:
#endif
data->regsTainted[DR_REG_R2] = 1;
break;
case DR_REG_R3:
#ifdef AARCH64
case DR_REG_W3:
#endif
data->regsTainted[DR_REG_R3] = 1;
break;
case DR_REG_R4:
#ifdef AARCH64
case DR_REG_W4:
#endif
data->regsTainted[DR_REG_R4] = 1;
break;
case DR_REG_R5:
#ifdef AARCH64
case DR_REG_W5:
#endif
data->regsTainted[DR_REG_R5] = 1;
break;
case DR_REG_R6:
#ifdef AARCH64
case DR_REG_W6:
#endif
data->regsTainted[DR_REG_R6] = 1;
break;
case DR_REG_R7:
#ifdef AARCH64
case DR_REG_W7:
#endif
data->regsTainted[DR_REG_R7] = 1;
break;
case DR_REG_R8:
#ifdef AARCH64
case DR_REG_W8:
#endif
data->regsTainted[DR_REG_R8] = 1;
break;
case DR_REG_R9:
#ifdef AARCH64
case DR_REG_W9:
#endif
data->regsTainted[DR_REG_R9] = 1;
break;
case DR_REG_R10:
#ifdef AARCH64
case DR_REG_W10:
#endif
data->regsTainted[DR_REG_R10] = 1;
break;
case DR_REG_R11:
#ifdef AARCH64
case DR_REG_W11:
#endif
data->regsTainted[DR_REG_R11] = 1;
break;
case DR_REG_R12:
#ifdef AARCH64
case DR_REG_W12:
#endif
data->regsTainted[DR_REG_R12] = 1;
break;
case DR_REG_R13:
#ifdef AARCH64
case DR_REG_W13:
#endif
data->regsTainted[DR_REG_R13] = 1;
break;
case DR_REG_R14:
#ifdef AARCH64
case DR_REG_W14:
#endif
data->regsTainted[DR_REG_R14] = 1;
break;
case DR_REG_R15:
#ifdef AARCH64
case DR_REG_W15:
#endif
data->regsTainted[DR_REG_R15] = 1;
break;
#ifdef AARCH64
case DR_REG_R16:
case DR_REG_W16:
data->regsTainted[DR_REG_R16] = 1;
break;
case DR_REG_R17:
case DR_REG_W17:
data->regsTainted[DR_REG_R17] = 1;
break;
case DR_REG_R18:
case DR_REG_W18:
data->regsTainted[DR_REG_R18] = 1;
break;
case DR_REG_R19:
case DR_REG_W19:
data->regsTainted[DR_REG_R19] = 1;
break;
case DR_REG_R20:
case DR_REG_W20:
data->regsTainted[DR_REG_R20] = 1;
break;
case DR_REG_R21:
case DR_REG_W21:
data->regsTainted[DR_REG_R21] = 1;
break;
case DR_REG_R22:
case DR_REG_W22:
data->regsTainted[DR_REG_R22] = 1;
break;
case DR_REG_R23:
case DR_REG_W23:
data->regsTainted[DR_REG_R23] = 1;
break;
case DR_REG_R24:
case DR_REG_W24:
data->regsTainted[DR_REG_R24] = 1;
break;
case DR_REG_R25:
case DR_REG_W25:
data->regsTainted[DR_REG_R25] = 1;
break;
case DR_REG_R26:
case DR_REG_W26:
data->regsTainted[DR_REG_R26] = 1;
break;
case DR_REG_R27:
case DR_REG_W27:
data->regsTainted[DR_REG_R27] = 1;
break;
case DR_REG_R28:
case DR_REG_W28:
data->regsTainted[DR_REG_R28] = 1;
break;
case DR_REG_R29:
case DR_REG_W29:
data->regsTainted[DR_REG_R29] = 1;
break;
case DR_REG_R30:
case DR_REG_W30:
data->regsTainted[DR_REG_R30] = 1;
break;
#endif
case DR_REG_Q0:
case DR_REG_D0:
data->regsTainted[DR_REG_D0] = 1;
case DR_REG_S0:
data->regsTainted[DR_REG_S0] = 1;
case DR_REG_H0:
data->regsTainted[DR_REG_H0] = 1;
case DR_REG_B0:
data->regsTainted[DR_REG_B0] = 1;
break;
case DR_REG_Q1:
case DR_REG_D1:
data->regsTainted[DR_REG_D1] = 1;
case DR_REG_S1:
data->regsTainted[DR_REG_S1] = 1;
case DR_REG_H1:
data->regsTainted[DR_REG_H1] = 1;
case DR_REG_B1:
data->regsTainted[DR_REG_B1] = 1;
break;
case DR_REG_Q2:
case DR_REG_D2:
data->regsTainted[DR_REG_D2] = 1;
case DR_REG_S2:
data->regsTainted[DR_REG_S2] = 1;
case DR_REG_H2:
data->regsTainted[DR_REG_H2] = 1;
case DR_REG_B2:
data->regsTainted[DR_REG_B2] = 1;
break;
case DR_REG_Q3:
case DR_REG_D3:
data->regsTainted[DR_REG_D3] = 1;
case DR_REG_S3:
data->regsTainted[DR_REG_S3] = 1;
case DR_REG_H3:
data->regsTainted[DR_REG_H3] = 1;
case DR_REG_B3:
data->regsTainted[DR_REG_B3] = 1;
break;
case DR_REG_Q4:
case DR_REG_D4:
data->regsTainted[DR_REG_D4] = 1;
case DR_REG_S4:
data->regsTainted[DR_REG_S4] = 1;
case DR_REG_H4:
data->regsTainted[DR_REG_H4] = 1;
case DR_REG_B4:
data->regsTainted[DR_REG_B4] = 1;
break;
case DR_REG_Q5:
case DR_REG_D5:
data->regsTainted[DR_REG_D5] = 1;
case DR_REG_S5:
data->regsTainted[DR_REG_S5] = 1;
case DR_REG_H5:
data->regsTainted[DR_REG_H5] = 1;
case DR_REG_B5:
data->regsTainted[DR_REG_B5] = 1;
break;
case DR_REG_Q6:
case DR_REG_D6:
data->regsTainted[DR_REG_D6] = 1;
case DR_REG_S6:
data->regsTainted[DR_REG_S6] = 1;
case DR_REG_H6:
data->regsTainted[DR_REG_H6] = 1;
case DR_REG_B6:
data->regsTainted[DR_REG_B6] = 1;
break;
case DR_REG_Q7:
case DR_REG_D7:
data->regsTainted[DR_REG_D7] = 1;
case DR_REG_S7:
data->regsTainted[DR_REG_S7] = 1;
case DR_REG_H7:
data->regsTainted[DR_REG_H7] = 1;
case DR_REG_B7:
data->regsTainted[DR_REG_B7] = 1;
break;
case DR_REG_Q8:
case DR_REG_D8:
data->regsTainted[DR_REG_D8] = 1;
case DR_REG_S8:
data->regsTainted[DR_REG_S8] = 1;
case DR_REG_H8:
data->regsTainted[DR_REG_H8] = 1;
case DR_REG_B8:
data->regsTainted[DR_REG_B8] = 1;
break;
case DR_REG_Q9:
case DR_REG_D9:
data->regsTainted[DR_REG_D9] = 1;
case DR_REG_S9:
data->regsTainted[DR_REG_S9] = 1;
case DR_REG_H9:
data->regsTainted[DR_REG_H9] = 1;
case DR_REG_B9:
data->regsTainted[DR_REG_B9] = 1;
break;
case DR_REG_Q10:
case DR_REG_D10:
data->regsTainted[DR_REG_D10] = 1;
case DR_REG_S10:
data->regsTainted[DR_REG_S10] = 1;
case DR_REG_H10:
data->regsTainted[DR_REG_H10] = 1;
case DR_REG_B10:
data->regsTainted[DR_REG_B10] = 1;
break;
case DR_REG_Q11:
case DR_REG_D11:
data->regsTainted[DR_REG_D11] = 1;
case DR_REG_S11:
data->regsTainted[DR_REG_S11] = 1;
case DR_REG_H11:
data->regsTainted[DR_REG_H11] = 1;
case DR_REG_B11:
data->regsTainted[DR_REG_B11] = 1;
break;
case DR_REG_Q12:
case DR_REG_D12:
data->regsTainted[DR_REG_D12] = 1;
case DR_REG_S12:
data->regsTainted[DR_REG_S12] = 1;
case DR_REG_H12:
data->regsTainted[DR_REG_H12] = 1;
case DR_REG_B12:
data->regsTainted[DR_REG_B12] = 1;
break;
case DR_REG_Q13:
case DR_REG_D13:
data->regsTainted[DR_REG_D13] = 1;
case DR_REG_S13:
data->regsTainted[DR_REG_S13] = 1;
case DR_REG_H13:
data->regsTainted[DR_REG_H13] = 1;
case DR_REG_B13:
data->regsTainted[DR_REG_B13] = 1;
break;
case DR_REG_Q14:
case DR_REG_D14:
data->regsTainted[DR_REG_D14] = 1;
case DR_REG_S14:
data->regsTainted[DR_REG_S14] = 1;
case DR_REG_H14:
data->regsTainted[DR_REG_H14] = 1;
case DR_REG_B14:
data->regsTainted[DR_REG_B14] = 1;
break;
case DR_REG_Q15:
case DR_REG_D15:
data->regsTainted[DR_REG_D15] = 1;
case DR_REG_S15:
data->regsTainted[DR_REG_S15] = 1;
case DR_REG_H15:
data->regsTainted[DR_REG_H15] = 1;
case DR_REG_B15:
data->regsTainted[DR_REG_B15] = 1;
break;
case DR_REG_Q16:
case DR_REG_D16:
data->regsTainted[DR_REG_D16] = 1;
case DR_REG_S16:
data->regsTainted[DR_REG_S16] = 1;
case DR_REG_H16:
data->regsTainted[DR_REG_H16] = 1;
case DR_REG_B16:
data->regsTainted[DR_REG_B16] = 1;
break;
case DR_REG_Q17:
case DR_REG_D17:
data->regsTainted[DR_REG_D17] = 1;
case DR_REG_S17:
data->regsTainted[DR_REG_S17] = 1;
case DR_REG_H17:
data->regsTainted[DR_REG_H17] = 1;
case DR_REG_B17:
data->regsTainted[DR_REG_B17] = 1;
break;
case DR_REG_Q18:
case DR_REG_D18:
data->regsTainted[DR_REG_D18] = 1;
case DR_REG_S18:
data->regsTainted[DR_REG_S18] = 1;
case DR_REG_H18:
data->regsTainted[DR_REG_H18] = 1;
case DR_REG_B18:
data->regsTainted[DR_REG_B18] = 1;
break;
case DR_REG_Q19:
case DR_REG_D19:
data->regsTainted[DR_REG_D19] = 1;
case DR_REG_S19:
data->regsTainted[DR_REG_S19] = 1;
case DR_REG_H19:
data->regsTainted[DR_REG_H19] = 1;
case DR_REG_B19:
data->regsTainted[DR_REG_B19] = 1;
break;
case DR_REG_Q20:
case DR_REG_D20:
data->regsTainted[DR_REG_D20] = 1;
case DR_REG_S20:
data->regsTainted[DR_REG_S20] = 1;
case DR_REG_H20:
data->regsTainted[DR_REG_H20] = 1;
case DR_REG_B20:
data->regsTainted[DR_REG_B20] = 1;
break;
case DR_REG_Q21:
case DR_REG_D21:
data->regsTainted[DR_REG_D21] = 1;
case DR_REG_S21:
data->regsTainted[DR_REG_S21] = 1;
case DR_REG_H21:
data->regsTainted[DR_REG_H21] = 1;
case DR_REG_B21:
data->regsTainted[DR_REG_B21] = 1;
break;
case DR_REG_Q22:
case DR_REG_D22:
data->regsTainted[DR_REG_D22] = 1;
case DR_REG_S22:
data->regsTainted[DR_REG_S22] = 1;
case DR_REG_H22:
data->regsTainted[DR_REG_H22] = 1;
case DR_REG_B22:
data->regsTainted[DR_REG_B22] = 1;
break;
case DR_REG_Q23:
case DR_REG_D23:
data->regsTainted[DR_REG_D23] = 1;
case DR_REG_S23:
data->regsTainted[DR_REG_S23] = 1;
case DR_REG_H23:
data->regsTainted[DR_REG_H23] = 1;
case DR_REG_B23:
data->regsTainted[DR_REG_B23] = 1;
break;
case DR_REG_Q24:
case DR_REG_D24:
data->regsTainted[DR_REG_D24] = 1;
case DR_REG_S24:
data->regsTainted[DR_REG_S24] = 1;
case DR_REG_H24:
data->regsTainted[DR_REG_H24] = 1;
case DR_REG_B24:
data->regsTainted[DR_REG_B24] = 1;
break;
case DR_REG_Q25:
case DR_REG_D25:
data->regsTainted[DR_REG_D25] = 1;
case DR_REG_S25:
data->regsTainted[DR_REG_S25] = 1;
case DR_REG_H25:
data->regsTainted[DR_REG_H25] = 1;
case DR_REG_B25:
data->regsTainted[DR_REG_B25] = 1;
break;
case DR_REG_Q26:
case DR_REG_D26:
data->regsTainted[DR_REG_D26] = 1;
case DR_REG_S26:
data->regsTainted[DR_REG_S26] = 1;
case DR_REG_H26:
data->regsTainted[DR_REG_H26] = 1;
case DR_REG_B26:
data->regsTainted[DR_REG_B26] = 1;
break;
case DR_REG_Q27:
case DR_REG_D27:
data->regsTainted[DR_REG_D27] = 1;
case DR_REG_S27:
data->regsTainted[DR_REG_S27] = 1;
case DR_REG_H27:
data->regsTainted[DR_REG_H27] = 1;
case DR_REG_B27:
data->regsTainted[DR_REG_B27] = 1;
break;
case DR_REG_Q28:
case DR_REG_D28:
data->regsTainted[DR_REG_D28] = 1;
case DR_REG_S28:
data->regsTainted[DR_REG_S28] = 1;
case DR_REG_H28:
data->regsTainted[DR_REG_H28] = 1;
case DR_REG_B28:
data->regsTainted[DR_REG_B28] = 1;
break;
case DR_REG_Q29:
case DR_REG_D29:
data->regsTainted[DR_REG_D29] = 1;
case DR_REG_S29:
data->regsTainted[DR_REG_S29] = 1;
case DR_REG_H29:
data->regsTainted[DR_REG_H29] = 1;
case DR_REG_B29:
data->regsTainted[DR_REG_B29] = 1;
break;
case DR_REG_Q30:
case DR_REG_D30:
data->regsTainted[DR_REG_D30] = 1;
case DR_REG_S30:
data->regsTainted[DR_REG_S30] = 1;
case DR_REG_H30:
data->regsTainted[DR_REG_H30] = 1;
case DR_REG_B30:
data->regsTainted[DR_REG_B30] = 1;
break;
case DR_REG_Q31:
case DR_REG_D31:
data->regsTainted[DR_REG_D31] = 1;
case DR_REG_S31:
data->regsTainted[DR_REG_S31] = 1;
case DR_REG_H31:
data->regsTainted[DR_REG_H31] = 1;
case DR_REG_B31:
data->regsTainted[DR_REG_B31] = 1;
break;

#else
#error "not supported yet"
#endif
#endif
