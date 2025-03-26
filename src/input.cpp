#include "input.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <unordered_map>

std::unordered_map<int, int> keymap = {
  {SDL_SCANCODE_X, 0},
  {SDL_SCANCODE_1, 1},
  {SDL_SCANCODE_2, 2},
  {SDL_SCANCODE_3, 3},
  {SDL_SCANCODE_Q, 4},
  {SDL_SCANCODE_W, 5},
  {SDL_SCANCODE_E, 6},
  {SDL_SCANCODE_A, 7},
  {SDL_SCANCODE_S, 8},
  {SDL_SCANCODE_D, 9},
  {SDL_SCANCODE_Z, 10},
  {SDL_SCANCODE_C, 11},
  {SDL_SCANCODE_4, 12},
  {SDL_SCANCODE_R, 13},
  {SDL_SCANCODE_F, 14},
  {SDL_SCANCODE_V, 15},
};

void handle_input(bool &running, CHIP8 &cpu)
{
  SDL_Event e;

  while (SDL_PollEvent(&e))
  {
    switch (e.type)
    {
      case SDL_EVENT_QUIT:
      running = false;
      break;
      // TODO : Input Handling
      case SDL_EVENT_KEY_DOWN:
      if (keymap.contains(e.key.scancode))
      {
        int key_index {keymap[e.key.scancode]};
        cpu.set_key(key_index, 1);
      }
      break;

      case SDL_EVENT_KEY_UP:
      if (keymap.contains(e.key.scancode))
      {
        int key_index {keymap[e.key.scancode]};
        cpu.set_key(key_index, 0);
      }
      break;
    }
  }
}
