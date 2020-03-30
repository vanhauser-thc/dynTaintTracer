static uintptr_t getRegValue(dr_mcontext_t *mc, int reg) {
  switch (reg) {
#ifdef X86
  case DR_REG_RAX:
  case DR_REG_EAX:
  case DR_REG_AX:
  case DR_REG_AH:
  case DR_REG_AL:
    return mc->rax;
    break;
  case DR_REG_RBX:
  case DR_REG_EBX:
  case DR_REG_BX:
  case DR_REG_BH:
  case DR_REG_BL:
    return mc->rbx;
    break;
  case DR_REG_RCX:
  case DR_REG_ECX:
  case DR_REG_CX:
  case DR_REG_CH:
  case DR_REG_CL:
    return mc->rcx;
    break;
  case DR_REG_RDX:
  case DR_REG_EDX:
  case DR_REG_DX:
  case DR_REG_DH:
  case DR_REG_DL:
    return mc->rdx;
    break;
  case DR_REG_RBP:
  case DR_REG_EBP:
  case DR_REG_BP:
  case DR_REG_BPL:
    return mc->rbp;
    break;
  case DR_REG_RDI:
  case DR_REG_EDI:
  case DR_REG_DI:
  case DR_REG_DIL:
    return mc->rdi;
    break;
  case DR_REG_RSI:
  case DR_REG_ESI:
  case DR_REG_SI:
  case DR_REG_SIL:
    return mc->rsi;
    break;
  case DR_REG_R8:
  case DR_REG_R8D:
  case DR_REG_R8W:
  case DR_REG_R8L:
    return mc->r8;
    break;
  case DR_REG_R9:
  case DR_REG_R9D:
  case DR_REG_R9W:
  case DR_REG_R9L:
    return mc->r9;
    break;
  case DR_REG_R10:
  case DR_REG_R10D:
  case DR_REG_R10W:
  case DR_REG_R10L:
    return mc->r10;
    break;
  case DR_REG_R11:
  case DR_REG_R11D:
  case DR_REG_R11W:
  case DR_REG_R11L:
    return mc->r11;
    break;
  case DR_REG_R12:
  case DR_REG_R12D:
  case DR_REG_R12W:
  case DR_REG_R12L:
    return mc->r12;
    break;
  case DR_REG_R13:
  case DR_REG_R13D:
  case DR_REG_R13W:
  case DR_REG_R13L:
    return mc->r13;
    break;
  case DR_REG_R14:
  case DR_REG_R14D:
  case DR_REG_R14W:
  case DR_REG_R14L:
    return mc->r14;
    break;
  case DR_REG_R15:
  case DR_REG_R15D:
  case DR_REG_R15W:
  case DR_REG_R15L:
    return mc->r15;
    break;
    /*
        case DR_REG_XMM0: return mc->xmm0; break;
        case DR_REG_XMM1: return mc->xmm1; break;
        case DR_REG_XMM2: return mc->xmm2; break;
        case DR_REG_XMM3: return mc->xmm3; break;
        case DR_REG_XMM4: return mc->xmm4; break;
        case DR_REG_XMM5: return mc->xmm5; break;
        case DR_REG_XMM6: return mc->xmm6; break;
        case DR_REG_XMM7: return mc->xmm7; break;
        case DR_REG_XMM8: return mc->xmm8; break;
        case DR_REG_XMM9: return mc->xmm9; break;
        case DR_REG_XMM10: return mc->xmm10; break;
        case DR_REG_XMM11: return mc->xmm11; break;
        case DR_REG_XMM12: return mc->xmm12; break;
        case DR_REG_XMM13: return mc->xmm13; break;
        case DR_REG_XMM14: return mc->xmm14; break;
        case DR_REG_XMM15: return mc->xmm15; break;
        case DR_REG_YMM0: return mc->ymm0; break;
        case DR_REG_YMM1: return mc->ymm1; break;
        case DR_REG_YMM2: return mc->ymm2; break;
        case DR_REG_YMM3: return mc->ymm3; break;
        case DR_REG_YMM4: return mc->ymm4; break;
        case DR_REG_YMM5: return mc->ymm5; break;
        case DR_REG_YMM6: return mc->ymm6; break;
        case DR_REG_YMM7: return mc->ymm7; break;
        case DR_REG_YMM8: return mc->ymm8; break;
        case DR_REG_YMM9: return mc->ymm9; break;
        case DR_REG_YMM10: return mc->ymm10; break;
        case DR_REG_YMM11: return mc->ymm11; break;
        case DR_REG_YMM12: return mc->ymm12; break;
        case DR_REG_YMM13: return mc->ymm13; break;
        case DR_REG_YMM14: return mc->ymm14; break;
        case DR_REG_YMM15: return mc->ymm15; break;
        case DR_REG_MM0: return mc->mm0; break;
        case DR_REG_MM1: return mc->mm1; break;
        case DR_REG_MM2: return mc->mm2; break;
        case DR_REG_MM3: return mc->mm3; break;
        case DR_REG_MM4: return mc->mm4; break;
        case DR_REG_MM5: return mc->mm5; break;
        case DR_REG_MM6: return mc->mm6; break;
        case DR_REG_MM7: return mc->mm7; break;
    */
#ifdef X64
#endif
#endif
#ifdef AARCHXX
  case DR_REG_R0:
    return mc->r0;
    break;
  case DR_REG_R1:
    return mc->r1;
    break;
  case DR_REG_R2:
    return mc->r2;
    break;
  case DR_REG_R3:
    return mc->r3;
    break;
  case DR_REG_R4:
    return mc->r4;
    break;
  case DR_REG_R5:
    return mc->r5;
    break;
  case DR_REG_R6:
    return mc->r6;
    break;
  case DR_REG_R7:
    return mc->r7;
    break;
  case DR_REG_R8:
    return mc->r8;
    break;
  case DR_REG_R9:
    return mc->r9;
    break;
  case DR_REG_R10:
    return mc->r10;
    break;
  case DR_REG_R11:
    return mc->r11;
    break;
  case DR_REG_R12:
    return mc->r12;
    break;
  case DR_REG_R13:
    return mc->r13;
    break;
  case DR_REG_R14:
    return mc->r14;
    break;
  case DR_REG_R15:
    return mc->r15;
    break;
#ifdef AARCH64
  case DR_REG_R16:
    return mc->r16;
    break;
  case DR_REG_R17:
    return mc->r17;
    break;
  case DR_REG_R18:
    return mc->r18;
    break;
  case DR_REG_R19:
    return mc->r19;
    break;
  case DR_REG_R20:
    return mc->r20;
    break;
  case DR_REG_R21:
    return mc->r21;
    break;
  case DR_REG_R22:
    return mc->r22;
    break;
  case DR_REG_R23:
    return mc->r23;
    break;
  case DR_REG_R24:
    return mc->r24;
    break;
  case DR_REG_R25:
    return mc->r25;
    break;
  case DR_REG_R26:
    return mc->r26;
    break;
  case DR_REG_R27:
    return mc->r27;
    break;
  case DR_REG_R28:
    return mc->r28;
    break;
  case DR_REG_R29:
    return mc->r29;
    break;
  case DR_REG_R30:
    return mc->r30;
    break;
  case DR_REG_R31:
    return mc->r31;
    break;
  case DR_REG_W0:
    return mc->w0;
    break;
  case DR_REG_W1:
    return mc->w1;
    break;
  case DR_REG_W2:
    return mc->w2;
    break;
  case DR_REG_W3:
    return mc->w3;
    break;
  case DR_REG_W4:
    return mc->w4;
    break;
  case DR_REG_W5:
    return mc->w5;
    break;
  case DR_REG_W6:
    return mc->w6;
    break;
  case DR_REG_W7:
    return mc->w7;
    break;
  case DR_REG_W8:
    return mc->w8;
    break;
  case DR_REG_W9:
    return mc->w9;
    break;
  case DR_REG_W10:
    return mc->w10;
    break;
  case DR_REG_W11:
    return mc->w11;
    break;
  case DR_REG_W12:
    return mc->w12;
    break;
  case DR_REG_W13:
    return mc->w13;
    break;
  case DR_REG_W14:
    return mc->w14;
    break;
  case DR_REG_W15:
    return mc->w15;
    break;
  case DR_REG_W16:
    return mc->w16;
    break;
  case DR_REG_W17:
    return mc->w17;
    break;
  case DR_REG_W18:
    return mc->w18;
    break;
  case DR_REG_W19:
    return mc->w19;
    break;
  case DR_REG_W20:
    return mc->w20;
    break;
  case DR_REG_W21:
    return mc->w21;
    break;
  case DR_REG_W22:
    return mc->w22;
    break;
  case DR_REG_W23:
    return mc->w23;
    break;
  case DR_REG_W24:
    return mc->w24;
    break;
  case DR_REG_W25:
    return mc->w25;
    break;
  case DR_REG_W26:
    return mc->w26;
    break;
  case DR_REG_W27:
    return mc->w27;
    break;
  case DR_REG_W28:
    return mc->w28;
    break;
  case DR_REG_W29:
    return mc->w29;
    break;
  case DR_REG_W30:
    return mc->w30;
    break;
  case DR_REG_W31:
    return mc->w31;
    break;
  case DR_REG_Q0:
    return mc->q0;
    break;
  case DR_REG_D0:
    return mc->d0;
    break;
  case DR_REG_S0:
    return mc->s0;
    break;
  case DR_REG_H0:
    return mc->h0;
    break;
  case DR_REG_B0:
    return mc->b0;
    break;
  case DR_REG_Q1:
    return mc->q1;
    break;
  case DR_REG_D1:
    return mc->d1;
    break;
  case DR_REG_S1:
    return mc->s1;
    break;
  case DR_REG_H1:
    return mc->h1;
    break;
  case DR_REG_B1:
    return mc->b1;
    break;
  case DR_REG_Q2:
    return mc->q2;
    break;
  case DR_REG_D2:
    return mc->d2;
    break;
  case DR_REG_S2:
    return mc->s2;
    break;
  case DR_REG_H2:
    return mc->h2;
    break;
  case DR_REG_B2:
    return mc->b2;
    break;
  case DR_REG_Q3:
    return mc->q3;
    break;
  case DR_REG_D3:
    return mc->d3;
    break;
  case DR_REG_S3:
    return mc->s3;
    break;
  case DR_REG_H3:
    return mc->h3;
    break;
  case DR_REG_B3:
    return mc->b3;
    break;
  case DR_REG_Q4:
    return mc->q4;
    break;
  case DR_REG_D4:
    return mc->d4;
    break;
  case DR_REG_S4:
    return mc->s4;
    break;
  case DR_REG_H4:
    return mc->h4;
    break;
  case DR_REG_B4:
    return mc->b4;
    break;
  case DR_REG_Q5:
    return mc->q5;
    break;
  case DR_REG_D5:
    return mc->d5;
    break;
  case DR_REG_S5:
    return mc->s5;
    break;
  case DR_REG_H5:
    return mc->h5;
    break;
  case DR_REG_B5:
    return mc->b5;
    break;
  case DR_REG_Q6:
    return mc->q6;
    break;
  case DR_REG_D6:
    return mc->d6;
    break;
  case DR_REG_S6:
    return mc->s6;
    break;
  case DR_REG_H6:
    return mc->h6;
    break;
  case DR_REG_B6:
    return mc->b6;
    break;
  case DR_REG_Q7:
    return mc->q7;
    break;
  case DR_REG_D7:
    return mc->d7;
    break;
  case DR_REG_S7:
    return mc->s7;
    break;
  case DR_REG_H7:
    return mc->h7;
    break;
  case DR_REG_B7:
    return mc->b7;
    break;
  case DR_REG_Q8:
    return mc->q8;
    break;
  case DR_REG_D8:
    return mc->d8;
    break;
  case DR_REG_S8:
    return mc->s8;
    break;
  case DR_REG_H8:
    return mc->h8;
    break;
  case DR_REG_B8:
    return mc->b8;
    break;
  case DR_REG_Q9:
    return mc->q9;
    break;
  case DR_REG_D9:
    return mc->d9;
    break;
  case DR_REG_S9:
    return mc->s9;
    break;
  case DR_REG_H9:
    return mc->h9;
    break;
  case DR_REG_B9:
    return mc->b9;
    break;
  case DR_REG_Q10:
    return mc->q10;
    break;
  case DR_REG_D10:
    return mc->d10;
    break;
  case DR_REG_S10:
    return mc->s10;
    break;
  case DR_REG_H10:
    return mc->h10;
    break;
  case DR_REG_B10:
    return mc->b10;
    break;
  case DR_REG_Q11:
    return mc->q11;
    break;
  case DR_REG_D11:
    return mc->d11;
    break;
  case DR_REG_S11:
    return mc->s11;
    break;
  case DR_REG_H11:
    return mc->h11;
    break;
  case DR_REG_B11:
    return mc->b11;
    break;
  case DR_REG_Q12:
    return mc->q12;
    break;
  case DR_REG_D12:
    return mc->d12;
    break;
  case DR_REG_S12:
    return mc->s12;
    break;
  case DR_REG_H12:
    return mc->h12;
    break;
  case DR_REG_B12:
    return mc->b12;
    break;
  case DR_REG_Q13:
    return mc->q13;
    break;
  case DR_REG_D13:
    return mc->d13;
    break;
  case DR_REG_S13:
    return mc->s13;
    break;
  case DR_REG_H13:
    return mc->h13;
    break;
  case DR_REG_B13:
    return mc->b13;
    break;
  case DR_REG_Q14:
    return mc->q14;
    break;
  case DR_REG_D14:
    return mc->d14;
    break;
  case DR_REG_S14:
    return mc->s14;
    break;
  case DR_REG_H14:
    return mc->h14;
    break;
  case DR_REG_B14:
    return mc->b14;
    break;
  case DR_REG_Q15:
    return mc->q15;
    break;
  case DR_REG_D15:
    return mc->d15;
    break;
  case DR_REG_S15:
    return mc->s15;
    break;
  case DR_REG_H15:
    return mc->h15;
    break;
  case DR_REG_B15:
    return mc->b15;
    break;
  case DR_REG_Q16:
    return mc->q16;
    break;
  case DR_REG_D16:
    return mc->d16;
    break;
  case DR_REG_S16:
    return mc->s16;
    break;
  case DR_REG_H16:
    return mc->h16;
    break;
  case DR_REG_B16:
    return mc->b16;
    break;
  case DR_REG_Q17:
    return mc->q17;
    break;
  case DR_REG_D17:
    return mc->d17;
    break;
  case DR_REG_S17:
    return mc->s17;
    break;
  case DR_REG_H17:
    return mc->h17;
    break;
  case DR_REG_B17:
    return mc->b17;
    break;
  case DR_REG_Q18:
    return mc->q18;
    break;
  case DR_REG_D18:
    return mc->d18;
    break;
  case DR_REG_S18:
    return mc->s18;
    break;
  case DR_REG_H18:
    return mc->h18;
    break;
  case DR_REG_B18:
    return mc->b18;
    break;
  case DR_REG_Q19:
    return mc->q19;
    break;
  case DR_REG_D19:
    return mc->d19;
    break;
  case DR_REG_S19:
    return mc->s19;
    break;
  case DR_REG_H19:
    return mc->h19;
    break;
  case DR_REG_B19:
    return mc->b19;
    break;
  case DR_REG_Q20:
    return mc->q20;
    break;
  case DR_REG_D20:
    return mc->d20;
    break;
  case DR_REG_S20:
    return mc->s20;
    break;
  case DR_REG_H20:
    return mc->h20;
    break;
  case DR_REG_B20:
    return mc->b20;
    break;
  case DR_REG_Q21:
    return mc->q21;
    break;
  case DR_REG_D21:
    return mc->d21;
    break;
  case DR_REG_S21:
    return mc->s21;
    break;
  case DR_REG_H21:
    return mc->h21;
    break;
  case DR_REG_B21:
    return mc->b21;
    break;
  case DR_REG_Q22:
    return mc->q22;
    break;
  case DR_REG_D22:
    return mc->d22;
    break;
  case DR_REG_S22:
    return mc->s22;
    break;
  case DR_REG_H22:
    return mc->h22;
    break;
  case DR_REG_B22:
    return mc->b22;
    break;
  case DR_REG_Q23:
    return mc->q23;
    break;
  case DR_REG_D23:
    return mc->d23;
    break;
  case DR_REG_S23:
    return mc->s23;
    break;
  case DR_REG_H23:
    return mc->h23;
    break;
  case DR_REG_B23:
    return mc->b23;
    break;
  case DR_REG_Q24:
    return mc->q24;
    break;
  case DR_REG_D24:
    return mc->d24;
    break;
  case DR_REG_S24:
    return mc->s24;
    break;
  case DR_REG_H24:
    return mc->h24;
    break;
  case DR_REG_B24:
    return mc->b24;
    break;
  case DR_REG_Q25:
    return mc->q25;
    break;
  case DR_REG_D25:
    return mc->d25;
    break;
  case DR_REG_S25:
    return mc->s25;
    break;
  case DR_REG_H25:
    return mc->h25;
    break;
  case DR_REG_B25:
    return mc->b25;
    break;
  case DR_REG_Q26:
    return mc->q26;
    break;
  case DR_REG_D26:
    return mc->d26;
    break;
  case DR_REG_S26:
    return mc->s26;
    break;
  case DR_REG_H26:
    return mc->h26;
    break;
  case DR_REG_B26:
    return mc->b26;
    break;
  case DR_REG_Q27:
    return mc->q27;
    break;
  case DR_REG_D27:
    return mc->d27;
    break;
  case DR_REG_S27:
    return mc->s27;
    break;
  case DR_REG_H27:
    return mc->h27;
    break;
  case DR_REG_B27:
    return mc->b27;
    break;
  case DR_REG_Q28:
    return mc->q28;
    break;
  case DR_REG_D28:
    return mc->d28;
    break;
  case DR_REG_S28:
    return mc->s28;
    break;
  case DR_REG_H28:
    return mc->h28;
    break;
  case DR_REG_B28:
    return mc->b28;
    break;
  case DR_REG_Q29:
    return mc->q29;
    break;
  case DR_REG_D29:
    return mc->d29;
    break;
  case DR_REG_S29:
    return mc->s29;
    break;
  case DR_REG_H29:
    return mc->h29;
    break;
  case DR_REG_B29:
    return mc->b29;
    break;
  case DR_REG_Q30:
    return mc->q30;
    break;
  case DR_REG_D30:
    return mc->d30;
    break;
  case DR_REG_S30:
    return mc->s30;
    break;
  case DR_REG_H30:
    return mc->h30;
    break;
  case DR_REG_B30:
    return mc->b30;
    break;
  case DR_REG_Q31:
    return mc->q31;
    break;
  case DR_REG_D31:
    return mc->d31;
    break;
  case DR_REG_S31:
    return mc->s31;
    break;
  case DR_REG_H31:
    return mc->h31;
    break;
  case DR_REG_B31:
    return mc->b31;
    break;
#endif
#endif
  default:
    return 0;
  }
}
