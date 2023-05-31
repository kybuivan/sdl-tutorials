#include "piece_king.h"

#include "piece.h"
#include "utils/enums.h"
#include "utils/position.h"

King::King(enums::Team player, Position *pos)
    : Piece(enums::Piece::KING, player, pos)
{
    inCheck = false;
}

King::~King()
{
}

void King::calculateValidMoves(Piece *board[8][8])
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
   4 4  |  |  |  |..|..|..|  |  |
        +--+--+--+--+--+--+--+--+
   3 5  |  |  |  |..|wK|..|  |  |
        +--+--+--+--+--+--+--+--+
   2 6  |  |  |  |..|..|..|  |  |
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

    //Move right
    int col = fixed_col + 1;
    int row = fixed_row;
    if (row >= 0 && row < 8 && col >= 0 && col < 8)
    {
        pos->setPosition(col, row);
        piece = board[col][row];

        if (piece == nullptr)
        {
            setValidMove(pos);
        }
        else if (piece != nullptr && piece->team != this->team &&
                 piece->getIsDefended() == false)
        {
            setValidMove(pos);
        }
        else
        {
            setInvalidMove(pos);
        }
    }
    //Move left
    row = fixed_row;
    col = fixed_col - 1;
    if (row >= 0 && row < 8 && col >= 0 && col < 8)
    {
        pos->setPosition(col, row);
        piece = board[col][row];

        if (piece == nullptr)
        {
            setValidMove(pos);
        }
        else if (piece != nullptr && piece->team != this->team &&
                 piece->getIsDefended() == false)
        {
            setValidMove(pos);
        }
        else
        {
            setInvalidMove(pos);
        }
    }
    //Move up
    row = fixed_row - 1;
    col = fixed_col;
    if (row >= 0 && row < 8 && col >= 0 && col < 8)
    {
        pos->setPosition(col, row);
        piece = board[col][row];

        if (piece == nullptr)
        {
            setValidMove(pos);
        }
        else if (piece != nullptr && piece->team != this->team &&
                 piece->getIsDefended() == false)
        {
            setValidMove(pos);
        }
        else
        {
            setInvalidMove(pos);
        }
    }
    //Move down
    row = fixed_row + 1;
    col = fixed_col;
    if (row >= 0 && row < 8 && col >= 0 && col < 8)
    {
        pos->setPosition(col, row);
        piece = board[col][row];

        if (piece == nullptr)
        {
            setValidMove(pos);
        }
        else if (piece != nullptr && piece->team != this->team &&
                 piece->getIsDefended() == false)
        {
            setValidMove(pos);
        }
        else
        {
            setInvalidMove(pos);
        }
    }
    //Move upper left
    row = fixed_row - 1;
    col = fixed_col - 1;
    if (row >= 0 && row < 8 && col >= 0 && col < 8)
    {
        pos->setPosition(col, row);
        piece = board[col][row];

        if (piece == nullptr)
        {
            setValidMove(pos);
        }
        else if (piece != nullptr && piece->team != this->team &&
                 piece->getIsDefended() == false)
        {
            setValidMove(pos);
        }
        else
        {
            setInvalidMove(pos);
        }
    }
    //Move upper right
    row = fixed_row - 1;
    col = fixed_col + 1;
    if (row >= 0 && row < 8 && col >= 0 && col < 8)
    {
        pos->setPosition(col, row);
        piece = board[col][row];

        if (piece == nullptr)
        {
            setValidMove(pos);
        }
        else if (piece != nullptr && piece->team != this->team &&
                 piece->getIsDefended() == false)
        {
            setValidMove(pos);
        }
        else
        {
            setInvalidMove(pos);
        }
    }
    //Move lower left
    row = fixed_row + 1;
    col = fixed_col - 1;
    if (row >= 0 && row < 8 && col >= 0 && col < 8)
    {
        pos->setPosition(col, row);
        piece = board[col][row];

        if (piece == nullptr)
        {
            setValidMove(pos);
        }
        else if (piece != nullptr && piece->team != this->team &&
                 piece->getIsDefended() == false)
        {
            setValidMove(pos);
        }
        else
        {
            setInvalidMove(pos);
        }
    }
    //Move lower right
    row = fixed_row + 1;
    col = fixed_col + 1;
    if (row >= 0 && row < 8 && col >= 0 && col < 8)
    {
        pos->setPosition(col, row);
        piece = board[col][row];

        if (piece == nullptr)
        {
            setValidMove(pos);
        }
        else if (piece != nullptr && piece->team != this->team &&
                 piece->getIsDefended() == false)
        {
            setValidMove(pos);
        }
        else
        {
            setInvalidMove(pos);
        }
    }
    delete (pos);
}


void King::invalidateKingMoves(Piece *piece)
{
    /*
        .. = allValidMoves
        xx = invalidMoves

         a  b  c  d  e  f  g  h
         0  1  2  3  4  5  6  7
        +--+--+--+--+--+--+--+--+
   8 0  |xx|  |  |  |xx|xx|  |  |
        +--+--+--+--+--+--+--+--+
   7 1  |  |xx|  |xx|  |xx|  |  |
        +--+--+--+--+--+--+--+--+
   6 2  |  |  |bB|  |  |xx|  |  |
        +--+--+--+--+--+--+--+--+
   5 3  |xx|xx|xx|xx|xx|bR|xx|xx|
        +--+--+--+--+--+--+--+--+
   4 4  |xx|  |  |..|xx|xx|  |  |
        +--+--+--+--+--+--+--+--+
   3 5  |  |  |  |..|wK|xx|  |  |
        +--+--+--+--+--+--+--+--+
   2 6  |  |  |  |..|..|xx|xx|  |
        +--+--+--+--+--+--+--+--+
   1 7  |  |  |  |  |  |xx|  |xx|
        +--+--+--+--+--+--+--+--+
         a  b  c  d  e  f  g  h
         0  1  2  3  4  5  6  7       */
    Position *pos = new Position();
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            pos->setPosition(i, j);
            if (piece->isValidMove(pos))
            {
                setInvalidMove(pos);
            }
        }
    }
    delete (pos);
}


void King::invalidateKingMovesFromOpponentsKingsPosition(
    Position *king_position)
{

    /*   a  b  c  d  e  f  g  h
          0  1  2  3  4  5  6  7
         +--+--+--+--+--+--+--+--+
    8 0  |  |  |  |  |  |  |  |  |
         +--+--+--+--+--+--+--+--+
    7 1  |  |  |  |  |bK|  |  |  |
         +--+--+--+--+--+--+--+--+
    6 2  |  |  |  |xx|xx|xx|  |  |
         +--+--+--+--+--+--+--+--+
    5 3  |  |  |  |..|wK|..|  |  |
         +--+--+--+--+--+--+--+--+
    4 4  |  |  |  |..|..|..|  |  |
         +--+--+--+--+--+--+--+--+
    3 5  |  |  |  |  |  |  |  |  |
         +--+--+--+--+--+--+--+--+
    2 6  |  |  |  |  |  |  |  |  |
         +--+--+--+--+--+--+--+--+
    1 7  |  |  |  |  |  |  |  |  |
         +--+--+--+--+--+--+--+--+
          a  b  c  d  e  f  g  h
          0  1  2  3  4  5  6  7       */

    int king_col = king_position->col;
    int king_row = king_position->row;

    Position *pos = new Position();

    //Move up
    int col = king_col;
    int row = king_row - 1;
    if (col >= 0 && col <= 7 && row >= 0 && row <= 7)
    {
        pos->setPosition(col, row);
        setInvalidMove(pos);
    }

    //Move upper left
    col = king_col - 1;
    row = king_row - 1;
    if (col >= 0 && col <= 7 && row >= 0 && row <= 7)
    {
        pos->setPosition(col, row);
        setInvalidMove(pos);
    }

    //Move upper right
    col = king_col + 1;
    row = king_row - 1;
    if (col >= 0 && col <= 7 && row >= 0 && row <= 7)
    {
        pos->setPosition(col, row);
        setInvalidMove(pos);
    }

    //Move left
    col = king_col - 1;
    row = king_row;
    if (col >= 0 && col <= 7 && row >= 0 && row <= 7)
    {
        pos->setPosition(col, row);
        setInvalidMove(pos);
    }

    //Move right
    col = king_col + 1;
    row = king_row;
    if (col >= 0 && col <= 7 && row >= 0 && row <= 7)
    {
        pos->setPosition(col, row);
        setInvalidMove(pos);
    }

    //Move down
    col = king_col;
    row = king_row + 1;
    if (col >= 0 && col <= 7 && row >= 0 && row <= 7)
    {
        pos->setPosition(col, row);
        setInvalidMove(pos);
    }

    //Move lower left
    col = king_col - 1;
    row = king_row + 1;
    if (col >= 0 && col <= 7 && row >= 0 && row <= 7)
    {
        pos->setPosition(col, row);
        setInvalidMove(pos);
    }

    //Move lower right
    col = king_col + 1;
    row = king_row + 1;
    if (col >= 0 && col <= 7 && row >= 0 && row <= 7)
    {
        pos->setPosition(col, row);
        setInvalidMove(pos);
    }

    delete (pos);
}

void King::invalidateKingMove(Position *pos)
{
    setInvalidMove(pos);
}

void King::calculateCastle(Piece *board[8][8])
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
    4 4  |  |  |  |  |  |  |  |  |
         +--+--+--+--+--+--+--+--+
    3 5  |  |  |  |  |  |  |  |  |
         +--+--+--+--+--+--+--+--+
    2 6  |  |  |  |  |  |  |  |  |
         +--+--+--+--+--+--+--+--+
    1 7  |wR|  |..|  |wK|  |..|wR|
         +--+--+--+--+--+--+--+--+
          a  b  c  d  e  f  g  h
          0  1  2  3  4  5  6  7       */

    //If King moved returns void
    if (this->getMoveCount() > 0)
    {
        return;
    }

    // Castle RULES:
    // 1) The king has not previously moved;
    // 2) There must be a rook in the initial position
    // 3) Your chosen rook has not previously moved;
    // 4) There must be no pieces between the king and the chosen rook;
    // 5) The king is not currently in check;
    // 6) Your king must not pass through a square that is under attack by enemy pieces;
    // 7) The king must not end up in check.

    int row = getPosition()->row;
    int col = getPosition()->col;

    Position *pos = new Position();
    if (row == 0 || row == 7)
    {

        //
        // Castle right
        //

        //1) The king has not previously moved;
        bool cond1 = this->getMoveCount() == 0;

        //2) There must be an ally rook in the initial position
        Piece *rook = board[7][row];
        bool cond2 = cond1 && rook != nullptr &&
                     rook->pieceType == enums::Piece::ROOK &&
                     rook->team == this->team;

        //3) Your chosen rook has not previously moved;
        bool cond3 = cond2 && rook->getMoveCount() == 0;

        //4) There must be no pieces between the king and the chosen rook;
        bool cond4 = cond3 && !board[5][row] && !board[6][row];

        //5) The king is not currently in check;
        bool cond5 = cond4 && !(isInCheck());

        //6) Your king must not pass through a square that is under attack by enemy pieces;
        pos->setPosition(5, row);
        bool cond6 = cond5 && isValidMove(pos);

        if (cond6)
        {
            //Castle King Right
            pos->setPosition(6, row);
            setValidMove(pos);
        }

        //
        // Castle left
        //

        //1) The king has not previously moved;
        cond1 = this->getMoveCount() == 0;

        //2) There must be an ally rook in the initial position
        rook = board[0][row];
        cond2 = cond1 && rook != nullptr &&
                rook->pieceType == enums::Piece::ROOK &&
                rook->team == this->team;

        //3) Your chosen rook has not previously moved;
        cond3 = cond2 && rook->getMoveCount() == 0;

        //4) There must be no pieces between the king and the chosen rook;
        cond4 = cond3 && !board[3][row] && !board[2][row] && !board[1][row];

        //5) The king is not currently in check;
        cond5 = cond4 && !(isInCheck());

        //6) Your king must not pass through a square that is under attack by enemy pieces;
        pos->setPosition(3, row);
        cond6 = cond5 && isValidMove(pos);

        if (cond6)
        {
            //Castle King Left
            pos->setPosition(2, row);
            setValidMove(pos);
        }
    }
    delete (pos);
}


//
// Checks
//
void King::calculateCausingCheck(Piece *board[8][8])
{

    cleanInCheck();
    cleanChecksArray();

    int fixed_row = getPosition()->row;
    int fixed_col = getPosition()->col;

    Piece *piece;

    int row = fixed_row;
    int col = fixed_col;

    //
    // Rook moves
    //

    //Rook move up
    for (row = fixed_row - 1; row >= 0; row--)
    {
        piece = board[fixed_col][row];

        if (piece != nullptr)
        {
            if (piece->team == this->team)
            {
                break;
            }
            else if (piece->team != this->team)
            {
                if (piece->pieceType == enums::Piece::ROOK ||
                    piece->pieceType == enums::Piece::QUEEN)
                {
                    causingCheck[fixed_col][row] = true;
                    setInCheckTrue();
                    while (row < fixed_row)
                    {
                        causingCheck[fixed_col][row] = true;
                        row++;
                    }
                    break;
                }
                else
                {
                    break;
                }
            }
        }
    }

    //Rook move down
    for (row = fixed_row + 1; row < 8; row++)
    {
        piece = board[fixed_col][row];

        if (piece != nullptr)
        {
            if (piece->team == this->team)
            {
                break;
            }
            else if (piece->team != this->team)
            {
                if (piece->pieceType == enums::Piece::ROOK ||
                    piece->pieceType == enums::Piece::QUEEN)
                {
                    causingCheck[fixed_col][row] = true;
                    setInCheckTrue();
                    while (row > fixed_row)
                    {
                        causingCheck[fixed_col][row] = true;
                        row--;
                    }
                    break;
                }
                else
                {
                    break;
                }
            }
        }
    }

    //Rook move right
    for (col = fixed_col + 1; col < 8; col++)
    {
        piece = board[col][fixed_row];

        if (piece != nullptr)
        {
            if (piece->team == this->team)
            {
                break;
            }
            else if (piece->team != this->team)
            {
                if (piece->pieceType == enums::Piece::ROOK ||
                    piece->pieceType == enums::Piece::QUEEN)
                {
                    causingCheck[col][fixed_row] = true;
                    setInCheckTrue();
                    while (col > fixed_col)
                    {
                        causingCheck[col][fixed_row] = true;
                        col--;
                    }
                    break;
                }
                else
                {
                    break;
                }
            }
        }
    }

    //Rook move left
    for (col = fixed_col - 1; col >= 0; col--)
    {
        piece = board[col][fixed_row];

        if (piece != nullptr)
        {
            if (piece->team == this->team)
            {
                break;
            }
            else if (piece->team != this->team)
            {
                if (piece->pieceType == enums::Piece::ROOK ||
                    piece->pieceType == enums::Piece::QUEEN)
                {
                    causingCheck[col][fixed_row] = true;
                    setInCheckTrue();
                    while (col < fixed_col)
                    {
                        causingCheck[col][fixed_row] = true;
                        col++;
                    }
                    break;
                }
                else
                {
                    break;
                }
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
        piece = board[col][row];

        if (piece != nullptr)
        {
            if (piece->team == this->team)
            {
                break;
            }
            else if (piece->team != this->team)
            {
                if (piece->pieceType == enums::Piece::BISHOP ||
                    piece->pieceType == enums::Piece::QUEEN)
                {
                    causingCheck[col][row] = true;
                    setInCheckTrue();
                    while (row > fixed_row && col > fixed_col)
                    {
                        causingCheck[col][row] = true;
                        row--;
                        col--;
                    }
                    break;
                }
                else
                {
                    break;
                }
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
        piece = board[col][row];

        if (piece != nullptr)
        {
            if (piece->team == this->team)
            {
                break;
            }
            else if (piece->team != this->team)
            {
                if (piece->pieceType == enums::Piece::BISHOP ||
                    piece->pieceType == enums::Piece::QUEEN)
                {
                    causingCheck[col][row] = true;
                    setInCheckTrue();
                    while (row > fixed_row && col < fixed_col)
                    {
                        causingCheck[col][row] = true;
                        row--;
                        col++;
                    }
                    break;
                }
                else
                {
                    break;
                }
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
        piece = board[col][row];

        if (piece != nullptr)
        {
            if (piece->team == this->team)
            {
                break;
            }
            else if (piece->team != this->team)
            {
                if (piece->pieceType == enums::Piece::BISHOP ||
                    piece->pieceType == enums::Piece::QUEEN)
                {
                    causingCheck[col][row] = true;
                    setInCheckTrue();
                    while (row < fixed_row && col < fixed_col)
                    {
                        causingCheck[col][row] = true;
                        row++;
                        col++;
                    }
                    break;
                }
                else
                {
                    break;
                }
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
        piece = board[col][row];

        if (piece != nullptr)
        {
            if (piece->team == this->team)
            {
                break;
            }
            else if (piece->team != this->team)
            {
                if (piece->pieceType == enums::Piece::BISHOP ||
                    piece->pieceType == enums::Piece::QUEEN)
                {
                    causingCheck[col][row] = true;
                    setInCheckTrue();
                    while (row < fixed_row && col > fixed_col)
                    {
                        causingCheck[col][row] = true;
                        row++;
                        col--;
                    }
                    break;
                }
                else
                {
                    break;
                }
            }
        }
        row--;
        col++;
    }

    //
    // Knight
    //

    //Knight moves above right
    row = fixed_row - 2;
    col = fixed_col + 1;
    if (row >= 0 && col < 8)
    {
        piece = board[col][row];

        if (piece != nullptr && piece->team != this->team &&
            piece->pieceType == enums::Piece::KNIGHT)
        {
            causingCheck[col][row] = true;
            setInCheckTrue();
        }
    }

    //Knight moves above left
    row = fixed_row - 2;
    col = fixed_col - 1;
    if (row >= 0 && col >= 0)
    {
        piece = board[col][row];

        if (piece != nullptr && piece->team != this->team &&
            piece->pieceType == enums::Piece::KNIGHT)
        {
            causingCheck[col][row] = true;
            setInCheckTrue();
        }
    }

    //Knight moves below left
    row = fixed_row + 2;
    col = fixed_col - 1;
    if (row < 8 && col >= 0)
    {
        piece = board[col][row];

        if (piece != nullptr && piece->team != this->team &&
            piece->pieceType == enums::Piece::KNIGHT)
        {
            causingCheck[col][row] = true;
            setInCheckTrue();
        }
    }

    //Knight moves below right
    row = fixed_row + 2;
    col = fixed_col + 1;
    if (row < 8 && col < 8)
    {
        piece = board[col][row];

        if (piece != nullptr && piece->team != this->team &&
            piece->pieceType == enums::Piece::KNIGHT)
        {
            causingCheck[col][row] = true;
            setInCheckTrue();
        }
    }

    //Knight moves right above
    row = fixed_row - 1;
    col = fixed_col + 2;
    if (row >= 0 && col < 8)
    {
        piece = board[col][row];

        if (piece != nullptr && piece->team != this->team &&
            piece->pieceType == enums::Piece::KNIGHT)
        {
            causingCheck[col][row] = true;
            setInCheckTrue();
        }
    }

    //Knight moves right below
    row = fixed_row + 1;
    col = fixed_col + 2;
    if (row < 8 && col < 8)
    {
        piece = board[col][row];

        if (piece != nullptr && piece->team != this->team &&
            piece->pieceType == enums::Piece::KNIGHT)
        {
            causingCheck[col][row] = true;
            setInCheckTrue();
        }
    }

    //Knight moves left above
    row = fixed_row - 1;
    col = fixed_col - 2;
    if (row >= 0 && col >= 0)
    {
        piece = board[col][row];

        if (piece != nullptr && piece->team != this->team &&
            piece->pieceType == enums::Piece::KNIGHT)
        {
            causingCheck[col][row] = true;
            setInCheckTrue();
        }
    }

    //Knight moves left below
    col = fixed_col - 2;
    row = fixed_row + 1;
    if (row < 8 && col >= 0)
    {
        piece = board[col][row];

        if (piece != nullptr && piece->team != this->team &&
            piece->pieceType == enums::Piece::KNIGHT)
        {
            causingCheck[col][row] = true;
            setInCheckTrue();
        }
    }

    //
    // Pawn moves
    //
    row = fixed_row;
    int col_left = fixed_col - 1;
    int col_right = fixed_col + 1;

    if (this->team == enums::Team::BLACK)
    {
        row += 1;
    }
    else if (this->team == enums::Team::WHITE)
    {
        row += -1;
    }

    if (col_left >= 0 && row >= 0 && row <= 8)
    {
        piece = board[col_left][row];
        if (piece != nullptr && piece->team != this->team &&
            piece->pieceType == enums::Piece::PAWN)
        {
            causingCheck[col_left][row] = true;
            setInCheckTrue();
        }
    }

    if (col_right <= 7 && row >= 0 && row <= 8)
    {
        piece = board[col_right][row];
        if (piece != nullptr && piece->team != this->team &&
            piece->pieceType == enums::Piece::PAWN)
        {
            causingCheck[col_right][row] = true;
            setInCheckTrue();
        }
    }
}

void King::cleanChecksArray()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            causingCheck[i][j] = false;
        }
    }
}

void King::cleanInCheck()
{
    inCheck = false;
}

bool King::isInCheck()
{
    return inCheck;
}

void King::setInCheckTrue()
{
    inCheck = true;
}
