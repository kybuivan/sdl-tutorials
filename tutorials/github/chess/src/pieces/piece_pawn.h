#ifndef _pawn
#define _pawn

#include "piece.h"
#include "utils/enums.h"
#include "utils/position.h"

class Pawn : public Piece
{
public:
    Pawn(enums::Team team, Position *pos);
    ~Pawn();
    void calculateValidMoves(Piece *board[8][8]);
};

#endif
