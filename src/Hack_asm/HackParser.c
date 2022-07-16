#include "HackParser.h"
#include "vm.h"
#include "HackTokens.h"
#include "HackScanner.h"
#include "opcodes.h"
#include "hash_table/hash_table_module.h"
#include "symbol_table/symbol_table_singleton.h"
#include <stdio.h>
#include <stdlib.h>

struct parser {
	struct token cur;
	struct token prev;
	int error;
};

static struct parser parser;
static unsigned char dest = 0;
static unsigned char comp = 0;
static unsigned char jump = 0;

static unsigned int  var_count = 16;

static void debug() {
	printf("TYPE: %d\n LINE: %d\n",
		parser.prev.type,
		parser.prev.line
		);
	
	string_print(parser.prev.lexeme);
}

void hp_init(){
	var_count = 16;
	if ( hs_advance() != SCAN_OK ) return;

	parser.prev.type	= HS_TYPE;
	parser.prev.lexeme	= string_move(HS_LEXEME);
	parser.prev.line	= HS_LINE;

	if ( hs_advance() != SCAN_OK ) return;

	parser.cur.type		= HS_TYPE;
	parser.cur.lexeme	= string_move(HS_LEXEME);
	parser.cur.line		= HS_LINE;
}

static void hp_adv() {
	string_close(parser.prev.lexeme);

	parser.prev.type	= parser.cur.type;
	parser.prev.lexeme	= string_move(parser.cur.lexeme);
	parser.prev.line	= parser.cur.line;

	if ( hs_advance() != SCAN_OK ) return;

	parser.cur.type		= HS_TYPE;
	parser.cur.lexeme	= string_move(HS_LEXEME);
	parser.cur.line		= HS_LINE;
}

static int hp_peek() {
	return parser.cur.type;
}

static int hp_match(int type) {
	return parser.prev.type == type;
}

static void hp_consume(int type, const char* msg) {
	if(hp_match(type)) hp_adv();
	else {
		printf("Parser Error: %s on line %d...\nTYPE: %d\n", msg, parser.prev.line, parser.prev.type);
		string_print(parser.prev.lexeme);
		string_close(parser.prev.lexeme);
		string_close(parser.cur.lexeme);
		hash_table_close(symbol_table);
		exit(0);
	}
}

static void hp_labels();

static void hp_program();
static void hp_at();
static void hp_dest();
static void hp_comp();
static void hp_jump();

static void hp_add_expr();
static void hp_sub_expr();
static void hp_neg_expr();
static void hp_not_expr();
static void hp_and_expr();
static void hp_or_expr() ;

void hp_start() {
	hp_program();
}

static void hp_program() {
	while (!hp_match(TK_EOF)) {
		jump = 0; dest = 0; comp = 0;
		if(hp_match(TK_LABEL)) hp_labels();
		else{
			hp_at();
			hp_dest();
			hp_comp();
			hp_jump();
			vm_make_op(jump, dest, comp);
		}
	}
}

static void hp_labels() {
	debug();

	struct pair* tmp = hash_table_find(symbol_table, parser.prev.lexeme);

	if(tmp == NULL){ hash_table_add_s(symbol_table, parser.prev.lexeme, TK_LABEL, vm_get_ip()); }
	else { tmp->pos = vm_get_ip(); }
	hp_adv();
}

static void hp_at() {
	if(!hp_match(TK_AT)) return;
	hp_adv();

	//hp_consume(TK_ID, "Expected an identifier/label after '@'...");
	if (!hp_match(TK_ID) && !hp_match(TK_LABEL)) hp_consume(-2, "Expected an identifier/label after '@'...");

	debug();

	struct pair* tmp = hash_table_find(symbol_table, parser.prev.lexeme);
	if (tmp == NULL) {
		if(hp_match(TK_NUM)) { vm_put_word(string_to_int(parser.prev.lexeme)); }
		else if (hp_match(TK_ID)) {
			vm_put_word(var_count);
			hash_table_add_s(symbol_table, parser.prev.lexeme, TK_ID, var_count++);
		}
	}
	else{ vm_put_word(tmp->pos); }
	hp_adv();
}

static void hp_dest() {
	if(hp_peek() != TK_EQ) return;

	switch (parser.prev.type) {
		case TK_A:  dest = OUT_A; break;
		case TK_D:  dest = OUT_D; break;
		case TK_M:  dest = OUT_M; break;
		case TK_AD: dest = OUT_AD; break;
		case TK_AM: dest = OUT_AM; break;
		case TK_MD: dest = OUT_MD; break;
		case TK_AMD: dest = OUT_AMD; break;
		default:
			hp_consume(-2, "Invalid destination mnumonic");
	}

	hp_adv(); hp_adv();
}

static void hp_comp() {
	if(hp_match(TK_BAN)){ hp_not_expr(); return; }
	if(hp_match(TK_SUB)){ hp_neg_expr(); return; }
	if(hp_peek() == TK_ADD) { hp_add_expr(); return; }
	if(hp_peek() == TK_SUB) { hp_sub_expr(); return; }
	if(hp_peek() == TK_AND) { hp_and_expr(); return; }
	if(hp_peek() == TK_OR)  { hp_or_expr() ; return; }

	switch (parser.prev.type) {
		case TK_0: comp = ZERO; break;
		case TK_1: comp = ONE ; break;
		case TK_A: comp = IN_A; break;
		case TK_D: comp = IN_D; break;
		case TK_M: comp = IN_M; break;
		default:
			hp_consume(-2, "Invalid comp mnumonic");
	}
	hp_adv();
}

static void hp_jump() {
	if(!hp_match(TK_SEMI)) return;
	hp_adv();

	switch (parser.prev.type) {
		case TK_JGT: { jump = JGT; hp_adv(); return; }
		case TK_JGE: { jump = JGE; hp_adv(); return; }
		case TK_JLT: { jump = JLT; hp_adv(); return; }
		case TK_JLE: { jump = JLE; hp_adv(); return; }
		case TK_JEQ: { jump = JEQ; hp_adv(); return; }
		case TK_JNE: { jump = JNE; hp_adv(); return; }
		case TK_JMP: { jump = JMP; hp_adv(); return; }
		default:
			hp_consume(-2, "Invalid jump mnumonic");
	}
}

static void hp_add_expr() {
	switch (parser.prev.type) {
		case TK_A: {
			hp_adv(); hp_adv();
			if(hp_match(TK_1)) { comp = A_p_1; hp_adv(); return; }
			//Error detection here
		}
		case TK_M: {
			hp_adv(); hp_adv();
			if(hp_match(TK_1)) { comp = M_p_1; hp_adv(); return; }
			//Error detection here
		}
		case TK_D: {
			hp_adv(); hp_adv();
			switch (parser.prev.type) {
				case TK_1: { comp = D_p_1; hp_adv(); return; }
				case TK_A: { comp = D_p_A; hp_adv(); return; }
				case TK_M: { comp = D_p_M; hp_adv(); return; }
				//default: //Error detection here
			}
		}
	}
}

static void hp_sub_expr() {
	switch (parser.prev.type) {
		case TK_A: {
			hp_adv(); hp_adv();
			if (hp_match(TK_1))		{ comp = A_s_1; hp_adv(); return; }
			else if(hp_match(TK_D)) { comp = A_s_D; hp_adv(); return; }
			//Error detection here
		}
		case TK_M: {
			hp_adv(); hp_adv();
			if (hp_match(TK_1))		{ comp = M_s_1; hp_adv(); return; }
			else if(hp_match(TK_D)) { comp = M_s_D; hp_adv(); return; }
			//Error detection here
		}
		case TK_D: {
			hp_adv(); hp_adv();
			switch (parser.prev.type) {
				case TK_1: { comp = D_s_1; hp_adv(); return; }
				case TK_A: { comp = D_s_A; hp_adv(); return; }
				case TK_M: { comp = D_s_M; hp_adv(); return; }
				//default: //Error detection here
			}
		}
	}
}
static void hp_neg_expr() {
	hp_adv();
	switch (parser.prev.type) {
		case TK_1: { comp = N_ONE; hp_adv(); return; }
		case TK_A: { comp = N_A  ; hp_adv(); return; }
		case TK_D: { comp = N_D  ; hp_adv(); return; }
		case TK_M: { comp = N_M  ; hp_adv(); return; }
		//default: //Error detection here
	}
}
static void hp_not_expr() {
	hp_adv();
	switch (parser.prev.type) {
		case TK_A: { comp = NOT_A; hp_adv(); return; }
		case TK_D: { comp = NOT_D; hp_adv(); return; }
		case TK_M: { comp = NOT_M; hp_adv(); return; }
		//default: //Error detection here
	}
}
static void hp_and_expr() {
	if (hp_match(TK_D)) {
		hp_adv(); hp_adv();
		switch (parser.prev.type) {
			case TK_A: { comp = D_a_A; hp_adv(); return; }
			case TK_M: { comp = D_a_M; hp_adv(); return; }
			//default: //Error detection here
		}
	}
	//Error detection here
}
static void hp_or_expr() {
	if (hp_match(TK_D)) {
		hp_adv(); hp_adv();
		switch (parser.prev.type) {
			case TK_A: { comp = D_o_A; hp_adv(); return; }
			case TK_M: { comp = D_o_M; hp_adv(); return; }
			//default: //Error detection here
		}
	}
	//Error detection here
}