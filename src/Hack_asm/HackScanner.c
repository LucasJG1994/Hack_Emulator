#include "HackScanner.h"

int stringcmp(const char* lex1, int len1, const char* lex2, int len2){
	if(len1 != len2) return 0;
	
	int length = len1;
	
	if(lex1 == NULL || lex2 == NULL) return -1;
	
	for(int i = 0; i < length; i++){
		if((lex1[i] - lex2[i]) != 0){
			return 0;
		}
	}
	
	return 1;
}

void initS(hackScanner_t* scan, const char* source){
	scan->begin = source;
	scan->start = source;
	scan->current = source;
	scan->line = 1;
	scan->error = SCAN_OK;
}

void resetS(hackScanner_t* scan){
	scan->start = scan->begin;
	scan->current = scan->begin;
	scan->line = 1;
}

void advS(hackScanner_t* scan){
	scan->current++;
}

char peekS(hackScanner_t* scan){
	return scan->current[1];
}

char curS(hackScanner_t* scan){
	return scan->current[0];
}

int matchS(hackScanner_t* scan, char c){
	return curS(scan) == c;
}

void initDFA(DFA_t* dfa){
	//STATE TRANSITION TABLE
	//STATE 0 | START STATE
	for(int i = 0; i < DFA_MAX_WIDTH; i++){
		dfa->table[i][0] = 2;
	}
	
	for(char i = '0'; i <= '9'; i++){
		dfa->table[i][0] = 1;
	}
	
	//STATE 1 | FINISH STATE
	for(int i = 0; i < DFA_MAX_WIDTH; i++){
		dfa->table[i][1] = 3;
	}
	
	for(char i = '0'; i <= '9'; i++){
		dfa->table[i][1] = 1;
	}
	
	//STATE 2 | FINISH STATE
	for(int i = 0; i < DFA_MAX_WIDTH; i++){
		dfa->table[i][2] = 2;
	}
	
	dfa->table[' '][2] = 3;
	dfa->table['\n'][2] = 3;
	
	//STATE 3 | ERROR STATE
	for(int i = 0; i < DFA_MAX_WIDTH; i++){
		dfa->table[i][3] = 3;
	}
}

void checkID(DFA_t* dfa, const char* lexeme, int length){
	dfa->state = 0; //STARTING STATE = 0
	for(int i = 0; i < length; i++){
		dfa->state = dfa->table [lexeme[i]] [dfa->state];
	}
}

hackToken_t makeToken(int type, const char* lexeme, int length, int line){
	hackToken_t token = {type, lexeme, length, line};
	return token;
}

void printToken(hackToken_t token){
	printf("( %d, %.*s, %d )", token.type, token.length, token.lexeme, token.line);
}

list_t getHackLabels(hackScanner_t* scan){
	int length = 0;
	char lexeme[50]; //This will probably be removed.
	list_t list = {NULL};
	DFA_t dfa = {0};
	
	initDFA(&dfa);
	
	while(curS(scan) != '\0'){
		if(matchS(scan, '(')){
			advS(scan);
			scan->start = scan->current;
			
			while(!matchS(scan,')')){
				if(curS(scan) == '\0'){
					freeList(&list);
					scan->error = INVALID_ID_ERROR;
					return list;
				}
				advS(scan);
			}
			
			length = scan->current - scan->start;
			if(length >= 49){
				freeList(&list);
				scan->error = STRING_TOO_LONG_ERROR;
				return list;
			}
			
			sprintf(lexeme, "%.*s", length, scan->start); //Might not be needed.
			checkID(&dfa, lexeme, length); //scan->start with length could be used instead of lexeme.
			
			if(dfa.state == START_STATE || dfa.state == NUMBER || dfa.state == ERROR_STATE){
				freeList(&list);
				scan->error = INVALID_ID_ERROR;
				return list;
			}
			
			push(&list, makeToken(TK_LABEL, scan->start, length, scan->line));
		}
		else if(matchS(scan, '\n')) scan->line++;
		advS(scan);
	}
	
	return list;
}

list_t lexer(hackScanner_t* scan, list_t* labels){
	int length = 0;
	char lexeme[50]; //Might not be needed.
	list_t list = {NULL}; //Used to store the tokens.
	DFA_t dfa = {0};
	
	initDFA(&dfa);
	
	while(curS(scan) != '\0'){
		switch(curS(scan)){
			case 'A':
			case 'a': push(&list, makeToken(TK_A, "A", 1, scan->line)); break;
			
			case 'D':
			case 'd': push(&list, makeToken(TK_D, "D", 1, scan->line)); break;
			
			case 'M':
			case 'm': push(&list, makeToken(TK_M, "M", 1, scan->line)); break;
			
			case '0': push(&list, makeToken(TK_0, "0", 1, scan->line)); break;
			case '1': push(&list, makeToken(TK_1, "1", 1, scan->line)); break;
			case '=': push(&list, makeToken(TK_EQ, "=", 1, scan->line)); break;
			case '+': push(&list, makeToken(TK_ADD, "+", 1, scan->line)); break;
			case '-': push(&list, makeToken(TK_SUB, "-", 1, scan->line)); break;
			case '|': push(&list, makeToken(TK_OR, "|", 1, scan->line)); break;
			case '&': push(&list, makeToken(TK_AND, "&", 1, scan->line)); break;
			case '!': push(&list, makeToken(TK_BAN, "!", 1, scan->line)); break;
			case ';': push(&list, makeToken(TK_SEMI, ";", 1, scan->line)); break;
			
			case '(':
				advS(scan);
				scan->start = scan->current;
			
				while(!matchS(scan,')')){
					if(curS(scan) == '\0'){
						freeList(&list);
						scan->error = INVALID_ID_ERROR;
						return list;
					}
					advS(scan);
				}
			
				length = scan->current - scan->start;
				if(length >= 49){
					freeList(&list);
					scan->error = STRING_TOO_LONG_ERROR;
					return list;
				}
				
				sprintf(lexeme, "%.*s", length, scan->start); //Might not be needed.
				checkID(&dfa, lexeme, length); //scan->start and length can replace lexeme
				
				if(dfa.state == START_STATE || dfa.state == NUMBER || dfa.state == ERROR_STATE){
					freeList(&list);
					scan->error = INVALID_ID_ERROR;
					return list;
				}
				
				push(&list, makeToken(TK_LABEL, scan->start, length, scan->line));
				break;
			
			case '@':
				push(&list, makeToken(TK_AT, "@", 1, scan->line));
				advS(scan);
				
				scan->start = scan->current;
				
				while(peekS(scan) != '\n'){
					if(peekS(scan) == '\0') break;
					advS(scan);
				}
				
				length = (scan->current - scan->start) + 1;
				if(length >= 49){
					freeList(&list);
					scan->error = STRING_TOO_LONG_ERROR;
					return list;
				}
				
				sprintf(lexeme, "%.*s", length, scan->start);
				checkID(&dfa, lexeme, length);
				
				if(dfa.state == NUMBER) push(&list, makeToken(TK_NUM, scan->start, length, scan->line));
				else if(dfa.state == IDENTIFIER){
					if(find(labels, scan->start, length)){
						push(&list, makeToken(TK_LABEL, scan->start, length, scan->line));
					}
					else{
						push(&list, makeToken(TK_ID, scan->start, length, scan->line));
					}
				}
				break;
			
			case ' ':
			case '\t': break;
			case '\n': scan->line++; break;
		}
		advS(scan);
	}
	push(&list, makeToken(TK_EOF, "", 0, 0));
	return list;
}

void push(list_t* list, hackToken_t token){
	if(list->head == NULL){
		struct Node* tmp = (struct Node*)calloc(1, sizeof(struct Node));
		tmp->token = token;
		tmp->next = NULL;
		tmp->prev = NULL;
		list->head = tmp;
		list->tail = tmp;
		list->length = 1;
		return;
	}
	else{
		struct Node* tmp;
		list->tail->next = (struct Node*)calloc(1, sizeof(struct Node));
		list->tail->next->token = token;
		list->tail->next->next = NULL;
		tmp = list->tail;
		list->tail = list->tail->next;
		list->tail->prev = tmp;
		list->length++;
	}
}

hackToken_t pop(list_t* list){
	hackToken_t token = {NULL};
	struct Node* tmp;
	if(list->head == NULL) return token;
	
	if(list->tail->prev != NULL){
		tmp = list->tail;
		list->tail = list->tail->prev;
		list->tail->next = NULL;
		token = tmp->token;
		free(tmp);
	}
	else{
		token = list->head->token;
		list->tail = NULL;
		tmp = list->head;
		list->head = NULL;
		free(tmp);
	}
	
	return token;
}

int find(list_t* list, const char* lexeme, int length){
	struct Node* current = list->head;
	while(current != NULL){
		if(stringcmp(lexeme, length, current->token.lexeme, current->token.length)) return 1;
		current = current->next;
	}
	return 0;
}

void printList(list_t* list){
	struct Node* current = list->head;
	printf("[ ");
	while(current != NULL){
		printToken(current->token);
		current = current->next;
	}
	printf(" ]");
}

void freeList(list_t* list){
	struct Node* tmp;
	if(list->head == NULL) return;
	
	list->tail = NULL;
	while(list->head != NULL){
		tmp = list->head;
		list->head = list->head->next;
		free(tmp);
	}
	list->head = NULL;
}