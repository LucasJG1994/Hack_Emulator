#include "HackScanner.h"

//This macro generates the needed functions and structures to create a list
//of tokens. Macro exists in list.h
LIST_FUNCTIONS(TOKEN);

//The states that have no name to them.
//such as DFA_<num>_STATE will be converted to DFA_ID_STATE.
//Since if an input "AR" was given. That should be recognized as
//an identifier.
const int DFA_NAMELESS_STATES[DFA_NAMELESS_STATE_LENGTH] = {
	DFA_11_STATE, DFA_13_STATE, DFA_30_STATE, DFA_31_STATE, DFA_33_STATE,
	DFA_34_STATE, DFA_36_STATE, DFA_37_STATE, DFA_38_STATE, DFA_39_STATE,
	DFA_42_STATE, DFA_44_STATE, DFA_45_STATE, DFA_46_STATE, DFA_47_STATE,
	DFA_49_STATE, DFA_50_STATE, DFA_53_STATE, DFA_56_STATE, DFA_58_STATE,
	DFA_60_STATE
};

int TOKEN_List_find(TOKEN_List_t* list, const char* lexeme, int length){
	TOKEN_Node_t* current = list->head;
	while(current != NULL){
		if(string_cmp(current->data.lexeme, current->data.length, lexeme, length)) return 1;
	}
	return 0;
} 

int string_cmp(const char* lex1, int len1, const char* lex2, int len2){
	if(len1 != len2) return 0;
	
	int length = len1;
	
	if(lex1 == NULL || lex2 == NULL) return -1;
	
	for(int i = 0; i < length; i++){
		if((lex1[i] - lex2[i]) != 0){
			return 0;
		}
	}
	
	return 1;
}

int char_is_alpha(char c){
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

struct hackScanner hackScanner_init(const char* source){
	struct hackScanner scan = {NULL};
	scan.begin = source;
	scan.start = source;
	scan.current = source;
	scan.line = 1;
	scan.error = SCAN_OK;
	return scan;
}

void hackScanner_reset(hackScanner_t* scan){
	scan->start = scan->begin;
	scan->current = scan->begin;
	scan->line = 1;
}

void hackScanner_adv(hackScanner_t* scan){
	scan->current++;
}

char hackScanner_peek(hackScanner_t* scan){
	return scan->current[1];
}

char hackScanner_cur(hackScanner_t* scan){
	return scan->current[0];
}

int hackScanner_match(hackScanner_t* scan, char c){
	return hackScanner_cur(scan) == c;
}

struct DFA DFA_init(){
	struct DFA dfa = {DFA_START_STATE};
	//STATE TRANSITION TABLE
	
	//Fill entire DFA table to DFA_ID_STATE
	for(int i = DFA_START_STATE; i < DFA_MAX_HEIGHT; i++){
		DFA_fill_state(&dfa, i, DFA_ID_STATE);
	}
	//STATE 0 | START STATE
	for(char i = '0'; i <= '9'; i++){
		dfa.table[i][DFA_START_STATE] = DFA_NUMBER_STATE;
	}
	
	dfa.table['A'][DFA_START_STATE] = DFA_A_STATE;
	dfa.table['a'][DFA_START_STATE] = DFA_A_STATE;
	dfa.table['D'][DFA_START_STATE] = DFA_D_STATE;
	dfa.table['d'][DFA_START_STATE] = DFA_D_STATE;
	dfa.table['M'][DFA_START_STATE] = DFA_M_STATE;
	dfa.table['m'][DFA_START_STATE] = DFA_M_STATE;
	dfa.table['R'][DFA_START_STATE] = DFA_13_STATE;
	dfa.table['r'][DFA_START_STATE] = DFA_13_STATE;
	dfa.table['K'][DFA_START_STATE] = DFA_30_STATE;
	dfa.table['k'][DFA_START_STATE] = DFA_30_STATE;
	dfa.table['L'][DFA_START_STATE] = DFA_33_STATE;
	dfa.table['l'][DFA_START_STATE] = DFA_33_STATE;
	dfa.table['T'][DFA_START_STATE] = DFA_36_STATE;
	dfa.table['t'][DFA_START_STATE] = DFA_36_STATE;
	dfa.table['S'][DFA_START_STATE] = DFA_42_STATE;
	dfa.table['s'][DFA_START_STATE] = DFA_42_STATE;
	dfa.table['J'][DFA_START_STATE] = DFA_49_STATE;
	dfa.table['j'][DFA_START_STATE] = DFA_49_STATE;
	
	//STATE 1 | NUMBER STATE
	DFA_fill_state(&dfa, DFA_NUMBER_STATE, DFA_ERROR_STATE);
	
	for(char i = '0'; i <= '9'; i++){
		dfa.table[i][DFA_NUMBER_STATE] = DFA_NUMBER_STATE;
	}
	
	//STATE 3 | ERROR STATE
	DFA_fill_state(&dfa, DFA_ERROR_STATE, DFA_ERROR_STATE);
	
	//STATE 4 | A STATE
	dfa.table['M'][DFA_A_STATE] = DFA_AM_STATE;
	dfa.table['m'][DFA_A_STATE] = DFA_AM_STATE;
	dfa.table['D'][DFA_A_STATE] = DFA_AD_STATE;
	dfa.table['d'][DFA_A_STATE] = DFA_AD_STATE;
	dfa.table['R'][DFA_A_STATE] = DFA_11_STATE;
	dfa.table['r'][DFA_A_STATE] = DFA_11_STATE;
	
	//STATE 6 | M STATE
	dfa.table['D'][DFA_M_STATE] = DFA_MD_STATE;
	dfa.table['d'][DFA_M_STATE] = DFA_MD_STATE;
	
	//STATE 8 | AM STATE
	dfa.table['D'][DFA_AM_STATE] = DFA_AMD_STATE;
	dfa.table['d'][DFA_AM_STATE] = DFA_AMD_STATE;
	
	//STATE 11
	dfa.table['G'][DFA_11_STATE] = DFA_ARG_STATE;
	dfa.table['g'][DFA_11_STATE] = DFA_ARG_STATE;
	
	//STATE 13
	dfa.table['0'][DFA_13_STATE] = DFA_R0_STATE;
	dfa.table['1'][DFA_13_STATE] = DFA_R1_STATE;
	dfa.table['2'][DFA_13_STATE] = DFA_R2_STATE;
	dfa.table['3'][DFA_13_STATE] = DFA_R3_STATE;
	dfa.table['4'][DFA_13_STATE] = DFA_R4_STATE;
	dfa.table['5'][DFA_13_STATE] = DFA_R5_STATE;
	dfa.table['6'][DFA_13_STATE] = DFA_R6_STATE;
	dfa.table['7'][DFA_13_STATE] = DFA_R7_STATE;
	dfa.table['8'][DFA_13_STATE] = DFA_R8_STATE;
	dfa.table['9'][DFA_13_STATE] = DFA_R9_STATE;
	
	//STATE 15 | R1 STATE
	dfa.table['0'][DFA_R1_STATE] = DFA_R10_STATE;
	dfa.table['1'][DFA_R1_STATE] = DFA_R11_STATE;
	dfa.table['2'][DFA_R1_STATE] = DFA_R12_STATE;
	dfa.table['3'][DFA_R1_STATE] = DFA_R13_STATE;
	dfa.table['4'][DFA_R1_STATE] = DFA_R14_STATE;
	dfa.table['5'][DFA_R1_STATE] = DFA_R15_STATE;
	
	//STATE 30
	dfa.table['B'][DFA_30_STATE] = DFA_31_STATE;
	dfa.table['b'][DFA_30_STATE] = DFA_31_STATE;
	
	
	//STATE 31
	dfa.table['D'][DFA_31_STATE] = DFA_KBD_STATE;
	dfa.table['d'][DFA_31_STATE] = DFA_KBD_STATE;
	
	//STATE 33
	dfa.table['C'][DFA_33_STATE] = DFA_34_STATE;
	dfa.table['c'][DFA_33_STATE] = DFA_34_STATE;
	
	//STATE 34
	dfa.table['L'][DFA_34_STATE] = DFA_LCL_STATE;
	dfa.table['l'][DFA_34_STATE] = DFA_LCL_STATE;
	
	//STATE 36
	dfa.table['H'][DFA_36_STATE] = DFA_37_STATE;
	dfa.table['h'][DFA_36_STATE] = DFA_37_STATE;
	
	//STATE 37
	dfa.table['I'][DFA_37_STATE] = DFA_38_STATE;
	dfa.table['i'][DFA_37_STATE] = DFA_38_STATE;
	dfa.table['A'][DFA_37_STATE] = DFA_39_STATE;
	dfa.table['a'][DFA_37_STATE] = DFA_39_STATE;
	
	//STATE 38
	dfa.table['S'][DFA_38_STATE] = DFA_THIS_STATE;
	dfa.table['s'][DFA_38_STATE] = DFA_THIS_STATE;
	
	//STATE 39
	dfa.table['T'][DFA_39_STATE] = DFA_THAT_STATE;
	dfa.table['t'][DFA_39_STATE] = DFA_THAT_STATE;
	
	//STATE 42
	dfa.table['P'][DFA_42_STATE] = DFA_SP_STATE;
	dfa.table['p'][DFA_42_STATE] = DFA_SP_STATE;
	dfa.table['C'][DFA_42_STATE] = DFA_44_STATE;
	dfa.table['c'][DFA_42_STATE] = DFA_44_STATE;
	
	//STATE 44
	dfa.table['R'][DFA_44_STATE] = DFA_45_STATE;
	dfa.table['r'][DFA_44_STATE] = DFA_45_STATE;
	
	//STATE 45
	dfa.table['E'][DFA_45_STATE] = DFA_46_STATE;
	dfa.table['e'][DFA_45_STATE] = DFA_46_STATE;
	
	//STATE 46
	dfa.table['E'][DFA_46_STATE] = DFA_47_STATE;
	dfa.table['e'][DFA_46_STATE] = DFA_47_STATE;
	
	//STATE 47
	dfa.table['N'][DFA_47_STATE] = DFA_SCREEN_STATE;
	dfa.table['n'][DFA_47_STATE] = DFA_SCREEN_STATE;
	
	//STATE 49
	dfa.table['G'][DFA_49_STATE] = DFA_50_STATE;
	dfa.table['g'][DFA_49_STATE] = DFA_50_STATE;
	dfa.table['L'][DFA_49_STATE] = DFA_53_STATE;
	dfa.table['l'][DFA_49_STATE] = DFA_53_STATE;
	dfa.table['E'][DFA_49_STATE] = DFA_56_STATE;
	dfa.table['e'][DFA_49_STATE] = DFA_56_STATE;
	dfa.table['N'][DFA_49_STATE] = DFA_58_STATE;
	dfa.table['n'][DFA_49_STATE] = DFA_58_STATE;
	dfa.table['M'][DFA_49_STATE] = DFA_60_STATE;
	dfa.table['m'][DFA_49_STATE] = DFA_60_STATE;
	
	//STATE 50
	dfa.table['T'][DFA_50_STATE] = DFA_JGT_STATE;
	dfa.table['t'][DFA_50_STATE] = DFA_JGT_STATE;
	dfa.table['E'][DFA_50_STATE] = DFA_JGE_STATE;
	dfa.table['e'][DFA_50_STATE] = DFA_JGE_STATE;
	
	//STATE 53
	dfa.table['T'][DFA_53_STATE] = DFA_JLT_STATE;
	dfa.table['t'][DFA_53_STATE] = DFA_JLT_STATE;
	dfa.table['E'][DFA_53_STATE] = DFA_JLE_STATE;
	dfa.table['e'][DFA_53_STATE] = DFA_JLE_STATE;
	
	//STATE 56
	dfa.table['Q'][DFA_56_STATE] = DFA_JEQ_STATE;
	dfa.table['q'][DFA_56_STATE] = DFA_JEQ_STATE;
	
	//STATE 58
	dfa.table['E'][DFA_58_STATE] = DFA_JNE_STATE;
	dfa.table['e'][DFA_58_STATE] = DFA_JNE_STATE;
	
	//STATE 60
	dfa.table['P'][DFA_60_STATE] = DFA_JMP_STATE;
	dfa.table['p'][DFA_60_STATE] = DFA_JMP_STATE;
	
	//Setup all ERROR transition for all STATES
	for(int i = DFA_START_STATE; i < DFA_MAX_HEIGHT; i++){
		dfa.table[' '][i] = DFA_ERROR_STATE;
		dfa.table['\n'][i] = DFA_ERROR_STATE;
	}
	
	return dfa;
}

void DFA_fill_state(DFA_t* dfa, int state_to_fill, int dest_state){
	for(int i = 0; i < DFA_MAX_WIDTH; i++){
		dfa->table[i][state_to_fill] = dest_state;
	}
}

void DFA_run(DFA_t* dfa, const char* lexeme, int length){
	dfa->state = 0; //STARTING STATE = 0
	for(int i = 0; i < length; i++){
		dfa->state = dfa->table [lexeme[i]] [dfa->state];
	}
	
	for(int i = 0; i < DFA_NAMELESS_STATE_LENGTH; i++){
		if(dfa->state == DFA_NAMELESS_STATES[i]){
			dfa->state = DFA_ID_STATE;
			break;
		}
	}
}

hackToken_t hackScanner_newToken(int type, const char* lexeme, int length, int line){
	hackToken_t token = {type, lexeme, length, line};
	return token;
}

void printToken(hackToken_t token){
	printf("( %d, %.*s, %d )", token.type, token.length, token.lexeme, token.line);
}

TOKEN_List_t hackScanner_labels(hackScanner_t* scan){
	int length = 0;
	TOKEN_List_t list = TOKEN_List_init();
	DFA_t dfa = DFA_init();
	
	while(hackScanner_cur(scan) != '\0'){
		if(hackScanner_match(scan, '(')){
			hackScanner_adv(scan);
			scan->start = scan->current;
			
			while(!hackScanner_match(scan,')')){
				if(hackScanner_cur(scan) == '\0'){
					TOKEN_List_destroy(&list);
					scan->error = SCAN_INVALID_ID_ERROR;
					return list;
				}
				hackScanner_adv(scan);
			}
			
			length = scan->current - scan->start;
			if(length >= 49){
				TOKEN_List_destroy(&list);
				scan->error = SCAN_STRING_TOO_LONG_ERROR;
				return list;
			}
			
			DFA_run(&dfa, scan->start, length);
			
			if(dfa.state == DFA_ID_STATE){
				TOKEN_List_push(&list, hackScanner_newToken(TK_LABEL, scan->start, length, scan->line));
				dfa.state = DFA_START_STATE;
			}
			else{
				TOKEN_List_destroy(&list);
				scan->error = SCAN_INVALID_ID_ERROR;
				return list;
			}
		}
		else if(hackScanner_match(scan, '\n')) scan->line++;
		hackScanner_adv(scan);
	}
	
	return list;
}

TOKEN_List_t hackScanner_lexer(hackScanner_t* scan, TOKEN_List_t* labels){
	int length = 0;
	TOKEN_List_t list = TOKEN_List_init(); //Used to store the tokens.
	DFA_t dfa = DFA_init();
	
	while(hackScanner_cur(scan) != '\0'){
		switch(hackScanner_cur(scan)){
			case '0': TOKEN_List_push(&list, hackScanner_newToken(TK_0, "0", 1, scan->line)); break;
			case '1': TOKEN_List_push(&list, hackScanner_newToken(TK_1, "1", 1, scan->line)); break;
			case '=': TOKEN_List_push(&list, hackScanner_newToken(TK_EQ, "=", 1, scan->line)); break;
			case '+': TOKEN_List_push(&list, hackScanner_newToken(TK_ADD, "+", 1, scan->line)); break;
			case '-': TOKEN_List_push(&list, hackScanner_newToken(TK_SUB, "-", 1, scan->line)); break;
			case '|': TOKEN_List_push(&list, hackScanner_newToken(TK_OR, "|", 1, scan->line)); break;
			case '&': TOKEN_List_push(&list, hackScanner_newToken(TK_AND, "&", 1, scan->line)); break;
			case '!': TOKEN_List_push(&list, hackScanner_newToken(TK_BAN, "!", 1, scan->line)); break;
			case ';': TOKEN_List_push(&list, hackScanner_newToken(TK_SEMI, ";", 1, scan->line)); break;
			
			case '(':
				hackScanner_adv(scan);
				scan->start = scan->current;
			
				while(!hackScanner_match(scan,')')){
					if(hackScanner_cur(scan) == '\0'){
						TOKEN_List_destroy(&list);
						scan->error = SCAN_INVALID_ID_ERROR;
						return list;
					}
					hackScanner_adv(scan);
				}
			
				length = scan->current - scan->start;
				if(length >= 49){
					TOKEN_List_destroy(&list);
					scan->error = SCAN_STRING_TOO_LONG_ERROR;
					return list;
				}
				
				DFA_run(&dfa, scan->start, length);
				
				if(dfa.state == DFA_ID_STATE){
					TOKEN_List_push(&list, hackScanner_newToken(TK_LABEL, scan->start, length, scan->line));
					dfa.state = DFA_START_STATE;
				}
				else{
					TOKEN_List_destroy(&list);
					scan->error = SCAN_INVALID_ID_ERROR;
					return list;
				}
				break;
			
			case '@':
				TOKEN_List_push(&list, hackScanner_newToken(TK_AT, "@", 1, scan->line));
				hackScanner_adv(scan);
				
				scan->start = scan->current;
				
				while(hackScanner_peek(scan) != '\n'){
					if(hackScanner_peek(scan) == '\0') break;
					hackScanner_adv(scan);
				}
				
				length = (scan->current - scan->start) + 1;
				if(length >= 49){
					TOKEN_List_destroy(&list);
					scan->error = SCAN_STRING_TOO_LONG_ERROR;
					return list;
				}
				
				DFA_run(&dfa, scan->start, length);
				
				if(dfa.state == DFA_NUMBER_STATE) TOKEN_List_push(&list, hackScanner_newToken(TK_NUM, scan->start, length, scan->line));
				else if(dfa.state == DFA_ID_STATE){
					if(TOKEN_List_find(labels, scan->start, length)){
						TOKEN_List_push(&list, hackScanner_newToken(TK_LABEL, scan->start, length, scan->line));
					}
					else{
						TOKEN_List_push(&list, hackScanner_newToken(TK_ID, scan->start, length, scan->line));
					}
				}
				else if(dfa.state == DFA_SP_STATE) TOKEN_List_push(&list, hackScanner_newToken(TK_SP, scan->start, length, scan->line));
				else if(dfa.state == DFA_LCL_STATE) TOKEN_List_push(&list, hackScanner_newToken(TK_LCL, scan->start, length, scan->line));
				else if(dfa.state == DFA_ARG_STATE) TOKEN_List_push(&list, hackScanner_newToken(TK_ARG, scan->start, length, scan->line));
				else if(dfa.state == DFA_THIS_STATE) TOKEN_List_push(&list, hackScanner_newToken(TK_THIS, scan->start, length, scan->line));
				else if(dfa.state == DFA_THAT_STATE) TOKEN_List_push(&list, hackScanner_newToken(TK_THAT, scan->start, length, scan->line));
				else if(dfa.state == DFA_SCREEN_STATE) TOKEN_List_push(&list, hackScanner_newToken(TK_SCREEN, scan->start, length, scan->line));
				else if(dfa.state == DFA_KBD_STATE) TOKEN_List_push(&list, hackScanner_newToken(TK_KBD, scan->start, length, scan->line));
				else if(dfa.state == DFA_R0_STATE) TOKEN_List_push(&list, hackScanner_newToken(TK_R0, scan->start, length, scan->line));
				else if(dfa.state == DFA_R1_STATE) TOKEN_List_push(&list, hackScanner_newToken(TK_R1, scan->start, length, scan->line));
				else if(dfa.state == DFA_R2_STATE) TOKEN_List_push(&list, hackScanner_newToken(TK_R2, scan->start, length, scan->line));
				else if(dfa.state == DFA_R3_STATE) TOKEN_List_push(&list, hackScanner_newToken(TK_R3, scan->start, length, scan->line));
				else if(dfa.state == DFA_R4_STATE) TOKEN_List_push(&list, hackScanner_newToken(TK_R4, scan->start, length, scan->line));
				else if(dfa.state == DFA_R5_STATE) TOKEN_List_push(&list, hackScanner_newToken(TK_R5, scan->start, length, scan->line));
				else if(dfa.state == DFA_R6_STATE) TOKEN_List_push(&list, hackScanner_newToken(TK_R6, scan->start, length, scan->line));
				else if(dfa.state == DFA_R7_STATE) TOKEN_List_push(&list, hackScanner_newToken(TK_R7, scan->start, length, scan->line));
				else if(dfa.state == DFA_R8_STATE) TOKEN_List_push(&list, hackScanner_newToken(TK_R8, scan->start, length, scan->line));
				else if(dfa.state == DFA_R9_STATE) TOKEN_List_push(&list, hackScanner_newToken(TK_R9, scan->start, length, scan->line));
				else if(dfa.state == DFA_R10_STATE) TOKEN_List_push(&list, hackScanner_newToken(TK_R10, scan->start, length, scan->line));
				else if(dfa.state == DFA_R11_STATE) TOKEN_List_push(&list, hackScanner_newToken(TK_R11, scan->start, length, scan->line));
				else if(dfa.state == DFA_R12_STATE) TOKEN_List_push(&list, hackScanner_newToken(TK_R12, scan->start, length, scan->line));
				else if(dfa.state == DFA_R13_STATE) TOKEN_List_push(&list, hackScanner_newToken(TK_R13, scan->start, length, scan->line));
				else if(dfa.state == DFA_R14_STATE) TOKEN_List_push(&list, hackScanner_newToken(TK_R14, scan->start, length, scan->line));
				else if(dfa.state == DFA_R15_STATE) TOKEN_List_push(&list, hackScanner_newToken(TK_R15, scan->start, length, scan->line));
				else{
					TOKEN_List_destroy(&list);
					scan->error = SCAN_INVALID_ID_ERROR;
					return list;
				}
				dfa.state = DFA_START_STATE;
				break;
			
			case ' ':
			case '\t': break;
			case '\n': scan->line++; break;
			default:
				scan->start = scan->current;
				while(char_is_alpha(hackScanner_cur(scan))){
					if(hackScanner_peek(scan) == '\0') break;
					if(0 == char_is_alpha(hackScanner_peek(scan))) break;
					hackScanner_adv(scan);
				}
				
				length = (scan->current - scan->start) + 1;
				if(length >= 49){
					TOKEN_List_destroy(&list);
					scan->error = SCAN_STRING_TOO_LONG_ERROR;
					return list;
				}
				
				if(length > 0){
					DFA_run(&dfa, scan->start, length);
					
					//printf("LEX: %.*s STATE: %d\n", length, scan->start, dfa.state);
					
					switch(dfa.state){
						case DFA_A_STATE: TOKEN_List_push(&list, hackScanner_newToken(TK_A, scan->start, length, scan->line)); break;
						case DFA_D_STATE: TOKEN_List_push(&list, hackScanner_newToken(TK_D, scan->start, length, scan->line)); break;
						case DFA_M_STATE: TOKEN_List_push(&list, hackScanner_newToken(TK_M, scan->start, length, scan->line)); break;
						case DFA_AM_STATE: TOKEN_List_push(&list, hackScanner_newToken(TK_AM, scan->start, length, scan->line)); break;
						case DFA_AD_STATE: TOKEN_List_push(&list, hackScanner_newToken(TK_AD, scan->start, length, scan->line)); break;
						case DFA_MD_STATE: TOKEN_List_push(&list, hackScanner_newToken(TK_MD, scan->start, length, scan->line)); break;
						case DFA_AMD_STATE: TOKEN_List_push(&list, hackScanner_newToken(TK_AMD, scan->start, length, scan->line)); break;
						case DFA_JGT_STATE: TOKEN_List_push(&list, hackScanner_newToken(TK_JGT, scan->start, length, scan->line)); break;
						case DFA_JEQ_STATE: TOKEN_List_push(&list, hackScanner_newToken(TK_JEQ, scan->start, length, scan->line)); break;
						case DFA_JGE_STATE: TOKEN_List_push(&list, hackScanner_newToken(TK_JGE, scan->start, length, scan->line)); break;
						case DFA_JLT_STATE: TOKEN_List_push(&list, hackScanner_newToken(TK_JLT, scan->start, length, scan->line)); break;
						case DFA_JNE_STATE: TOKEN_List_push(&list, hackScanner_newToken(TK_JNE, scan->start, length, scan->line)); break;
						case DFA_JLE_STATE: TOKEN_List_push(&list, hackScanner_newToken(TK_JLE, scan->start, length, scan->line)); break;
						case DFA_JMP_STATE: TOKEN_List_push(&list, hackScanner_newToken(TK_JMP, scan->start, length, scan->line)); break;
						default:
							TOKEN_List_destroy(&list);
							scan->error = SCAN_KEYWORD_ERROR;
							return list;
					}
				}
		}
		hackScanner_adv(scan);
	}
	TOKEN_List_push(&list, hackScanner_newToken(TK_EOF, "", 0, 0));
	return list;
}