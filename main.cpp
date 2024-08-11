#include <iostream>
#include <vector>

#include <SDL2/SDL.h>

class GVector2D {
private:
    std::vector<int> vector;
public:
    GVector2D(int x, int y);
    ~GVector2D();
    void Draw();
    int Magnitude();
};

int SDLHelloWorld() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("gengproto", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        SDL_DestroyWindow(window);
        std::cerr << "SDL_CreaterRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect rect;
    rect.x = 200;
    rect.y = 150;
    rect.w = 200;
    rect.h = 100;

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
    SDL_Delay(5000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}

int main() {
    //TODO world space
        //2D grid space first
        //2D library that was used in tetris example engine
        //Then 3D next


    //TODO vector stuff
        //Vector class
        //Store vectors
        //Modify/compute vectors
        //Draw vectors


    int result = SDLHelloWorld();
    return result;

    //return 0;
}