//
// Created by Marcin Jarczewski on 08.02.2022.
//

#include "player.h"
#include <SDL.h>
#include <SDL_main.h>

#ifndef SOKOBAN_GRAPHICS_H
#define SOKOBAN_GRAPHICS_H

typedef struct field
{
    SDL_Surface *empty, *chest, *chestDest, *wall, *chestAtDest;
} field_t;

typedef struct playerSprites
{
    SDL_Surface *p;
    SDL_Surface *sprites[4][NUM_FRAMES];
} pSprites_t;

typedef struct graphics
{
    SDL_Surface *charset, *screen, *winScreen;
    SDL_Texture *scrtex;
    SDL_Renderer *renderer;
    SDL_Window *window;

    field_t field;
    pSprites_t pSprites;
} graphics_t;

const int SPRITE_WIDTH = 64;
const int SPRITE_HEIGHT = 64;

const int WIN_SCREEN_WIDTH = 250;
const int WIN_SCREEN_HEIGHT = 250;

#endif //SOKOBAN_GRAPHICS_H
