#include "HackScanner.h"
#include "HackTokens.h"
#include "hash_table/Hash_table_module.h"
#include "symbol_table/symbol_table_singleton.h"
#include <stdio.h>
#include <stdlib.h>

struct scanner {
	const char* begin;
	const char* cur;
	const char* start;
	int line;
	int error;
};

static struct scanner scan;

//Shared Globals
int				HS_TYPE;
struct string*	HS_LEXEME = NULL;
int				HS_LINE;

static int char_is_alpha(char c){
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

static int char_is_num(char c) {
	return c >= '0' && c <= '9';
}

static int str_all_num(const char* str, int length){
	if(length == 0) return 0;
	for(int i = 0; i < length; i++){
		if(char_is_num(str[i]) == 0) return 0;
	}
	return 1;
}

void hs_init(const char* source){
	scan.begin  = source;
	scan.cur	= source;
	scan.start	= source;
	scan.line	= 1;
	scan.error	= SCAN_OK;


	//Symbol_table is a singleton residing in symbol_table folder
	hash_table_add(symbol_table, "r0",     2, TK_R0     , 0);
	hash_table_add(symbol_table, "r1",     2, TK_R1     , 1);
	hash_table_add(symbol_table, "r2",     2, TK_R2     , 2);
	hash_table_add(symbol_table, "r3",     2, TK_R3     , 3);
	hash_table_add(symbol_table, "r4",     2, TK_R4     , 4);
	hash_table_add(symbol_table, "r5",     2, TK_R5     , 5);
	hash_table_add(symbol_table, "r6",     2, TK_R6     , 6);
	hash_table_add(symbol_table, "r7",     2, TK_R7     , 7);
	hash_table_add(symbol_table, "r8",     2, TK_R8     , 8);
	hash_table_add(symbol_table, "r9",     2, TK_R9     , 9);
	hash_table_add(symbol_table, "r10",    3, TK_R10    , 10);
	hash_table_add(symbol_table, "r11",    3, TK_R11    , 11);
	hash_table_add(symbol_table, "r12",    3, TK_R12    , 12);
	hash_table_add(symbol_table, "r13",    3, TK_R13    , 13);
	hash_table_add(symbol_table, "r14",    3, TK_R14    , 14);
	hash_table_add(symbol_table, "r15",    3, TK_R15    , 15);
	hash_table_add(symbol_table, "sp",     2, TK_SP     , 0);
	hash_table_add(symbol_table, "lcl",    3, TK_LCL    , 1);
	hash_table_add(symbol_table, "arg",    3, TK_ARG    , 2);
	hash_table_add(symbol_table, "this",   4, TK_THIS   , 3);
	hash_table_add(symbol_table, "that",   4, TK_THAT   , 4);
	hash_table_add(symbol_table, "screen", 6, TK_SCREEN , 16384);
	hash_table_add(symbol_table, "kbd",    3, TK_KBD    , 24576);

	hash_table_add(symbol_table, "jgt", 3, TK_JGT, 0);
	hash_table_add(symbol_table, "jge", 3, TK_JGE, 0);
	hash_table_add(symbol_table, "jlt", 3, TK_JLT, 0);
	hash_table_add(symbol_table, "jle", 3, TK_JLE, 0);
	hash_table_add(symbol_table, "jne", 3, TK_JNE, 0);
	hash_table_add(symbol_table, "jeq", 3, TK_JEQ, 0);
	hash_table_add(symbol_table, "jmp", 3, TK_JMP, 0);

	hash_table_add(symbol_table, "a"  , 1, TK_A  , 0);
	hash_table_add(symbol_table, "d"  , 1, TK_D  , 0);
	hash_table_add(symbol_table, "m"  , 1, TK_M  , 0);
	hash_table_add(symbol_table, "ad" , 2, TK_AD , 0);
	hash_table_add(symbol_table, "am" , 2, TK_AM , 0);
	hash_table_add(symbol_table, "md" , 2, TK_MD , 0);
	hash_table_add(symbol_table, "amd", 3, TK_AMD, 0);
}

static inline void hs_adv(){
	scan.cur++;
}

static inline char hs_peek(){
	return scan.cur[1];
}

static inline int hs_match(char c){
	return *scan.cur == c;
}

static inline int hs_get_len() {
	return (int)(scan.cur - scan.start);
}

void hs_reset() {
	scan.start = scan.begin;
	scan.cur   = scan.begin;
	scan.line = 1;
}

static inline void hs_token(int type, int length) {
	HS_TYPE			= type;
	HS_LEXEME		= string_init(scan.start, length);
	HS_LINE			= scan.line;
}

static void hs_tokenizer() {
	while(*scan.cur != 0){
		switch (*scan.cur) {
			case '=': { hs_token(TK_EQ, 1)  ; hs_adv(); return; }
			case '+': { hs_token(TK_ADD, 1) ; hs_adv(); return; }
			case '-': { hs_token(TK_SUB, 1) ; hs_adv(); return; }
			case '!': { hs_token(TK_BAN, 1) ; hs_adv(); return; }
			case '&': { hs_token(TK_AND, 1) ; hs_adv(); return; }
			case '|': { hs_token(TK_OR, 1)  ; hs_adv(); return; }
			case '@': { hs_token(TK_AT, 1)  ; hs_adv(); return; }
			case ';': { hs_token(TK_SEMI, 1); hs_adv(); return; }
			case '(': {
				hs_adv();
				scan.start = scan.cur;
				while (!hs_match(')'))
					hs_adv();
				
				hs_token(TK_LABEL, hs_get_len());
				hs_adv();
				return;
			}
			case '/': {
				if (hs_peek() == '/') {
					while(hs_peek() != '\n')
						hs_adv();
				}
				//Put error recovery here.
				break;
			}
			case ' ': break;
			case '\t': break;
			case '\n': scan.line++; break;
			default: {
				scan.start = scan.cur;
				while (char_is_alpha(*scan.cur) || char_is_num(*scan.cur)) {
					hs_adv();
				}

				int len = hs_get_len();

				if(len > 0){
					struct string* str = string_init(scan.start, len);
					struct pair* tmp = hash_table_find(symbol_table, str);
					string_close(str);

					if (tmp == NULL) {
						if (str_all_num(scan.start, len)) { hs_token(TK_NUM, len); return; }
						else{ hs_token(TK_ID,len); return; }
					}
					else{ hs_token(tmp->type, len); return; }
				}
			}
		}
		
		hs_adv();
	}

	hs_token(TK_EOF, 0);
}

scanner_states hs_advance() {
	hs_tokenizer();
	if(scan.error == 0) return SCAN_OK;
	return 1;
}