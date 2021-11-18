#ifndef HackScanner_h
#define HackScanner_h

#include "HackTokens.h"
#include "vm.h"

#define DFA_MAX_WIDTH 0xff
#define DFA_MAX_HEIGHT 4

//Scanner Error Codes
#define SCAN_OK 0
#define STRING_TOO_LONG_ERROR 1
#define INVALID_ID_ERROR 2

//DFA states
#define START_STATE 0
#define NUMBER 1
#define IDENTIFIER 2
#define ERROR_STATE 3

typedef struct{
	const char* begin;
	const char* start;
	const char* current;
	int line;
	int error;
}hackScanner_t;

typedef struct{
	int type;
	const char* lexeme;
	int length;
	int line;
}hackToken_t;

typedef struct{
	int table[DFA_MAX_WIDTH][DFA_MAX_HEIGHT];
	int state;
}DFA_t; //A DFA is used to check if ID names/numbers are valid.

typedef struct Node{
	hackToken_t token;
	struct Node* next;
	struct Node* prev;
}Node_t;

typedef struct{
	struct Node* head;
	struct Node* tail;
	int length;
}list_t;

//string function
//Made this as an easy way to deal with string comparison.
int stringcmp(const char* lex1, int len1, const char* lex2, int len2);

//Scanner function
void initS(hackScanner_t* scan, const char* source);
void resetS(hackScanner_t* scan);
void advS(hackScanner_t* scan);
char peekS(hackScanner_t* scan);
char curS(hackScanner_t* scan);
int matchS(hackScanner_t* scan, char c);
hackToken_t makeToken(int type, const char* lexeme, int length, int line);
void printToken(hackToken_t token);

//Gets all the labels first before going through the code.
//Helps with the differentiating between variable and label.
list_t getHackLabels(hackScanner_t* scan);
list_t lexer(hackScanner_t* scan, list_t* labels);

//DFA functions
void initDFA(DFA_t* dfa);
void checkID(DFA_t* dfa, const char* lexeme, int length);

//List functions
void push(list_t* list, hackToken_t token);
hackToken_t pop(list_t* list);
int find(list_t* list, const char* lexeme, int length);
void printList(list_t* list);
void freeList(list_t* list);

#endif