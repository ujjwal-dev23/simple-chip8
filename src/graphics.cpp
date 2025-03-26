#include "graphics.h"
#include "constants.h"
#include <cstring>
#include <iostream>

bool error_check(bool true_exp, std::string error_text)
{
  if (!true_exp)
  {
    std::cerr << error_text << '\n';
    return true;
  }
  return false;
}

void init_graphics()
{
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
  {
    return;
  }
  window = SDL_CreateWindow("Simple Chip-8", WINDOW_W, WINDOW_H, 0);
  if (error_check(window != NULL, "Window Initialization Failed!")) return;

  renderer = SDL_CreateRenderer(window, NULL);
  if (error_check(renderer != NULL, "Renderer Initialization Failed!")) return;

  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB332, SDL_TEXTUREACCESS_STREAMING, CHIP8_WIDTH, CHIP8_HEIGHT);
  if (error_check(texture != NULL, "Texture Initialization Failed!")) return;

  SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

}

void deinit_graphics()
{
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void draw_graphics(uint8_t framebuffer[])
{
  SDL_RenderClear(renderer);

  SDL_FRect dest_Rect = {0, 0, WINDOW_W, WINDOW_H};

  uint8_t* pixels;
  int pitch {0};

  SDL_LockTexture(texture, NULL, (void**)&pixels, &pitch);

  for (int i = 0; i < 2048; i++)
  {
    pixels[i] = (framebuffer[i] == 1) ? 0xFF : 0x00;
  }

  SDL_UnlockTexture(texture);

  SDL_RenderTexture(renderer, texture, NULL, &dest_Rect);
  SDL_RenderPresent(renderer);
  SDL_Delay(16);
}
