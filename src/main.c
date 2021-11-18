#include "vm.h"
#include "HackScanner.h"

int main(int argc, char** argv){
	UpdateState state;
	vm_t vm = {0};
	hackScanner_t scan = {NULL};
	list_t tokens = {NULL};
	list_t labels = {NULL};
	
	const char* code = "(end)\n\
	(foo1)\
	@end\n\
	d;jmp\n\
	@foo\n\
	a=0\n\
	amd=-1\n\
	@54321\0";
	
	initS(&scan, code);
	labels = getHackLabels(&scan);
	
	if(scan.error != SCAN_OK){
		freeList(&labels);
		printf("Invalid ID\n");
		getchar();
		return 0;
	}
	
	resetS(&scan);
	
	tokens = lexer(&scan, &labels);
	
	if(scan.error != SCAN_OK){
		freeList(&labels);
		freeList(&tokens);
		printf("Error in code");
		getchar();
		return 0;
	}
	
	printList(&labels);
	printf("\n");
	printList(&tokens);
	
	freeList(&labels);
	freeList(&tokens);
	
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