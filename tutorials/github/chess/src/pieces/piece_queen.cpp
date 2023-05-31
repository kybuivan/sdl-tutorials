#include "piece_queen.h"

#include "piece.h"
#include "utils/enums.h"
#include "utils/position.h"


Queen::Queen(enums::Team team, Position *pos)
    : Piece(enums::Piece::QUEEN, team, pos)
{
}

Queen::~Queen()
{
}

void Queen::calculateValidMoves(Piece *board[8][8])
{
    /*       a  b  c  d  e  f  g  h
             0  1  2  3  4  5  6  7
            +--+--+--+--+--+--+--+--+
       8 0  |  |  |..|  |..|  |..|  |
            +--+--+--+--+--+--+--+--+
       7 1  |  |  |  |..|..|..|  |  |
            +--+--+--+--+--+--+--+--+
       6 2  |..|..|..|..|WQ|..|..|..|
            +--+--+--+--+--+--+--+--+
       5 3  |  |  |  |..|..|..|  |  |
            +--+--+--+--+--+--+--+--+
       4 4  |  |  |..|  |..|  |..|  |
            +--+--+--+--+--+--+--+--+
       3 5  |  |..|  |  |..|  |  |..|
            +--+--+--+--+--+--+--+--+
       2 6  |..|  |  |  |..|  |  |  |
            +--+--+--+--+--+--+--+--+
       1 7  |  |  |  |  |..|  |  |  |
            +--+--+--+--+--+--+--+--+
             a  b  c  d  e  f  g  h
             0  1  2  3  4  5  6  7       */

    this->cleanAllValidMoves();

    int fixed_row = getPosition()->row;
    int fixed_col = getPosition()->col;


    int row = 0;
    int col = 0;

    Piece *piece;
    Position *pos = new Position();

    //
    // Rook moves
    //

    //Rook move up
    for (row = fixed_row - 1; row >= 0; row--)
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
    for (row = fixed_row + 1; row < 8; row++)
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
    for (col = fixed_col + 1; col < 8; col++)
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
    for (col = fixed_col - 1; col >= 0; col--)
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

    //
    // Bishop moves
    //

    //Bishop moves lower right
    row = fixed_row + 1;
    col = fixed_col + 1;
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
