#include "piece_rook.h"

#include "piece.h"
#include "utils/enums.h"
#include "utils/position.h"


Rook::Rook(enums::Team team, Position *pos)
    : Piece(enums::Piece::ROOK, team, pos)
{
}

Rook::~Rook()
{
}

void Rook::calculateValidMoves(Piece *board[8][8])
{
    /*       a  b  c  d  e  f  g  h
             0  1  2  3  4  5  6  7
            +--+--+--+--+--+--+--+--+
       8 0  |  |  |  |  |..|  |  |  |
            +--+--+--+--+--+--+--+--+
       7 1  |  |  |  |  |..|  |  |  |
            +--+--+--+--+--+--+--+--+
       6 2  |  |  |  |  |..|  |  |  |
            +--+--+--+--+--+--+--+--+
       5 3  |..|..|..|..|wR|..|..|..|
            +--+--+--+--+--+--+--+--+
       4 4  |  |  |  |  |..|  |  |  |
            +--+--+--+--+--+--+--+--+
       3 5  |  |  |  |  |..|  |  |  |
            +--+--+--+--+--+--+--+--+
       2 6  |  |  |  |  |..|  |  |  |
            +--+--+--+--+--+--+--+--+
       1 7  |  |  |  |  |..|  |  |  |
            +--+--+--+--+--+--+--+--+
             a  b  c  d  e  f  g  h
             0  1  2  3  4  5  6  7       */

    this->cleanAllValidMoves();

    int fixed_row = getPosition()->row;
    int fixed_col = getPosition()->col;

    Piece *piece;
    Position *pos = new Position();

    //Rook move up
    for (int row = fixed_row - 1; row >= 0; row--)
    {
        pos->setPosition(fixed_col, row);
        piece = board[fixed_col][row];

        if (piece == nullptr)
        {
            setValidMove(pos);
        }
        else if (piece != nullptr)
        {
            if (piece->team != this->team)
            {
                if (piece->pieceType != enums::Piece::KING)
                {
                    setValidMove(pos);
                    break;
                }
            }
            else
            {
                piece->setIsDefended(true);
                break;
            }
        }
    }

    //Rook move down
    for (int row = fixed_row + 1; row < 8; row++)
    {
        pos->setPosition(fixed_col, row);
        piece = board[fixed_col][row];

        if (piece == nullptr)
        {
            setValidMove(pos);
        }
        else if (piece != nullptr)
        {
            if (piece->team != this->team)
            {
                if (piece->pieceType != enums::Piece::KING)
                {
                    setValidMove(pos);
                    break;
                }
            }
            else
            {
                piece->setIsDefended(true);
                break;
            }
        }
    }

    //Rook move right
    for (int col = fixed_col + 1; col < 8; col++)
    {
        pos->setPosition(col, fixed_row);
        piece = board[col][fixed_row];

        if (piece == nullptr)
        {
            setValidMove(pos);
        }
        else if (piece != nullptr)
        {
            if (piece->team != this->team)
            {
                if (piece->pieceType != enums::Piece::KING)
                {
                    setValidMove(pos);
                    break;
                }
            }
            else
            {
                piece->setIsDefended(true);
                break;
            }
        }
    }

    //Rook move left
    for (int col = fixed_col - 1; col >= 0; col--)
    {
        pos->setPosition(col, fixed_row);
        piece = board[col][fixed_row];

        if (piece == nullptr)
        {
            setValidMove(pos);
        }
        else if (piece != nullptr)
        {
            if (piece->team != this->team)
            {
                if (piece->pieceType != enums::Piece::KING)
                {
                    setValidMove(pos);
                    break;
                }
            }
            else
            {
                piece->setIsDefended(true);
                break;
            }
        }
    }
    delete (pos);
}
