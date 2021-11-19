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

struct hackScanner hackScanner_init(const char* source){
	struct hackScanner scan = {NULL};
	scan.begin = source;
	scan.start = source;
	scan.current = source;
	scan.line = 1;
	scan.error = SCAN_OK;
	return scan;
}

void hackScanner_reset(hackScanner_t* scan){
	scan->start = scan->begin;
	scan->current = scan->begin;
	scan->line = 1;
}

void hackScanner_adv(hackScanner_t* scan){
	scan->current++;
}

char hackScanner_peek(hackScanner_t* scan){
	return scan->current[1];
}

char hackScanner_cur(hackScanner_t* scan){
	return scan->current[0];
}

int hackScanner_match(hackScanner_t* scan, char c){
	return hackScanner_cur(scan) == c;
}

struct DFA DFA_init(){
	struct DFA dfa = {0};
	//STATE TRANSITION TABLE
	//STATE 0 | START STATE
	for(int i = 0; i < DFA_MAX_WIDTH; i++){
		dfa.table[i][0] = 2;
	}
	
	for(char i = '0'; i <= '9'; i++){
		dfa.table[i][0] = 1;
	}
	
	//STATE 1 | FINISH STATE
	for(int i = 0; i < DFA_MAX_WIDTH; i++){
		dfa.table[i][1] = 3;
	}
	
	for(char i = '0'; i <= '9'; i++){
		dfa.table[i][1] = 1;
	}
	
	//STATE 2 | FINISH STATE
	for(int i = 0; i < DFA_MAX_WIDTH; i++){
		dfa.table[i][2] = 2;
	}
	
	dfa.table[' '][2] = 3;
	dfa.table['\n'][2] = 3;
	
	//STATE 3 | ERROR STATE
	for(int i = 0; i < DFA_MAX_WIDTH; i++){
		dfa.table[i][3] = 3;
	}
	return dfa;
}

void DFA_run(DFA_t* dfa, const char* lexeme, int length){
	dfa->state = 0; //STARTING STATE = 0
	for(int i = 0; i < length; i++){
		dfa->state = dfa->table [lexeme[i]] [dfa->state];
	}
}

hackToken_t hackScanner_newToken(int type, const char* lexeme, int length, int line){
	hackToken_t token = {type, lexeme, length, line};
	return token;
}

void printToken(hackToken_t token){
	printf("( %d, %.*s, %d )", token.type, token.length, token.lexeme, token.line);
}

list_t hackScanner_labels(hackScanner_t* scan){
	int length = 0;
	list_t list = list_new();
	DFA_t dfa = DFA_init();
	
	while(hackScanner_cur(scan) != '\0'){
		if(hackScanner_match(scan, '(')){
			hackScanner_adv(scan);
			scan->start = scan->current;
			
			while(!hackScanner_match(scan,')')){
				if(hackScanner_cur(scan) == '\0'){
					list_destroy(&list);
					scan->error = SCAN_INVALID_ID_ERROR;
					return list;
				}
				hackScanner_adv(scan);
			}
			
			length = scan->current - scan->start;
			if(length >= 49){
				list_destroy(&list);
				scan->error = SCAN_STRING_TOO_LONG_ERROR;
				return list;
			}
			
			DFA_run(&dfa, scan->start, length); //scan->start with length could be used instead of lexeme.
			
			if(dfa.state == DFA_START_STATE || dfa.state == DFA_NUMBER_STATE || dfa.state == DFA_ERROR_STATE){
				list_destroy(&list);
				scan->error = SCAN_INVALID_ID_ERROR;
				return list;
			}
			
			list_push(&list, hackScanner_newToken(TK_LABEL, scan->start, length, scan->line));
		}
		else if(hackScanner_match(scan, '\n')) scan->line++;
		hackScanner_adv(scan);
	}
	
	return list;
}

list_t hackScanner_lexer(hackScanner_t* scan, list_t* labels){
	int length = 0;
	list_t list = list_new(); //Used to store the tokens.
	DFA_t dfa = DFA_init();
	
	while(hackScanner_cur(scan) != '\0'){
		switch(hackScanner_cur(scan)){
			case 'A':
			case 'a': list_push(&list, hackScanner_newToken(TK_A, "A", 1, scan->line)); break;
			
			case 'D':
			case 'd': list_push(&list, hackScanner_newToken(TK_D, "D", 1, scan->line)); break;
			
			case 'M':
			case 'm': list_push(&list, hackScanner_newToken(TK_M, "M", 1, scan->line)); break;
			
			case '0': list_push(&list, hackScanner_newToken(TK_0, "0", 1, scan->line)); break;
			case '1': list_push(&list, hackScanner_newToken(TK_1, "1", 1, scan->line)); break;
			case '=': list_push(&list, hackScanner_newToken(TK_EQ, "=", 1, scan->line)); break;
			case '+': list_push(&list, hackScanner_newToken(TK_ADD, "+", 1, scan->line)); break;
			case '-': list_push(&list, hackScanner_newToken(TK_SUB, "-", 1, scan->line)); break;
			case '|': list_push(&list, hackScanner_newToken(TK_OR, "|", 1, scan->line)); break;
			case '&': list_push(&list, hackScanner_newToken(TK_AND, "&", 1, scan->line)); break;
			case '!': list_push(&list, hackScanner_newToken(TK_BAN, "!", 1, scan->line)); break;
			case ';': list_push(&list, hackScanner_newToken(TK_SEMI, ";", 1, scan->line)); break;
			
			case '(':
				hackScanner_adv(scan);
				scan->start = scan->current;
			
				while(!hackScanner_match(scan,')')){
					if(hackScanner_cur(scan) == '\0'){
						list_destroy(&list);
						scan->error = SCAN_INVALID_ID_ERROR;
						return list;
					}
					hackScanner_adv(scan);
				}
			
				length = scan->current - scan->start;
				if(length >= 49){
					list_destroy(&list);
					scan->error = SCAN_STRING_TOO_LONG_ERROR;
					return list;
				}
				
				DFA_run(&dfa, scan->start, length); //scan->start and length can replace lexeme
				
				if(dfa.state == DFA_START_STATE || dfa.state == DFA_NUMBER_STATE || dfa.state == DFA_ERROR_STATE){
					list_destroy(&list);
					scan->error = SCAN_INVALID_ID_ERROR;
					return list;
				}
				
				list_push(&list, hackScanner_newToken(TK_LABEL, scan->start, length, scan->line));
				break;
			
			case '@':
				list_push(&list, hackScanner_newToken(TK_AT, "@", 1, scan->line));
				hackScanner_adv(scan);
				
				scan->start = scan->current;
				
				while(hackScanner_peek(scan) != '\n'){
					if(hackScanner_peek(scan) == '\0') break;
					hackScanner_adv(scan);
				}
				
				length = (scan->current - scan->start) + 1;
				if(length >= 49){
					list_destroy(&list);
					scan->error = SCAN_STRING_TOO_LONG_ERROR;
					return list;
				}
				
				DFA_run(&dfa, scan->start, length);
				
				if(dfa.state == DFA_NUMBER_STATE) list_push(&list, hackScanner_newToken(TK_NUM, scan->start, length, scan->line));
				else if(dfa.state == DFA_ID_STATE){
					if(list_find(labels, scan->start, length)){
						list_push(&list, hackScanner_newToken(TK_LABEL, scan->start, length, scan->line));
					}
					else{
						list_push(&list, hackScanner_newToken(TK_ID, scan->start, length, scan->line));
					}
				}
				break;
			
			case ' ':
			case '\t': break;
			case '\n': scan->line++; break;
		}
		hackScanner_adv(scan);
	}
	list_push(&list, hackScanner_newToken(TK_EOF, "", 0, 0));
	return list;
}

struct list list_new(){
	struct list new_list;
	new_list.head = NULL;
	new_list.tail = NULL;
	new_list.length = 0;
	return new_list;
}

void list_push(list_t* list, hackToken_t token){
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

hackToken_t list_pop(list_t* list){
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

int list_find(list_t* list, const char* lexeme, int length){
	struct Node* current = list->head;
	while(current != NULL){
		if(stringcmp(lexeme, length, current->token.lexeme, current->token.length)) return 1;
		current = current->next;
	}
	return 0;
}

void list_print(list_t* list){
	struct Node* current = list->head;
	printf("[ ");
	while(current != NULL){
		printToken(current->token);
		current = current->next;
	}
	printf(" ]\n");
}

void list_destroy(list_t* list){
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