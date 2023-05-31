#include "game.h"

#include "pieces/piece.h"
#include "pieces/piece_bishop.h"
#include "pieces/piece_king.h"
#include "pieces/piece_knight.h"
#include "pieces/piece_pawn.h"
#include "pieces/piece_queen.h"
#include "pieces/piece_rook.h"
#include "utils/enums.h"
#include "utils/position.h"
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>


//
// Constructors and Destructors
//
Game::Game()
{
    checkmate = false;
    draw = false;
    totalMoves = 0;
}

Game::~Game()
{
}

//
//Game
//
void Game::initializePiecesOnChessboard()
{

    /*   a  b  c  d  e  f  g  h
      0  1  2  3  4  5  6  7
     +--+--+--+--+--+--+--+--+
8 0  |bR|bN|bB|bQ|bK|bB|bN|bR|
     +--+--+--+--+--+--+--+--+
7 1  |bp|bp|bp|bp|bp|bp|bp|bp|
     +--+--+--+--+--+--+--+--+
6 2  |  |  |  |  |  |  |  |  |
     +--+--+--+--+--+--+--+--+
5 3  |  |  |  |  |  |  |  |  |
     +--+--+--+--+--+--+--+--+
4 4  |  |  |  |  |  |  |  |  |
     +--+--+--+--+--+--+--+--+
3 5  |  |  |  |  |  |  |  |  |
     +--+--+--+--+--+--+--+--+
2 6  |wp|wp|wp|wp|wp|wp|wp|wp|
     +--+--+--+--+--+--+--+--+
1 7  |wR|wN|wB|wQ|bK|wB|wN|wR|
     +--+--+--+--+--+--+--+--+
      a  b  c  d  e  f  g  h
      0  1  2  3  4  5  6  7       */

    Rook *bR1 = new Rook(enums::Team::BLACK, new Position(0, 0));
    Rook *bR2 = new Rook(enums::Team::BLACK, new Position(7, 0));
    Knight *bN1 = new Knight(enums::Team::BLACK, new Position(1, 0));
    Knight *bN2 = new Knight(enums::Team::BLACK, new Position(6, 0));
    Bishop *bB1 = new Bishop(enums::Team::BLACK, new Position(2, 0));
    Bishop *bB2 = new Bishop(enums::Team::BLACK, new Position(5, 0));
    Queen *bQ = new Queen(enums::Team::BLACK, new Position(3, 0));
    blackKing = new King(enums::Team::BLACK, new Position(4, 0));
    Pawn *bP1 = new Pawn(enums::Team::BLACK, new Position(0, 1));
    Pawn *bP2 = new Pawn(enums::Team::BLACK, new Position(1, 1));
    Pawn *bP3 = new Pawn(enums::Team::BLACK, new Position(2, 1));
    Pawn *bP4 = new Pawn(enums::Team::BLACK, new Position(3, 1));
    Pawn *bP5 = new Pawn(enums::Team::BLACK, new Position(4, 1));
    Pawn *bP6 = new Pawn(enums::Team::BLACK, new Position(5, 1));
    Pawn *bP7 = new Pawn(enums::Team::BLACK, new Position(6, 1));
    Pawn *bP8 = new Pawn(enums::Team::BLACK, new Position(7, 1));

    allPiecesOnBoard.push_back(bR1);
    allPiecesOnBoard.push_back(bR2);
    allPiecesOnBoard.push_back(bN1);
    allPiecesOnBoard.push_back(bN2);
    allPiecesOnBoard.push_back(bB1);
    allPiecesOnBoard.push_back(bB2);
    allPiecesOnBoard.push_back(bQ);
    allPiecesOnBoard.push_back(blackKing);
    allPiecesOnBoard.push_back(bP1);
    allPiecesOnBoard.push_back(bP2);
    allPiecesOnBoard.push_back(bP3);
    allPiecesOnBoard.push_back(bP4);
    allPiecesOnBoard.push_back(bP5);
    allPiecesOnBoard.push_back(bP6);
    allPiecesOnBoard.push_back(bP7);
    allPiecesOnBoard.push_back(bP8);

    Rook *wR1 = new Rook(enums::Team::WHITE, new Position(0, 7));
    Rook *wR2 = new Rook(enums::Team::WHITE, new Position(7, 7));
    Knight *wN1 = new Knight(enums::Team::WHITE, new Position(1, 7));
    Knight *wN2 = new Knight(enums::Team::WHITE, new Position(6, 7));
    Bishop *wB1 = new Bishop(enums::Team::WHITE, new Position(2, 7));
    Bishop *wB2 = new Bishop(enums::Team::WHITE, new Position(5, 7));
    Queen *wQ = new Queen(enums::Team::WHITE, new Position(3, 7));
    whiteKing = new King(enums::Team::WHITE, new Position(4, 7));
    Pawn *wP1 = new Pawn(enums::Team::WHITE, new Position(0, 6));
    Pawn *wP2 = new Pawn(enums::Team::WHITE, new Position(1, 6));
    Pawn *wP3 = new Pawn(enums::Team::WHITE, new Position(2, 6));
    Pawn *wP4 = new Pawn(enums::Team::WHITE, new Position(3, 6));
    Pawn *wP5 = new Pawn(enums::Team::WHITE, new Position(4, 6));
    Pawn *wP6 = new Pawn(enums::Team::WHITE, new Position(5, 6));
    Pawn *wP7 = new Pawn(enums::Team::WHITE, new Position(6, 6));
    Pawn *wP8 = new Pawn(enums::Team::WHITE, new Position(7, 6));

    allPiecesOnBoard.push_back(wR1);
    allPiecesOnBoard.push_back(wR2);
    allPiecesOnBoard.push_back(wN1);
    allPiecesOnBoard.push_back(wN2);
    allPiecesOnBoard.push_back(wB1);
    allPiecesOnBoard.push_back(wB2);
    allPiecesOnBoard.push_back(wQ);
    allPiecesOnBoard.push_back(whiteKing);
    allPiecesOnBoard.push_back(wP1);
    allPiecesOnBoard.push_back(wP2);
    allPiecesOnBoard.push_back(wP3);
    allPiecesOnBoard.push_back(wP4);
    allPiecesOnBoard.push_back(wP5);
    allPiecesOnBoard.push_back(wP6);
    allPiecesOnBoard.push_back(wP7);
    allPiecesOnBoard.push_back(wP8);

    for (auto &piece : allPiecesOnBoard)
    {
        board[piece->getPosition()->col][piece->getPosition()->row] = piece;
    }
}

bool Game::isCheckmate()
{
    checkmate = false;
    if (whiteKing->isInCheck())
    {
        for (auto &piece : allPiecesOnBoard)
        {
            if (piece->team == enums::Team::WHITE)
            {
                checkmate = piece->hasNoValidMove();
                if (!checkmate)
                {
                    break;
                }
            }
        }
    }
    else if (blackKing->isInCheck())
    {
        for (auto &piece : allPiecesOnBoard)
        {
            if (piece->team == enums::Team::BLACK)
            {
                checkmate = piece->hasNoValidMove();
                if (!checkmate)
                {
                    break;
                }
            }
        }
    }
    return checkmate;
}

bool Game::isDraw(enums::Team team)
{
    draw = false;
    for (auto &piece : allPiecesOnBoard)
    {
        if (piece->team == team)
        {
            draw = piece->hasNoValidMove();
            if (!draw)
            {
                break;
            }
        }
    }
    return draw;
}

//
// Prints
//
void Game::printBoard()
{
    std::cout << "   a  b  c  d  e  f  g  h  " << std::endl;
    for (int j = 0; j < 8; j++)
    {
        std::cout << "  +--+--+--+--+--+--+--+--+" << std::endl;
        std::cout << (8 - j) << " |";
        for (int i = 0; i < 8; i++)
        {
            if (board[i][j])
            {
                std::cout << board[i][j]->toString() << "|";
            }
            else
            {
                std::cout << "  "
                          << "|";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "  +--+--+--+--+--+--+--+--+" << std::endl;
    std::cout << "   a  b  c  d  e  f  g  h  " << std::endl;
}

void Game::printRound()
{
    std::cout << "_" << std::endl;
    std::cout << "Move number " << (totalMoves + 1) << std::endl;
}

void Game::printCapturedPieces()
{
    std::cout << "Captured white pieces: ";
    for (auto &piece : capturedWhitePieces)
    {
        std::cout << piece->toString() << " ";
    }
    std::cout << "\nCaptured black pieces: ";
    for (auto &piece : capturedBlackPieces)
    {
        std::cout << piece->toString() << " ";
    }
    std::cout << std::endl;
}

void Game::printChecks()
{
    if (whiteKing->isInCheck())
    {
        std::cout << "WHITE KING IN CHECK!" << std::endl;
    }
    else if (blackKing->isInCheck())
    {
        std::cout << "BLACK KING IN CHECK!" << std::endl;
    }
}

void Game::printTeamToMove()
{
    if (!checkmate && !draw)
    {
        if (totalMoves % 2 == 0)
        {
            std::cout << "WHITE TO MOVE" << std::endl;
        }
        else
        {
            std::cout << "BLACK TO MOVE" << std::endl;
        }
        std::cout << std::endl;
    }
}

void Game::printEndGame()
{
    if (checkmate)
    {
        if (totalMoves % 2 == 0)
        {
            std::cout << "Checkmate! Black Wins! " << std::endl;
        }
        else
        {
            std::cout << "Checkmate! White Wins!" << std::endl;
        }
    }
    else if (draw)
    {
        std::cout << "Draw!" << std::endl;
    }
}

//
// Board
//
Piece *Game::getPieceFromBoardPosition(Position *pos)
{
    return board[pos->col][pos->row];
}

bool Game::isBoardPositionEmpty(Position *pos)
{
    return (board[pos->col][pos->row] == nullptr);
}

Piece *Game::movePiece(Position *from, Position *to)
{
    Piece *p = getPieceFromBoardPosition(from);
    board[from->col][from->row] = nullptr;
    board[to->col][to->row] = p;
    p->addMoveCount();
    p->setPosition(to->col, to->row);
    return p;
}

//
// Pieces vector
//
void Game::removePieceFromVector(Piece *piece)
{
    for (int i = 0; i < allPiecesOnBoard.size(); i++)
    {
        if (allPiecesOnBoard[i]->getPosition() == piece->getPosition())
        {
            allPiecesOnBoard.erase(std::next(allPiecesOnBoard.begin(), i));
            break;
        }
    }
}

void Game::addToCapturedPiecesVector(Piece *piece)
{
    if (piece->team == enums::Team::WHITE)
    {
        capturedWhitePieces.push_back(piece);
    }
    else
    {
        capturedBlackPieces.push_back(piece);
    }
}

//
// Pieces
//
void Game::calculateAllValidMovesForBoardPieces()
{
    for (auto &piece : allPiecesOnBoard)
    {
        piece->calculateValidMoves(board);
    }
}

void Game::invalidateAllMovesThatDontProtectKing()
{
    if (blackKing->isInCheck())
    {
        for (auto &piece : allPiecesOnBoard)
        {
            if (piece->team == enums::Team::BLACK &&
                piece->pieceType != enums::Piece::KING)
            {
                piece->invalidateAllMoves(blackKing->causingCheck);
            }
        }
    }
    else if (whiteKing->isInCheck())
    {
        for (auto &piece : allPiecesOnBoard)
        {
            if (piece->team == enums::Team::WHITE &&
                piece->pieceType != enums::Piece::KING)
            {
                piece->invalidateAllMoves(whiteKing->causingCheck);
            }
        }
    }
}

void Game::cleanAllIsDefendedPieceAtribute()
{
    for (auto &piece : allPiecesOnBoard)
    {
        piece->setIsDefended(false);
    }
}


//
// Pawn
//
bool Game::isPawnPromotion(Position *from, Position *to)
{
    Piece *piece = getPieceFromBoardPosition(from);
    Piece *pieceTo = getPieceFromBoardPosition(to);

    return (piece->pieceType == enums::Piece::PAWN &&
            (pieceTo == nullptr || piece->team != pieceTo->team) &&
            ((piece->team == enums::Team::WHITE && to->row == 0) ||
             (piece->team == enums::Team::BLACK && to->row == 7)));
}


Piece *Game::promoteToQueen(Piece *pawn)
{
    Queen *nQ = new Queen(
        pawn->team,
        new Position(pawn->getPosition()->col, pawn->getPosition()->row));
    allPiecesOnBoard.push_back(nQ);
    board[pawn->getPosition()->col][pawn->getPosition()->row] = nQ;
    return nQ;
}

bool Game::isEnPassant(Position *from, Position *to)
{

    Piece *piece = getPieceFromBoardPosition(from);
    Piece *pieceTo = getPieceFromBoardPosition(to);


    //Checks if theres a piece in the position to move
    if (pieceTo)
        return false;

    //Gets enemys piece position
    Position *enemyPos = nullptr;
    int en_passant_row = 0;
    if (piece->team == enums::Team::WHITE)
    {
        enemyPos = new Position(to->col, to->row + 1);
        en_passant_row = 3;
    }
    else if (piece->team == enums::Team::BLACK)
    {
        enemyPos = new Position(to->col, to->row - 1);
        en_passant_row = 4;
    }

    //Gets enemys piece
    Piece *enemyPiece = getPieceFromBoardPosition(enemyPos);

    //En Passant:
    //  1 - "from" position must have an allied pawn
    //  2 - Position aside must have an enemy pawn
    //  3 - Enemy pawn must have moved two sqaures
    //  4 - Enemy pawn must have made only one move
    //  5 - Enemy pawn must be the last piece moved

    if (piece && piece->pieceType == enums::Piece::PAWN     //1
        && enemyPiece && enemyPiece->pieceType == enums::Piece::PAWN &&
        enemyPiece->team != piece->team                     //2
        && enemyPiece->getPosition()->row == en_passant_row //3
        && enemyPiece->getMoveCount() == 1                  //4
        && enemyPiece->getIsLastPieceMoved()                //5
    )
    {
        delete enemyPos;
        return true;
    }

    delete enemyPos;
    return false;
}

void Game::removeEnPassantPawn(Piece *pawn)
{
    if (pawn && pawn->pieceType == enums::Piece::PAWN)
    {
        board[pawn->getPosition()->col][pawn->getPosition()->row] = nullptr;
    }
}

//
// King
//
void Game::calculateCausingCheckForBothKings()
{
    blackKing->calculateCausingCheck(board);
    whiteKing->calculateCausingCheck(board);
}

void Game::calculateCastleMoveForBothKings()
{
    blackKing->calculateCastle(board);
    whiteKing->calculateCastle(board);
}

void Game::calculateBothKingInvalidMoves()
{
    Position *pos = new Position();
    for (auto &piece : allPiecesOnBoard)
    {
        //Invalidates diagonal valid moves of pawn for King
        if (piece->pieceType == enums::Piece::PAWN)
        {
            int row = piece->getPosition()->row;
            int col = piece->getPosition()->col;

            if (piece->team == enums::Team::WHITE)
            {
                if (piece->getIsDefended())
                {
                    blackKing->invalidateKingMove(piece->getPosition());
                }
                if (row > 0 && col < 7)
                {
                    pos->setPosition(col + 1, row - 1);
                    blackKing->invalidateKingMove(pos);
                }
                if (row > 0 && col > 0)
                {
                    pos->setPosition(col - 1, row - 1);
                    blackKing->invalidateKingMove(pos);
                }
            }
            else
            {
                if (piece->getIsDefended())
                {
                    whiteKing->invalidateKingMove(piece->getPosition());
                }
                if (row < 7 && col < 7)
                {
                    pos->setPosition(col + 1, row + 1);
                    whiteKing->invalidateKingMove(pos);
                }
                if (row < 7 && col > 0)
                {
                    pos->setPosition(col - 1, row + 1);
                    whiteKing->invalidateKingMove(pos);
                }
            }
        }
        //Invalidates all valid moves from enemy pieces for King
        else if (piece->pieceType != enums::Piece::KING)
        {
            if (piece->team == enums::Team::WHITE)
            {
                blackKing->invalidateKingMoves(piece);
                if (piece->getIsDefended())
                {
                    blackKing->invalidateKingMove(piece->getPosition());
                }
            }
            else
            {
                whiteKing->invalidateKingMoves(piece);
                if (piece->getIsDefended())
                {
                    whiteKing->invalidateKingMove(piece->getPosition());
                }
            }
        }
    }
    //Invalidates all enemy King moves for King
    whiteKing->invalidateKingMovesFromOpponentsKingsPosition(
        blackKing->getPosition());
    blackKing->invalidateKingMovesFromOpponentsKingsPosition(
        whiteKing->getPosition());
    delete (pos);
}


void Game::cleanBothKingChecks()
{
    whiteKing->cleanInCheck();
    blackKing->cleanInCheck();
}


bool Game::causesCheck(Position *from, Position *to)
{
    enums::Team team = board[from->col][from->row]->team;
    Piece *pieceFrom = nullptr;
    Piece *pieceTo = nullptr;
    bool isCheck = false;

    if (isBoardPositionEmpty(to))
    {
        //Moves piece
        pieceFrom = getPieceFromBoardPosition(from);
        board[from->col][from->row] = nullptr;
        board[to->col][to->row] = pieceFrom;
        pieceFrom->setPosition(to->col, to->row);


        if (team == enums::Team::WHITE)
        {
            whiteKing->calculateCausingCheck(board);
        }
        else if (team == enums::Team::BLACK)
        {
            blackKing->calculateCausingCheck(board);
        }

        //Checks if is white piece and causes white king check
        if (team == enums::Team::WHITE && whiteKing->isInCheck())
        {
            isCheck = true;
        }
        //Checks if is black piece and causes black king check
        else if (team == enums::Team::BLACK && blackKing->isInCheck())
        {
            isCheck = true;
        }
        //Rollback
        board[from->col][from->row] = pieceFrom;
        board[to->col][to->row] = nullptr;
        pieceFrom->setPosition(from->col, from->row);
    }
    // If theres a enemy piece on "to" position
    else
    {
        pieceFrom = getPieceFromBoardPosition(from);
        pieceTo = getPieceFromBoardPosition(to);

        //Checks if moving piece is a king and the attacked piece is defended
        if (pieceFrom->pieceType == enums::Piece::KING &&
            pieceTo->getIsDefended())
        {
            isCheck = false;
        }
        else
        {
            //Removes enemy piece from board pieces vector
            removePieceFromVector(pieceTo);

            //Attacks enemy piece
            board[from->col][from->row] = nullptr;
            board[to->col][to->row] = pieceFrom;
            pieceFrom->setPosition(to->col, to->row);


            if (team == enums::Team::WHITE)
            {
                whiteKing->calculateCausingCheck(board);
            }
            else if (team == enums::Team::BLACK)
            {
                blackKing->calculateCausingCheck(board);
            }

            //Checks if is white piece and causes white king check
            if (team == enums::Team::WHITE && whiteKing->isInCheck())
            {
                isCheck = true;
            }
            //Checks if is black piece and causes black king check
            else if (team == enums::Team::BLACK && blackKing->isInCheck())
            {
                isCheck = true;
            }
            //Rollback
            board[from->col][from->row] = pieceFrom;
            board[to->col][to->row] = pieceTo;
            pieceFrom->setPosition(from->col, from->row);
            pieceTo->setPosition(to->col, to->row);
            allPiecesOnBoard.push_back(pieceTo);
        }
    }

    if (team == enums::Team::WHITE)
    {
        whiteKing->calculateCausingCheck(board);
    }
    else if (team == enums::Team::BLACK)
    {
        blackKing->calculateCausingCheck(board);
    }

    cleanBothKingChecks();
    cleanAllIsDefendedPieceAtribute();
    calculateAllValidMovesForBoardPieces();
    calculateBothKingInvalidMoves();

    return isCheck;
}

enums::Castle Game::getCastleMovement(Position *from, Position *to)
{

    Piece *pieceFrom = getPieceFromBoardPosition(from);

    if (pieceFrom->pieceType == enums::Piece::KING && to->row == from->row &&
        (from->row == 0 || from->row == 7))
    {

        if (to->col == (from->col + 2))
        {
            return enums::Castle::CASTLE_RIGHT;
        }
        else if (to->col == (from->col - 2))
        {
            return enums::Castle::CASTLE_LEFT;
        }
    }
    return enums::Castle::NO_CASTLE;
}

//
//
//
bool Game::isWhiteKingInCheck()
{
    return whiteKing->isInCheck();
}

bool Game::isBlackKingInCheck()
{
    return blackKing->isInCheck();
}

Position *Game::getWhiteKingPosition()
{
    return whiteKing->getPosition();
}

Position *Game::getBlackKingPosition()
{
    return blackKing->getPosition();
}

//
// Current player
//
enums::Team Game::getCurrentTeamTurn()
{
    if (totalMoves % 2 == 0)
    {
        return enums::Team::WHITE;
    }
    else
    {
        return enums::Team::BLACK;
    }
}

//
// En passant
//
void Game::setLastPieceMoved(Piece *lastPieceMoved)
{
    cleanAllLastPieceMoved();
    for (auto &piece : allPiecesOnBoard)
    {
        if (piece->getPosition() == lastPieceMoved->getPosition())
        {
            piece->setIsLastPieceMoved(true);
            break;
        }
    }
}

void Game::cleanAllLastPieceMoved()
{
    for (auto &piece : allPiecesOnBoard)
    {
        piece->setIsLastPieceMoved(false);
    }
}

//
// Total moves
//
void Game::addTotalMoves()
{
    totalMoves += 1;
}
