#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <string>
#include <iostream>

class Texture {
    SDL_Texture* texture;
    SDL_Rect srcRect;
    SDL_Rect destRect;
public:
    Texture(unsigned int width, unsigned int height);
    ~Texture();

    void setPosition(int x, int y);

    bool loadFromText(SDL_Renderer* renderer, std::string text, TTF_Font* font, SDL_Color textColor);

    void free();
    void setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
    void setBlendMode(SDL_BlendMode blending);
    void render(SDL_Renderer* renderer);
};

#endif
