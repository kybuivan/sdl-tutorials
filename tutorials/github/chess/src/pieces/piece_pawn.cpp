#include "piece_pawn.h"

#include "piece.h"
#include "utils/enums.h"
#include "utils/position.h"

Pawn::Pawn(enums::Team team, Position *pos)
    : Piece(enums::Piece::PAWN, team, pos)
{
}

Pawn::~Pawn()
{
}

void Pawn::calculateValidMoves(Piece *board[8][8])
{
    /*   a  b  c  d  e  f  g  h
         0  1  2  3  4  5  6  7
        +--+--+--+--+--+--+--+--+
   8 0  |  |  |  |  |  |  |  |  |
        +--+--+--+--+--+--+--+--+
   7 1  |  |  |  |  |  |  |  |  |
        +--+--+--+--+--+--+--+--+
   6 2  |  |  |  |  |  |  |  |  |
        +--+--+--+--+--+--+--+--+
   5 3  |  |  |  |  |  |  |  |  |
        +--+--+--+--+--+--+--+--+
   4 4  |  |  |  |  |..|  |  |  |
        +--+--+--+--+--+--+--+--+
   3 5  |  |  |  |  |..|bP|  |  |
        +--+--+--+--+--+--+--+--+
   2 6  |  |  |  |  |wP|  |  |  |
        +--+--+--+--+--+--+--+--+
   1 7  |  |  |  |  |  |  |  |  |
        +--+--+--+--+--+--+--+--+
         a  b  c  d  e  f  g  h
         0  1  2  3  4  5  6  7       */

    this->cleanAllValidMoves();

    int col = getPosition()->col;
    int row = getPosition()->row;

    int next_row = row;
    int next_next_row = row;
    int en_passant_row = row;
    int en_passant_row_prev = row;

    enums::Team this_team = board[col][row]->team;

    if (this_team == enums::Team::WHITE)
    {
        next_row -= 1;
        next_next_row -= 2;
        en_passant_row = 3;
        en_passant_row_prev = 2;
    }
    else if (this_team == enums::Team::BLACK)
    {
        next_row += 1;
        next_next_row += 2;
        en_passant_row = 4;
        en_passant_row_prev = 5;
    }

    Position *pos = new Position();
    if (row > 0 && row < 7)
    {
        //Moves one square
        if (board[col][next_row] == nullptr)
        {
            pos->setPosition(col, next_row);
            setValidMove(pos);
        }

        //Moves two squares
        if ((row == 6 || row == 1) && board[col][row]->isFirstMove() &&
            board[col][next_row] == nullptr &&
            board[col][next_next_row] == nullptr)
        {
            pos->setPosition(col, next_next_row);
            setValidMove(pos);
        }

        //Attacks left piece
        if (col > 0 && board[col - 1][next_row] != nullptr &&
            board[col - 1][next_row]->team != this_team)
        {
            pos->setPosition(col - 1, next_row);
            setValidMove(pos);
        }

        //Attacks right piece
        if (col < 7 && board[col + 1][next_row] != nullptr &&
            board[col + 1][next_row]->team != this_team)
        {
            pos->setPosition(col + 1, next_row);
            setValidMove(pos);
        }

        //Pawn defends left diagonal piece
        if (col > 0 && board[col - 1][next_row] != nullptr &&
            board[col - 1][next_row]->team == this_team)
            board[col - 1][next_row]->setIsDefended(true);

        //Pawn defends right diagonal piece
        if (col < 7 && board[col + 1][next_row] != nullptr &&
            board[col + 1][next_row]->team == this_team)
            board[col + 1][next_row]->setIsDefended(true);

        //En Passant:
        //  1 - "from" position must have an allied pawn
        //  2 - Position aside must have an enemy pawn
        //  3 - Enemy pawn must have moved two sqaures
        //  4 - Enemy pawn must have made only one move
        //  5 - Enemy pawn must be the last piece moved

        //Left En Passant
        if (col > 0)
        {
            Piece *enemyPiece = board[col - 1][en_passant_row];
            if (enemyPiece != nullptr && enemyPiece->team != this->team //2
                && this->getPosition()->row == en_passant_row           //3
                && enemyPiece->getMoveCount() == 1                      //4
                && enemyPiece->getIsLastPieceMoved()                    //5
            )
            {
                pos->setPosition(col - 1, en_passant_row_prev);
                setValidMove(pos);
            }
        }

        //Right En Passant
        if (col < 7)
        {
            Piece *enemyPiece = board[col + 1][en_passant_row];
            if (enemyPiece != nullptr && enemyPiece->team != this->team //2
                && this->getPosition()->row == en_passant_row           //3
                && enemyPiece->getMoveCount() == 1                      //4
                && enemyPiece->getIsLastPieceMoved()                    //5
            )
            {
                pos->setPosition(col + 1, en_passant_row_prev);
                setValidMove(pos);
            }
        }
    }
    delete (pos);
}
