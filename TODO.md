Emulate the screen memory. (DONE)

Add Keyboard input. (DONE)

Create an assembler for the hack assembler.

Started working on the assembler:
	Scanner: (COMPLETE)
		Implement scanner functions. (DONE)
		Initialize the DFA. (DONE)
		Create function for checking ID name/numbers using DFA. (DONE)
		Create list functions for storing the tokens. (DONE)

	Parser:
		implement parser functions.
		Create 2 Lists, 1 for label declaration and the other for lost labels.
		Create Parser Rules.

**ISSUES**
ROM array is somehow being edited during code execution. (FIXED)
The VM was drawing past the screen's max buffer size which was
rewriting the data in the ROM which was placed after the 
screen's buffer within the struct (vm_t).

(MUST BE CAREFUL WHEN ACCESSING MEMORY, NO ARRAY BOUNDS CHECKING).
