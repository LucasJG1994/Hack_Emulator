#include "cpu.h"
#include "log.h"
#include "rom_loader.h"
#include "vram.h"
#include <thread>

#define MODULE "CPU"
#define M RAM[A]

#define JGT(T,F) IP = (!ZR & !NG)? T : F
#define JEQ(T,F) IP = (ZR & !NG) ? T : F
#define JGE(T,F) IP = (ZR & !NG) ? T : F
#define JLT(T,F) IP = (!ZR & NG) ? T : F
#define JNE(T,F) IP = (!ZR & NG) ? T : F
#define JLE(T,F) IP = (ZR & NG)  ? T : F
#define JMP(T)   IP = T

//Shared variables with VRAM thread
unsigned short RAM[32768] = { 0 };

void cpu_init(const char* file){
	if(file == nullptr) return;
	
	ROM* rom = rom_load(file);
	
	if(rom == nullptr){
		logging(MODULE, "Failed to load ROM...");
		return;
	}
	
	//CPU Registers
	unsigned short IP = 0;
	unsigned short A = 0;
	unsigned short D = 0;
	
	//CPU Bus
	unsigned short BUS = 0;
	
	std::thread vram_start(vram_init);
	
	while(IP < rom->size){
		short i = rom->ctx[IP++] | (rom->ctx[IP++] << 8);
		if(i & 0x8000){
			A = i;
			continue;
		}
		
		char cmp = (i & 0x1fc0) >> 6;
		char dst = (i & 0x0038) >> 3;
		char jmp = (i & 0x0007) >> 0;
		
		switch (cmp) {
			case 0b101010 : BUS = 0     ; break;
			case 0b111111 : BUS = 1     ; break;
			case 0b111010 : BUS = -1    ; break;
			case 0b001100 : BUS = D     ; break;
			case 0b110000 : BUS = A     ; break;
			case 0b1110000: BUS = M     ; break;
			case 0b001101 : BUS = ~D    ; break;
			case 0b110001 : BUS = ~A    ; break;
			case 0b1110001: BUS = ~M    ; break;
			case 0b001111 : BUS = -D    ; break;
			case 0b110011 : BUS = -A    ; break;
			case 0b1110011: BUS = -M    ; break;
			case 0b011111 : BUS = D + 1 ; break;
			case 0b110111 : BUS = A + 1 ; break;
			case 0b1110111: BUS = M + 1 ; break;
			case 0b001110 : BUS = D - 1 ; break;
			case 0b110010 : BUS = A - 1 ; break;
			case 0b1110010: BUS = M - 1 ; break;
			case 0b000010 : BUS = D + A ; break;
			case 0b1000010: BUS = D + M ; break;
			case 0b010011 : BUS = D - A ; break;
			case 0b1010011: BUS = D - M ; break;
			case 0b000111 : BUS = A - D ; break;
			case 0b1000111: BUS = M - D ; break;
			case 0b000000 : BUS = D & A ; break;
			case 0b1000000: BUS = D & M ; break;
			case 0b010101 : BUS = D | A ; break;
			case 0b1010101: BUS = D | M ; break;
		}

		char ZR = BUS == 0;
		char NG = BUS & 0x8000;

		switch (dst) {
			case 0b001: M = BUS; break;
			case 0b010: D = BUS; break;
			case 0b011: M = BUS;
			            D = BUS; break;
			case 0b100: A = BUS; break;
			case 0b101: M = BUS;
			            A = BUS; break;
			case 0b110: A = BUS;
			            D = BUS; break;
			case 0b111: M = BUS;
			            A = BUS;
						D = BUS; break;
		}

		switch (jmp) {
			case 0b001: JGT(A, IP); break;
			case 0b010: JEQ(A, IP); break;
			case 0b011: JGE(A, IP); break;
			case 0b100: JLT(A, IP); break;
			case 0b101: JNE(A, IP); break;
			case 0b110: JLE(A, IP); break;
			case 0b111: JMP(A)	  ; break;
		}
	}
	vram_start.join();
}