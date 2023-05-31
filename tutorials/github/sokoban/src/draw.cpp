//
// Created by Marcin Jarczewski on 08.02.2022.
//
#include "draw.h"
#include "board.h"
#include "consts.h"


// draw a text txt on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images
void drawString(SDL_Surface *screen,
                int x,
                int y,
                const char *text,
                SDL_Surface *charset)
{
    int px, py, c;
    SDL_Rect s, d;
    s.w = 8;
    s.h = 8;
    d.w = 8;
    d.h = 8;
    while (*text)
    {
        c = *text & 255;
        px = (c % 16) * 8;
        py = (c / 16) * 8;
        s.x = px;
        s.y = py;
        d.x = x;
        d.y = y;
        SDL_BlitSurface(charset, &s, screen, &d);
        x += 8;
        text++;
    };
};


// draw a surface sprite on a surface screen in point (x, y) (top-left corner)
void drawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = sprite->w;
    dest.h = sprite->h;
    SDL_BlitSurface(sprite, NULL, screen, &dest);
};


// draw a single pixel
void drawPixel(SDL_Surface *surface, int x, int y, Uint32 color)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    *(Uint32 *)p = color;
};


// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void drawLine(SDL_Surface *screen,
              int x,
              int y,
              int l,
              int dx,
              int dy,
              Uint32 color)
{
    for (int i = 0; i < l; i++)
    {
        drawPixel(screen, x, y, color);
        x += dx;
        y += dy;
    };
};


// draw a rectangle of size l by k
void drawRectangle(SDL_Surface *screen,
                   int x,
                   int y,
                   int l,
                   int k,
                   Uint32 outlineColor,
                   Uint32 fillColor)
{
    int i;
    drawLine(screen, x, y, k, 0, 1, outlineColor);
    drawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
    drawLine(screen, x, y, l, 1, 0, outlineColor);
    drawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
    for (i = y + 1; i < y + k - 1; i++)
        drawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};


void drawPlayer(const graphics_t *vfx,
                const player_t *player,
                const int topLeftX,
                const int topLeftY,
                const int t1)
{
    int newX, newY;

    int oppositeDir = (player->moveDir + 2) % 4; // reverse dir
    int movePhaseX =
        (player->hasMoved ? dx[oppositeDir] * (SPRITE_WIDTH / NUM_FRAMES) : 0);
    int movePhaseY =
        (player->hasMoved ? dy[oppositeDir] * (SPRITE_HEIGHT / NUM_FRAMES) : 0);

    if (movePhaseX || movePhaseY)
    {
        if (player->lastUpdate + NUM_FRAMES * DELAY < t1)
        {                                // if movement was animated
            movePhaseX = movePhaseY = 0; // dont animate more
        }
        movePhaseX *= player->hasMoved;
        movePhaseY *= player->hasMoved;
        //        printf("x: %d\t y: %d\t moves: %d\n", movePhaseX, movePhaseY, player->hasMoved);
    };

    newX = topLeftX + player->x * SPRITE_WIDTH + movePhaseX;
    newY = topLeftY + player->y * SPRITE_HEIGHT + movePhaseY;

    drawSurface(vfx->screen, vfx->pSprites.p, newX, newY);
}


// function draws board and everything on it, to screen
void drawBoard(const graphics_t *vfx,
               const player_t *player,
               const board_t *board,
               int t1)
{
    int topLeftX = (SCREEN_WIDTH - board->cols * SPRITE_WIDTH) / 2;
    int topLeftY = (SCREEN_HEIGHT - board->rows * SPRITE_HEIGHT) / 2;
    int newX;
    int newY;

    for (int row = 0; row < board->rows; row++)
    {
        for (int col = 0; col < board->cols; col++)
        {
            newX = topLeftX + col * SPRITE_WIDTH;
            newY = topLeftY + row * SPRITE_HEIGHT;

            drawSurface(vfx->screen, vfx->field.empty, newX, newY);

            switch (board->grid[row][col])
            {
            case WALL:
                drawSurface(vfx->screen, vfx->field.wall, newX, newY);
                break;
            case CHEST_DEST:
                drawSurface(vfx->screen, vfx->field.chestDest, newX, newY);
                break;
            case CHEST:
                drawSurface(vfx->screen, vfx->field.chest, newX, newY);
                break;
            case CHEST_AT_DEST:
                drawSurface(vfx->screen, vfx->field.chestAtDest, newX, newY);
                break;
            default:
                break;
            }
        }
    }

    drawPlayer(vfx, player, topLeftX, topLeftY, t1);
}
