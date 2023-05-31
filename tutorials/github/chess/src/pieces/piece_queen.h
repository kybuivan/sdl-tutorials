#ifndef _queen
#define _queen

#include "piece.h"
#include "utils/enums.h"
#include "utils/position.h"

class Queen : public Piece
{
public:
    Queen(enums::Team team, Position *pos);
    ~Queen();
    void calculateValidMoves(Piece *board[8][8]);
};

#endif
