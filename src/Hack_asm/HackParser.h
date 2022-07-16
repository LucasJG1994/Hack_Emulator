#ifndef HackParser_h
#define HackParser_h

//Parser states
typedef enum{
	PARSER_OK, PARSER_ERROR
}parser_states;

//Parser functions
void hp_init();
void hp_start();

#endif