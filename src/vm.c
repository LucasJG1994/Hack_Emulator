#include "vm.h"

const int PALETTE[2] = {0,255}; //Color palette for the screen
//Look up table for the individual bits, 16 bit width
const int TABLE[16] = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768};
int KEYS;

//Constructs the opcode.
void vm_make_opcode(vm_t* _vm, u8 _jump, u8 _dest, u8 _comp){
	u16 instruction = 0;
	instruction |= _jump;
	instruction |= (_dest << 3);
	instruction |= (_comp << 6);
	instruction |= (0x7 << 13);
	_vm->ROM[_vm->IP++] = instruction;
}

void vm_put_word(vm_t* _vm, u16 word){
	_vm->ROM[_vm->IP++] = word;
}

void vm_reset(vm_t* _vm){
	_vm->IP = 0;
}

struct VM vm_init(){
	struct VM vm = {NULL};
	vm.window = mfb_open_ex("Hack Computer", w_width, w_height, WF_RESIZABLE);
	
	if(vm.window == NULL){
		printf("Failed to open window\n");
		exit(0);
	}
	
	mfb_set_keyboard_callback(vm.window, mfb_keyboard);
	mfb_set_char_input_callback(vm.window, mfb_char_input);
	vm.state = VM_OK;
	return vm;
}

void vm_cleanup(vm_t* _vm){ //Not sure where to use this function.
	mfb_close(_vm->window);
}

void mfb_keyboard(struct Window* window, Key key, KeyMod mod, bool isPressed){
	if(isPressed){
		//Do nothing with (KEYS)
	}
	else{
		KEYS = 0;
	}
	if(key == KB_KEY_ESCAPE){
		mfb_close(window);
		exit(0);
	}
}

void mfb_char_input(struct Window* window, unsigned int charCode){
	KEYS = charCode;
}

void vm_next(vm_t* _vm){
	if(_vm->IP > 32767) return VM_CPU_HALT;
	
	u16 instruction = _vm->ROM[_vm->IP++]; //Fectch OPcode
	
	if(!(instruction & 0x8000)){
		_vm->A = instruction;
	}
	else{
		//Decode instruction
		u8 comp = (instruction & 0x1fc0) >> 6;
		u8 dest = (instruction & 0x0038) >> 3;
		u8 jump = (instruction & 0x0007) >> 0;
		
		if((comp & 0x40) || (dest & 0x01))
			if((_vm->A < 0) || (_vm->A > 24576)){
				_vm->state = VM_INVALID_ADDRESS;
				return;
			}
		
		switch(comp){
			case ZERO: _vm->BUS = 0; break;
			case ONE: _vm->BUS = 1; break;
			case N_ONE: _vm->BUS = -1; break;
			case IN_D: _vm->BUS = _vm->D; break;
			case IN_A: _vm->BUS = _vm->A; break;
			case IN_M: _vm->BUS = _vm->RAM[_vm->A]; break;
			case NOT_D: _vm->BUS = ~_vm->D; break;
			case NOT_A: _vm->BUS = ~_vm->A; break;
			case NOT_M: _vm->BUS = ~_vm->RAM[_vm->A]; break;
			case N_D: _vm->BUS = -_vm->D; break;
			case N_A: _vm->BUS = -_vm->A; break;
			case N_M: _vm->BUS = -_vm->RAM[_vm->A]; break;
			case D_p_1: _vm->BUS = _vm->D + 1; break;
			case A_p_1: _vm->BUS = _vm->A + 1; break;
			case M_p_1: _vm->BUS = _vm->RAM[_vm->A] + 1; break;
			case D_s_1: _vm->BUS = _vm->D - 1; break;
			case A_s_1: _vm->BUS = _vm->A - 1; break;
			case M_s_1: _vm->BUS = _vm->RAM[_vm->A] - 1; break;
			case D_p_A: _vm->BUS = _vm->D + _vm->A; break;
			case D_p_M: _vm->BUS = _vm->D + _vm->RAM[_vm->A]; break;
			case D_s_A: _vm->BUS = _vm->D - _vm->A; break;
			case D_s_M: _vm->BUS = _vm->D - _vm->RAM[_vm->A]; break;
			case A_s_D: _vm->BUS = _vm->A - _vm->D; break;
			case M_s_D: _vm->BUS = _vm->RAM[_vm->A] - _vm->D; break;
			case D_a_A: _vm->BUS = _vm->D & _vm->A; break;
			case D_a_M: _vm->BUS = _vm->D & _vm->RAM[_vm->A]; break;
			case D_o_A: _vm->BUS = _vm->D | _vm->A; break;
			case D_o_M: _vm->BUS = _vm->D | _vm->RAM[_vm->A]; break;
			default:
				_vm->state = VM_INVALID_COMP;
				return;
		}
		
		switch(dest){
			case OUT_M: _vm->RAM[_vm->A] = _vm->BUS; break;
			case OUT_D: _vm->D = _vm->BUS; break;
			case OUT_MD:
				_vm->RAM[_vm->A] = _vm->BUS;
				_vm->D = _vm->BUS;
				break;
			case OUT_A: _vm->A = _vm->BUS; break;
			case OUT_AM: 
				_vm->RAM[_vm->A] = _vm->BUS;
				_vm->A = _vm->BUS;
				break;
			case OUT_AD:
				_vm->A = _vm->BUS;
				_vm->D = _vm->BUS;
				break;
			case OUT_AMD:
				_vm->RAM[_vm->A] = _vm->BUS;
				_vm->A = _vm->BUS;
				_vm->D = _vm->BUS;
				break;
			case 0: break;
		}
		
		switch(jump){
			case JGT:
				if(_vm->BUS > 0)
					_vm->IP = _vm->A;
				break;
			case JEQ:
				if(_vm->BUS == 0)
					_vm->IP = _vm->A;
				break;
			case JGE:
				if(_vm->BUS >= 0)
					_vm->IP = _vm->A;
				break;
			case JLT:
				if(_vm->BUS < 0)
					_vm->IP = _vm->A;
				break;
			case JNE:
				if(_vm->BUS != 0)
					_vm->IP = _vm->A;
				break;
			case JLE:
				if(_vm->BUS <= 0)
					_vm->IP = _vm->A;
				break;
			case JMP: _vm->IP = _vm->A; break;
			case 0: break;
		}
		
		//IF the destination is M and the A register is in the range of 
		//screen memory. Draw what is in that RAM location to the screen.
		if(dest & 0x01)
			if(_vm->A >= 16384 && _vm->A < 24576){
				for(int i = 0; i < 16; i++){
					_vm->buffer[(_vm->A - 16384) * 16 + i] = MFB_RGB(
						PALETTE[(_vm->RAM[_vm->A] & TABLE[i]) >> i],
						PALETTE[(_vm->RAM[_vm->A] & TABLE[i]) >> i],
						PALETTE[(_vm->RAM[_vm->A] & TABLE[i]) >> i]);
				}
			}
	}
}