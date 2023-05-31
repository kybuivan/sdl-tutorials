#include "game_service.h"

#include "game.h"
#include "pieces/piece.h"
#include "utils/enums.h"
#include "utils/position.h"
#include <iostream>
#include <memory>

//
// Constructors and Destructors
//
GameService::GameService()
{
    game = std::make_unique<Game>();
    game->initializePiecesOnChessboard();
    checkmate = false;
    draw = false;
    lastPieceMoved = nullptr;
}

GameService::~GameService()
{
    delete lastPieceMoved;
}

//
// Validate mouse click
//
bool GameService::validateFirstMouseClick(Position *pos)
{
    Piece *pieceSelected = game->getPieceFromBoardPosition(pos);
    return (pieceSelected != nullptr && pieceSelected->team == currentTeamTurn);
}

bool GameService::validateSecondMouseClick(Position *from, Position *to)
{
    Piece *piece = game->getPieceFromBoardPosition(from);

    // Gets piece to remove if it exists
    Piece *pieceToRemove = game->getPieceFromBoardPosition(to);

    if (piece->isValidMove(to))
    {

        if (game->causesCheck(from, to))
        {
            //std::cout<<"Move causes check!"<<std::endl;
            return false;
        }
        // Checks if move is Castle
        else if (game->getCastleMovement(from, to) != enums::Castle::NO_CASTLE)
        {
            Position *lastRookPos = new Position();
            Position *newRookPos = new Position();

            //Castle right
            if (game->getCastleMovement(from, to) ==
                enums::Castle::CASTLE_RIGHT)
            {
                lastRookPos->setPosition(7, from->row);
                newRookPos->setPosition(5, from->row);
                //Moves rook
                game->movePiece(lastRookPos, newRookPos);
            }
            //Castle left
            else
            {
                lastRookPos->setPosition(0, from->row);
                newRookPos->setPosition(3, from->row);
                //Moves rook
                game->movePiece(lastRookPos, newRookPos);
            }
            //Moves pawn
            lastPieceMoved = game->movePiece(from, to);
            game->setLastPieceMoved(lastPieceMoved);

            //Updates total moves number
            game->addTotalMoves();

            //Cleans
            delete (lastRookPos);
            delete (newRookPos);

            //Validates move
            return true;
        }
        //Checks if move is pawn promotion
        else if (game->isPawnPromotion(from, to))
        {

            //Removes pawn
            game->removePieceFromVector(piece);

            //Removes piece if it exists
            if (pieceToRemove)
                game->removePieceFromVector(pieceToRemove);

            //Moves pawn
            game->movePiece(from, to);

            //Promotes pawn to queen
            lastPieceMoved = game->promoteToQueen(piece);
            game->setLastPieceMoved(lastPieceMoved);

            //Updates total moves number
            game->addTotalMoves();

            //Validates move
            return true;
        }
        //Checks if move is en passant
        else if (game->isEnPassant(from, to))
        {

            //Gets enemy piece position
            Position *enemyPos = nullptr;
            if (piece->team == enums::Team::WHITE)
            {
                enemyPos = new Position(to->col, to->row + 1);
            }
            else if (piece->team == enums::Team::BLACK)
            {
                enemyPos = new Position(to->col, to->row - 1);
            }

            //Gets enemy piece
            Piece *enemyPiece = game->getPieceFromBoardPosition(enemyPos);

            //Add enemy piece to captured pieces vector
            game->addToCapturedPiecesVector(enemyPiece);

            //Removes pawn
            game->removePieceFromVector(enemyPiece);
            game->removeEnPassantPawn(enemyPiece);

            //Attacks enemy piece
            lastPieceMoved = game->movePiece(from, to);
            game->setLastPieceMoved(lastPieceMoved);

            //Updates total moves number
            game->addTotalMoves();

            //Cleans
            delete (enemyPos);

            //Validates move
            return true;
        }
        //Checks if position is empty
        else if (game->isBoardPositionEmpty(to))
        {
            //Moves piece
            lastPieceMoved = game->movePiece(from, to);
            game->setLastPieceMoved(lastPieceMoved);

            //Updates total moves number
            game->addTotalMoves();

            //Validates move
            return true;
        }
        //Checks if it is a enemy piece
        else
        {
            //Checks if piece to move is King and if piece to remove is defended
            if (piece->pieceType == enums::Piece::KING &&
                pieceToRemove->getIsDefended())
            {
                return false;
            }
            else
            {
                //Add enemy piece to captured pieces vector
                game->addToCapturedPiecesVector(pieceToRemove);

                //Remove enemy piece from board pieces vector
                game->removePieceFromVector(pieceToRemove);

                //Attacks enemy piece
                lastPieceMoved = game->movePiece(from, to);
                game->setLastPieceMoved(lastPieceMoved);

                //Updates total moves number
                game->addTotalMoves();

                //Validates move
                return true;
            }
        }
    }
    //If it is an invalid move
    else
    {
        return false;
    }
}

//
// Current game status
//
void GameService::calculateCurrentGameStatus()
{
    game->cleanBothKingChecks();

    game->cleanAllIsDefendedPieceAtribute();

    game->calculateAllValidMovesForBoardPieces();

    game->calculateBothKingInvalidMoves();

    game->calculateCastleMoveForBothKings();

    game->calculateCausingCheckForBothKings();

    game->invalidateAllMovesThatDontProtectKing();

    currentTeamTurn = game->getCurrentTeamTurn();

    checkmate = game->isCheckmate();

    draw = game->isDraw(currentTeamTurn);

    printCurrentGameOnConsole();
}

bool GameService::hasCurentGameEnded()
{
    return (checkmate || draw);
}

void GameService::printCurrentGameOnConsole()
{
    game->printRound();
    game->printCapturedPieces();
    game->printChecks();
    game->printTeamToMove();
    game->printEndGame();
}

//
// Board pieces
//
Piece *GameService::getPieceFromBoardPosition(Position *pos)
{
    return game->getPieceFromBoardPosition(pos);
}

std::string GameService::getPieceNameFromBoardPosition(Position *pos)
{
    return getPieceFromBoardPosition(pos)->toString();
}

bool GameService::isPieceValidMove(Position *piecePos, Position *movePos)
{
    Piece *piece = getPieceFromBoardPosition(piecePos);
    if (piece != nullptr)
    {
        return piece->isValidMove(movePos);
    }
    return false;
}

//
// King
//
bool GameService::isWhiteKingInCheck()
{
    return game->isWhiteKingInCheck();
}

bool GameService::isBlackKingInCheck()
{
    return game->isBlackKingInCheck();
}

Position *GameService::getWhiteKingPosition()
{
    return game->getWhiteKingPosition();
}

Position *GameService::getBlackKingPosition()
{
    return game->getBlackKingPosition();
}
