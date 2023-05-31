#ifndef _texture
#define _texture

#include <SDL_image.h>
#include <string>

struct Texture
{
    std::string name = " ";
    SDL_Texture *texture = nullptr;
    Texture(std::string name, SDL_Texture *texture);
};

#endif
