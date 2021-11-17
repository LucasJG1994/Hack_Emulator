#include "vm.h"

int main(int argc, char** argv){
	UpdateState state;
	vm_t vm = {0};
	
	init(&vm);
	
	do {
		vm.RAM[24576] = keys;
		if(vm.state == OK){
			vm.state = compute(&vm);
			
			//VM state feedback
			switch(vm.state){
				case INVALID_COMP: printf("Error: Invalid comp opcode\n"); break;
				case INVALID_ADDRESS: printf("Error: Invalid address is being accessed\n"); break;
				case CPU_HALT: printf("Cpu has ran out of instructions\n");
				default: break;
			}
		}
		
		state = mfb_update(vm.window, vm.buffer);
		if(state != STATE_OK){
			vm.window = NULL;
			break;
		}
	}while(1);
	getchar();
	return 0;
}