#ifndef SDL_RENDERER_HPP
#define SDL_RENDERER_HPP

#include "/opt/homebrew/Cellar/sdl2/2.30.11/include/SDL2/SDL.h"
#include <vector>
#include <string>

class SDLRenderer {
public:
    SDLRenderer(int width, int height, int tileSize);
    ~SDLRenderer();

    void drawDungeon(const std::vector<std::string>& dungeon);
    void render();
    bool handleEvents();

private:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    int TILE_SIZE;
    int ROWS;
    int COLS;

    SDL_Window* window;
    SDL_Renderer* renderer;

    bool initSDL();
    void closeSDL();
};

#endif
