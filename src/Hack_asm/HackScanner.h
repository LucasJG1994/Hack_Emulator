#ifndef HackScanner_h
#define HackScanner_h

#include "HackTokens.h"
#include "vm.h"

#define DFA_MAX_WIDTH 0xff
#define DFA_MAX_HEIGHT 4

//Scanner Error Codes
typedef enum{
	SCAN_OK, SCAN_STRING_TOO_LONG_ERROR, SCAN_INVALID_ID_ERROR
}scanner_codes;

//DFA states
typedef enum{
	DFA_START_STATE, DFA_NUMBER_STATE, DFA_ID_STATE, DFA_ERROR_STATE
}dfa_states;

typedef struct hackScanner{
	const char* begin;
	const char* start;
	const char* current;
	int line;
	int error;
}hackScanner_t;

typedef struct hackToken{
	int type;
	const char* lexeme;
	int length;
	int line;
}hackToken_t;

typedef struct DFA{
	int table[DFA_MAX_WIDTH][DFA_MAX_HEIGHT];
	int state;
}DFA_t; //A DFA is used to check if ID names/numbers are valid.

typedef struct Node{
	hackToken_t token;
	struct Node* next;
	struct Node* prev;
}Node_t;

typedef struct list{
	struct Node* head;
	struct Node* tail;
	int length;
}list_t;

//string function
//Made this as an easy way to deal with string comparison.
int stringcmp(const char* lex1, int len1, const char* lex2, int len2);

//Scanner function
struct hackScanner hackScanner_init(const char* source);
void hackScanner_reset(hackScanner_t* scan);
void hackScanner_adv(hackScanner_t* scan);
char hackScanner_peek(hackScanner_t* scan);
char hackScanner_cur(hackScanner_t* scan);
int hackScanner_match(hackScanner_t* scan, char c);
hackToken_t hackScanner_newToken(int type, const char* lexeme, int length, int line);
void printToken(hackToken_t token);

//Gets all the labels first before going through the code.
//Helps with the differentiating between variable and label.
list_t hackScanner_labels(hackScanner_t* scan);
list_t hackScanner_lexer(hackScanner_t* scan, list_t* labels);

//DFA functions
struct DFA DFA_init();
void DFA_run(DFA_t* dfa, const char* lexeme, int length);

//List functions
struct list list_new();
void list_push(list_t* list, hackToken_t token);
hackToken_t list_pop(list_t* list);
int list_find(list_t* list, const char* lexeme, int length);
void list_print(list_t* list);
void list_destroy(list_t* list);

#endif