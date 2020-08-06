#include "texture.hpp"

Texture::Texture(unsigned int width, unsigned int height) {
    texture = nullptr;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = 0;
    srcRect.h = 0;

    destRect.x = 0;
    destRect.y = 0;
    destRect.w = width;
    destRect.h = height;

    textColor = {255, 255, 255, 255};
    backColor = {0, 0, 0, 255};
}

Texture::~Texture() {
    free();
}

void Texture::setPosition(int x, int y) {
    destRect.x = x;
    destRect.y = y;
}

bool Texture::loadFromText(SDL_Renderer* renderer, std::string text, TTF_Font* font) {
    free();
    SDL_Surface* surface = TTF_RenderText_Shaded(font, text.c_str(), textColor, backColor);
    if (surface == nullptr) {
        std::cerr << "Error rendering SDL surface: " << TTF_GetError() << std::endl;
    } else {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == nullptr) {
            std::cerr << "Error creating texture from text: " << TTF_GetError() << std::endl;
        } else {
            srcRect.w = surface->w;
            srcRect.h = surface->h;
        }
        SDL_FreeSurface(surface);
    }

    return texture != nullptr;
}

void Texture::free() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
        srcRect.w = 0;
        srcRect.h = 0;
    }
}

void Texture::setForeColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
    textColor = {red, green, blue, alpha};
}

void Texture::setBackColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
    backColor = {red, green, blue, alpha};
}

void Texture::setBlendMode(SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(texture, blending);
    SDL_SetTextureAlphaMod(texture, textColor.a);
}

void Texture::render(SDL_Renderer* renderer) {
    SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0.0, nullptr, SDL_FLIP_NONE);
}
