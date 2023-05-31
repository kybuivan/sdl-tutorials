#include "game_window.h"
#include "game_service.h"
#include "utils/position.h"
#include "utils/texture.h"
#include <fstream>
#include <iostream>
#include <string>

//
// Constructors and Destructors
//
GameWindow::GameWindow()
{
    init("chess",
         SDL_WINDOWPOS_CENTERED,
         SDL_WINDOWPOS_CENTERED,
         600,
         600,
         false);
}

GameWindow::~GameWindow()
{
    clean();
}

//
// Main cycle
//
void GameWindow::init(const char *title,
                      int xpos,
                      int ypos,
                      int width,
                      int height,
                      bool fullscreen)
{
    mouseX = -1;
    mouseY = -1;
    mouseClicked = false;
    validFirstClick = false;

    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    //Gets square size in pixels
    if (width == height)
    {
        squareSizePx = width / 8;
    }
    else
    {
        squareSizePx = 75;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems Initialized!..." << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window)
        {
            std::cout << "Window created!" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created!" << std::endl;
        }

        setIcon("icon");

        isRunning = true;
    }
    else
    {
        isRunning = false;
    }
}

void GameWindow::setIcon(std::string file_name)
{
    std::string path_str = (std::string() + "res/" + file_name + ".png");
    const char *icon_path = path_str.c_str();
    SDL_Surface *icon = IMG_Load("res/icon.png");
    SDL_SetWindowIcon(window, icon);
}

void GameWindow::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_MOUSEBUTTONDOWN:
        handleMouseEvent(event);
        break;
    default:
        break;
    }
}

void GameWindow::handleMouseEvent(SDL_Event &event)
{
    mouseClicked = true;
    mouseX = event.button.x / squareSizePx;
    mouseY = event.button.y / squareSizePx;
}

void GameWindow::updateWindow(GameService *gameService)
{
    if (mouseClicked)
    {


        if (gameService->hasCurentGameEnded())
            isRunning = false;

        if (!validFirstClick)
        {
            firstPos.setPosition(mouseX, mouseY);
            validFirstClick = gameService->validateFirstMouseClick(&firstPos);
            if (validFirstClick)
                renderPieceValidMoves(&firstPos, gameService);
        }
        else
        {
            secondPos.setPosition(mouseX, mouseY);
            validSecondClick =
                gameService->validateSecondMouseClick(&firstPos, &secondPos);
            validFirstClick = false;
            renderPieces(gameService);
            if (validSecondClick)
            {
                highlightsPreviousMove(&firstPos, &secondPos, gameService);
                gameService->calculateCurrentGameStatus();
            }
        }

        highlightsKing(gameService);
        mouseClicked = false;
    }
}

void GameWindow::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}

bool GameWindow::running()
{
    return isRunning;
}

void GameWindow::delay(int ms)
{
    SDL_Delay(ms);
}

//
// Textures
//
void GameWindow::loadAllTexturesFromFile(std::string file_name)
{
    std::string path_str = (std::string() + "res/" + file_name + ".txt");
    const char *textures_file_path = path_str.c_str();

    std::ifstream file;
    file.open(textures_file_path);
    std::string line;

    int lineCount = 0;
    int sizeOfTexturesArray = sizeof(texturesArray) / sizeof(texturesArray[0]);

    if (file.is_open())
    {
        while (file)
        {
            std::getline(file, line);
            if (lineCount < sizeOfTexturesArray)
            {
                texturesArray[lineCount] =
                    new Texture(line, loadTextureFromFile(line));
            }
            lineCount++;
        }
    }
    file.close();
}

SDL_Texture *GameWindow::loadTextureFromFile(std::string pieceName)
{
    std::string img_path_str = (std::string() + "res/" + pieceName + ".png");
    const char *img_path = img_path_str.c_str();

    SDL_Surface *tmpSurface = IMG_Load(img_path);
    pieceTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return pieceTexture;
}

SDL_Texture *GameWindow::findTextureInTexturesArray(std::string textName)
{
    int sizeOfTexturesArray = sizeof(texturesArray) / sizeof(texturesArray[0]);
    for (int i = 0; i < sizeOfTexturesArray; i++)
    {
        if (texturesArray[i]->name == textName)
        {
            return texturesArray[i]->texture;
        }
    }
    return nullptr;
}

//
// Rendering
//
void GameWindow::renderBackground()
{

    SDL_SetRenderDrawColor(renderer, 209, 139, 70, 255); // #D18B46
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 254, 206, 158, 255); //#FECE9E
    SDL_Rect chessboardSquare;
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            if ((x + y) % 2 == 0)
            {
                chessboardSquare = {x * squareSizePx,
                                    y * squareSizePx,
                                    squareSizePx,
                                    squareSizePx};

                SDL_RenderFillRect(renderer, &chessboardSquare);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

void GameWindow::renderPieces(GameService *gameService)
{
    std::string pieceName;
    SDL_Rect chessboardSquareSrc = {0, 0, squareSizePx, squareSizePx};
    SDL_Rect chessboardSquareDest;

    renderBackground(); // Clean rendering

    Position boardPosition;
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            boardPosition.setPosition(x, y);
            if (gameService->getPieceFromBoardPosition(&boardPosition))
            {
                chessboardSquareDest = {x * squareSizePx,
                                        y * squareSizePx,
                                        squareSizePx,
                                        squareSizePx};

                pieceName =
                    gameService->getPieceNameFromBoardPosition(&boardPosition);
                SDL_RenderCopy(renderer,
                               findTextureInTexturesArray(pieceName),
                               &chessboardSquareSrc,
                               &chessboardSquareDest);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

void GameWindow::renderPieceValidMoves(Position *pos, GameService *gameService)
{
    std::string pieceName;
    SDL_Rect chessboardSquareSrc = {0, 0, squareSizePx, squareSizePx};
    SDL_Rect chessboardSquareDest;

    //
    // Highlights the square of the selected piece
    //
    SDL_SetRenderDrawColor(renderer, 47, 196, 54, 255); //#2FC436
    chessboardSquareDest = {pos->col * squareSizePx,
                            pos->row * squareSizePx,
                            squareSizePx,
                            squareSizePx};
    SDL_RenderFillRect(renderer, &chessboardSquareDest);

    //
    // Renders selected piece above square
    //
    pieceName = gameService->getPieceNameFromBoardPosition(pos);
    SDL_RenderCopy(renderer,
                   findTextureInTexturesArray(pieceName),
                   &chessboardSquareSrc,
                   &chessboardSquareDest);

    Position boardPosition;
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            boardPosition.setPosition(x, y);
            if (gameService->isPieceValidMove(pos, &boardPosition))
            {
                if ((x + y) % 2 == 0)
                {
                    SDL_SetRenderDrawColor(renderer,
                                           102,
                                           159,
                                           217,
                                           255); //#669FD9
                }
                else
                {
                    SDL_SetRenderDrawColor(renderer, 2, 96, 189, 255); //#0260BD
                }
                chessboardSquareDest = {x * squareSizePx,
                                        y * squareSizePx,
                                        squareSizePx,
                                        squareSizePx};

                SDL_RenderFillRect(renderer, &chessboardSquareDest);

                //
                // If there is a piece in the position, renders the piece above the highlighted square
                //
                if (gameService->getPieceFromBoardPosition(&boardPosition))
                {
                    pieceName = gameService->getPieceNameFromBoardPosition(
                        &boardPosition);
                    SDL_RenderCopy(renderer,
                                   findTextureInTexturesArray(pieceName),
                                   &chessboardSquareSrc,
                                   &chessboardSquareDest);
                }
            }
        }
    }
    SDL_RenderPresent(renderer);
}

void GameWindow::highlightsPreviousMove(Position *from,
                                        Position *to,
                                        GameService *gameService)
{

    SDL_Rect chessboardSquareSrc = {0, 0, squareSizePx, squareSizePx};

    //
    //	Highlights previous move "from" square
    //
    if ((from->col + from->row) % 2 == 0)
    {
        SDL_SetRenderDrawColor(renderer, 205, 210, 107, 255);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 167, 164, 57, 255);
    }

    SDL_Rect chessboardSquareDest = {from->col * squareSizePx,
                                     from->row * squareSizePx,
                                     squareSizePx,
                                     squareSizePx};

    SDL_RenderFillRect(renderer, &chessboardSquareDest);

    //
    //	Highlights previous move "to" square
    //
    if ((to->col + to->row) % 2 == 0)
    {
        SDL_SetRenderDrawColor(renderer, 205, 210, 107, 255);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 167, 164, 57, 255);
    }

    chessboardSquareDest = {to->col * squareSizePx,
                            to->row * squareSizePx,
                            squareSizePx,
                            squareSizePx};

    SDL_RenderFillRect(renderer, &chessboardSquareDest);


    // Renders the piece above the highlighted square
    std::string pieceName = gameService->getPieceNameFromBoardPosition(to);
    SDL_RenderCopy(renderer,
                   findTextureInTexturesArray(pieceName),
                   &chessboardSquareSrc,
                   &chessboardSquareDest);

    //Renders
    SDL_RenderPresent(renderer);
}

void GameWindow::highlightsKing(GameService *gameService)
{
    if (gameService->isWhiteKingInCheck())
    {
        Position *kingPos = gameService->getWhiteKingPosition();

        SDL_Rect chessboardSquareSrc = {0, 0, squareSizePx, squareSizePx};
        SDL_Rect chessboardSquareDest = {kingPos->col * squareSizePx,
                                         kingPos->row * squareSizePx,
                                         squareSizePx,
                                         squareSizePx};

        SDL_SetRenderDrawColor(renderer, 209, 70, 70, 255);
        SDL_RenderFillRect(renderer, &chessboardSquareDest);
        SDL_RenderCopy(renderer,
                       findTextureInTexturesArray("wK"),
                       &chessboardSquareSrc,
                       &chessboardSquareDest);
        SDL_RenderPresent(renderer);
    }
    else if (gameService->isBlackKingInCheck())
    {
        Position *kingPos = gameService->getBlackKingPosition();

        SDL_Rect chessboardSquareSrc = {0, 0, squareSizePx, squareSizePx};
        SDL_Rect chessboardSquareDest = {kingPos->col * squareSizePx,
                                         kingPos->row * squareSizePx,
                                         squareSizePx,
                                         squareSizePx};

        SDL_SetRenderDrawColor(renderer, 209, 70, 70, 255);
        SDL_RenderFillRect(renderer, &chessboardSquareDest);
        SDL_RenderCopy(renderer,
                       findTextureInTexturesArray("bK"),
                       &chessboardSquareSrc,
                       &chessboardSquareDest);
        SDL_RenderPresent(renderer);
    }
}
