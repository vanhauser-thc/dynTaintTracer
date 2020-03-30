#ifndef _NUM_REG_H_
#define _NUM_REG_H_
const char *num2reg[]{"NULL",
#ifdef X86
                      "RAX",    "RCX",    "RDX", "RBX", "RSP", "RBP", "RSI",  "RDI",  "R8",   "R9",   "R10",  "R11",  "R12",  "R13",  "R14",  "R15",  "EAX",  "ECX",  "EDX", "EBX", "ESP", "EBP", "ESI", "EDI", "R8D",  "R9D",  "R10D", "R11D", "R12D", "R13D", "R14D", "R15D", "AX",   "CX",   "DX",      "BX",    "SP",    "BP",    "SI",    "DI",    "R8W",  "R9W",  "R10W", "R11W", "R12W", "R13W",  "R14W",  "R15W",  "AL",     "CL",     "DL",     "BL",
                      "AH",     "CH",     "DH",  "BH",  "R8L", "R9L", "R10L", "R11L", "R12L", "R13L", "R14L", "R15L", "SPL",  "BPL",  "SIL",  "DIL",  "MM0",  "MM1",  "MM2", "MM3", "MM4", "MM5", "MM6", "MM7", "XMM0", "XMM1", "XMM2", "XMM3", "XMM4", "XMM5", "XMM6", "XMM7", "XMM8", "XMM9", "XMM10",   "XMM11", "XMM12", "XMM13", "XMM14", "XMM15", "ST0",  "ST1",  "ST2",  "ST3",  "ST4",  "ST5",   "ST6",   "ST7",   "SEG_ES", "SEG_CS", "SEG_SS", "SEG_DS",
                      "SEG_FS", "SEG_GS", "DR0", "DR1", "DR2", "DR3", "DR4",  "DR5",  "DR6",  "DR7",  "DR8",  "DR9",  "DR10", "DR11", "DR12", "DR13", "DR14", "DR15", "CR0", "CR1", "CR2", "CR3", "CR4", "CR5", "CR6",  "CR7",  "CR8",  "CR9",  "CR10", "CR11", "CR12", "CR13", "CR14", "CR15", "INVALID", "YMM0",  "YMM1",  "YMM2",  "YMM3",  "YMM4",  "YMM5", "YMM6", "YMM7", "YMM8", "YMM9", "YMM10", "YMM11", "YMM12", "YMM13",  "YMM14",  "YMM15",
#elif defined(AARCHXX)
                      "INVALID",
#ifdef AARCH64
                      "X0",        "X1",          "X2",         "X3",         "X4",
                      "X5",        "X6",          "X7",         "X8",         "X9",
                      "X10",       "X11",         "X12",        "X13",        "X14",
                      "X15",       "X16",         "X17",        "X18",        "X19",
                      "X20",       "X21",         "X22",        "X23",        "X24",
                      "X25",       "X26",         "X27",        "X28",        "X29",
                      "X30",       "XSP",         "XZR",        "W0",         "W1",
                      "W2",        "W3",          "W4",         "W5",         "W6",
                      "W7",        "W8",          "W9",         "W10",        "W11",
                      "W12",       "W13",         "W14",        "W15",        "W16",
                      "W17",       "W18",         "W19",        "W20",        "W21",
                      "W22",       "W23",         "W24",        "W25",        "W26",
                      "W27",       "W28",         "W29",        "W30",        "WSP",
                      "WZR",
#else
                      "R0",        "R1",          "R2",         "R3",         "R4",
                      "R5",        "R6",          "R7",         "R8",         "R9",
                      "R10",       "R11",         "R12",        "R13",        "R14",
                      "R15",
#endif
                      "Q0",        "Q1",          "Q2",         "Q3",         "Q4",
                      "Q5",        "Q6",          "Q7",         "Q8",         "Q9",
                      "Q10",       "Q11",         "Q12",        "Q13",        "Q14",
                      "Q15",       "Q16",         "Q17",        "Q18",        "Q19",
                      "Q20",       "Q21",         "Q22",        "Q23",        "Q24",
                      "Q25",       "Q26",         "Q27",        "Q28",        "Q29",
                      "Q30",       "Q31",         "D0",         "D1",         "D2",
                      "D3",        "D4",          "D5",         "D6",         "D7",
                      "D8",        "D9",          "D10",        "D11",        "D12",
                      "D13",       "D14",         "D15",        "D16",        "D17",
                      "D18",       "D19",         "D20",        "D21",        "D22",
                      "D23",       "D24",         "D25",        "D26",        "D27",
                      "D28",       "D29",         "D30",        "D31",        "S0",
                      "S1",        "S2",          "S3",         "S4",         "S5",
                      "S6",        "S7",          "S8",         "S9",         "S10",
                      "S11",       "S12",         "S13",        "S14",        "S15",
                      "S16",       "S17",         "S18",        "S19",        "S20",
                      "S21",       "S22",         "S23",        "S24",        "S25",
                      "S26",       "S27",         "S28",        "S29",        "S30",
                      "S31",       "H0",          "H1",         "H2",         "H3",
                      "H4",        "H5",          "H6",         "H7",         "H8",
                      "H9",        "H10",         "H11",        "H12",        "H13",
                      "H14",       "H15",         "H16",        "H17",        "H18",
                      "H19",       "H20",         "H21",        "H22",        "H23",
                      "H24",       "H25",         "H26",        "H27",        "H28",
                      "H29",       "H30",         "H31",        "B0",         "B1",
                      "B2",        "B3",          "B4",         "B5",         "B6",
                      "B7",        "B8",          "B9",         "B10",        "B11",
                      "B12",       "B13",         "B14",        "B15",        "B16",
                      "B17",       "B18",         "B19",        "B20",        "B21",
                      "B22",       "B23",         "B24",        "B25",        "B26",
                      "B27",       "B28",         "B29",        "B30",        "B31",
#ifndef AARCH64
                      "CR0",       "CR1",         "CR2",        "CR3",        "CR4",
                      "CR5",       "CR6",         "CR7",        "CR8",        "CR9",
                      "CR10",      "CR11",        "CR12",       "CR13",       "CR14",
                      "CR15",
#endif
#ifdef AARCH64
                      "NZCV",      "FPCR",        "FPSR",
#else
                      "CPSR",      "SPSR",        "FPSCR",
#endif
                      "TPIDRURW",  "TPIDRURO",
#ifdef AARCH64
                      "R0",        "R1",          "R2",         "R3",         "R4",
                      "R5",        "R6",          "R7",         "R8",         "R9",
                      "R10",       "R11",         "R12",        "R13",        "R14",
                      "R15",       "R16",         "R17",        "R18",        "R19",
                      "R20",       "R21",         "R22",        "R23",        "R24",
                      "R25",       "R26",         "R27",        "R28",        "R29",
                      "R30",       "SP",          "LR",
#else
                      "SP",        "LR",          "PC",
#endif
                      "SL",        "FP",          "IP",
#ifndef AARCH64
                      "APSR",
#endif
                      "TPIDR_EL0", "TPIDRRO_EL0", "CP15_C13_2", "CP15_C13_3", "LAST_VALID_ENUM",
                      "LAST_ENUM",
#ifdef AARCH64
                      "START_64",  "STOP_64",     "START_32",   "STOP_32",    "START_GPR",
                      "STOP_GPR",
#else
                      "START_32",  "STOP_32",     "START_GPR",  "STOP_GPR",
#endif
                      "GPR_REGS",
#ifndef AARCH64
                      "XSP",
#endif
#endif
                      ""};
#endif
