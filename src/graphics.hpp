#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "texture.hpp"
#include <vector>
#include <string>
#include <memory>

class Graphics {
    std::string title;
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    Uint32 fullscreen;
    unsigned int screenWidth;
    unsigned int screenHeight;
    unsigned int numRows;
    unsigned int numCols;
    std::vector<std::vector<Buffer>> preBuffer;
    std::vector<std::vector<std::shared_ptr<Texture>>> textDisplay;

public:
    Graphics(std::string title, Uint32 fullscreenFlag, 
             unsigned int screenWidth, unsigned int screenHeight,
             unsigned int numRows, unsigned int numCols);
    ~Graphics();

    void setCh(char ch, unsigned int x, unsigned int y);
    void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a, int x, int y);

    void clear();
    void render();
};

#endif
