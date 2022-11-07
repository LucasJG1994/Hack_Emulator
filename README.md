# Hack Emulator
A small emulator project for the Nand2Tetris Hack Computer.  

**Usage**  
```
hackemu example.bin
```
**Debugging mode**  
The debugging mode exports a **test.out** file which you can use with your **.tst** scripts on Nand2Tetris CPU Emulator.
```
hackemu -d example.bin
```

# Important
The emulator by itself only reads **.bin** files and thus requires an assembler to assemble the Hack Language to binary. That will be done on a separate project.