#include "sdl_renderer.hpp"
#include <iostream>

SDLRenderer::SDLRenderer(int width, int height, int tileSize)
    : SCREEN_WIDTH(width), SCREEN_HEIGHT(height), TILE_SIZE(tileSize) {
    ROWS = SCREEN_HEIGHT / TILE_SIZE;
    COLS = SCREEN_WIDTH / TILE_SIZE;

    if (!initSDL()) {
        std::cerr << "Failed to initialize SDL" << std::endl;
    }
}

SDLRenderer::~SDLRenderer() {
    closeSDL();
}

bool SDLRenderer::initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    window = SDL_CreateWindow("Dungeon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void SDLRenderer::drawDungeon(const std::vector<std::string>& dungeon) {
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            SDL_Rect tile = {col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE};

            if (dungeon[row][col] == '#') {
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // Mur
            } else if (dungeon[row][col] == '.') {
                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // Sol
            } else if (dungeon[row][col] == '+') {
                SDL_SetRenderDrawColor(renderer, 150, 100, 50, 255); // Porte
            } else if (dungeon[row][col] == '@') {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Joueur
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Fond
            }
            SDL_RenderFillRect(renderer, &tile);
        }
    }
}

void SDLRenderer::render() {
    SDL_RenderPresent(renderer);
}

bool SDLRenderer::handleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            return false;
        }
    }
    return true;
}

void SDLRenderer::closeSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
