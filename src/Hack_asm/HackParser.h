#ifndef HackParser_h
#define HackParser_h

#include "HackScanner.h"
#include "vm.h"

//Parser states
typedef enum{
	PARSER_OK, PARSER_ERROR
}parser_states;

typedef struct hackParser{
	list_t* tokens;
	hackToken_t current;
	int error;
}hackParser_t

hackParser_t hackParser_init(list_t* tokens);
void hackParser_adv(hackParser_t* parser);
int hackParser_cur(hackParser_t* parser);
int hackParser_match(hackParser_t* parser, int type);
int hackParser_consume(hackParser_t* parser, int type, const char* msg);
void hackParser_run(hackParser_t* parser, vm_t* vm);

#endif