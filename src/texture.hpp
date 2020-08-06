#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <string>
#include <iostream>

struct Buffer {
    char ch;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
};

class Texture {
    SDL_Texture* texture;
    SDL_Rect srcRect;
    SDL_Rect destRect;
    SDL_Color textColor;
public:
    Texture(unsigned int width, unsigned int height);
    ~Texture();

    void setPosition(int x, int y);

    bool loadFromText(SDL_Renderer* renderer, std::string text, TTF_Font* font);

    void free();
    void setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
    void setBlendMode(SDL_BlendMode blending);
    void render(SDL_Renderer* renderer);
};

#endif
