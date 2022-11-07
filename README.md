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
The emulator by itself only reads **.bin** files and thus requires an assembler to assemble the Hack Language to binary. You can get the Assembler from here https://github.com/LucasJG1994/Hack_Assembler.git