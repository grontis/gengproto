#include "Game.h"

//TODO refactor all SDL related code out of here other than the SDLManager. Encapsulate everything into that
Game::Game()
    : engine(rd())
{
    rectSpawnDist = std::uniform_int_distribution<int>(0, 3);
    xDist = std::uniform_int_distribution<int>(100, sdlManager.getWindowWidth() - 100);
    yDist = std::uniform_int_distribution<int>(100, sdlManager.getWindowHeight() - 100);

    mainEntity = std::make_unique<Entity>(GRectangle(100, 100, 100, 100, SDL_Color{0, 255, 0, 255}));
}

void Game::run() {
    lastTime = sdlManager.getTicks();

    while (!quit) {
        handleEvents();
        update();
        render();
        sdlManager.delay(16);
    }
}

//TODO refactor SDL events here to SDL manager (or perhaps an event/input handler)
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
    //TODO refactor and implement color constants to support better readability
        //ex: sdlManager.clearScreen(GColor_BLUE, 255);
    sdlManager.clearScreen(0, 0, 255, 255);

    //TODO refactor drawRect to only need to pass in entity
        //ex: sdlManager.drawEntity(mainEntity)
        //then the rect/color data is encapsulated inside of draw method.
    sdlManager.drawRect(mainEntity->body.rect, mainEntity->body.color.r, mainEntity->body.color.g, mainEntity->body.color.b, mainEntity->body.color.a);

    for (const auto& pair : entitiesMap) {
        sdlManager.drawRect(pair.second.body.rect, pair.second.body.color.r, pair.second.body.color.g, pair.second.body.color.b, pair.second.body.color.a);
    }

    sdlManager.presentRenderer();
}

void Game::spawnEntities() {
    int rectsToSpawn = rectSpawnDist(engine);
    for (int i = 0; i < rectsToSpawn; ++i) {
        int x = xDist(engine);
        int y = yDist(engine);
        Coordinate coord = {x, y};

        if (!isWithinRange(coord, Coordinate{mainEntity->body.rect.x, mainEntity->body.rect.y}, mainEntity->body.rect.w, mainEntity->body.rect.h)) {
            entitiesMap.emplace(coord, Entity(GRectangle(x, y, 25, 25, SDL_Color{255, 0, 255, 255})));
        }
    }
}

void Game::handleEntityInteractions() {
    std::vector<Coordinate> toRemove;
    for (auto& pair : entitiesMap) {
        if (isWithinRange(pair.first, Coordinate{mainEntity->body.rect.x, mainEntity->body.rect.y}, mainEntity->body.rect.w, mainEntity->body.rect.h)) {
            toRemove.push_back(pair.first);

            movementSpeed += 25;
            mainEntity->body.rect.w += 5;
            mainEntity->body.rect.h += 5;
        }
    }

    for (const auto& coord : toRemove) {
        entitiesMap.erase(coord);
    }
}

bool Game::isWithinRange(const Coordinate& coord, const Coordinate& center, int width, int height) const {
    return coord.x >= center.x && coord.x <= center.x + width &&
           coord.y >= center.y && coord.y <= center.y + height;
}