#include "texture.h"

#include <SDL_image.h>
#include <string>

Texture::Texture(std::string name, SDL_Texture *texture)
    : name(name), texture(texture)
{
}
