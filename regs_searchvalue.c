#ifdef X86
if (mc.rax == bufptr)
  addTaintReg(DR_REG_AL);
if (mc.rbx == bufptr)
  addTaintReg(DR_REG_BL);
if (mc.rcx == bufptr)
  addTaintReg(DR_REG_CL);
if (mc.rdx == bufptr)
  addTaintReg(DR_REG_DL);
if (mc.rbp == bufptr)
  addTaintReg(DR_REG_BPL);
if (mc.rdi == bufptr)
  addTaintReg(DR_REG_DIL);
if (mc.rsi == bufptr)
  addTaintReg(DR_REG_SIL);
if (mc.r8 == bufptr)
  addTaintReg(DR_REG_R8L);
if (mc.r9 == bufptr)
  addTaintReg(DR_REG_R9L);
if (mc.r10 == bufptr)
  addTaintReg(DR_REG_R10L);
if (mc.r11 == bufptr)
  addTaintReg(DR_REG_R11L);
if (mc.r12 == bufptr)
  addTaintReg(DR_REG_R12L);
if (mc.r13 == bufptr)
  addTaintReg(DR_REG_R13L);
if (mc.r14 == bufptr)
  addTaintReg(DR_REG_R14L);
if (mc.r15 == bufptr)
  addTaintReg(DR_REG_R15L);
if (mc.xmm0 == bufptr)
  addTaintReg(DR_REG_XMM0);
if (mc.xmm1 == bufptr)
  addTaintReg(DR_REG_XMM1);
if (mc.xmm2 == bufptr)
  addTaintReg(DR_REG_XMM2);
if (mc.xmm3 == bufptr)
  addTaintReg(DR_REG_XMM3);
if (mc.xmm4 == bufptr)
  addTaintReg(DR_REG_XMM4);
if (mc.xmm5 == bufptr)
  addTaintReg(DR_REG_XMM5);
if (mc.xmm6 == bufptr)
  addTaintReg(DR_REG_XMM6);
if (mc.xmm7 == bufptr)
  addTaintReg(DR_REG_XMM7);
if (mc.xmm8 == bufptr)
  addTaintReg(DR_REG_XMM8);
if (mc.xmm9 == bufptr)
  addTaintReg(DR_REG_XMM9);
if (mc.xmm10 == bufptr)
  addTaintReg(DR_REG_XMM10);
if (mc.xmm11 == bufptr)
  addTaintReg(DR_REG_XMM11);
if (mc.xmm12 == bufptr)
  addTaintReg(DR_REG_XMM12);
if (mc.xmm13 == bufptr)
  addTaintReg(DR_REG_XMM13);
if (mc.xmm14 == bufptr)
  addTaintReg(DR_REG_XMM14);
if (mc.xmm15 == bufptr)
  addTaintReg(DR_REG_XMM15);
if (mc.ymm0 == bufptr)
  addTaintReg(DR_REG_YMM0);
if (mc.ymm1 == bufptr)
  addTaintReg(DR_REG_YMM1);
if (mc.ymm2 == bufptr)
  addTaintReg(DR_REG_YMM2);
if (mc.ymm3 == bufptr)
  addTaintReg(DR_REG_YMM3);
if (mc.ymm4 == bufptr)
  addTaintReg(DR_REG_YMM4);
if (mc.ymm5 == bufptr)
  addTaintReg(DR_REG_YMM5);
if (mc.ymm6 == bufptr)
  addTaintReg(DR_REG_YMM6);
if (mc.ymm7 == bufptr)
  addTaintReg(DR_REG_YMM7);
if (mc.ymm8 == bufptr)
  addTaintReg(DR_REG_YMM8);
if (mc.ymm9 == bufptr)
  addTaintReg(DR_REG_YMM9);
if (mc.ymm10 == bufptr)
  addTaintReg(DR_REG_YMM10);
if (mc.ymm11 == bufptr)
  addTaintReg(DR_REG_YMM11);
if (mc.ymm12 == bufptr)
  addTaintReg(DR_REG_YMM12);
if (mc.ymm13 == bufptr)
  addTaintReg(DR_REG_YMM13);
if (mc.ymm14 == bufptr)
  addTaintReg(DR_REG_YMM14);
if (mc.ymm15 == bufptr)
  addTaintReg(DR_REG_YMM15);
if (mc.mm0 == bufptr)
  addTaintReg(DR_REG_MM0);
if (mc.mm1 == bufptr)
  addTaintReg(DR_REG_MM1);
if (mc.mm2 == bufptr)
  addTaintReg(DR_REG_MM2);
if (mc.mm3 == bufptr)
  addTaintReg(DR_REG_MM3);
if (mc.mm4 == bufptr)
  addTaintReg(DR_REG_MM4);
if (mc.mm5 == bufptr)
  addTaintReg(DR_REG_MM5);
if (mc.mm6 == bufptr)
  addTaintReg(DR_REG_MM6);
if (mc.mm7 == bufptr)
  addTaintReg(DR_REG_MM7);
#ifdef X64
if (mc.rax == bufptr)
  addTaintReg(DR_REG_AL);
if (mc.rbx == bufptr)
  addTaintReg(DR_REG_BL);
if (mc.rcx == bufptr)
  addTaintReg(DR_REG_CL);
if (mc.rdx == bufptr)
  addTaintReg(DR_REG_DL);
if (mc.rbp == bufptr)
  addTaintReg(DR_REG_BPL);
if (mc.rdi == bufptr)
  addTaintReg(DR_REG_DIL);
if (mc.rsi == bufptr)
  addTaintReg(DR_REG_SIL);
if (mc.r8 == bufptr)
  addTaintReg(DR_REG_R8L);
if (mc.r9 == bufptr)
  addTaintReg(DR_REG_R9L);
if (mc.r10 == bufptr)
  addTaintReg(DR_REG_R10L);
if (mc.r11 == bufptr)
  addTaintReg(DR_REG_R11L);
if (mc.r12 == bufptr)
  addTaintReg(DR_REG_R12L);
if (mc.r13 == bufptr)
  addTaintReg(DR_REG_R13L);
if (mc.r14 == bufptr)
  addTaintReg(DR_REG_R14L);
if (mc.r15 == bufptr)
  addTaintReg(DR_REG_R15L);
if (mc.xmm0 == bufptr)
  addTaintReg(DR_REG_XMM0);
if (mc.xmm1 == bufptr)
  addTaintReg(DR_REG_XMM1);
if (mc.xmm2 == bufptr)
  addTaintReg(DR_REG_XMM2);
if (mc.xmm3 == bufptr)
  addTaintReg(DR_REG_XMM3);
if (mc.xmm4 == bufptr)
  addTaintReg(DR_REG_XMM4);
if (mc.xmm5 == bufptr)
  addTaintReg(DR_REG_XMM5);
if (mc.xmm6 == bufptr)
  addTaintReg(DR_REG_XMM6);
if (mc.xmm7 == bufptr)
  addTaintReg(DR_REG_XMM7);
if (mc.xmm8 == bufptr)
  addTaintReg(DR_REG_XMM8);
if (mc.xmm9 == bufptr)
  addTaintReg(DR_REG_XMM9);
if (mc.xmm10 == bufptr)
  addTaintReg(DR_REG_XMM10);
if (mc.xmm11 == bufptr)
  addTaintReg(DR_REG_XMM11);
if (mc.xmm12 == bufptr)
  addTaintReg(DR_REG_XMM12);
if (mc.xmm13 == bufptr)
  addTaintReg(DR_REG_XMM13);
if (mc.xmm14 == bufptr)
  addTaintReg(DR_REG_XMM14);
if (mc.xmm15 == bufptr)
  addTaintReg(DR_REG_XMM15);
if (mc.ymm0 == bufptr)
  addTaintReg(DR_REG_YMM0);
if (mc.ymm1 == bufptr)
  addTaintReg(DR_REG_YMM1);
if (mc.ymm2 == bufptr)
  addTaintReg(DR_REG_YMM2);
if (mc.ymm3 == bufptr)
  addTaintReg(DR_REG_YMM3);
if (mc.ymm4 == bufptr)
  addTaintReg(DR_REG_YMM4);
if (mc.ymm5 == bufptr)
  addTaintReg(DR_REG_YMM5);
if (mc.ymm6 == bufptr)
  addTaintReg(DR_REG_YMM6);
if (mc.ymm7 == bufptr)
  addTaintReg(DR_REG_YMM7);
if (mc.ymm8 == bufptr)
  addTaintReg(DR_REG_YMM8);
if (mc.ymm9 == bufptr)
  addTaintReg(DR_REG_YMM9);
if (mc.ymm10 == bufptr)
  addTaintReg(DR_REG_YMM10);
if (mc.ymm11 == bufptr)
  addTaintReg(DR_REG_YMM11);
if (mc.ymm12 == bufptr)
  addTaintReg(DR_REG_YMM12);
if (mc.ymm13 == bufptr)
  addTaintReg(DR_REG_YMM13);
if (mc.ymm14 == bufptr)
  addTaintReg(DR_REG_YMM14);
if (mc.ymm15 == bufptr)
  addTaintReg(DR_REG_YMM15);
if (mc.mm0 == bufptr)
  addTaintReg(DR_REG_MM0);
if (mc.mm1 == bufptr)
  addTaintReg(DR_REG_MM1);
if (mc.mm2 == bufptr)
  addTaintReg(DR_REG_MM2);
if (mc.mm3 == bufptr)
  addTaintReg(DR_REG_MM3);
if (mc.mm4 == bufptr)
  addTaintReg(DR_REG_MM4);
if (mc.mm5 == bufptr)
  addTaintReg(DR_REG_MM5);
if (mc.mm6 == bufptr)
  addTaintReg(DR_REG_MM6);
if (mc.mm7 == bufptr)
  addTaintReg(DR_REG_MM7);
#endif
#endif
#ifdef AARCHXX
if (mc.r0 == bufptr)
  addTaintReg(DR_REG_R0);
if (mc.r1 == bufptr)
  addTaintReg(DR_REG_R1);
if (mc.r2 == bufptr)
  addTaintReg(DR_REG_R2);
if (mc.r3 == bufptr)
  addTaintReg(DR_REG_R3);
if (mc.r4 == bufptr)
  addTaintReg(DR_REG_R4);
if (mc.r5 == bufptr)
  addTaintReg(DR_REG_R5);
if (mc.r6 == bufptr)
  addTaintReg(DR_REG_R6);
if (mc.r7 == bufptr)
  addTaintReg(DR_REG_R7);
if (mc.r8 == bufptr)
  addTaintReg(DR_REG_R8);
if (mc.r9 == bufptr)
  addTaintReg(DR_REG_R9);
if (mc.r10 == bufptr)
  addTaintReg(DR_REG_R10);
if (mc.r11 == bufptr)
  addTaintReg(DR_REG_R11);
if (mc.r12 == bufptr)
  addTaintReg(DR_REG_R12);
if (mc.r13 == bufptr)
  addTaintReg(DR_REG_R13);
if (mc.r14 == bufptr)
  addTaintReg(DR_REG_R14);
if (mc.r15 == bufptr)
  addTaintReg(DR_REG_R15);
#ifdef AARCH64
if (mc.r16 == bufptr)
  addTaintReg(DR_REG_R16);
if (mc.r17 == bufptr)
  addTaintReg(DR_REG_R17);
if (mc.r18 == bufptr)
  addTaintReg(DR_REG_R18);
if (mc.r19 == bufptr)
  addTaintReg(DR_REG_R19);
if (mc.r20 == bufptr)
  addTaintReg(DR_REG_R20);
if (mc.r21 == bufptr)
  addTaintReg(DR_REG_R21);
if (mc.r22 == bufptr)
  addTaintReg(DR_REG_R22);
if (mc.r23 == bufptr)
  addTaintReg(DR_REG_R23);
if (mc.r24 == bufptr)
  addTaintReg(DR_REG_R24);
if (mc.r25 == bufptr)
  addTaintReg(DR_REG_R25);
if (mc.r26 == bufptr)
  addTaintReg(DR_REG_R26);
if (mc.r27 == bufptr)
  addTaintReg(DR_REG_R27);
if (mc.r28 == bufptr)
  addTaintReg(DR_REG_R28);
if (mc.r29 == bufptr)
  addTaintReg(DR_REG_R29);
if (mc.r30 == bufptr)
  addTaintReg(DR_REG_R30);
if (mc.r31 == bufptr)
  addTaintReg(DR_REG_R31);
if (mc.w0 == bufptr)
  addTaintReg(DR_REG_W0);
if (mc.w1 == bufptr)
  addTaintReg(DR_REG_W1);
if (mc.w2 == bufptr)
  addTaintReg(DR_REG_W2);
if (mc.w3 == bufptr)
  addTaintReg(DR_REG_W3);
if (mc.w4 == bufptr)
  addTaintReg(DR_REG_W4);
if (mc.w5 == bufptr)
  addTaintReg(DR_REG_W5);
if (mc.w6 == bufptr)
  addTaintReg(DR_REG_W6);
if (mc.w7 == bufptr)
  addTaintReg(DR_REG_W7);
if (mc.w8 == bufptr)
  addTaintReg(DR_REG_W8);
if (mc.w9 == bufptr)
  addTaintReg(DR_REG_W9);
if (mc.w10 == bufptr)
  addTaintReg(DR_REG_W10);
if (mc.w11 == bufptr)
  addTaintReg(DR_REG_W11);
if (mc.w12 == bufptr)
  addTaintReg(DR_REG_W12);
if (mc.w13 == bufptr)
  addTaintReg(DR_REG_W13);
if (mc.w14 == bufptr)
  addTaintReg(DR_REG_W14);
if (mc.w15 == bufptr)
  addTaintReg(DR_REG_W15);
if (mc.w16 == bufptr)
  addTaintReg(DR_REG_W16);
if (mc.w17 == bufptr)
  addTaintReg(DR_REG_W17);
if (mc.w18 == bufptr)
  addTaintReg(DR_REG_W18);
if (mc.w19 == bufptr)
  addTaintReg(DR_REG_W19);
if (mc.w20 == bufptr)
  addTaintReg(DR_REG_W20);
if (mc.w21 == bufptr)
  addTaintReg(DR_REG_W21);
if (mc.w22 == bufptr)
  addTaintReg(DR_REG_W22);
if (mc.w23 == bufptr)
  addTaintReg(DR_REG_W23);
if (mc.w24 == bufptr)
  addTaintReg(DR_REG_W24);
if (mc.w25 == bufptr)
  addTaintReg(DR_REG_W25);
if (mc.w26 == bufptr)
  addTaintReg(DR_REG_W26);
if (mc.w27 == bufptr)
  addTaintReg(DR_REG_W27);
if (mc.w28 == bufptr)
  addTaintReg(DR_REG_W28);
if (mc.w29 == bufptr)
  addTaintReg(DR_REG_W29);
if (mc.w30 == bufptr)
  addTaintReg(DR_REG_W30);
if (mc.w31 == bufptr)
  addTaintReg(DR_REG_W31);
if (mc.q0 == bufptr)
  addTaintReg(DR_REG_Q0);
if (mc.d0 == bufptr)
  addTaintReg(DR_REG_D0);
if (mc.s0 == bufptr)
  addTaintReg(DR_REG_S0);
if (mc.h0 == bufptr)
  addTaintReg(DR_REG_H0);
if (mc.b0 == bufptr)
  addTaintReg(DR_REG_B0);
if (mc.q1 == bufptr)
  addTaintReg(DR_REG_Q1);
if (mc.d1 == bufptr)
  addTaintReg(DR_REG_D1);
if (mc.s1 == bufptr)
  addTaintReg(DR_REG_S1);
if (mc.h1 == bufptr)
  addTaintReg(DR_REG_H1);
if (mc.b1 == bufptr)
  addTaintReg(DR_REG_B1);
if (mc.q2 == bufptr)
  addTaintReg(DR_REG_Q2);
if (mc.d2 == bufptr)
  addTaintReg(DR_REG_D2);
if (mc.s2 == bufptr)
  addTaintReg(DR_REG_S2);
if (mc.h2 == bufptr)
  addTaintReg(DR_REG_H2);
if (mc.b2 == bufptr)
  addTaintReg(DR_REG_B2);
if (mc.q3 == bufptr)
  addTaintReg(DR_REG_Q3);
if (mc.d3 == bufptr)
  addTaintReg(DR_REG_D3);
if (mc.s3 == bufptr)
  addTaintReg(DR_REG_S3);
if (mc.h3 == bufptr)
  addTaintReg(DR_REG_H3);
if (mc.b3 == bufptr)
  addTaintReg(DR_REG_B3);
if (mc.q4 == bufptr)
  addTaintReg(DR_REG_Q4);
if (mc.d4 == bufptr)
  addTaintReg(DR_REG_D4);
if (mc.s4 == bufptr)
  addTaintReg(DR_REG_S4);
if (mc.h4 == bufptr)
  addTaintReg(DR_REG_H4);
if (mc.b4 == bufptr)
  addTaintReg(DR_REG_B4);
if (mc.q5 == bufptr)
  addTaintReg(DR_REG_Q5);
if (mc.d5 == bufptr)
  addTaintReg(DR_REG_D5);
if (mc.s5 == bufptr)
  addTaintReg(DR_REG_S5);
if (mc.h5 == bufptr)
  addTaintReg(DR_REG_H5);
if (mc.b5 == bufptr)
  addTaintReg(DR_REG_B5);
if (mc.q6 == bufptr)
  addTaintReg(DR_REG_Q6);
if (mc.d6 == bufptr)
  addTaintReg(DR_REG_D6);
if (mc.s6 == bufptr)
  addTaintReg(DR_REG_S6);
if (mc.h6 == bufptr)
  addTaintReg(DR_REG_H6);
if (mc.b6 == bufptr)
  addTaintReg(DR_REG_B6);
if (mc.q7 == bufptr)
  addTaintReg(DR_REG_Q7);
if (mc.d7 == bufptr)
  addTaintReg(DR_REG_D7);
if (mc.s7 == bufptr)
  addTaintReg(DR_REG_S7);
if (mc.h7 == bufptr)
  addTaintReg(DR_REG_H7);
if (mc.b7 == bufptr)
  addTaintReg(DR_REG_B7);
if (mc.q8 == bufptr)
  addTaintReg(DR_REG_Q8);
if (mc.d8 == bufptr)
  addTaintReg(DR_REG_D8);
if (mc.s8 == bufptr)
  addTaintReg(DR_REG_S8);
if (mc.h8 == bufptr)
  addTaintReg(DR_REG_H8);
if (mc.b8 == bufptr)
  addTaintReg(DR_REG_B8);
if (mc.q9 == bufptr)
  addTaintReg(DR_REG_Q9);
if (mc.d9 == bufptr)
  addTaintReg(DR_REG_D9);
if (mc.s9 == bufptr)
  addTaintReg(DR_REG_S9);
if (mc.h9 == bufptr)
  addTaintReg(DR_REG_H9);
if (mc.b9 == bufptr)
  addTaintReg(DR_REG_B9);
if (mc.q10 == bufptr)
  addTaintReg(DR_REG_Q10);
if (mc.d10 == bufptr)
  addTaintReg(DR_REG_D10);
if (mc.s10 == bufptr)
  addTaintReg(DR_REG_S10);
if (mc.h10 == bufptr)
  addTaintReg(DR_REG_H10);
if (mc.b10 == bufptr)
  addTaintReg(DR_REG_B10);
if (mc.q11 == bufptr)
  addTaintReg(DR_REG_Q11);
if (mc.d11 == bufptr)
  addTaintReg(DR_REG_D11);
if (mc.s11 == bufptr)
  addTaintReg(DR_REG_S11);
if (mc.h11 == bufptr)
  addTaintReg(DR_REG_H11);
if (mc.b11 == bufptr)
  addTaintReg(DR_REG_B11);
if (mc.q12 == bufptr)
  addTaintReg(DR_REG_Q12);
if (mc.d12 == bufptr)
  addTaintReg(DR_REG_D12);
if (mc.s12 == bufptr)
  addTaintReg(DR_REG_S12);
if (mc.h12 == bufptr)
  addTaintReg(DR_REG_H12);
if (mc.b12 == bufptr)
  addTaintReg(DR_REG_B12);
if (mc.q13 == bufptr)
  addTaintReg(DR_REG_Q13);
if (mc.d13 == bufptr)
  addTaintReg(DR_REG_D13);
if (mc.s13 == bufptr)
  addTaintReg(DR_REG_S13);
if (mc.h13 == bufptr)
  addTaintReg(DR_REG_H13);
if (mc.b13 == bufptr)
  addTaintReg(DR_REG_B13);
if (mc.q14 == bufptr)
  addTaintReg(DR_REG_Q14);
if (mc.d14 == bufptr)
  addTaintReg(DR_REG_D14);
if (mc.s14 == bufptr)
  addTaintReg(DR_REG_S14);
if (mc.h14 == bufptr)
  addTaintReg(DR_REG_H14);
if (mc.b14 == bufptr)
  addTaintReg(DR_REG_B14);
if (mc.q15 == bufptr)
  addTaintReg(DR_REG_Q15);
if (mc.d15 == bufptr)
  addTaintReg(DR_REG_D15);
if (mc.s15 == bufptr)
  addTaintReg(DR_REG_S15);
if (mc.h15 == bufptr)
  addTaintReg(DR_REG_H15);
if (mc.b15 == bufptr)
  addTaintReg(DR_REG_B15);
if (mc.q16 == bufptr)
  addTaintReg(DR_REG_Q16);
if (mc.d16 == bufptr)
  addTaintReg(DR_REG_D16);
if (mc.s16 == bufptr)
  addTaintReg(DR_REG_S16);
if (mc.h16 == bufptr)
  addTaintReg(DR_REG_H16);
if (mc.b16 == bufptr)
  addTaintReg(DR_REG_B16);
if (mc.q17 == bufptr)
  addTaintReg(DR_REG_Q17);
if (mc.d17 == bufptr)
  addTaintReg(DR_REG_D17);
if (mc.s17 == bufptr)
  addTaintReg(DR_REG_S17);
if (mc.h17 == bufptr)
  addTaintReg(DR_REG_H17);
if (mc.b17 == bufptr)
  addTaintReg(DR_REG_B17);
if (mc.q18 == bufptr)
  addTaintReg(DR_REG_Q18);
if (mc.d18 == bufptr)
  addTaintReg(DR_REG_D18);
if (mc.s18 == bufptr)
  addTaintReg(DR_REG_S18);
if (mc.h18 == bufptr)
  addTaintReg(DR_REG_H18);
if (mc.b18 == bufptr)
  addTaintReg(DR_REG_B18);
if (mc.q19 == bufptr)
  addTaintReg(DR_REG_Q19);
if (mc.d19 == bufptr)
  addTaintReg(DR_REG_D19);
if (mc.s19 == bufptr)
  addTaintReg(DR_REG_S19);
if (mc.h19 == bufptr)
  addTaintReg(DR_REG_H19);
if (mc.b19 == bufptr)
  addTaintReg(DR_REG_B19);
if (mc.q20 == bufptr)
  addTaintReg(DR_REG_Q20);
if (mc.d20 == bufptr)
  addTaintReg(DR_REG_D20);
if (mc.s20 == bufptr)
  addTaintReg(DR_REG_S20);
if (mc.h20 == bufptr)
  addTaintReg(DR_REG_H20);
if (mc.b20 == bufptr)
  addTaintReg(DR_REG_B20);
if (mc.q21 == bufptr)
  addTaintReg(DR_REG_Q21);
if (mc.d21 == bufptr)
  addTaintReg(DR_REG_D21);
if (mc.s21 == bufptr)
  addTaintReg(DR_REG_S21);
if (mc.h21 == bufptr)
  addTaintReg(DR_REG_H21);
if (mc.b21 == bufptr)
  addTaintReg(DR_REG_B21);
if (mc.q22 == bufptr)
  addTaintReg(DR_REG_Q22);
if (mc.d22 == bufptr)
  addTaintReg(DR_REG_D22);
if (mc.s22 == bufptr)
  addTaintReg(DR_REG_S22);
if (mc.h22 == bufptr)
  addTaintReg(DR_REG_H22);
if (mc.b22 == bufptr)
  addTaintReg(DR_REG_B22);
if (mc.q23 == bufptr)
  addTaintReg(DR_REG_Q23);
if (mc.d23 == bufptr)
  addTaintReg(DR_REG_D23);
if (mc.s23 == bufptr)
  addTaintReg(DR_REG_S23);
if (mc.h23 == bufptr)
  addTaintReg(DR_REG_H23);
if (mc.b23 == bufptr)
  addTaintReg(DR_REG_B23);
if (mc.q24 == bufptr)
  addTaintReg(DR_REG_Q24);
if (mc.d24 == bufptr)
  addTaintReg(DR_REG_D24);
if (mc.s24 == bufptr)
  addTaintReg(DR_REG_S24);
if (mc.h24 == bufptr)
  addTaintReg(DR_REG_H24);
if (mc.b24 == bufptr)
  addTaintReg(DR_REG_B24);
if (mc.q25 == bufptr)
  addTaintReg(DR_REG_Q25);
if (mc.d25 == bufptr)
  addTaintReg(DR_REG_D25);
if (mc.s25 == bufptr)
  addTaintReg(DR_REG_S25);
if (mc.h25 == bufptr)
  addTaintReg(DR_REG_H25);
if (mc.b25 == bufptr)
  addTaintReg(DR_REG_B25);
if (mc.q26 == bufptr)
  addTaintReg(DR_REG_Q26);
if (mc.d26 == bufptr)
  addTaintReg(DR_REG_D26);
if (mc.s26 == bufptr)
  addTaintReg(DR_REG_S26);
if (mc.h26 == bufptr)
  addTaintReg(DR_REG_H26);
if (mc.b26 == bufptr)
  addTaintReg(DR_REG_B26);
if (mc.q27 == bufptr)
  addTaintReg(DR_REG_Q27);
if (mc.d27 == bufptr)
  addTaintReg(DR_REG_D27);
if (mc.s27 == bufptr)
  addTaintReg(DR_REG_S27);
if (mc.h27 == bufptr)
  addTaintReg(DR_REG_H27);
if (mc.b27 == bufptr)
  addTaintReg(DR_REG_B27);
if (mc.q28 == bufptr)
  addTaintReg(DR_REG_Q28);
if (mc.d28 == bufptr)
  addTaintReg(DR_REG_D28);
if (mc.s28 == bufptr)
  addTaintReg(DR_REG_S28);
if (mc.h28 == bufptr)
  addTaintReg(DR_REG_H28);
if (mc.b28 == bufptr)
  addTaintReg(DR_REG_B28);
if (mc.q29 == bufptr)
  addTaintReg(DR_REG_Q29);
if (mc.d29 == bufptr)
  addTaintReg(DR_REG_D29);
if (mc.s29 == bufptr)
  addTaintReg(DR_REG_S29);
if (mc.h29 == bufptr)
  addTaintReg(DR_REG_H29);
if (mc.b29 == bufptr)
  addTaintReg(DR_REG_B29);
if (mc.q30 == bufptr)
  addTaintReg(DR_REG_Q30);
if (mc.d30 == bufptr)
  addTaintReg(DR_REG_D30);
if (mc.s30 == bufptr)
  addTaintReg(DR_REG_S30);
if (mc.h30 == bufptr)
  addTaintReg(DR_REG_H30);
if (mc.b30 == bufptr)
  addTaintReg(DR_REG_B30);
if (mc.q31 == bufptr)
  addTaintReg(DR_REG_Q31);
if (mc.d31 == bufptr)
  addTaintReg(DR_REG_D31);
if (mc.s31 == bufptr)
  addTaintReg(DR_REG_S31);
if (mc.h31 == bufptr)
  addTaintReg(DR_REG_H31);
if (mc.b31 == bufptr)
  addTaintReg(DR_REG_B31);
#endif
#endif
