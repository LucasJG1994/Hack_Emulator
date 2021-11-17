#ifndef vm_h
#define vm_h

#include "common.h"

//VM States
typedef enum{
	OK, INVALID_COMP, INVALID_ADDRESS, CPU_HALT
}states;

typedef struct{
	struct Window* window;
	int buffer[w_width * w_height];
	int state; //Used for storeing the VM states
	
	u16 ROM[32768];
	s16 RAM[24578];
	s16 A,D;
	s16 BUS;
	u16 IP;
}vm_t;

void setInstr(vm_t* _vm, u8 _jump, u8 _dest, u8 _comp);
void setValue(vm_t* _vm, u16 value);
u16 getInstr(vm_t* _vm);
int compute(vm_t* _vm);
void reset(vm_t* _vm);
void init(vm_t* _vm);

#endif