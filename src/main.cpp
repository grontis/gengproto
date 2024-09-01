#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <random>
#include <memory>

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

//TODO refactor Entity struct into separate files
struct Entity {
    SDL_Rect rect;
    SDL_Color color;

    Entity(int x, int y, int w, int h, SDL_Color c)
        : color(c)
    {
        rect = {x, y, w, h};
    }

    //TODO it doesn't feel right that rendering logic is here in this struct. move elsewhere
        //put rendering in separate 
    void render(SDL_Renderer* renderer) const {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &rect);
    }

    void move(int dx, int dy) {
        rect.x += dx;
        rect.y += dy;
    }
};
///------ END Entity struct

//TODO refactor SDLManager class into separate files
class SDLManager {
public:
    SDLManager() {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
        }

        //TODO put "gengproto" into ApplicationTitle const somewhere
        window = SDL_CreateWindow("gengproto", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
        if (!window) {
            SDL_Quit();
            throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
        }

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!renderer) {
            SDL_DestroyWindow(window);
            SDL_Quit();
            throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
        }
    }

    ~SDLManager() {
        if (renderer) SDL_DestroyRenderer(renderer);
        if (window) SDL_DestroyWindow(window);
        SDL_Quit();
    }

    SDL_Renderer* getRenderer() const { return renderer; }
private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};
///////------ END SDLManager class


//TODO refactor Game class into separate files
class Game {
public:
    Game()
        : engine(rd())
    {
        rectSpawnDist = std::uniform_int_distribution<int>(0, 3);
        xDist = std::uniform_int_distribution<int>(100, windowWidth - 100);
        yDist = std::uniform_int_distribution<int>(100, windowHeight - 100);

        mainEntity = std::make_unique<Entity>(100, 100, 100, 100, SDL_Color{0, 255, 0, 255});
    }

    void run() {
        lastTime = SDL_GetTicks();

        while (!quit) {
            handleEvents();
            update();
            render();
            SDL_Delay(16);
        }
    }

private:
    //TODO refactor/encapsulate SDL stuff?
    SDLManager sdlManager;
    SDL_Renderer* renderer = sdlManager.getRenderer();

    //TODO refactor/encapsulate Entity/game object stuffs?
    std::unique_ptr<Entity> mainEntity;
    std::unordered_map<Coordinate, Entity> entities;

    //TODO refactor/encapsulate RNG stuff?
    std::random_device rd;
    std::default_random_engine engine;
    std::uniform_int_distribution<int> rectSpawnDist;
    std::uniform_int_distribution<int> xDist;
    std::uniform_int_distribution<int> yDist;
    
    
    //todo refactor/encapsulate spawn control stuff?
    int spawnWaitCount = 0;
    const int spawnWaitLimit = 25;


    int movementSpeed = 700;

    Uint32 lastTime;
    float deltaTime;

    const int windowWidth = 800;
    const int windowHeight = 600;

    bool quit = false;

    void handleEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    void update() {
        Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f; // Convert to seconds
        lastTime = currentTime;

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        int dx = 0;
        int dy = 0;

        if (currentKeyStates[SDL_SCANCODE_W]) {
            dy -= static_cast<int>(movementSpeed * deltaTime);
        }
        if (currentKeyStates[SDL_SCANCODE_S]) {
            dy += static_cast<int>(movementSpeed * deltaTime);
        }
        if (currentKeyStates[SDL_SCANCODE_A]) {
            dx -= static_cast<int>(movementSpeed * deltaTime);
        }
        if (currentKeyStates[SDL_SCANCODE_D]) {
            dx += static_cast<int>(movementSpeed * deltaTime);
        }

        mainEntity->move(dx, dy);

        // Handle spawning
        if (spawnWaitCount >= spawnWaitLimit) {
            spawnEntities();
            spawnWaitCount = 0;
        } else {
            spawnWaitCount++;
        }

        // Handle entity interactions
        handleEntityInteractions();

        // Debug: Print movement speed
        std::cout << "speed: " << movementSpeed << std::endl;    
    }

    // Render Game Entities
    void render() const {
        // Clear screen with blue color
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderClear(renderer);

        // Render main entity (green)
        mainEntity->render(renderer);

        // Render other entities (magenta)
        for (const auto& pair : entities) {
            pair.second.render(renderer);
        }

        // Present the rendered frame
        SDL_RenderPresent(renderer);
    }

    
    // Spawn New Entities
    void spawnEntities() {
        int rectsToSpawn = rectSpawnDist(engine);
        for (int i = 0; i < rectsToSpawn; ++i) {
            int x = xDist(engine);
            int y = yDist(engine);
            Coordinate coord = {x, y};

            // Avoid spawning on top of the main entity
            if (!isWithinRange(coord, Coordinate{mainEntity->rect.x, mainEntity->rect.y}, mainEntity->rect.w, mainEntity->rect.h)) {
                entities.emplace(coord, Entity(x, y, 25, 25, SDL_Color{255, 0, 255, 255}));
            }
        }
    }

    void handleEntityInteractions() {
        std::vector<Coordinate> toRemove;
        for (auto& pair : entities) {
            if (isWithinRange(pair.first, Coordinate{mainEntity->rect.x, mainEntity->rect.y}, mainEntity->rect.w, mainEntity->rect.h)) {
                toRemove.push_back(pair.first);

                // TODO refactor Increase speed and size to function
                movementSpeed += 25;
                mainEntity->rect.w += 5;
                mainEntity->rect.h += 5;
            }
        }

        for (const auto& coord : toRemove) {
            entities.erase(coord);
        }
    }

    bool isWithinRange(const Coordinate& coord, const Coordinate& center, int width, int height) const {
        return coord.x >= center.x && coord.x <= center.x + width &&
               coord.y >= center.y && coord.y <= center.y + height;
    }
};

int main(int argc, char *argv[]) {
    try {
        Game game;
        game.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}