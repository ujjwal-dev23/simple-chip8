#include "chip8.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

void CHIP8::init()
{
  PC = 0x200;
  SP = 0;
  I = 0;
  delay_timer = 0;
  sound_timer = 0;

  for(auto &i : memory) {
    i = 0;
  }
  for(auto &i : V) {
    i = 0;
  }
  for(auto &i : stack) {
    i = 0;
  }
  for(auto &i : framebuffer) {
    i = 0;
  }
  for(auto &i : keyboard) {
    i = 0;
  }

  // Load the fontset at memory address (0x000 to 0x1FF)
  constexpr uint8_t chip8_fontset[80] =
  { 
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
  };
  int index {0};
  for (uint8_t i : chip8_fontset)
  {
    memory[index++] = i;
  }
}

void CHIP8::print_state() const
{
  std::cout << "PC : " << PC << '\n';
  std::cout << "SP : " << +SP << '\n';
  std::cout << "I : " << I << '\n';
  /*std::cout << "Delay Timer : " << +delay_timer << '\n';*/
  /*std::cout << "Sound Timer : " << +sound_timer << '\n';*/
  std::cout << "V : ";
  for(auto i : V) {
    std::cout << +i << " ";
  }
  std::cout << "\n";
}
  
void CHIP8::increment_PC()
{
  PC += 2;
}

void CHIP8::fetch_and_decode_opcode()
{
  opcode = memory[PC] << 8 | memory[PC + 1];

  std::cout << std::hex << opcode << "\n";

  uint8_t msn {static_cast<uint8_t>(opcode >> 12)}; //Most Significant Nibble

  // Splitting msn,x,y,n = opcode ; x,y,n = addr ; y,n = kk
  uint16_t addr {static_cast<uint16_t>(opcode & ((1 << 12) - 1))};

  uint8_t x {static_cast<uint8_t>(opcode >> 8 & ((1 << 4) - 1))};
  uint8_t y {static_cast<uint8_t>(opcode >> 4 & ((1 << 4) - 1))};
  uint8_t n {static_cast<uint8_t>(opcode & ((1 << 4) - 1))};

  uint8_t kk {static_cast<uint8_t>(opcode & ((1 << 8) - 1))};

  switch (msn)
  {
    case 0x0:
    if (opcode == 0x00E0)
    {
      for(uint8_t &i : framebuffer) {
        i = 0;
      }
    }
    else if (opcode == 0x00EE)
    {
      if (SP > 0)
      {
      PC = stack[SP--];
      }
      else {
        std::cerr << "Stack Underflow";
      }
    }
    else 
    {
      // 0nnn - SYS addr
      PC = addr;
    }
    break;

    case 0x1:
    PC = addr;
    PC -= 2;
    break;

    case 0x2:
    if (SP < 15)
    {
      stack[++SP] = PC;
      PC = addr;
      PC -= 2;
    }
    else {
        std::cerr << "Stack Overflow";
    }
    break;

    case 0x3:
    if (V[x] == kk)
    {
      increment_PC();
    }
    break;

    case 0x4:
    if (V[x] != kk)
    {
      increment_PC();
    }
    break;

    case 0x5:
    if (V[x] == V[y])
    {
        increment_PC();
    }
    break;

    case 0x6:
    V[x] = kk;
    break;

    case 0x7:
    V[x] += kk;
    break;

    case 0x8:
    switch (n)
    {
      case 0x0:
      V[x] = V[y];
      break;
      
      case 0x1:
      V[x] |= V[y];
      break;

      case 0x2:
      V[x] &= V[y];
      break;

      case 0x3:
      V[x] ^= V[y];
      break;

      case 0x4:
      V[x] += V[y];
      if (x + y > 256)
      {
        V[0xF] = 1;
      }
      break;
      
      case 0x5:
      V[x] -= V[y];
      V[0xF] = (V[x] > V[y]);
      break;

      case 0x6:
      V[0xF] = (V[x] & 1) ? 1 : 0;
      V[x] /= 2;
      break;

      case 0x7:
      V[x] = V[y] - V[x];
      V[0xF] = (V[y] > V[x]) ? 1 : 0;
      break;

      case 0xE:
      V[0xF] = V[x] >> 7;
      V[x] *= 2;
      break;
    }
    break;

    case 0x9:
    if (V[x] != V[y])
    {
      increment_PC();
    }
    break;

    case 0xA:
    I = addr;
    break;

    case 0xB:
    PC = addr + V[0];
    break;

    case 0xC:
    {
      std::srand(static_cast<unsigned int>(std::time(0)));
      uint8_t random_number {static_cast<uint8_t>(std::rand() % 256)};

      V[x] = random_number & kk;
      break;
    }

    case 0xD:
    V[0xF] = 0;

    for (int row = 0; row < n; row++) 
    {
      uint8_t spriteByte {memory[I + row]};
      int coordY = (V[y] + row) % 32;

      for (int col = 0; col < 8; col++)
      {
        int coordX = (V[x] + col) % 64;

        if ((spriteByte & (0x80 >> col)) != 0)
        {
          int index = coordY * 64 + coordX;

          if (framebuffer[index] == 1)
          {
            V[0xF] = 1;
          }

          framebuffer[index] ^= 1;
        }
      }
    }

    break;

    case 0xE:
    if (n == 0xE && keyboard[V[x]])
    {
      increment_PC();
    }
    else if (n == 0x1 && !keyboard[V[x]]) 
    {
      increment_PC();
    }
    break;

    case 0xF:
    if (n == 0x7)
    {
      V[x] = delay_timer;
    }
    else if (n == 0xA)
    {
      bool key_pressed {false};

      for(uint8_t i = 0; i < 16; i++) {
        if (keyboard[i] != 0)
        {
          V[x] = i;
          key_pressed = true;
          break;
        }
      }
      
      if (!key_pressed)
      {
        PC -= 2;
      }
    }
    else if (n == 0x5 && y == 0x1)
    {
      delay_timer = V[x];
    }
    else if (n == 0x8)
    {
      sound_timer = V[x];
    }
    else if (n == 0xE)
    {
      I += V[x];
    }
    else if (n == 0x9)
    {
      if (V[x] < 16)
      {
        I = memory[5 * V[x]];
      }
    }
    else if (n == 0x3)
    {
      uint8_t number {V[x]};
      for (int i = 2; i >= 0; i--)
      {
        uint8_t digit {static_cast<uint8_t>(number % 10)};
        number /= 10;

        memory[I + i] = digit;
      }
    }
    else if (n == 0x5 && y == 0x5)
    {
      for (int i = 0; i <= x; i++)
      {
        memory[I + i] = V[i];
      }
    }
    else if (n == 0x5 && y == 0x6)
    {
      for (int i = 0; i <= x; i++)
      {
        V[i] = memory[I + i];
      }
    }
    break;
  }

  increment_PC();
}

void CHIP8::set_memory(uint16_t address, uint8_t data)
{
  if (address >= 0x200 && address <= 0xFFF)
  {
    memory[address] = data;
  }
  else
  {
    std::cerr << "Memory address out of bounds.\n";  
  }
}
