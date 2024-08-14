#include <iostream>
#include <vector>

#include <SDL2/SDL.h>

class GVector {
private:
    std::vector<int> vector;
public:
    GVector(int x, int y);
    GVector(int x, int y, int z);
    ~GVector();
    void Draw();
    int Magnitude();
};

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("gengproto", 100, 100, 1024, 860, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        SDL_DestroyWindow(window);
        std::cerr << "SDL_CreaterRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Rect mainRect;
    mainRect.x = 100;
    mainRect.y = 100;
    mainRect.w = 50;
    mainRect.h = 50;

    std::vector<SDL_Rect> rectangles;

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                        mainRect.y -= 10;
                        break;
                    case SDLK_s:
                        mainRect.y += 10;
                        break;
                    case SDLK_a:
                        mainRect.x -= 10;
                        break;
                    case SDLK_d:
                        mainRect.x += 10;
                        break;
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    SDL_Rect newRect;
                    newRect.x = x;
                    newRect.y = y;
                    newRect.w = 10;
                    newRect.h = 10;

                    rectangles.push_back(newRect);
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &mainRect);

        for (const auto &rect : rectangles) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
            SDL_RenderFillRect(renderer, &rect);
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}