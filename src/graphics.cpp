#include "graphics.hpp"

Graphics::Graphics(std::string title, Uint32 fullscreenFlag,
                   unsigned int screenWidth, unsigned int screenHeight, 
                   unsigned int numRows, unsigned int numCols) 
    : title{title}, fullscreen{fullscreenFlag}, 
    screenWidth{screenWidth}, screenHeight{screenHeight}, 
    numRows{numRows}, numCols{numCols} {
    
    window = nullptr;
    renderer = nullptr;
    font = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
    } else {
        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
        SDL_SetWindowFullscreen(window, fullscreen);
        if (window == nullptr) {
            std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        } else {
            renderer = SDL_CreateRenderer(window, -1, 0);
            SDL_SetRenderDrawColor(renderer, 0, 50, 100, 255);
            if (TTF_Init() == -1) {
                std::cerr << "TTF initialization failed: " << TTF_GetError() << std::endl;
            } else {
                font = TTF_OpenFont("assets/fonts/courier.ttf", 12);
                if (font == nullptr) {
                    std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
                }
            }
        }
    }

    textDisplay = std::vector<std::vector<std::shared_ptr<Texture>>>(numRows);
    for (int i = 0; i < numRows; ++i) {
        textDisplay[i] = std::vector<std::shared_ptr<Texture>>(numCols);
        for (int j = 0; j < numCols; ++j) {
            textDisplay[i][j] = std::make_shared<Texture>(screenWidth/numCols, screenHeight/numRows);
            SDL_Color color = {255, 255, 255, 255};
            textDisplay[i][j]->loadFromText(renderer, "0", font, color);
            textDisplay[i][j]->setPosition(j*(screenWidth/numCols), i*(screenHeight/numRows));
        }
    }
}

Graphics::~Graphics() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Graphics::clear() {
    SDL_RenderClear(renderer);
}

void Graphics::render() {
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            textDisplay[i][j]->render(renderer);
        }
    }
    SDL_RenderPresent(renderer);
}
