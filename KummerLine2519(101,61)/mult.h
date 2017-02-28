#ifndef MULT_H_
#define MULT_H_

#define ADD(C,A,B) {C = A+B;}
#define SUB(C,A,B) {C = A-B;}
#define MULT(C,A,B) {C = A*B;}
#define SHIFTL(C,A,B) {C = A << (B);}
#define SHIFTR(C,A,B) {C = A >> (B);}
#define AND(C,A,B) {C = A & B;}


u64 MULT2S0,MULT2T0,MULT2U0; 
u64 MULT3S1,MULT3T1,MULT3U1,MULT3U2;
u64 MULT5S1,MULT5S2,MULT5T1,MULT5T2,MULT5U0,MULT5U1,MULT5U2,MULT5U3,MULT5U4;
u64 MULT9S1,MULT9S2,MULT9S3,MULT9S4,MULT9T1,MULT9T2,MULT9T3,MULT9T4,MULT9U0,MULT9U1,MULT9U2,MULT9U3,MULT9U4,MULT9U5,MULT9U6,MULT9U7,MULT9U8;
u64 SQ4S0,SQ4T0,SQ4U0,SQ4U1,SQ4U2;
u64 SQ5U0,SQ5U1,SQ5U2,SQ5U3,SQ5U4;
u64 SQ9U0,SQ9U1,SQ9U2,SQ9U3,SQ9U4,SQ9U5,SQ9U6,SQ9U7,SQ9U8;

#define MULT2(C0,C1,C2,F0,F1,G0,G1){ \
	MULT(C0,F0,G0); MULT(MULT2S0,F0,G1); MULT(C2,F1,G1); MULT(MULT2T0,F1,G0); \
	ADD(C1,MULT2S0,MULT2T0); \
}

#define ModifiedMULT2(C1,C2,F0,F1,G0,G1,C0){ \
	MULT(MULT2S0,F0,G1); MULT(C2,F1,G1); MULT(MULT2T0,F1,G0); \
	ADD(C1,MULT2S0,MULT2T0); \
}

#define MULT2Karatsuba(C0,C1,C2,F0,F1,G0,G1){ \
	MULT(C0,F0,G0); \
	MULT(C2,F1,G1); \
	ADD(MULT2S0,F0,F1); \
	ADD(MULT2T0,G0,G1); \
	MULT(MULT2U0,MULT2S0,MULT2T0); \
	SUB(MULT2U0,MULT2U0,C0); \
	SUB(MULT2U0,MULT2U0,C2); \
	C1=MULT2U0; \
}

#define ModifiedMULT2Karatsuba(C1,C2,F0,F1,G0,G1,C0){ /* C0=F0*G0 is provided as input */ \
	MULT(C2,F1,G1); \
	ADD(MULT2S0,F0,F1); \
	ADD(MULT2T0,G0,G1); \
	MULT(MULT2U0,MULT2S0,MULT2T0); \
	SUB(MULT2U0,MULT2U0,C0); \
	SUB(MULT2U0,MULT2U0,C2); \
	C1=MULT2U0; \
}

#define MULT3(C0,C1,C2,C3,C4,F0,F1,F2,G0,G1,G2){ \
	MULT(C0,F0,G0); \
	MULT2(C2,C3,C4,F1,F2,G1,G2); \
	ADD(MULT3S1,F0,F2); \
	ADD(MULT3T1,G0,G2); \
	ModifiedMULT2(MULT3U1,MULT3U2,F1,MULT3S1,G1,MULT3T1,C2); \
	SUB(MULT3U1,MULT3U1,C3); SUB(MULT3U2,MULT3U2,C4); SUB(MULT3U2,MULT3U2,C0); \
	C1 = MULT3U1; ADD(C2,C2,MULT3U2); \
}

#define ModifiedMULT3(C1,C2,C3,C4,F0,F1,F2,G0,G1,G2,C0){ /* C0=F0*G0 is provided as input */ \
	MULT2(C2,C3,C4,F1,F2,G1,G2); \
	ADD(MULT3S1,F0,F2); \
	ADD(MULT3T1,G0,G2); \
	ModifiedMULT2(MULT3U1,MULT3U2,F1,MULT3S1,G1,MULT3T1,C2); \
	SUB(MULT3U1,MULT3U1,C3); SUB(MULT3U2,MULT3U2,C4); SUB(MULT3U2,MULT3U2,C0); \
	C1 = MULT3U1; ADD(C2,C2,MULT3U2); \
}

#define MULT4(C0,C1,C2,C3,C4,C5,C6,F0,F1,F2,F3,G0,G1,G2,G3) { /* internal vars for MULT5 are used */ \
	MULT2(C0,C1,C2,F0,F1,G0,G1); \
	MULT2(C4,C5,C6,F2,F3,G2,G3);; \
	ADD(MULT5S1,F0,F2); ADD(MULT5S2,F1,F3); \
	ADD(MULT5T1,G0,G2); ADD(MULT5T2,G1,G3); \
	MULT2(MULT5U1,MULT5U2,MULT5U3,MULT5S1,MULT5S2,MULT5T1,MULT5T2); \
	SUB(MULT5U1,MULT5U1,C0); SUB(MULT5U2,MULT5U2,C1); SUB(MULT5U3,MULT5U3,C2); \
	SUB(MULT5U1,MULT5U1,C4); SUB(MULT5U2,MULT5U2,C5); SUB(MULT5U3,MULT5U3,C6); \
	ADD(C2,C2,MULT5U1); C3=MULT5U2; ADD(C4,C4,MULT5U3); \
}

#define MULT5Hybrid(C0,C1,C2,C3,C4,C5,C6,C7,C8,F0,F1,F2,F3,F4,G0,G1,G2,G3,G4) { \
	MULT2(C0,C1,C2,F0,F1,G0,G1); \
	MULT2(C4,C5,C6,F2,F3,G2,G3); \
	ADD(MULT5S1,F0,F2); ADD(MULT5S2,F1,F3); ADD(MULT5T1,G0,G2); ADD(MULT5T2,G1,G3); \
	MULT2(MULT5U0,MULT5U1,MULT5U2,MULT5S1,MULT5S2,MULT5T1,MULT5T2); \
	SUB(MULT5U0,MULT5U0,C0); SUB(MULT5U0,MULT5U0,C4); \
	SUB(MULT5U1,MULT5U1,C1); SUB(MULT5U1,MULT5U1,C5); \
	SUB(MULT5U2,MULT5U2,C2); SUB(MULT5U2,MULT5U2,C6); \
	ADD(C2,C2,MULT5U0); C3=MULT5U1; ADD(C4,C4,MULT5U2); \
	MULT(MULT5U0,F4,G0); MULT(MULT5U1,F4,G1); MULT(MULT5U2,F4,G2); MULT(MULT5U3,F4,G3); MULT(MULT5U4,F4,G4); \
	MULT(MULT5S1,G4,F0); MULT(MULT5S2,G4,F1); MULT(MULT5T1,G4,F2); MULT(MULT5T2,G4,F3); \
	ADD(MULT5U0,MULT5U0,MULT5S1); ADD(MULT5U1,MULT5U1,MULT5S2); ADD(MULT5U2,MULT5U2,MULT5T1); ADD(MULT5U3,MULT5U3,MULT5T2); \
	ADD(C4,C4,MULT5U0); ADD(C5,C5,MULT5U1); ADD(C6,C6,MULT5U2); \
	C7=MULT5U3; C8=MULT5U4; \
}

#define ModifiedMULT5Hybrid(C1,C2,C3,C4,C5,C6,C7,C8,F0,F1,F2,F3,F4,G0,G1,G2,G3,G4,C0) { \
	ModifiedMULT2(C1,C2,F0,F1,G0,G1,C0); \
	MULT2(C4,C5,C6,F2,F3,G2,G3); \
	ADD(MULT5S1,F0,F2); ADD(MULT5S2,F1,F3); ADD(MULT5T1,G0,G2); ADD(MULT5T2,G1,G3); \
	MULT2(MULT5U0,MULT5U1,MULT5U2,MULT5S1,MULT5S2,MULT5T1,MULT5T2); \
	SUB(MULT5U0,MULT5U0,C0); SUB(MULT5U0,MULT5U0,C4); \
	SUB(MULT5U1,MULT5U1,C1); SUB(MULT5U1,MULT5U1,C5); \
	SUB(MULT5U2,MULT5U2,C2); SUB(MULT5U2,MULT5U2,C6); \
	ADD(C2,C2,MULT5U0); C3=MULT5U1; ADD(C4,C4,MULT5U2); \
	MULT(MULT5U0,F4,G0); MULT(MULT5U1,F4,G1); MULT(MULT5U2,F4,G2); MULT(MULT5U3,F4,G3); MULT(MULT5U4,F4,G4); \
	MULT(MULT5S1,G4,F0); MULT(MULT5S2,G4,F1); MULT(MULT5T1,G4,F2); MULT(MULT5T2,G4,F3); \
	ADD(MULT5U0,MULT5U0,MULT5S1); ADD(MULT5U1,MULT5U1,MULT5S2); ADD(MULT5U2,MULT5U2,MULT5T1); ADD(MULT5U3,MULT5U3,MULT5T2); \
	ADD(C4,C4,MULT5U0); ADD(C5,C5,MULT5U1); ADD(C6,C6,MULT5U2); \
	C7=MULT5U3; C8=MULT5U4; \
}

#define MULT5(C0,C1,C2,C3,C4,C5,C6,C7,C8,F0,F1,F2,F3,F4,G0,G1,G2,G3,G4) { \
	MULT2(C0,C1,C2,F0,F1,G0,G1) \
	MULT3(C4,C5,C6,C7,C8,F2,F3,F4,G2,G3,G4); \
	ADD(MULT5S1,F0,F3); ADD(MULT5S2,F1,F4); ADD(MULT5T1,G0,G3); ADD(MULT5T2,G1,G4); \
	ModifiedMULT3(MULT5U1,MULT5U2,MULT5U3,MULT5U4,F2,MULT5S1,MULT5S2,G2,MULT5T1,MULT5T2,C4); \
	SUB(MULT5U1,MULT5U1,C5); SUB(MULT5U2,MULT5U2,C6); SUB(MULT5U3,MULT5U3,C7); SUB(MULT5U4,MULT5U4,C8); \
	SUB(MULT5U2,MULT5U2,C0); SUB(MULT5U3,MULT5U3,C1); SUB(MULT5U4,MULT5U4,C2); \
	ADD(C2,C2,MULT5U1); C3 = MULT5U2; ADD(C4,C4,MULT5U3); ADD(C5,C5,MULT5U4); \
}

#define ModifiedMULT5(C1,C2,C3,C4,C5,C6,C7,C8,F0,F1,F2,F3,F4,G0,G1,G2,G3,G4,C0) { \
	ModifiedMULT2(C1,C2,F0,F1,G0,G1,C0) \
	MULT3(C4,C5,C6,C7,C8,F2,F3,F4,G2,G3,G4); \
	ADD(MULT5S1,F0,F3); ADD(MULT5S2,F1,F4); ADD(MULT5T1,G0,G3); ADD(MULT5T2,G1,G4); \
	ModifiedMULT3(MULT5U1,MULT5U2,MULT5U3,MULT5U4,F2,MULT5S1,MULT5S2,G2,MULT5T1,MULT5T2,C4); \
	SUB(MULT5U1,MULT5U1,C5); SUB(MULT5U2,MULT5U2,C6); SUB(MULT5U3,MULT5U3,C7); SUB(MULT5U4,MULT5U4,C8); \
	SUB(MULT5U2,MULT5U2,C0); SUB(MULT5U3,MULT5U3,C1); SUB(MULT5U4,MULT5U4,C2); \
	ADD(C2,C2,MULT5U1); C3 = MULT5U2; ADD(C4,C4,MULT5U3); ADD(C5,C5,MULT5U4); \
}

#define MULT9(C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16,F0,F1,F2,F3,F4,F5,F6,F7,F8,G0,G1,G2,G3,G4,G5,G6,G7,G8) { \
	MULT4(C0,C1,C2,C3,C4,C5,C6,F0,F1,F2,F3,G0,G1,G2,G3); \
	MULT4(C8,C9,C10,C11,C12,C13,C14,F4,F5,F6,F7,G4,G5,G6,G7); \
	ADD(MULT9S1,F0,F4); ADD(MULT9S2,F1,F5); ADD(MULT9S3,F2,F6); ADD(MULT9S4,F3,F7); \
	ADD(MULT9T1,G0,G4); ADD(MULT9T2,G1,G5); ADD(MULT9T3,G2,G6); ADD(MULT9T4,G3,G7); \
	MULT4(MULT9U1,MULT9U2,MULT9U3,MULT9U4,MULT9U5,MULT9U6,MULT9U7,MULT9S1,MULT9S2,MULT9S3,MULT9S4,MULT9T1,MULT9T2,MULT9T3,MULT9T4); \
	SUB(MULT9U1,MULT9U1,C0); SUB(MULT9U2,MULT9U2,C1); SUB(MULT9U3,MULT9U3,C2); SUB(MULT9U4,MULT9U4,C3); SUB(MULT9U5,MULT9U5,C4); SUB(MULT9U6,MULT9U6,C5); SUB(MULT9U7,MULT9U7,C6); \
	SUB(MULT9U1,MULT9U1,C8); SUB(MULT9U2,MULT9U2,C9); SUB(MULT9U3,MULT9U3,C10); SUB(MULT9U4,MULT9U4,C11); SUB(MULT9U5,MULT9U5,C12); SUB(MULT9U6,MULT9U6,C13); SUB(MULT9U7,MULT9U7,C14); \
	ADD(C4,C4,MULT9U1); ADD(C5,C5,MULT9U2); ADD(C6,C6,MULT9U3); C7=MULT9U4; ADD(C8,C8,MULT9U5); ADD(C9,C9,MULT9U6); ADD(C10,C10,MULT9U7); \
	MULT(MULT9U0,F8,G0); MULT(MULT9U1,F8,G1); MULT(MULT9U2,F8,G2); MULT(MULT9U3,F8,G3); MULT(MULT9U4,F8,G4); \
	MULT(MULT9U5,F8,G5); MULT(MULT9U6,F8,G6); MULT(MULT9U7,F8,G7); MULT(MULT9U8,F8,G8); \
	MULT(MULT9S1,G8,F0); MULT(MULT9S2,G8,F1); MULT(MULT9S3,G8,F2); MULT(MULT9S4,G8,F3); \
	MULT(MULT9T1,G8,F4); MULT(MULT9T2,G8,F5); MULT(MULT9T3,G8,F6); MULT(MULT9T4,G8,F7); \
	ADD(MULT9U0,MULT9U0,MULT9S1); ADD(MULT9U1,MULT9U1,MULT9S2); ADD(MULT9U2,MULT9U2,MULT9S3); ADD(MULT9U3,MULT9U3,MULT9S4); \
	ADD(MULT9U4,MULT9U4,MULT9T1); ADD(MULT9U5,MULT9U5,MULT9T2); ADD(MULT9U6,MULT9U6,MULT9T3); ADD(MULT9U7,MULT9U7,MULT9T4); \
	ADD(C8,C8,MULT9U0); ADD(C9,C9,MULT9U1); ADD(C10,C10,MULT9U2); ADD(C11,C11,MULT9U3); \
	ADD(C12,C12,MULT9U4); ADD(C13,C13,MULT9U5); ADD(C14,C14,MULT9U6); \
	C15 = MULT9U7; C16 = MULT9U8; \
}

#define MULT9Montgomery(C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16,F0,F1,F2,F3,F4,F5,F6,F7,F8,G0,G1,G2,G3,G4,G5,G6,G7,G8) { \
	MULT4(C0,C1,C2,C3,C4,C5,C6,F0,F1,F2,F3,G0,G1,G2,G3); \
	MULT5(C8,C9,C10,C11,C12,C13,C14,C15,C16,F4,F5,F6,F7,F8,G4,G5,G6,G7,G8); \
	ADD(MULT9S1,F0,F5); ADD(MULT9S2,F1,F6); ADD(MULT9S3,F2,F7); ADD(MULT9S4,F3,F8); \
	ADD(MULT9T1,G0,G5); ADD(MULT9T2,G1,G6); ADD(MULT9T3,G2,G7); ADD(MULT9T4,G3,G8); \
	ModifiedMULT5(MULT9U1,MULT9U2,MULT9U3,MULT9U4,MULT9U5,MULT9U6,MULT9U7,MULT9U8,F4,MULT9S1,MULT9S2,MULT9S3,MULT9S4,G4,MULT9T1,MULT9T2,MULT9T3,MULT9T4,C8); \
	SUB(MULT9U1,MULT9U1,C9); SUB(MULT9U2,MULT9U2,C10); SUB(MULT9U3,MULT9U3,C11); SUB(MULT9U4,MULT9U4,C12); SUB(MULT9U5,MULT9U5,C13); SUB(MULT9U6,MULT9U6,C14); SUB(MULT9U7,MULT9U7,C15); SUB(MULT9U8,MULT9U8,C16); \
	SUB(MULT9U2,MULT9U2,C0); SUB(MULT9U3,MULT9U3,C1); SUB(MULT9U4,MULT9U4,C2); SUB(MULT9U5,MULT9U5,C3); SUB(MULT9U6,MULT9U6,C4); SUB(MULT9U7,MULT9U7,C5); SUB(MULT9U8,MULT9U8,C6); \
	ADD(C4,C4,MULT9U1); ADD(C5,C5,MULT9U2); ADD(C6,C6,MULT9U3); C7=MULT9U4; ADD(C8,C8,MULT9U5); ADD(C9,C9,MULT9U6); ADD(C10,C10,MULT9U7); ADD(C11,C11,MULT9U8); \
}

#define SQ4(C0,C1,C2,C3,C4,C5,C6,F0,F1,F2,F3){ \
\
	MULT(C0,F0,F0); MULT(C2,F1,F1); MULT(C1,F0,F1); \
	MULT(C4,F2,F2); MULT(C6,F3,F3); MULT(C5,F2,F3); \
	MULT(SQ4U0,F0,F2); MULT(SQ4U2,F1,F3); MULT(SQ4U1,F0,F3); MULT(SQ4S0,F1,F2); \
\
	ADD(SQ4U1,SQ4U1,SQ4S0); \
\
	SHIFTL(C1,C1,1); SHIFTL(C5,C5,1); SHIFTL(SQ4U0,SQ4U0,1); SHIFTL(SQ4U1,SQ4U1,1); SHIFTL(SQ4U2,SQ4U2,1); \
\
	ADD(C2,C2,SQ4U0); C3=SQ4U1; ADD(C4,C4,SQ4U2); \
}

#define SQ4Karatsuba(C0,C1,C2,C3,C4,C5,C6,F0,F1,F2,F3){ \
\
	ADD(SQ4S0,F0,F1); ADD(SQ4T0,F2,F3); \
\
	MULT(C0,F0,F0); MULT(C2,F1,F1); MULT(C1,F0,F1); \
	MULT(C4,F2,F2); MULT(C6,F3,F3); MULT(C5,F2,F3); \
	MULT(SQ4U0,F0,F2); MULT(SQ4U2,F1,F3); MULT(SQ4U1,SQ4S0,SQ4T0); \
\
	SUB(SQ4U1,SQ4U1,SQ4U0); SUB(SQ4U1,SQ4U1,SQ4U2); \
\
	SHIFTL(C1,C1,1); SHIFTL(C5,C5,1); SHIFTL(SQ4U0,SQ4U0,1); SHIFTL(SQ4U1,SQ4U1,1); SHIFTL(SQ4U2,SQ4U2,1); \
\
	ADD(C2,C2,SQ4U0); C3=SQ4U1; ADD(C4,C4,SQ4U2); \
}

#define SQ5(C0,C1,C2,C3,C4,C5,C6,C7,C8,F0,F1,F2,F3,F4) { \
	SQ4(C0,C1,C2,C3,C4,C5,C6,F0,F1,F2,F3); \
	MULT(SQ5U0,F4,F0); MULT(SQ5U1,F4,F1); MULT(SQ5U2,F4,F2); MULT(SQ5U3,F4,F3); MULT(SQ5U4,F4,F4); \
	SHIFTL(SQ5U0,SQ5U0,1); SHIFTL(SQ5U1,SQ5U1,1); SHIFTL(SQ5U2,SQ5U2,1); SHIFTL(SQ5U3,SQ5U3,1); \
	ADD(C4,C4,SQ5U0); ADD(C5,C5,SQ5U1); ADD(C6,C6,SQ5U2); \
	C7 = SQ5U3; C8 = SQ5U4; \
}

#define SQ9(C0,C1,C2,C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,C14,C15,C16,F0,F1,F2,F3,F4,F5,F6,F7,F8) { \
	SQ4(C0,C1,C2,C3,C4,C5,C6,F0,F1,F2,F3); \
	SQ4(C8,C9,C10,C11,C12,C13,C14,F4,F5,F6,F7); \
	MULT4(SQ9U0,SQ9U1,SQ9U2,SQ9U3,SQ9U4,SQ9U5,SQ9U6,F0,F1,F2,F3,F4,F5,F6,F7); \
	SHIFTL(SQ9U0,SQ9U0,1); SHIFTL(SQ9U1,SQ9U1,1); SHIFTL(SQ9U2,SQ9U2,1); SHIFTL(SQ9U3,SQ9U3,1); \
	SHIFTL(SQ9U4,SQ9U4,1); SHIFTL(SQ9U5,SQ9U5,1); SHIFTL(SQ9U6,SQ9U6,1); \
	ADD(C4,C4,SQ9U0); ADD(C5,C5,SQ9U1); ADD(C6,C6,SQ9U2); C7=SQ9U3; \
	ADD(C8,C8,SQ9U4); ADD(C9,C9,SQ9U5); ADD(C10,C10,SQ9U6); \
	MULT(SQ9U0,F8,F0); MULT(SQ9U1,F8,F1); MULT(SQ9U2,F8,F2); MULT(SQ9U3,F8,F3); MULT(SQ9U4,F8,F4); \
	MULT(SQ9U5,F8,F5); MULT(SQ9U6,F8,F6); MULT(SQ9U7,F8,F7); MULT(SQ9U8,F8,F8); \
	SHIFTL(SQ9U0,SQ9U0,1); SHIFTL(SQ9U1,SQ9U1,1); SHIFTL(SQ9U2,SQ9U2,1); SHIFTL(SQ9U3,SQ9U3,1); \
	SHIFTL(SQ9U4,SQ9U4,1); SHIFTL(SQ9U5,SQ9U5,1); SHIFTL(SQ9U6,SQ9U6,1); SHIFTL(SQ9U7,SQ9U7,1); \
	ADD(C8,C8,SQ9U0); ADD(C9,C9,SQ9U1); ADD(C10,C10,SQ9U2); ADD(C11,C11,SQ9U3); \
	ADD(C12,C12,SQ9U4); ADD(C13,C13,SQ9U5); ADD(C14,C14,SQ9U6); \
	C15=SQ9U7; C16=SQ9U8; \
}

#define REDUCE2519(RES0,RES1,RES2,RES3,RES4,RES5,RES6,RES7,RES8,TEMP) {\
\
	MULT(TEMP[9],TEMP[9],18ULL); MULT(TEMP[10],TEMP[10],18ULL); MULT(TEMP[11],TEMP[11],18ULL); MULT(TEMP[12],TEMP[12],18ULL); \
	MULT(TEMP[13],TEMP[13],18ULL); MULT(TEMP[14],TEMP[14],18ULL); MULT(TEMP[15],TEMP[15],18ULL); MULT(TEMP[16],TEMP[16],18ULL); \
 \
	ADD(RES0,TEMP[0],TEMP[9]); ADD(RES1,TEMP[1],TEMP[10]); ADD(RES2,TEMP[2],TEMP[11]); ADD(RES3,TEMP[3],TEMP[12]); \
	ADD(RES4,TEMP[4],TEMP[13]); ADD(RES5,TEMP[5],TEMP[14]); ADD(RES6,TEMP[6],TEMP[15]); ADD(RES7,TEMP[7],TEMP[16]); RES8=TEMP[8];\
 \
	SHIFTR(MULT9S1,RES0,28); AND(RES0,RES0,mask28); ADD(RES1,RES1,MULT9S1); \
	SHIFTR(MULT9S1,RES1,28); AND(RES1,RES1,mask28); ADD(RES2,RES2,MULT9S1); \
	SHIFTR(MULT9S1,RES2,28); AND(RES2,RES2,mask28); ADD(RES3,RES3,MULT9S1); \
	SHIFTR(MULT9S1,RES3,28); AND(RES3,RES3,mask28); ADD(RES4,RES4,MULT9S1); \
	SHIFTR(MULT9S1,RES4,28); AND(RES4,RES4,mask28); ADD(RES5,RES5,MULT9S1); \
	SHIFTR(MULT9S1,RES5,28); AND(RES5,RES5,mask28); ADD(RES6,RES6,MULT9S1); \
	SHIFTR(MULT9S1,RES6,28); AND(RES6,RES6,mask28); ADD(RES7,RES7,MULT9S1); \
	SHIFTR(MULT9S1,RES7,28); AND(RES7,RES7,mask28); ADD(RES8,RES8,MULT9S1); \
	SHIFTR(MULT9S1,RES8,27); AND(RES8,RES8,mask27); \
	MULT(MULT9S1,MULT9S1,9ULL); ADD(RES0,RES0,MULT9S1); \
	SHIFTR(MULT9S1,RES0,28); AND(RES0,RES0,mask28); ADD(RES1,RES1,MULT9S1); \
}

#endif
