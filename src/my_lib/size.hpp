#ifndef _SIZE_H_
#define _SIZE_H_

/**
 * @brief A class representing a two-dimensional size with width and height attributes.
 */
class Size
{
public:
    /**
     * @brief Default constructor.
     */
    Size() noexcept = default;

    /**
     * @brief Parameterized constructor.
     *
     * @param width The width value.
     * @param height The height value.
     */
    Size(int width, int height) noexcept;

    /**
     * @brief Get the width value.
     *
     * @return The width value.
     */
    auto width() const noexcept -> int;

    /**
     * @brief Set the width value.
     *
     * @param width The width value to set.
     */
    auto setWidth(int width) noexcept -> void;

    /**
     * @brief Get the height value.
     *
     * @return The height value.
     */
    auto height() const noexcept -> int;

    /**
     * @brief Set the height value.
     *
     * @param height The height value to set.
     */
    auto setHeight(int height) noexcept -> void;

private:
    int mWidth;  /**< The width value. */
    int mHeight; /**< The height value. */
};

#endif
