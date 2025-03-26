#include "chip8.h"
#include "graphics.h"
#include "input.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

static CHIP8 cpu;

int load_rom(std::string romPath)
{
  std::ifstream rom(romPath, std::ios::binary);
  if (!rom)
  {
    std::cerr << "Error while loading rom.\n";
    return -1;
  }

  char byte;
  uint16_t mem_offset {0};
  while (rom.get(byte))
  {
    cpu.set_memory(0x200 + mem_offset++, static_cast<uint8_t>(byte));
  }

  rom.close();
  return 0;
}

int main (int argc, char* argv[]) 
{
  std::string romPath;

  if (argc < 2)
  {
    std::cerr << "Expected usage : " << argv[0] << " " << "--rom <path to rom>\n";
    return -1;
  }

  for (int i = 1; i < argc; i++) 
  {
    if (std::strncmp(argv[i], "--rom", 5) == 0)
    {
      if (i + 1 < argc)
      {
        romPath = argv[i+1];
        break;
      }
      else 
      {
        std::cerr << "Rom path not provided!\n";
      }
    }
  }

  if (romPath.empty())
  {
    std::cerr << "Expected usage : " << argv[0] << " " << "--rom <path to rom>\n";
    return -1;
  }

  cpu.init();
  load_rom(romPath);

  cpu.print_state();

  init_graphics();

  bool running {true};
  while (running)
  {
    cpu.fetch_and_decode_opcode();
    handle_input(running, cpu);
    draw_graphics(cpu.framebuffer);
    cpu.print_state();
  }

  deinit_graphics();
  return 0;
}
