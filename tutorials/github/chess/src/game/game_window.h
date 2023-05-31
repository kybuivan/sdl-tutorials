#ifndef _window
#define _window

#include "game/game_service.h"
#include "utils/position.h"
#include "utils/texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include <fstream>
#include <iostream>
#include <string>

class GameWindow
{
public:
    //
    // Constructors and Destructors
    //
    GameWindow();
    ~GameWindow();

    //
    // Main cycle
    //
    void init(const char *title,
              int xpos,
              int ypos,
              int width,
              int height,
              bool fullscreen);
    void setIcon(std::string file_name);
    void handleEvents();
    void handleMouseEvent(SDL_Event &event);
    void updateWindow(GameService *gameService);
    void clean();
    bool running();
    void delay(int ms);

    //
    // Textures
    //
    void loadAllTexturesFromFile(std::string file_name);
    SDL_Texture *loadTextureFromFile(std::string pieceName);
    SDL_Texture *findTextureInTexturesArray(std::string textName);

    //
    // Rendering
    //
    void renderBackground();
    void renderPieces(GameService *gameService);
    void renderPieceValidMoves(Position *pos, GameService *gameService);
    void highlightsPreviousMove(Position *from,
                                Position *to,
                                GameService *gameService);
    void highlightsKing(GameService *gameService);

private:
    //
    // SDL
    //
    SDL_Window *window;
    SDL_Renderer *renderer;

    //
    // Square size in pixels
    //
    int squareSizePx;

    //
    // True if game is running
    //
    bool isRunning;

    //
    // Textures
    //
    SDL_Texture *pieceTexture;
    Texture *texturesArray[12];

    //
    // Mouse
    //
    int mouseX;
    int mouseY;
    bool mouseClicked;
    bool validFirstClick;
    bool validSecondClick;

    //
    // Positions
    //
    Position firstPos;
    Position secondPos;
};

#endif
