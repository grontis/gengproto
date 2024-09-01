#include "Game.h"

Game::Game()
    : engine(rd())
{
    //TODO refactor use of renderer out of this class so that it is encapsulated in SDLManager
    renderer = sdlManager.getRenderer();
    if (!renderer) {
        throw std::runtime_error("Renderer initialization failed.");
    }

    rectSpawnDist = std::uniform_int_distribution<int>(0, 3);
    xDist = std::uniform_int_distribution<int>(100, windowWidth - 100);
    yDist = std::uniform_int_distribution<int>(100, windowHeight - 100);

    mainEntity = std::make_unique<Entity>(100, 100, 100, 100, SDL_Color{0, 255, 0, 255});
}

void Game::run() {
    lastTime = SDL_GetTicks();

    while (!quit) {
        handleEvents();
        update();
        render();
        auto foo = SDL_GetError();
        SDL_Delay(16);
    }
}

//TODO refactor SDL events here to SDL manager
void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quit = true;
        }
    }
}

void Game::update() {
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

    if (spawnWaitCount >= spawnWaitLimit) {
        spawnEntities();
        spawnWaitCount = 0;
    } else {
        spawnWaitCount++;
    }

    handleEntityInteractions();   
}

void Game::render() const {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);

    mainEntity->render(renderer);

    for (const auto& pair : entities) {
        pair.second.render(renderer);
    }

    SDL_RenderPresent(renderer);
}

void Game::spawnEntities() {
    int rectsToSpawn = rectSpawnDist(engine);
    for (int i = 0; i < rectsToSpawn; ++i) {
        int x = xDist(engine);
        int y = yDist(engine);
        Coordinate coord = {x, y};

        if (!isWithinRange(coord, Coordinate{mainEntity->rect.x, mainEntity->rect.y}, mainEntity->rect.w, mainEntity->rect.h)) {
            entities.emplace(coord, Entity(x, y, 25, 25, SDL_Color{255, 0, 255, 255}));
        }
    }
}

void Game::handleEntityInteractions() {
    std::vector<Coordinate> toRemove;
    for (auto& pair : entities) {
        if (isWithinRange(pair.first, Coordinate{mainEntity->rect.x, mainEntity->rect.y}, mainEntity->rect.w, mainEntity->rect.h)) {
            toRemove.push_back(pair.first);

            movementSpeed += 25;
            mainEntity->rect.w += 5;
            mainEntity->rect.h += 5;
        }
    }

    for (const auto& coord : toRemove) {
        entities.erase(coord);
    }
}

bool Game::isWithinRange(const Coordinate& coord, const Coordinate& center, int width, int height) const {
    return coord.x >= center.x && coord.x <= center.x + width &&
           coord.y >= center.y && coord.y <= center.y + height;
}