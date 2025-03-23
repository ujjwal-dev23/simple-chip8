#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <cstdint>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

inline SDL_Window *window = NULL;
inline SDL_Renderer *renderer = NULL;
inline SDL_Texture *texture = NULL;

bool error_check(bool true_exp, std::string error_text);
void init_graphics();
void deinit_graphics();
void draw_graphics(uint8_t framebuffer[]);
void handle_input(bool &running);

#endif // !GRAPHICS_H
