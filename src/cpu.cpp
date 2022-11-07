#include "cpu.h"
#include "rom_loader.h"
#include "vram.h"
#include <thread>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>

#define MODULE "CPU"
#define M RAM[A & 0x7FFF]

#define JGT IP = (!ZR & !NG) ? (A*2) : IP
#define JEQ IP = ( ZR & !NG) ? (A*2) : IP
#define JGE IP = ( ZR | !NG) ? (A*2) : IP
#define JLT IP = (!ZR &  NG) ? (A*2) : IP
#define JNE IP = (!ZR |  NG) ? (A*2) : IP
#define JLE IP = ( ZR |  NG) ? (A*2) : IP
#define JMP IP = (A*2)

#define LOG(E) std::cout << "[ " << MODULE << " ] " << E << std::endl

extern bool DEBUG;
extern bool HALT;

std::string bits(short data){
	char bits[17] = {0};
	unsigned short table[] = { 32768, 16384, 8192, 4096, 2048, 1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1 };
	for(int i = 0; i < 16; i++){
		bits[i] = (table[i] & data) ? '1' : '0';
	}

	return std::string(bits);
}

void cpu_init(const char* file){
	if(file == nullptr) return;
	
	ROM* rom = rom_load(file);
	
	if(rom == nullptr){
		LOG("Failed to load ROM...");
		return;
	}
	
	FILE* fp = NULL;
	std::string output;
	std::stringstream outstream(output);
	outstream << "|       PC       |       A        |       D        |     RAM[0]     |\n";

	if(DEBUG) fp = fopen("Release/test.out", "w");

	//CPU RAM
	unsigned short* RAM = new unsigned short[32768]{ 0 };

	//CPU Registers
	unsigned short IP = 0;
	unsigned short A = 0;
	unsigned short D = 0;
	
	//CPU Bus
	unsigned short BUS = 0;
	
	union {
		struct {
			unsigned char ia;
			unsigned char ib;
		};
		unsigned short i;
	};

	std::thread vram_start(vram_init, RAM);

	while((IP < rom->size) && !HALT){
		if (DEBUG) outstream << "|" << bits((IP / 2)) << "|" << bits(A) << "|" << bits(D) << "|" << bits(RAM[0]) << "|" << std::endl;

		ib = rom->ctx[IP++];
		ia = rom->ctx[IP++];

		if((i & 0x8000) == 0){
			A = i;
			continue;
		}

		short cmp = (i & 0x0fc0) >> 6;
		short dst = (i & 0x0038) >> 3;
		short jmp = (i & 0x0007) >> 0;

		short ALU_in_a = D;
		short ALU_in_b = (i & 0x1000) ? M : A;

		switch (cmp) {
			case 0b101010 : BUS = 0						; break;
			case 0b111111 : BUS = 1						; break;
			case 0b111010 : BUS = -1					; break;
			case 0b001100 : BUS = ALU_in_a				; break;
			case 0b110000 : BUS = ALU_in_b				; break;
			case 0b001101 : BUS = ~ALU_in_a				; break;
			case 0b110001 : BUS = ~ALU_in_b				; break;
			case 0b001111 : BUS = -ALU_in_a				; break;
			case 0b110011 : BUS = -ALU_in_b				; break;
			case 0b011111 : BUS = ALU_in_a + 1			; break;
			case 0b110111 : BUS = ALU_in_b + 1			; break;
			case 0b001110 : BUS = ALU_in_a - 1			; break;
			case 0b110010 : BUS = ALU_in_b - 1			; break;
			case 0b000010 : BUS = ALU_in_a + ALU_in_b	; break;
			case 0b010011 : BUS = ALU_in_a - ALU_in_b	; break;
			case 0b000111 : BUS = ALU_in_b - ALU_in_a	; break;
			case 0b000000 : BUS = ALU_in_a & ALU_in_b	; break;
			case 0b010101 : BUS = ALU_in_a | ALU_in_b	; break;
			default: break;
		}

		char ZR = BUS == 0;
		char NG = (BUS & 0x8000) ? 1 : 0;

		switch (dst) {
			case 0b001: M = BUS; break;
			case 0b010: D = BUS; break;
			case 0b011: 
				M = BUS;
				D = BUS;
				break;
			case 0b100: A = BUS; break;
			case 0b101:
				M = BUS;
				A = BUS;
				break;
			case 0b110:
				A = BUS;
				D = BUS;
				break;
			case 0b111:
				M = BUS;
				A = BUS;
				D = BUS;
				break;
			default: break;
		}

		switch (jmp) {
			case 0b001: JGT; break;
			case 0b010: JEQ; break;
			case 0b011: JGE; break;
			case 0b100: JLT; break;
			case 0b101: JNE; break;
			case 0b110: JLE; break;
			case 0b111: JMP; break;
			default: break;
		}
	}
	if (DEBUG) fwrite(outstream.str().c_str(), sizeof(char), outstream.str().length(), fp);
	if (fp != NULL) fclose(fp);
	vram_start.join();
	delete[] RAM;
}