#ifndef CHIP8_H
#define CHIP8_H

#include <cstdint>

class CHIP8
{
private:
  std::uint8_t memory[4096];

  std::uint8_t V[16];
  std::uint16_t I;

  std::uint8_t delay_timer;
  std::uint8_t sound_timer;

  std::uint16_t PC;
  std::uint8_t SP;

  std::uint16_t stack[16];
  
  std::uint16_t opcode;
  
  std::uint8_t keyboard[16];
public:
  std::uint8_t framebuffer[64 * 32];

  void init();
  void print_state() const; //Debugging function
  void increment_PC();
  void fetch_and_decode_opcode();
  void set_memory(uint16_t address, uint8_t data);
  void set_key(int index, uint8_t value);
};

#endif // !CHIP8_H
