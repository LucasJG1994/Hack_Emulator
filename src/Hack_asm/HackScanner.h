#ifndef HackScanner_h
#define HackScanner_h

#include "HackTokens.h"
#include "vm.h"

#define DFA_MAX_WIDTH 0xff
#define DFA_MAX_HEIGHT 50

//Scanner Error Codes
typedef enum{
	SCAN_OK, SCAN_STRING_TOO_LONG_ERROR, SCAN_INVALID_ID_ERROR,
	SCAN_KEYWORD_ERROR
}scanner_codes;

//DFA states
typedef enum{
	DFA_START_STATE, DFA_NUMBER_STATE, DFA_ID_STATE, DFA_ERROR_STATE,
	DFA_A_STATE, DFA_D_STATE, DFA_M_STATE, DFA_MD_STATE, DFA_AM_STATE,
	DFA_AMD_STATE, DFA_AD_STATE, DFA_11_STATE, DFA_ARG_STATE, DFA_13_STATE,
	DFA_R0_STATE, DFA_R1_STATE, DFA_R2_STATE, DFA_R3_STATE, DFA_R4_STATE,
	DFA_R5_STATE, DFA_R6_STATE, DFA_R7_STATE, DFA_R8_STATE, DFA_R9_STATE,
	DFA_R10_STATE, DFA_R11_STATE, DFA_R12_STATE, DFA_R13_STATE, DFA_R14_STATE,
	DFA_R15_STATE, DFA_30_STATE, DFA_31_STATE, DFA_KBD_STATE, DFA_33_STATE,
	DFA_34_STATE, DFA_LCL_STATE, DFA_36_STATE, DFA_37_STATE, DFA_38_STATE,
	DFA_39_STATE, DFA_THIS_STATE, DFA_THAT_STATE, DFA_42_STATE,
	DFA_SP_STATE, DFA_44_STATE, DFA_45_STATE, DFA_46_STATE, DFA_47_STATE,
	DFA_SCREEN_STATE, DFA_49_STATE, DFA_50_STATE, DFA_JGT_STATE,
	DFA_JGE_STATE, DFA_53_STATE, DFA_JLT_STATE, DFA_JLE_STATE,
	DFA_56_STATE, DFA_JEQ_STATE, DFA_58_STATE, DFA_JNE_STATE,
	DFA_60_STATE, DFA_JMP_STATE
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
int string_cmp(const char* lex1, int len1, const char* lex2, int len2);
int char_is_alpha(char c);

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
void DFA_fill_state(DFA_t* dfa, int state_to_fill, int dest_state);
void DFA_run(DFA_t* dfa, const char* lexeme, int length);

//List functions
struct list list_new();
void list_push(list_t* list, hackToken_t token);
hackToken_t list_peek(list_t* list);
hackToken_t list_pop(list_t* list);
int list_find(list_t* list, const char* lexeme, int length);
void list_print(list_t* list);
void list_destroy(list_t* list);

#endif