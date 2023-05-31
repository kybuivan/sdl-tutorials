/*
 * Snake game program using the SDL library
 *
 * @author J. Alvarez
 */
#include "Drawable.hpp"
#include "Screen.hpp"
#include <SDL.h>

#ifndef COLLIDEABLE_HPP
#define COLLIDEABLE_HPP

/**
 * This class represents an object that can collide with others
 * The most basic collision is implemented: objects have same size, so if they
 * are in the same position a collision is assumed
 */
struct Collideable : Drawable
{
    /**
	 * Creates an Collideable instance with a position
	 * @param x X position of this object
	 * @param y Y position of this object
	 */
    Collideable(int x, int y);

    /**
	 * Validates whether there is a collision between this object and another
	 * @param other The other object to check whether collision occurs
	 * @return boolean indicating whether collision occurs
	 */
    bool collidesWith(Collideable &other);
};

#endif // COLLIDEABLE_HPP
