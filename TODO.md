Emulate the screen memory. (DONE)

Add Keyboard input. (DONE)

Create an assembler for the hack assembler.

- Started working on the assembler
	- Scanner (COMPLETE)
		- Implement scanner functions. (DONE)
		- Initialize the DFA. (DONE)
		- Create function for checking ID name/numbers using DFA. (DONE)
		- Create list functions for storing the tokens. (DONE)

	- Parser
		- [x] implement parser functions.
		- [ ] Create 2 Lists, 1 for label declaration and the other for lost labels.
		- [x] Create Parser Rules.
		- [ ] Print error messages
		
### CHANGES
The linked lists are now a macro which is used as a template.
The macro accepts a type and generates the required .h and .c code.
Really helps with code repetition. Found in **list.h**


### ISSUES
ROM array is somehow being edited during code execution. (FIXED)
The VM was drawing past the screen's max buffer size which was
rewriting the data in the ROM which was placed after the 
screen's buffer within the struct (vm_t).

FIX compiler error!!!

(MUST BE CAREFUL WHEN ACCESSING MEMORY, NO ARRAY BOUNDS CHECKING).


(Code Refactoring needed)
1. refactor code in main.c
	- [x] refactor getchar() code
	- [ ] put test code into it's own test.c file
	- [x] deal with naming convention. More readable names!
	- [x] VM should handle its own state
	- [ ] implement a vm_cleanup() function
	- [x] methods should use namespace prefix
	- [ ] use enums than #define
	- [x] all caps for const varaibles
	- [ ] global variable (keys) must be protected.
	- [ ] !(instruction & 0x8000) -> 0 == (instruction & 0x8000) -> 0 == (instruction & MASK_OPCODE)
	- [ ] MAGIC numbers referring to over use of case statements. Would be better handling them better in a file.
	- [ ] blocks without braces avoid it.
	- [x] arguments put on new lines should be indented.
	
2. refactor code in HackScanner.c
	- Replace the usage of linked lists. Find a better data structure, chunk lists (Look it up) (EDIT: maybe an issue since the project is integrated with linked lists.)