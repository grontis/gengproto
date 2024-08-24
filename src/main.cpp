#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <random>

#include <SDL2/SDL.h>

struct Coordinate {
    int x;
    int y;

    bool operator==(const Coordinate& other) const {
        return x == other.x && y == other.y;
    }
};

//Custom hash function for the Coordinate data structure
namespace std {
    template <>
    struct hash<Coordinate> {
        std::size_t operator()(const Coordinate& coord) const {
            // Compute individual hash values for x and y and combine them
            return std::hash<int>()(coord.x) ^ (std::hash<int>()(coord.y) << 1);
        }
    };
}

bool isWithinRange(const Coordinate& coord, const Coordinate& center, int width, int height) {
    return coord.x >= center.x && coord.x <= center.x + width &&
        coord.y >= center.y && coord.y <= center.y + height;
}

//TODO refactor into classes and separate engine/game concerns into layers
int main(int argc, char *argv[]) {
    int windowWidth = 800;
    int windowHeight = 600;


    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("gengproto", 100, 100, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    //SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        SDL_DestroyWindow(window);
        std::cerr << "SDL_CreaterRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit(); 
        return 1;
    }

    std::unordered_map<Coordinate, SDL_Rect> xyRectMap;

    SDL_Rect mainRect;
    mainRect.x = 100;
    mainRect.y = 100;
    mainRect.w = 100;
    mainRect.h = 100;

    bool quit = false;
    SDL_Event event;

    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> rectSpawnDist(0, 3);
    std::uniform_int_distribution<int> xDist(100, windowWidth - 100);
    std::uniform_int_distribution<int> yDist(100, windowHeight - 100);
    int spawnWaitCount = 0;
    int spawnWaitLimit = 25;

    int movementSpeed = 700;

    Uint32 lastTime = SDL_GetTicks();
    Uint32 currentTime;
    float deltaTime;


    //TODO current pacman like ideas.
        //enemies come to attack player, harming and slowing down or decreasing in size
        //powerups like time warp, speeding up player but slowing down the world. or a gravity pull
        //power ups come from destroying enemies? 

    while (!quit) {
        currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f; // convert to seconds
        lastTime = currentTime;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_W]) {
            mainRect.y -= movementSpeed * deltaTime;
        }
        if (currentKeyStates[SDL_SCANCODE_S]) {
            mainRect.y += movementSpeed * deltaTime;
        }
        if (currentKeyStates[SDL_SCANCODE_A]) {
            mainRect.x -= movementSpeed * deltaTime;
        }
        if (currentKeyStates[SDL_SCANCODE_D]) {
            mainRect.x += movementSpeed * deltaTime;
        }

        if (spawnWaitCount == spawnWaitLimit) {
            int rectsToSpawn = rectSpawnDist(engine);
            for (int i = 0; i < rectsToSpawn; i++) {
                int x = xDist(engine);
                int y = yDist(engine);

                std::vector<int> coordinates = {x, y};

                SDL_Rect newRect;
                newRect.x = x;
                newRect.y = y;
                newRect.w = 25;
                newRect.h = 25;

                xyRectMap[{x, y}] = newRect;
            }
            spawnWaitCount = 0;
        }
        else {
            spawnWaitCount++;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &mainRect);

        for (auto it = xyRectMap.begin(); it != xyRectMap.end(); ) {
            if (isWithinRange(it->first, {mainRect.x, mainRect.y}, mainRect.w, mainRect.h)) {
                it = xyRectMap.erase(it);
                movementSpeed += 25;
                mainRect.w += 5;
                mainRect.h += 5;
            } else {
                SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
                SDL_RenderFillRect(renderer, &it->second);
                ++it;
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);

        std::cout << "speed: " << movementSpeed << std::endl;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}