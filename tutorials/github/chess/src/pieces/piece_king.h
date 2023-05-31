#ifndef _king
#define _king

#include "piece.h"
#include "utils/enums.h"
#include "utils/position.h"

class King : public Piece
{
public:
    King(enums::Team player, Position *pos);
    ~King();

    //
    // Validate moves
    //
    void calculateValidMoves(Piece *board[8][8]);
    void invalidateKingMoves(Piece *piece);
    void invalidateKingMovesFromOpponentsKingsPosition(Position *king_position);
    void invalidateKingMove(Position *pos);
    void calculateCastle(Piece *board[8][8]);

    //
    // Checks
    //
    void calculateCausingCheck(Piece *board[8][8]);
    void cleanChecksArray();
    void cleanInCheck();
    bool isInCheck();
    void setInCheckTrue();

    bool causingCheck[8][8] = {false};

private:
    bool inCheck;
};

#endif
