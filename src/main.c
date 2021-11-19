#include "vm.h"
#include "HackScanner.h"

int main(int argc, char** argv){
	UpdateState state;
	
	/*
		TEST CODE
	*/
	//=================================
	const char* code = "(end)\n\
	(foo1)\
	@end\n\
	d;jmp\n\
	@foo\n\
	a=0\n\
	amd=-1\n\
	@54321\0";
	
	struct hackScanner scan = hackScanner_init(code);
	struct list labels = hackScanner_labels(&scan);
	
	if(scan.error != SCAN_OK){
		list_destroy(&labels);
		printf("Invalid ID\n");
		return 0;
	}
	
	hackScanner_reset(&scan);
	
	struct list tokens = hackScanner_lexer(&scan, &labels);
	
	if(scan.error != SCAN_OK){
		list_destroy(&labels);
		list_destroy(&tokens);
		printf("Error in code");
		return 0;
	}
	
	list_print(&labels);
	list_print(&tokens);
	
	list_destroy(&labels);
	list_destroy(&tokens);
	
	//=================================
	
	struct VM vm = vm_init();
	
	do {
		vm.RAM[24576] = keys;
		if(vm.state == VM_OK){
			vm_next(&vm);
			
			//VM state feedback
			switch(vm.state){
				case VM_INVALID_COMP: printf("Error: Invalid comp opcode\n"); break;
				case VM_INVALID_ADDRESS: printf("Error: Invalid address is being accessed\n"); break;
				case VM_CPU_HALT: printf("Cpu has ran out of instructions\n");
				default: break;
			}
		}
		
		state = mfb_update(vm.window, vm.buffer);
		if(state != STATE_OK){
			vm.window = NULL;
			break;
		}
	}while(1);
	return 0;
}