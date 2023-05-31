#ifndef _knight
#define _knight

#include "piece.h"
#include "utils/enums.h"
#include "utils/position.h"

class Knight : public Piece
{
public:
    Knight(enums::Team team, Position *pos);
    ~Knight();
    void calculateValidMoves(Piece *board[8][8]);
};

#endif
