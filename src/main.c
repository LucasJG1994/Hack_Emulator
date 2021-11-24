#include "HackScanner.h"
//#include "HackParser.h"

int main(int argc, char** argv){
	UpdateState state;
	
	/*
		TEST CODE
	*/
	//=================================
	
	const char* code = "\n\
	@screen\n\
	d=a\n\
	(loop)\n\
	m=-1\n\
	ad=d+1\n\
	@loop\n\
	0;jmp\n\0";
	
	struct hackScanner scan = hackScanner_init(code);
	TOKEN_List_t labels = hackScanner_labels(&scan);
	
	if(scan.error != SCAN_OK){
		TOKEN_List_destroy(&labels);
		printf("Invalid ID\n");
		return 0;
	}
	
	hackScanner_reset(&scan);
	
	TOKEN_List_t tokens = hackScanner_lexer(&scan, &labels);
	
	if(scan.error != SCAN_OK){
		TOKEN_List_destroy(&labels);
		TOKEN_List_destroy(&tokens);
		switch(scan.error){
			case SCAN_STRING_TOO_LONG_ERROR:
				printf("Error: String too long\n"); break;
			case SCAN_INVALID_ID_ERROR:
				printf("Error: Invalid ID\n"); break;
			case SCAN_KEYWORD_ERROR:
				printf("Error: Keyword error\n"); break;
		}
		return 0;
	}
	
	TOKEN_List_destroy(&labels);
	TOKEN_List_destroy(&tokens);
	
	//=================================
	
	struct VM vm = vm_init();
	
	do {
		vm.RAM[24576] = KEYS;
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