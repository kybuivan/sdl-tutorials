#ifndef _game
#define _game

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


class Game
{
public:
    //
    // Constructors and Destructors
    //
    Game();
    ~Game();

    //
    // Game
    //
    void initializePiecesOnChessboard();
    bool isCheckmate();
    bool isDraw(enums::Team team);

    //
    // Prints
    //
    void printBoard();
    void printRound();
    void printCapturedPieces();
    void printChecks();
    void printTeamToMove();
    void printEndGame();

    //
    // Board
    //
    Piece *getPieceFromBoardPosition(Position *pos);
    bool isBoardPositionEmpty(Position *pos);
    Piece *movePiece(Position *from, Position *to);

    //
    // Pieces vector
    //
    void removePieceFromVector(Piece *piece);
    void addToCapturedPiecesVector(Piece *piece);

    //
    // Pieces
    //
    void calculateAllValidMovesForBoardPieces();
    void invalidateAllMovesThatDontProtectKing();
    void cleanAllIsDefendedPieceAtribute();

    //
    // Pawn
    //
    bool isPawnPromotion(Position *from, Position *to);
    Piece *promoteToQueen(Piece *pawn);
    bool isEnPassant(Position *from, Position *to);
    void removeEnPassantPawn(Piece *pawn);

    //
    // King
    //
    void calculateCausingCheckForBothKings();
    void calculateCastleMoveForBothKings();
    void calculateBothKingInvalidMoves();
    void cleanBothKingChecks();
    bool causesCheck(Position *from, Position *to);
    enums::Castle getCastleMovement(Position *from, Position *to);

    bool isWhiteKingInCheck();
    bool isBlackKingInCheck();
    Position *getWhiteKingPosition();
    Position *getBlackKingPosition();

    //
    // Current player
    //
    enums::Team getCurrentTeamTurn();

    //
    // En passant
    //
    void setLastPieceMoved(Piece *lastPieceMoved);
    void cleanAllLastPieceMoved();

    //
    // Total moves
    //
    void addTotalMoves();

private:
    Piece *board[8][8] = {NULL};
    bool checkmate = false;
    bool draw = false;
    int totalMoves = 0;

    King *whiteKing;
    King *blackKing;

    std::vector<Piece *> allPiecesOnBoard;
    std::vector<Piece *> capturedWhitePieces;
    std::vector<Piece *> capturedBlackPieces;
};
#endif
