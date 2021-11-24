#ifndef HackParser_h
#define HackParser_h

#include "HackScanner.h"
#include "vm.h"

typedef struct Label_Declartion{
	const char* string;
	int length;
	int value;
}Lab_Dec;

typedef struct Lost_Labels{
	const char* string;
	int length;
	u16 addr[1000];
	int index;
}L_Lab;

LIST_HEADER(Lab_Dec);
LIST_HEADER(L_Lab);

//Parser states
typedef enum{
	PARSER_OK, PARSER_ERROR
}parser_states;

typedef struct hackParser{
	TOKEN_List_t* tokens;
	Lab_Dec_List_t labels;
	Lab_Dec_List_t variables;
	L_Lab_List_t lost;
	hackToken_t current;
	int error;
}hackParser_t;

//Function will be used for both labels and varaibles
Lab_Dec make_label(const char* lexeme, int length, int value);
L_Lab make_lost_label(const char* lexeme, int length, int value);

//Parser functions
hackParser_t hackParser_init(TOKEN_List_t* tokens);
void hackParser_adv(hackParser_t* parser);
int hackParser_cur(hackParser_t* parser);
int hackParser_match(hackParser_t* parser, int type);
int hackParser_consume(hackParser_t* parser, int type, const char* msg);
void hackParser_run(hackParser_t* parser, vm_t* vm);
void hackParser_comp(hackParser_t* parser, int* comp);

#endif