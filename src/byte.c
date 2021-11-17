#include "vm.h"
/*TEST FILE*/
int main(){
	UpdateState state;
	vm_t vm = {0};
	
	init(&vm);
	
	//Test code for the VM
	setValue(&vm, 24500);
	setInstr(&vm, 0, OUT_D, IN_A);
	setInstr(&vm, 0, OUT_A, IN_D);
	setInstr(&vm, 0, OUT_M, ONE);
	setInstr(&vm, 0, OUT_D, D_p_1); //ROM gets edited at this opcode.
	setValue(&vm, 2);
	setInstr(&vm, JMP, 0, ZERO);
	reset(&vm);
	
	do {
		if(vm.state == OK){
			vm.state = compute(&vm);
			//DEBUG CODE
			//printf("A: %d D: %d M: %d IP: %d BUS: %d ROM: %d\n", vm.A, vm.D, vm.RAM[vm.A], vm.IP, vm.BUS, vm.ROM[4]);
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