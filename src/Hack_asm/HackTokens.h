#ifndef HackTokens_h
#define HackTokens_h

#include "string/string_module.h"

enum token_type{
	TK_AT = 1, TK_A, TK_D, TK_M, TK_AM, TK_AD, TK_MD, TK_AMD,
	TK_0, TK_1, TK_EQ, TK_ADD, TK_SUB, TK_ID, TK_LABEL, TK_AND,
	TK_OR, TK_BAN, TK_NUM, TK_SEMI, TK_JGT, TK_JEQ, TK_JGE,
	TK_JLT, TK_JNE, TK_JLE, TK_JMP, TK_SP, TK_LCL, TK_ARG, TK_THIS,
	TK_THAT, TK_SCREEN, TK_KBD, TK_R0, TK_R1, TK_R2, TK_R3, TK_R4, 
	TK_R5, TK_R6, TK_R7, TK_R8, TK_R9, TK_R10, TK_R11, TK_R12, TK_R13, 
	TK_R14, TK_R15, TK_EOF = -1
};

struct token{
	enum token_type	type;
	struct string*  lexeme;
	int				line;
};

struct token* token_new(enum token_type type, const char* lexeme, int length, int line);
void		  token_print(struct token* token);

#endif