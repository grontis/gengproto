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

}

int main() {
    bool isRunning = true;

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

    SDL_Event e;
    while(isRunning) {
        while ( SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT:
                    return false;
                case SDL_KEYDOWN:
                        SDL_RenderClear(renderer);
                        SDL_Rect rect;
                        rect.x = 250;
                        rect.y = 200;
                        rect.w = 100;
                        rect.h = 100;
                        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
                        SDL_RenderFillRect(renderer, &rect);
                        SDL_RenderPresent(renderer);
                default:
                    break;
            }
        }

        SDL_Delay(100);
    }

    SDL_Delay(5000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}