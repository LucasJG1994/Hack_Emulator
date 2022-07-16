#ifndef vm_h
#define vm_h

typedef unsigned char u8;

//VM States
typedef enum{
	VM_OK, VM_INVALID_COMP, VM_INVALID_ADDRESS, VM_CPU_HALT
}vm_states;

//VM functions
//Initialize the MiniFB's keyboard and window.
void vm_init();
void vm_make_op(u8 _jump, u8 _dest, u8 _comp);
void vm_put_word(int word);
void vm_adv();
void vm_next();
int  vm_get_ip();
void vm_reset();

void vm_run();
#endif