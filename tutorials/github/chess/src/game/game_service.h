#ifndef _gameservice
#define _gameservice

#include "game.h"
#include "pieces/piece.h"
#include "utils/enums.h"
#include "utils/position.h"
#include <iostream>
#include <memory>


class GameService
{
public:
    //
    // Constructors and Destructors
    //
    GameService();
    ~GameService();

    //
    // Validate mouse click
    //
    bool validateFirstMouseClick(Position *pos);
    bool validateSecondMouseClick(Position *from, Position *to);

    //
    // Current game status
    //
    void calculateCurrentGameStatus();
    bool hasCurentGameEnded();
    void printCurrentGameOnConsole();

    //
    // Board pieces
    //
    Piece *getPieceFromBoardPosition(Position *pos);
    std::string getPieceNameFromBoardPosition(Position *pos);
    bool isPieceValidMove(Position *piecePos, Position *movePos);

    //
    // King
    //
    bool isWhiteKingInCheck();
    bool isBlackKingInCheck();
    Position *getWhiteKingPosition();
    Position *getBlackKingPosition();

private:
    //
    // Game
    //
    std::unique_ptr<Game> game;

    //
    // Current players turn
    //
    enums::Team currentTeamTurn;

    //
    // End game variables
    //
    bool checkmate;
    bool draw;

    //
    // lastPieceMoved
    //
    Piece *lastPieceMoved;
};

#endif
