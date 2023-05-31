#ifndef _piece
#define _piece

#include "piece.h"
#include "utils/enums.h"
#include "utils/position.h"
#include <iostream>
#include <string>


class Piece
{
public:
    //
    // Constructors and Destructors
    //
    Piece();
    Piece(enums::Piece piece, enums::Team team, Position *pos);
    ~Piece();

    //
    // Enums
    //
    enums::Piece pieceType;
    enums::Team team;


    //
    // String
    //
    std::string toString();

    //
    // Valid Moves
    //
    virtual void calculateValidMoves(Piece *board[8][8]);
    void cleanAllValidMoves();
    void setValidMove(Position *pos);
    bool isValidMove(Position *pos);

    //
    // Invalid Moves
    //
    void invalidateAllMoves(bool (&moves)[8][8]);
    void setInvalidMove(Position *pos);
    bool hasNoValidMove();

    //
    // Moves
    //
    void addMoveCount();
    int getMoveCount();
    bool isFirstMove();

    //
    // Position
    //
    void setPosition(int col, int row);
    Position *getPosition();
    void setIsDefended(bool b);
    bool getIsDefended();

    //
    // En Passant
    //
    void setIsLastPieceMoved(bool b);
    bool getIsLastPieceMoved();

private:
    //
    // Chars
    //
    char getTeamChar();
    char getPieceChar();

    int moveCount;
    Position *pos;
    bool isDefended;
    bool isLastPieceMoved;
    bool allValidMoves[8][8] = {false};
};

#endif
