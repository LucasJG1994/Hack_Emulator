#include "HackParser.h"

hackParser_t hackParser_init(list_t* tokens){
	hackParser_t parser = {NULL};
	parser.tokens = tokens;
	parser.current = list_pop(parser.tokens);
	return parser;
}

void hackParser_adv(hackParser_t* parser){
	parser->current = list_pop(parser->tokens);
}

int hackParser_cur(hackParser_t* parser){
	return parser->current.type;
}

int hackParser_match(hackParser_t* parser, int type){
	return hackParser_cur(parser) == type;
}

int hackParser_consume(hackParser_t* parser, int type, const char* msg){
	if(hackParser_match(parser, type){
		hackParser_adv(parser);
	}
	else{
		printf("Error: %s on line %d\n", msg, parser->current.line);
		return PARSER_ERROR;
	}
}

void hackParser_run(hackParser_t* parser, vm_t* vm){
	switch(hackParser_cur(parser)){
		case TK_A:
			
		case TK_D:
		case TK_M:
	}
}