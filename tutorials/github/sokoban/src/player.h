//
// Created by Marcin Jarczewski on 08.02.2022.
//
#include <SDL.h>

#ifndef SOKOBAN_PLAYER_H
#define SOKOBAN_PLAYER_H

const int NUM_FRAMES = 3;

typedef struct player
{
    int x, y, lastUpdate, lastFrame, hasMoved, moveDir;
} player_t;

#endif //SOKOBAN_PLAYER_H
