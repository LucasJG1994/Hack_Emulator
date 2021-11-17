#ifndef HackScanner_h
#define HackScanner_h

#include "HackTokens.h"
#include "vm.h"

typedef struct{
	const char* start;
	const char* current;
	int line;
	int error;
}hackScanner_t;

typedef struct{
	int type;
	const char* lexeme;
	int line;
}hackToken_t;

typedef struct{
	int table[0xff][4];
	int state;
}DFA_t; //A DFA is used to check if ID names/numbers are valid.

typedef struct Node{
	hackToken_t token;
	struct Node* next;
	struct Node* prev;
}Node_t;

typedef struct{
	struct Node* head, tail;
}list_t;

void initS(hackScanner_t* scan, const char* source);
void advS(hackScanner_t* scan);
char peekS(hackScanner_t* scan);
int matchS(hackScanner_t* scan, int type);
void lexer(list_t* list);

void initDFA(DFA_t* dfa);
int checkID(DFA_t* dfa, const char* lexeme);

#endif