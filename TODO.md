# Rebooting the project.
This project has been stalled for quite a long time.  
Instead I'll be building the Hack Emulator as a stand-alone project, the only file type it will read will be **.bin** files.  
Which the Assembler **(A separate project)** will generate.

# TODO modules

- [x] CPU module
- [x] VRAM module (want to put this in a separate thread)
- [ ] miniFB callback module (Mainly for keyboard support)

- [x] Emulator Crashes (Memory Access Violation)
- [x] Emulator Runs but **.bin** does not run correctly.

- [x] Pong game failed to run properly (Emulator can run small code snippets).

- [x] Added testing support with Nand2Tetris tools when Debug mode is enabled
- [ ] Pong game runs way too fast to be playable. 
