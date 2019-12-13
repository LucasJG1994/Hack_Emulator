#include <stdio.h>
#include <stdlib.h> 
#include <stdint.h>
#include <MiniFB.h>
 
int16_t ROM32K[20000];
int16_t RAM16K[20000];
int16_t zr;
int16_t ng;
int16_t out;
int16_t loop;
int16_t outtM;
int16_t outM;
int16_t A;
int16_t D;
int16_t inM;
int16_t addressM;
int16_t writeM;
int16_t outMem;
int16_t keyboard;

 
void ALU(int16_t x,int16_t y, int16_t zx, int16_t nx, int16_t zy, int16_t ny, int16_t f, int16_t no){
	zr = 0;
	ng = 0;
	out = 0;
	printf("zx: %d nx: %d zy: %d ny: %d f: %d no: %d x: %d y: %d\n", zx,nx,zy,ny,f,no,x,y);
	if(zx) x = 0;
	if(nx) x = ~x;
	if(zy) y = 0;
	if(ny) y = ~y;
	if(f){
		out = x + y;
	}else{
		out = x & y;
	}
	if(no) out = ~out;
	if(out < 0){
		ng = 1;
	}else if(out == 0){
		zr = 1;
	}
}

void PC(int16_t in, int16_t load, int16_t reset, int16_t inc){
	if(inc) loop++;
	if(load) loop = in;
	if(reset) loop = 0;
}

void CPU(int16_t inM, int16_t instruction, int16_t reset){
	int16_t ni;
	int16_t intoA;
	int16_t i;
	int16_t AorM;
	int16_t AM;
	int16_t pos;
	int16_t nzr;
	int16_t jgt;
	int16_t jeq;
	int16_t jlt;
	int16_t posnzr;
	int16_t ld1;
	int16_t ld2;
	int16_t ld3;
	int16_t ldt;
	int16_t ld;
	int16_t intoD;
	ni = 0;
	intoA = 0;
	i = 0;
	AorM = 0;
	AM = 0;
	pos = 0;
	nzr = 0;
	jgt = 0;
	jeq = 0;
	jlt = 0;
	posnzr = 0;
	ld1 = 0;
	ld2 = 0;
	ld3 = 0;
	ldt = 0;
	ld = 0;
	intoD = 0;
	
	
	//ni = ~(instruction & 32768);
	printf("inM: %d\n",inM);
	if(~(instruction & 32768)){
		i = instruction;
	}else{
		i = inM;
	}
	intoA = (instruction | 32);
	if(intoA > 0) A = i;
	addressM = A;
	if((instruction & 32768)){
		AorM = (instruction & 4096);
	}
	if(AorM){
		AM = inM;
	}else{
		AM = A;
	}
	printf("AM: %d\n",AM);
	ALU(D,AM,(instruction & 2048),(instruction & 1024),(instruction & 512),(instruction & 256),(instruction & 128),(instruction & 64));
	outM = out;
	outtM = outM;
	if(instruction & 32768){
		intoD = (instruction & 16);
	}
	if(intoD) D = outtM;
	if(instruction & 32768){
		writeM = (instruction & 8);
	}
	printf("A: %d D: %d\n", A,D);
	pos = ~ng;
	nzr = ~zr;
	if(instruction & 32768){
		jgt = (instruction & 1);
		posnzr = pos & nzr;
		ld1 = jgt & posnzr;
		jeq = (instruction & 2);
		ld2 = jeq & zr;
		jlt = (instruction & 4);
		ld3 = jlt & ng;
		ldt = ld1 | ld2;
		ld = ld3 | ldt;
		//PC(A,ld,reset,1);
	}
	PC(A,ld,reset,1);
	
}

void memory(int16_t in, int16_t load, int16_t address){
	if(address < 16384){
		if(load){
			RAM16K[address] = in;
		}
		outMem = RAM16K[address];
	}else if( address > 16383 && address < 24576){
		if(load){
			
		}
	}else if( address == 24577){
		keyboard = outMem;
	}
}

void computer(int16_t reset){
	int16_t instruction;
	instruction = ROM32K[loop];
	printf("Loop: %d\n",loop);
	printf("RAM: %d\n", RAM16K[loop]);
	CPU(outMem,instruction,reset);
	memory(outM,writeM,addressM);
}
 
int main(){ 
	//ALU(5,10,1,0,0,1,1,0);
	//CPU(10,-1008,0);
	int i;
	ROM32K[0] = 5;
	ROM32K[1] = -5104;
	ROM32K[2] = -7416;
	ROM32K[3] = -8048;
	ROM32K[4] = 10;
	ROM32K[5] = -7416;
	for(i = 0; i < 10; i++){
		computer(0);
		system("Pause");
	}
	printf("%d %d %d\n",zr,ng,out);
	system("Pause");
	return 0;
	
} 
