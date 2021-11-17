Emulate the screen memory. (DONE)

Create an assembler for the hack assembler

**ISSUES**
ROM array is somehow being edited during code execution. (FIXED)
The VM was drawing past the screen's max buffer size which was
rewriting the data in the ROM which was placed after the 
screen's buffer within the struct (vm_t).

(MUST BE CAREFUL WHEN ACCESSING MEMORY, NO ARRAY BOUNDS CHECKING).
