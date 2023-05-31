#ifndef _bishop
#define _bishop

#include "piece.h"
#include "utils/enums.h"
#include "utils/position.h"

class Bishop : public Piece
{
public:
    Bishop(enums::Team team, Position *pos);
    ~Bishop();
    void calculateValidMoves(Piece *board[8][8]);
};

#endif
