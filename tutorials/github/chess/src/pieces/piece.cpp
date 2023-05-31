#include "piece.h"

#include "piece.h"
#include "utils/enums.h"
#include "utils/position.h"
#include <iostream>
#include <string>

//
// Constructors and Destructors
//
Piece::Piece()
{
    moveCount = 0;
    isDefended = false;
    isLastPieceMoved = false;
}

Piece::Piece(enums::Piece piece, enums::Team team, Position *pos)
    : pieceType(piece), team(team), pos(pos)
{
    moveCount = 0;
};

Piece::~Piece()
{
}

//
// String
//
std::string Piece::toString()
{
    return (std::string() + getTeamChar() + getPieceChar());
}

//
// Chars
//
char Piece::getTeamChar()
{
    switch (this->team)
    {
    case enums::Team::NONE:
    {
        return ' ';
    }
    case enums::Team::WHITE:
    {
        return 'w';
    }
    case enums::Team::BLACK:
    {
        return 'b';
    }
    default:
    {
        return ' ';
    }
    }
}

char Piece::getPieceChar()
{
    switch (this->pieceType)
    {
    case enums::Piece::EMPTY:
    {
        return ' ';
    }
    case enums::Piece::PAWN:
    {
        return 'p';
    }
    case enums::Piece::ROOK:
    {
        return 'R';
    }
    case enums::Piece::KNIGHT:
    {
        return 'N';
    }
    case enums::Piece::BISHOP:
    {
        return 'B';
    }
    case enums::Piece::KING:
    {
        return 'K';
    }
    case enums::Piece::QUEEN:
    {
        return 'Q';
    }
    default:
    {
        return ' ';
    }
    }
}

//
// Valid Moves
//
void Piece::calculateValidMoves(Piece *board[8][8])
{
}

void Piece::cleanAllValidMoves()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            this->allValidMoves[i][j] = false;
        }
    }
}

void Piece::setValidMove(Position *pos)
{
    if (pos->col >= 0 && pos->col <= 7 && pos->row >= 0 && pos->row <= 7)
    {
        allValidMoves[pos->col][pos->row] = true;
    }
}

bool Piece::isValidMove(Position *pos)
{
    return this->allValidMoves[pos->col][pos->row];
}

//
// Invalid Moves
//
void Piece::invalidateAllMoves(bool (&moves)[8][8])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (moves[i][j] && allValidMoves[i][j])
            {
                this->allValidMoves[i][j] = true;
            }
            else
            {
                this->allValidMoves[i][j] = false;
            }
        }
    }
}

void Piece::setInvalidMove(Position *pos)
{
    if (pos->col >= 0 && pos->col <= 7 && pos->row >= 0 && pos->row <= 7)
    {
        allValidMoves[pos->col][pos->row] = false;
    }
}

bool Piece::hasNoValidMove()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (allValidMoves[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

//
// Moves
//
void Piece::addMoveCount()
{
    moveCount++;
}

int Piece::getMoveCount()
{
    return moveCount;
}

bool Piece::isFirstMove()
{
    return moveCount == 0;
}

//
// Position
//
void Piece::setPosition(int col, int row)
{
    pos->col = col;
    pos->row = row;
}

Position *Piece::getPosition()
{
    return this->pos;
}

void Piece::setIsDefended(bool b)
{
    isDefended = b;
}

bool Piece::getIsDefended()
{
    return isDefended;
}

//
// En Passant
//
void Piece::setIsLastPieceMoved(bool b)
{
    this->isLastPieceMoved = b;
}

bool Piece::getIsLastPieceMoved()
{
    return this->isLastPieceMoved;
}
