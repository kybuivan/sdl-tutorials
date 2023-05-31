#include "piece_knight.h"

#include "piece.h"
#include "utils/enums.h"
#include "utils/position.h"

Knight::Knight(enums::Team team, Position *pos)
    : Piece(enums::Piece::KNIGHT, team, pos)
{
}

Knight::~Knight()
{
}

void Knight::calculateValidMoves(Piece *board[8][8])
{
    /*  a  b  c  d  e  f  g  h
        0  1  2  3  4  5  6  7
       +--+--+--+--+--+--+--+--+
  8 0  |  |  |  |  |  |  |  |  |
       +--+--+--+--+--+--+--+--+
  7 1  |  |  |wN|  |wN|  |  |  |
       +--+--+--+--+--+--+--+--+
  6 2  |  |wN|  |  |  |wN|  |  |
       +--+--+--+--+--+--+--+--+
  5 3  |  |  |  |wN|  |  |  |  |
       +--+--+--+--+--+--+--+--+
  4 4  |  |wN|  |  |  |wN|  |  |
       +--+--+--+--+--+--+--+--+
  3 5  |  |  |wN|  |wN|  |  |  |
       +--+--+--+--+--+--+--+--+
  2 6  |  |  |  |  |  |  |  |  |
       +--+--+--+--+--+--+--+--+
  1 7  |  |  |  |  |  |  |  |  |
       +--+--+--+--+--+--+--+--+
        a  b  c  d  e  f  g  h
        0  1  2  3  4  5  6  7       */

    this->cleanAllValidMoves();

    int fixed_row = getPosition()->row;
    int fixed_col = getPosition()->col;

    Piece *piece;
    Position *pos = new Position();

    //Knight moves above right
    int row = fixed_row - 2;
    int col = fixed_col + 1;
    if (row >= 0 && col < 8)
    {
        pos->setPosition(col, row);
        piece = board[col][row];

        if (piece == nullptr)
        {
            setValidMove(pos);
        }
        else if (piece != nullptr && piece->team != this->team)
        {
            setValidMove(pos);
        }
        else if (piece != nullptr && piece->team == this->team)
        {
            piece->setIsDefended(true);
        }
    }

    //Knight moves above left
    row = fixed_row - 2;
    col = fixed_col - 1;
    if (row >= 0 && col >= 0)
    {
        pos->setPosition(col, row);
        piece = board[col][row];

        if (piece == nullptr)
        {
            setValidMove(pos);
        }
        else if (piece != nullptr && piece->team != this->team)
        {
            setValidMove(pos);
        }
        else if (piece != nullptr && piece->team == this->team)
        {
            piece->setIsDefended(true);
        }
    }

    //Knight moves right above
    row = fixed_row - 1;
    col = fixed_col + 2;
    if (row >= 0 && col < 8)
    {
        pos->setPosition(col, row);
        piece = board[col][row];

        if (piece == nullptr)
        {
            setValidMove(pos);
        }
        else if (piece != nullptr && piece->team != this->team)
        {
            setValidMove(pos);
        }
        else if (piece != nullptr && piece->team == this->team)
        {
            piece->setIsDefended(true);
        }
    }

    //Knight moves right below
    row = fixed_row + 1;
    col = fixed_col + 2;
    if (row < 8 && col < 8)
    {
        pos->setPosition(col, row);
        piece = board[col][row];

        if (piece == nullptr)
        {
            setValidMove(pos);
        }
        else if (piece != nullptr && piece->team != this->team)
        {
            setValidMove(pos);
        }
        else if (piece != nullptr && piece->team == this->team)
        {
            piece->setIsDefended(true);
        }
    }

    //Knight moves below left
    row = fixed_row + 2;
    col = fixed_col - 1;
    if (row < 8 && col >= 0)
    {
        pos->setPosition(col, row);
        piece = board[col][row];

        if (piece == nullptr)
        {
            setValidMove(pos);
        }
        else if (piece != nullptr && piece->team != this->team)
        {
            setValidMove(pos);
        }
        else if (piece != nullptr && piece->team == this->team)
        {
            piece->setIsDefended(true);
        }
    }

    //Knight moves below right
    row = fixed_row + 2;
    col = fixed_col + 1;
    if (row < 8 && col < 8)
    {
        pos->setPosition(col, row);
        piece = board[col][row];

        if (piece == nullptr)
        {
            setValidMove(pos);
        }
        else if (piece != nullptr && piece->team != this->team)
        {
            setValidMove(pos);
        }
        else if (piece != nullptr && piece->team == this->team)
        {
            piece->setIsDefended(true);
        }
    }

    //Knight moves left above
    row = fixed_row - 1;
    col = fixed_col - 2;
    if (row >= 0 && col >= 0)
    {
        pos->setPosition(col, row);
        piece = board[col][row];

        if (piece == nullptr)
        {
            setValidMove(pos);
        }
        else if (piece != nullptr && piece->team != this->team)
        {
            setValidMove(pos);
        }
        else if (piece != nullptr && piece->team == this->team)
        {
            piece->setIsDefended(true);
        }
    }

    //Knight moves left below
    row = fixed_row + 1;
    col = fixed_col - 2;
    if (row < 8 && col >= 0)
    {
        pos->setPosition(col, row);
        piece = board[col][row];

        if (piece == nullptr)
        {
            setValidMove(pos);
        }
        else if (piece != nullptr && piece->team != this->team)
        {
            setValidMove(pos);
        }
        else if (piece != nullptr && piece->team == this->team)
        {
            piece->setIsDefended(true);
        }
    }
    delete (pos);
}
