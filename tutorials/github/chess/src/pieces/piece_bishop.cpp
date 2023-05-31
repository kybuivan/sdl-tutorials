#include "piece_bishop.h"

#include "piece.h"
#include "utils/enums.h"
#include "utils/position.h"


Bishop::Bishop(enums::Team team, Position *pos)
    : Piece(enums::Piece::BISHOP, team, pos)
{
}

Bishop::~Bishop()
{
}

void Bishop::calculateValidMoves(Piece *board[8][8])
{
    /*       a  b  c  d  e  f  g  h
             0  1  2  3  4  5  6  7
            +--+--+--+--+--+--+--+--+
       8 0  |  |..|  |  |  |  |  |  |
            +--+--+--+--+--+--+--+--+
       7 1  |  |  |..|  |  |  |  |  |
            +--+--+--+--+--+--+--+--+
       6 2  |  |  |  |..|  |  |  |..|
            +--+--+--+--+--+--+--+--+
       5 3  |  |  |  |  |..|  |..|  |
            +--+--+--+--+--+--+--+--+
       4 4  |  |  |  |  |  |wB|  |  |
            +--+--+--+--+--+--+--+--+
       3 5  |  |  |  |  |..|  |..|  |
            +--+--+--+--+--+--+--+--+
       2 6  |  |  |  |..|  |  |  |..|
            +--+--+--+--+--+--+--+--+
       1 7  |  |  |..|  |  |  |  |  |
            +--+--+--+--+--+--+--+--+
             a  b  c  d  e  f  g  h
             0  1  2  3  4  5  6  7       */

    this->cleanAllValidMoves();

    int fixed_row = getPosition()->row;
    int fixed_col = getPosition()->col;

    Piece *piece;
    Position *pos = new Position();

    //Bishop moves lower right
    int row = fixed_row + 1;
    int col = fixed_col + 1;
    while (row < 8 && col < 8)
    {
        pos->setPosition(col, row);
        piece = board[col][row];

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
        col++;
        row++;
    }

    //Bishop moves lower left
    row = fixed_row + 1;
    col = fixed_col - 1;
    while (row < 8 && col >= 0)
    {
        pos->setPosition(col, row);
        piece = board[col][row];

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
        row++;
        col--;
    }

    //Bishop moves upper left
    row = fixed_row - 1;
    col = fixed_col - 1;
    while (row >= 0 && col >= 0)
    {
        pos->setPosition(col, row);
        piece = board[col][row];

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
        row--;
        col--;
    }

    //Bishop moves upper right
    row = fixed_row - 1;
    col = fixed_col + 1;
    while (row >= 0 && col < 8)
    {
        pos->setPosition(col, row);
        piece = board[col][row];

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
        row--;
        col++;
    }
    delete (pos);
}
