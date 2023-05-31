#include "CardView.hpp"

#include "Grid.hpp"
#include "ImageLoading.hpp"
#include "RectangleFunctions.hpp"
#include "Renderer.hpp"

namespace HiLo
{

static Grid const grid{{4180, 1580}, {280, 380}, 20};
static Rectangle const bounds{0, 288, 1080, 1344};
constexpr double scaleFactor{0.8};
constexpr char const *spritesheetPath{"Assets/playingCards.png"};

static auto getDestination() noexcept -> Rectangle
{
    auto destination = fittingRectangle(grid.fieldSize(), bounds);
    scaleInPlace(destination, scaleFactor);
    return destination;
}

CardView::CardView() noexcept
    : mCardSpritesheet{loadTexture(spritesheetPath)}, mSource{0, 0, 0, 0},
      mDestination{getDestination()}
{
}

auto CardView::setCard(Card const &card) noexcept -> void
{
    auto const x = [&]() {
        if (card.rank() == Card::Rank::A)
        {
            return 0;
        }
        else
        {
            return static_cast<int>(card.rank()) + 1;
        }
    }();
    auto const y = [&]() {
        if (card.suit() == Card::Suit::spades)
        {
            return 0;
        }
        else
        {
            return static_cast<int>(card.suit()) + 1;
        }
    }();
    mSource = grid.fieldBounds(x, y);
}

auto CardView::draw() const noexcept -> void
{
    Renderer::instance().copy(mCardSpritesheet, mSource, mDestination);
}

} // namespace HiLo
