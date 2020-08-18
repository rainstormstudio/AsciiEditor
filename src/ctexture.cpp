#include "ctexture.hpp"

CTexture::CTexture(SDL_Texture* texture, unsigned int numSrcRows, unsigned int numSrcCols, 
    unsigned int tileWidth, unsigned int tileHeight, unsigned int width, unsigned int height)
    : texture{texture}, numSrcRows{numSrcRows}, numSrcCols{numSrcCols} {

    srcRect = {0, 0, static_cast<int>(tileWidth), static_cast<int>(tileHeight)};
    destRect = {0, 0, static_cast<int>(width), static_cast<int>(height)};
    
    foreColor = {255, 255, 255, 255};
    backColor = {0, 0, 0, 255};
}

CTexture::~CTexture() {
}

void CTexture::setIndex(char index) {
    srcRect.x = (index % numSrcCols) * srcRect.w;
    srcRect.y = (index / numSrcCols) * srcRect.h;
}

void CTexture::setDestPosition(int x, int y) {
    destRect.x = x;
    destRect.y = y;
}

void CTexture::setSrcPosition(int x, int y) {
    srcRect.x = x;
    srcRect.y = y;
}

void CTexture::setForeColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
    foreColor = {red, green, blue, alpha};
}

void CTexture::setBackColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
    backColor = {red, green, blue, alpha};
}

void CTexture::setBlendMode(SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(texture, blending);
}

void CTexture::render(SDL_Renderer* renderer) {
    SDL_SetTextureColorMod(texture, foreColor.r, foreColor.g, foreColor.b);
    SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, 0.0, nullptr, SDL_FLIP_NONE);
}
