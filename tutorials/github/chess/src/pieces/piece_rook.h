#ifndef _rook
#define _rook

#include "piece.h"
#include "utils/enums.h"
#include "utils/position.h"

class Rook : public Piece
{
public:
    Rook(enums::Team team, Position *pos);
    ~Rook();
    void calculateValidMoves(Piece *board[8][8]);
};

#endif
