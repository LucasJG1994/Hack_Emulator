#include "vm.h"
#include "miniFB.h"
#include "opcodes.h"
#include <stdint.h>

#define W_WIDTH 512
#define W_HEIGHT 256

typedef uint16_t u16;
typedef int16_t s16;

static struct VM {
	struct Window* window;
	int buffer[W_WIDTH * W_HEIGHT];
	int state; //Used for storeing the VM states

	u16 ROM[32768];
	s16 RAM[24577];
	s16 A, D;
	s16 BUS;
	u16 IP;
};

static const int PALETTE[2] = {0,255}; //Color palette for the screen

//Look up table for the individual bits, 16 bit width
static const int TABLE[16] = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768};
static int KEYS;

static struct VM vm;

static void mfb_keyboard(struct Window* window, Key key, KeyMod mod, bool isPressed);
static void mfb_char_input(struct Window* window, unsigned int charCode);

//Constructs the opcode.
void vm_make_op(u8 _jump, u8 _dest, u8 _comp){
	u16 instruction = 0;
	instruction |= _jump;
	instruction |= (_dest << 3);
	instruction |= (_comp << 6);
	instruction |= (0x7 << 13);
	vm.ROM[vm.IP++] = instruction;
}

void vm_put_word(int word){
	vm.ROM[vm.IP++] = word;
}

void vm_adv(){
	vm.IP++;
}

void vm_reset(){
	vm.IP = 0;
}

void vm_init(){
	vm.window = mfb_open_ex("Hack Computer", W_WIDTH, W_HEIGHT, WF_RESIZABLE);
	
	if(vm.window == NULL){
		printf("Failed to open window\n");
		exit(0);
	}
	
	mfb_set_keyboard_callback(vm.window, mfb_keyboard);
	mfb_set_char_input_callback(vm.window, mfb_char_input);
	vm.state = VM_OK;
}

static void mfb_keyboard(struct Window* window, Key key, KeyMod mod, bool isPressed){
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

static void mfb_char_input(struct Window* window, unsigned int charCode){
	KEYS = charCode;
}

void vm_next(){
	if(vm.IP > 32767) { vm.state = VM_CPU_HALT; return; }
	if(vm.ROM[vm.IP] == 0) { vm.state = VM_CPU_HALT; return; }
	
	printf("IP: %d\n", vm.IP);

	u16 instruction = vm.ROM[vm.IP++]; //Fectch OPcode

	if(!(instruction & 0x8000)){
		vm.A = instruction;
	}
	else{
		//Decode instruction
		u8 comp = (instruction & 0x1fc0) >> 6;
		u8 dest = (instruction & 0x0038) >> 3;
		u8 jump = (instruction & 0x0007) >> 0;
		
		if((comp & 0x40) || (dest & 0x01))
			if((vm.A < 0) || (vm.A > 24576)){
				vm.state = VM_INVALID_ADDRESS;
				return;
			}
		
		switch(comp){
			case ZERO:	vm.BUS = 0; break;
			case ONE:	vm.BUS = 1; break;
			case N_ONE: vm.BUS = -1; break;
			case IN_D:	vm.BUS = vm.D; break;
			case IN_A:	vm.BUS = vm.A; break;
			case IN_M:	vm.BUS = vm.RAM[vm.A]; break;
			case NOT_D: vm.BUS= ~vm.D; break;
			case NOT_A: vm.BUS= ~vm.A; break;
			case NOT_M: vm.BUS= ~vm.RAM[vm.A]; break;
			case N_D:	vm.BUS= -vm.D; break;
			case N_A:	vm.BUS= -vm.A; break;
			case N_M:	vm.BUS= -vm.RAM[vm.A]; break;
			case D_p_1: vm.BUS = vm.D + 1; break;
			case A_p_1: vm.BUS = vm.A + 1; break;
			case M_p_1: vm.BUS = vm.RAM[vm.A] + 1; break;
			case D_s_1: vm.BUS = vm.D - 1; break;
			case A_s_1: vm.BUS = vm.A - 1; break;
			case M_s_1: vm.BUS = vm.RAM[vm.A] - 1; break;
			case D_p_A: vm.BUS = vm.D + vm.A; break;
			case D_p_M: vm.BUS = vm.D + vm.RAM[vm.A]; break;
			case D_s_A: vm.BUS = vm.D - vm.A; break;
			case D_s_M: vm.BUS = vm.D - vm.RAM[vm.A]; break;
			case A_s_D: vm.BUS = vm.A - vm.D; break;
			case M_s_D: vm.BUS = vm.RAM[vm.A] - vm.D; break;
			case D_a_A: vm.BUS = vm.D & vm.A; break;
			case D_a_M: vm.BUS = vm.D & vm.RAM[vm.A]; break;
			case D_o_A: vm.BUS = vm.D | vm.A; break;
			case D_o_M: vm.BUS = vm.D | vm.RAM[vm.A]; break;
			default:
				vm.state = VM_INVALID_COMP;
				return;
		}
		
		switch(dest){
			case OUT_M: vm.RAM[vm.A] = vm.BUS; break;
			case OUT_D: vm.D = vm.BUS; break;
			case OUT_MD:
				vm.RAM[vm.A] = vm.BUS;
				vm.D = vm.BUS;
				break;
			case OUT_A: vm.A = vm.BUS; break;
			case OUT_AM: 
				vm.RAM[vm.A] = vm.BUS;
				vm.A = vm.BUS;
				break;
			case OUT_AD:
				vm.A = vm.BUS;
				vm.D = vm.BUS;
				break;
			case OUT_AMD:
				vm.RAM[vm.A] = vm.BUS;
				vm.A = vm.BUS;
				vm.D = vm.BUS;
				break;
			case 0: break;
		}
		
		switch(jump){
			case JGT:
				if(vm.BUS > 0)
					vm.IP = vm.A;
				break;
			case JEQ:
				if(vm.BUS == 0)
					vm.IP = vm.A;
				break;
			case JGE:
				if(vm.BUS >= 0)
					vm.IP = vm.A;
				break;
			case JLT:
				if(vm.BUS < 0)
					vm.IP = vm.A;
				break;
			case JNE:
				if(vm.BUS != 0)
					vm.IP = vm.A;
				break;
			case JLE:
				if(vm.BUS <= 0)
					vm.IP = vm.A;
				break;
			case JMP: vm.IP = vm.A; break;
			case 0: break;
		}
		
		//IF the destination is M and the A register is in the range of 
		//screen memory. Draw what is in that RAM location to the screen.
		if(dest & 0x01)
			if(vm.A >= 16384 && vm.A < 24576){
				for(int i = 0; i < 16; i++){
					vm.buffer[(vm.A - 16384) * 16 + i] = MFB_RGB(
						PALETTE[(vm.RAM[vm.A] & TABLE[i]) >> i],
						PALETTE[(vm.RAM[vm.A] & TABLE[i]) >> i],
						PALETTE[(vm.RAM[vm.A] & TABLE[i]) >> i]);
				}
			}
	}
}

int vm_get_ip() {
	return vm.IP;
}

void vm_run() {
	UpdateState state;
	vm_reset();
	do {
		vm.RAM[24576] = KEYS;
		if (vm.state == VM_OK) {
			vm_next();

			//VM state feedback
			switch (vm.state) {
				case VM_INVALID_COMP: { printf("Error: Invalid comp opcode\n"); mfb_close(vm.window); return; }
				case VM_INVALID_ADDRESS: { printf("Error: Invalid address is being accessed\n"); mfb_close(vm.window); return; }
				case VM_CPU_HALT: { printf("Cpu has ran out of instructions\n"); mfb_close(vm.window); return; }
				default: break;
			}
		}

		state = mfb_update(vm.window, vm.buffer);	
		if (state != STATE_OK) {
			vm.window = NULL;
			break;
		}
	} while (1);

	mfb_close(vm.window);
}