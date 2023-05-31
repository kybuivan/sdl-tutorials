//
// Created by Marcin Jarczewski on 08.02.2022.
//
#include "board.h"
#include "colors.h"
#include "consts.h"
#include "graphics.h"
#include "player.h"

#ifndef SOKOBAN_GAME_H
#define SOKOBAN_GAME_H

typedef struct result
{
    int score;
    double time;
    char name[MAX_TEXT_LENGTH];
} result_t;

typedef struct variables
{
    Uint32 t1, t2, quit, frames, reset, moves, chestNum;
    double delta, worldTime, fpsTimer, fps;

    board_t board;

    graphics_t vfx;
    colors_t colors;
    player_t player;

} var_t;

int startProgram();

#endif //SOKOBAN_GAME_H
