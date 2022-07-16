#ifndef HackScanner_h
#define HackScanner_h

//Scanner Error Codes
typedef enum{
	SCAN_OK, SCAN_STRING_TOO_LONG_ERROR, SCAN_INVALID_ID_ERROR,
	SCAN_KEYWORD_ERROR
}scanner_states;

//Scanner function
void			hs_init(const char* source);
void			hs_reset();
scanner_states  hs_advance();

//Shared Globals for scanner module
extern int				HS_TYPE;
extern struct string*	HS_LEXEME;
extern int				HS_LINE;

#endif