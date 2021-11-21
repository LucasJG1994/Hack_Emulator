#ifndef HackTokens_h
#define HackTokens_h

typedef enum{
	TK_AT = 1, TK_A, TK_D, TK_M, TK_AM, TK_AD, TK_MD, TK_AMD,
	TK_0, TK_1, TK_EQ, TK_ADD, TK_SUB, TK_ID, TK_LABEL, TK_AND,
	TK_OR, TK_BAN, TK_NUM, TK_SEMI, TK_JGT, TK_JEQ, TK_JGE,
	TK_JLT, TK_JNE, TK_JLE, TK_JMP, TK_SP, TK_LCL, TK_ARG, TK_THIS,
	TK_THAT, TK_SCREEN, TK_KBD, TK_EOF = -1
}tok;

typedef struct{
	const char* key;
	const int value;
}token_map;

/*token_map tok_map[] = {
	{"@", TK_AT},
	{"A", TK_A},
	{"D", TK_D},
	{"M", TK_M},
	{"0", TK_0},
	{"1", TK_1},
	{"=", TK_EQ},
	{"+", TK_ADD},
	{"-", TK_SUB},
	{"&", TK_AND},
	{"|", TK_OR},
	{"!", TK_BAN},
	{";", TK_SEMI}
};*/

#endif