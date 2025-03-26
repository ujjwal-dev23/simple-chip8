# Simple Chip-8
CHIP-8 Emulator (Interpreter) written in C++ with SDL3.  
Built to be as reasonably modular as possible.  
This time actually complete *(hopefully)*.  

### Build
Compile using g++ (need to have SDL3 libraries installed)
```bash
g++ -std=c++23 -O2 -lSDL3 src/*.cpp -o chip8
```
*(not tested with -O3, but should work)*

### Usage
```bash
chip8 --rom <path_to_rom>
```

## TODOs 
- [x] Implement Opcodes
- [x] Drawing Graphics
- [x] Implement Delay Timer and Sound Timer
- [ ] Sound Timer Beep
- [x] Input Handling
- [ ] Error Handling and Logging
- [ ] Separate Threads for Timers

### Additional Features
- [ ] Variable Resolution
- [ ] Config File
- [ ] Configurable keybindings
- [ ] Better Frame Timing Management
- [ ] Debug Mode

## Test ROMs
- [x] Timendus' Chip8 Splash Screen
- [x] IBM Logo
- [x] Corax+ Opcode Test
- [x] Flags Test
- [ ] Quirks Test (CHIP8 Only)

Planning to add SUPER CHIP-8 capabilites after adding bells and whistles.

## References
1. <img src="https://www.google.com/s2/favicons?domain=devernay.free.fr" alt="Website Icon" width="16" height="16" style="vertical-align: middle;"/>[Cowgod's Chip-8 Technical Reference](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM)

2. [How to write an emulator (CHIP-8 interpreter) - Multigesture.net](https://multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/)

3. <img src="https://www.google.com/s2/favicons?domain=youtu.be" alt="Website Icon" width="16" height="16" style="vertical-align: middle;"/>[Introduction to Emulation: Build your own CHIP-8 emulator in just 1 hour! - Iridescence](https://youtu.be/YHkBgR6yvbY?si=Fj21qiRvNa_rC_jQ)
