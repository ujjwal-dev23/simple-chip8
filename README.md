# Simple Chip-8
CHIP-8 Emulator (Interpreter) written in C++ with SDL3.  
Built to be as reasonably modular as possible.  
This time actually complete *(hopefully)*.  

### Build
Compile using g++ (need to have SDL3 libraries installed)
```bash
g++ -O2 -lSDL3 src/main.cpp src/chip8.cpp src/graphics.cpp -o chip8
```
*(not tested with -O3, but should work)*

### Usage
```bash
chip8 --rom <path_to_rom>
```

## TODOs 
- [ ] Input Handling
- [ ] Error Handling and Logging
- [x] Implement Opcodes (Partialy Done)
- [x] Building the Texture
- [ ] Implement Delay Timer and Sound Timer

### Additional Features
- [ ] Variable Resolution
- [ ] Configuration Support
- [ ] Debug Mode
- [ ] Better Frame Timing Management

## Test ROMs
- [x] Timendus' Chip8 Splash Screen
- [x] IBM Logo
- [x] Corax+ Opcode Test
- [x] Flags Test
- [ ] Quirks Test (CHIP8 Only)

Planning to add SUPER CHIP-8 capabilites after adding bells and whistles.

## References
- <a style="text-decoration:none" href="http://devernay.free.fr/hacks/chip8/C8TECH10.HTM">
    <img src="https://www.google.com/s2/favicons?domain=devernay.free.fr" alt="Website Icon" width="16" height="16" style="vertical-align: middle;"/> Cowgod's Chip-8 Technical Reference
    </a>

- <a style="text-decoration:none" href="https://multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/">
    How to write an emulator (CHIP-8 interpreter) - Multigesture.net
    </a>

- <a style="text-decoration:none" href="https://youtu.be/YHkBgR6yvbY?si=Fj21qiRvNa_rC_jQ">
    <img src="https://www.google.com/s2/favicons?domain=youtu.be" alt="Website Icon" width="16" height="16" style="vertical-align: middle;"/> Introduction to Emulation: Build your own CHIP-8 emulator in just 1 hour! - Iridescence
    </a>
