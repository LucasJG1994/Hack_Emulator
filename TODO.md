Emulate the screen memory. (DONE)

Add Keyboard input. (DONE)

Create an assembler for the hack assembler.

Started working on the assembler:
	Scanner:
		Implement scanner functions.
		Initialize the DFA.
		Create function for checking ID name/numbers using DFA.
		Create list functions for storing the tokens.

**ISSUES**
ROM array is somehow being edited during code execution. (FIXED)
The VM was drawing past the screen's max buffer size which was
rewriting the data in the ROM which was placed after the 
screen's buffer within the struct (vm_t).

(MUST BE CAREFUL WHEN ACCESSING MEMORY, NO ARRAY BOUNDS CHECKING).
