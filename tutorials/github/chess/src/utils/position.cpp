#include "position.h"

#include <string>

Position::Position()
{
    this->col = 0;
    this->row = 0;
}

Position::Position(int col, int row) : col(col), row(row)
{
}

void Position::setPosition(int x, int y)
{
    col = x;
    row = y;
}
