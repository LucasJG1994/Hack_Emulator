#include "HackParser.h"

LIST_FUNCTIONS(Lab_Dec);
LIST_FUNCTIONS(L_Lab);

hackParser_t hackParser_init(TOKEN_List_t* tokens){
	hackParser_t parser = {NULL};
	parser.tokens = tokens;
	parser.current = TOKEN_List_pop_first(parser.tokens);
	return parser;
}

void hackParser_adv(hackParser_t* parser){
	parser->current = TOKEN_List_pop_first(parser->tokens);
}

int hackParser_cur(hackParser_t* parser){
	return parser->current.type;
}

int hackParser_peek(hackParser_t* parser){
	return TOKEN_List_bottom(parser->tokens).type;
}

int hackParser_match(hackParser_t* parser, int type){
	return hackParser_cur(parser) == type;
}

int hackParser_consume(hackParser_t* parser, int type, const char* msg){
	if(hackParser_match(parser, type)){
		hackParser_adv(parser);
	}
	else{
		printf("Error: %s on line %d\n", msg, parser->current.line);
		return PARSER_ERROR;
	}
}

void hackParser_run(hackParser_t* parser, vm_t* vm){
	u8 dest, comp, jump;
	int var_index = 0;

	while(hackParser_cur(parser) != TK_EOF){
		//Reset values
		dest = 0; comp = 0; jump = 0;
		
		if(hackParser_match(parser, TK_AT)){
			char string_buffer[50] = {0};
			hackParser_adv(parser);
			
			sprintf(string_buffer, "%.*s", parser->current.length, parser->current.lexeme);
			switch(hackParser_cur(parser)){
				case TK_NUM: vm_put_word(vm, atoi(string_buffer)); break;
				case TK_ID: vm_put_word(vm, var_index++); break;
				case TK_SP: vm_put_word(vm, 0); break;
				case TK_LCL: vm_put_word(vm, 1); break;
				case TK_ARG: vm_put_word(vm, 2); break;
				case TK_THIS: vm_put_word(vm, 3); break;
				case TK_THAT: vm_put_word(vm, 4); break;
				case TK_SCREEN: vm_put_word(vm, 16384); break;
				case TK_KBD: vm_put_word(vm, 24576); break;
				case TK_R0: vm_put_word(vm, 0); break;
				case TK_R1: vm_put_word(vm, 1); break;
				case TK_R2: vm_put_word(vm, 2); break;
				case TK_R3: vm_put_word(vm, 3); break;
				case TK_R4: vm_put_word(vm, 4); break;
				case TK_R5: vm_put_word(vm, 5); break;
				case TK_R6: vm_put_word(vm, 6); break;
				case TK_R7: vm_put_word(vm, 7); break;
				case TK_R8: vm_put_word(vm, 8); break;
				case TK_R9: vm_put_word(vm, 9); break;
				case TK_R10: vm_put_word(vm, 10); break;
				case TK_R11: vm_put_word(vm, 11); break;
				case TK_R12: vm_put_word(vm, 12); break;
				case TK_R13: vm_put_word(vm, 13); break;
				case TK_R14: vm_put_word(vm, 14); break;
				case TK_R15: vm_put_word(vm, 15); break;
			}
		}
		else{
			if(hackParser_peek(parser) == TK_EQ){
				switch(hackParser_cur(parser)){
					case TK_A: dest = OUT_A; break;
					case TK_D: dest = OUT_D; break;
					case TK_M: dest = OUT_M; break;
					case TK_AD: dest = OUT_AD; break;
					case TK_AM: dest = OUT_AM; break;
					case TK_AMD: dest = OUT_AMD; break;
					default:
						hackParser_consume(parser, 0, "Invalid destination opcode");
				}
				
				hackParser_adv(parser);
				hackParser_adv(parser);
				hackParser_comp(parser, &comp);
				
				hackParser_adv(parser);
				if(hackParser_match(parser, TK_SEMI)){
					hackParser_adv(parser);
					
					switch(hackParser_cur(parser)){
						case TK_JGT: jump = JGT; break;
						case TK_JEQ: jump = JEQ; break;
						case TK_JGE: jump = JGE; break;
						case TK_JLT: jump = JLT; break;
						case TK_JNE: jump = JNE; break;
						case TK_JLE: jump = JLE; break;
						case TK_JMP: jump = JMP; break;
					}
					hackParser_adv(parser);
				}
			}
			else{
				hackParser_comp(parser, &comp);
				hackParser_adv(parser);
				
				if(hackParser_match(parser, TK_SEMI)){
					hackParser_adv(parser);
					
					switch(hackParser_cur(parser)){
						case TK_JGT: jump = JGT; break;
						case TK_JEQ: jump = JEQ; break;
						case TK_JGE: jump = JGE; break;
						case TK_JLT: jump = JLT; break;
						case TK_JNE: jump = JNE; break;
						case TK_JLE: jump = JLE; break;
						case TK_JMP: jump = JMP; break;
					}
					hackParser_adv(parser);
				}
			}
			vm_make_opcode(vm, jump, dest, comp);
		}
	}
}

void hackParser_comp(hackParser_t* parser, int* comp){
	if(hackParser_match(parser, TK_0)) *comp = ZERO;
	else if(hackParser_match(parser, TK_1)) *comp = ONE;
	else if(hackParser_match(parser, TK_BAN)){
		hackParser_adv(parser);
				
		switch(hackParser_cur(parser)){
			case TK_A: *comp = NOT_A; break;
			case TK_D: *comp = NOT_D; break;
			case TK_M: *comp = NOT_M; break;
		}
	}
	else if(hackParser_match(parser, TK_SUB)){
		hackParser_adv(parser);
				
		switch(hackParser_cur(parser)){
			case TK_1: *comp = N_ONE; break;
			case TK_A: *comp = N_A; break;
			case TK_D: *comp = N_D; break;
			case TK_M: *comp = N_M; break;
		}
	}
	else if(hackParser_match(parser, TK_A)){
		*comp = IN_A;
		hackParser_adv(parser);
				
		if(hackParser_match(parser, TK_ADD)){
			*comp = A_p_1;
			hackParser_adv(parser);
		}
		else if(hackParser_match(parser, TK_SUB)){
			hackParser_adv(parser);
					
			switch(hackParser_cur(parser)){
				case TK_1: *comp = A_s_1; break;
				case TK_D: *comp = A_s_D; break;
			}
		}
	}
	else if(hackParser_match(parser, TK_M)){
		*comp = IN_M;
		hackParser_adv(parser);
				
		if(hackParser_match(parser, TK_ADD)){
			*comp = M_p_1;
			hackParser_adv(parser);
		}
		else if(hackParser_match(parser, TK_SUB)){
			hackParser_adv(parser);
					
			switch(hackParser_cur(parser)){
				case TK_1: *comp = M_s_1; break;
				case TK_D: *comp = M_s_D; break;
			}
		}
	}
	else if(hackParser_match(parser, TK_D)){
		*comp = IN_D;
		hackParser_adv(parser);
				
		if(hackParser_match(parser, TK_ADD)){
			hackParser_adv(parser);
					
			switch(hackParser_cur(parser)){
				case TK_1: *comp = D_p_1; break;
				case TK_A: *comp = D_p_A; break;
				case TK_M: *comp = D_p_M; break;
			}
		}
		else if(hackParser_match(parser, TK_SUB)){
			hackParser_adv(parser);
					
			switch(hackParser_cur(parser)){
				case TK_1: *comp = D_s_1; break;
				case TK_A: *comp = D_s_A; break;
				case TK_M: *comp = D_s_M; break;
			}
		}
		else if(hackParser_match(parser, TK_AND)){
			hackParser_adv(parser);
					
			switch(hackParser_cur(parser)){
				case TK_A: *comp = D_a_A; break;
				case TK_M: *comp = D_a_M; break;
			}
		}
		else if(hackParser_match(parser, TK_OR)){
			hackParser_adv(parser);
					
			switch(hackParser_cur(parser)){
				case TK_A: *comp = D_o_A; break;
				case TK_M: *comp = D_o_M; break;
			}
		}
	}
}