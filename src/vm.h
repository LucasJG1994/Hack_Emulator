#ifndef vm_h
#define vm_h

#include "common.h"

//VM States
typedef enum{
	VM_OK, VM_INVALID_COMP, VM_INVALID_ADDRESS, VM_CPU_HALT
}vm_states;

typedef struct VM{
	struct Window* window;
	int buffer[w_width * w_height];
	int state; //Used for storeing the VM states
	
	u16 ROM[32768];
	s16 RAM[24577];
	s16 A,D;
	s16 BUS;
	u16 IP;
}vm_t;

extern int KEYS; //Used for storing keyboard scancodes.

//These functions are the callback for MiniFB's keyboard implementation.
void mfb_keyboard(struct Window* window, Key key, KeyMod mod, bool isPressed);
void mfb_char_input(struct Window* window, unsigned int charCode);

//VM functions
void vm_make_opcode(vm_t* _vm, u8 _jump, u8 _dest, u8 _comp);
void vm_put_word(vm_t* _vm, u16 word);
void vm_adv(vm_t* _vm);
void vm_next(vm_t* _vm);
void vm_reset(vm_t* _vm);

//Initialize the MiniFB's keyboard and window.
struct VM vm_init();

#endif