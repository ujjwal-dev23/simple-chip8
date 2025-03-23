# Simple Chip-8
CHIP-8 Emulator (Interpreter) written in C++ with SDL3.
Built to be as reasonably modular as possible.
This time actually complete *(hopefully)*.

### Usage
```
chip8 --rom <path_to_rom>
```

## TODOs 
- [ ] Input Handling
- [ ] Error Handling and Logging
- [x] Implement Opcodes (Partialy Done)
- [x] Building the Texture
- [ ] Implement Delay Timer and Sound Timer

## Additional Features
- [ ] Variable Resolution
- [ ] Config File
- [ ] Debug Mode
- [ ] Better Frame Timing Management

## Test ROMs
- [x] Timendus' Chip8 Splash Screen
- [x] IBM Logo
- [ ] Corax+ Opcode Test
- [ ] Flags Test
- [ ] Quirks Test (CHIP8 Only)

Planning to add SUPER CHIP-8 capabilites after adding bells and whistles.

# Build
Compile using g++ (need to have SDL3 libraries installed)
Linux
```
g++ -O2 -lSDL3 src/main.cpp src/chip8.cpp src/graphics.cpp -o chip8
```
*(not tested with -O3, but should work)*
