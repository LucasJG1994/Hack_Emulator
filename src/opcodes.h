#ifndef opcodes_h
#define opcodes_h

//COMP OPCODES
#define ZERO 0x2a // 0
#define ONE 0x3f // 1
#define N_ONE 0x3a // -1
#define IN_D 0x0c // D
#define IN_A 0x30 // A
#define IN_M 0x70 // M
#define NOT_D 0x0d // !D
#define NOT_A 0x31 // !A
#define NOT_M 0x71 // !M
#define N_D 0x0f // -D
#define N_A 0x33 // -A
#define N_M 0x73 // -M
#define D_p_1 0x1f // D+1
#define A_p_1 0x37 // A+1
#define M_p_1 0x77 // M+1
#define D_s_1 0x0e // D-1
#define A_s_1 0x32 // A-1
#define M_s_1 0x72 // M-1
#define D_p_A 0x02 // D+A
#define D_p_M 0x42 // D+M
#define D_s_A 0x13 // D-A
#define D_s_M 0x53 // D-M
#define A_s_D 0x07 // A-D
#define M_s_D 0x47 // M-D
#define D_a_A 0x00 // D&A
#define D_a_M 0x40 // D&M
#define D_o_A 0x15 // D|A
#define D_o_M 0x55 // D|M

//DEST OPCODES
#define OUT_M 0x1 // M
#define OUT_D 0x2 // D
#define OUT_MD 0x3 // MD
#define OUT_A 0x4 // A
#define OUT_AM 0x5 // AM
#define OUT_AD 0x6 // AD
#define OUT_AMD 0x7 // AMD

//JUMP OPCODES
#define JGT 0x1 // JGT
#define JEQ 0x2 // JEQ
#define JGE 0x3 // JGE
#define JLT 0x4 // JLT
#define JNE 0x5 // JNE
#define JLE 0x6 // JLE
#define JMP 0x7 // JMP

#endif