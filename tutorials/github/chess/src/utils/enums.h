#ifndef _enums
#define _enums

namespace enums
{
enum class Piece
{
    EMPTY = 0,
    PAWN = 1,
    ROOK = 2,
    KNIGHT = 3,
    BISHOP = 4,
    KING = 5,
    QUEEN = 6
};
enum class Team
{
    NONE = 0,
    WHITE = 1,
    BLACK = 2
};
enum class Castle
{
    NO_CASTLE = 0,
    CASTLE_RIGHT = 1,
    CASTLE_LEFT = 2
};
} // namespace enums

#endif
