//
// Created by Marcin Jarczewski on 08.02.2022.
//

#ifndef SOKOBAN_CONSTS_H
#define SOKOBAN_CONSTS_H

enum Status
{
    SUCCESS = 0,
    RESET,
    ERROR,
    QUIT
};

enum Field
{
    EMPTY = 1000,
    PLAYER,
    CHEST,
    CHEST_DEST,
    WALL,
    CHEST_AT_DEST
};

enum Dir
{
    LEFT = 0,
    UP,
    RIGHT,
    DOWN
};

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

const char WINDOW_TITLE[] = "Sokoban";
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int MAX_ROW_LENGTH = 100;
const int MAX_LEVEL_NAME_LENGTH = 100;
const int MAX_TEXT_LENGTH = 200;
const float ANIMATED_FPS = 20.0f;

const int DELAY = 300;

#endif //SOKOBAN_CONSTS_H
