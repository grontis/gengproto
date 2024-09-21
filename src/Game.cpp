#include "Game.h"

Game::Game()
    : rng(), graphics("gengproto", 2560, 1440)
{
    setupEventHandlers();
    mainEntity = std::make_unique<Entity>(core::GRectangle(100, 100, 100, 100, core::G_COLOR_YELLOW, 255));
}

void Game::run()
{
    lastTime = graphics.getTicks();

    while (!quit)
    {
        update();
        render();
        graphics.delay(16);
    }
}

void Game::setupEventHandlers()
{
    // TODO refactor/encapsulate SDL scancodes into wrapper implementation so games class dont need to touch SDL
    eventManager.registerKeyAction(SDL_SCANCODE_W, [this]()
                                   { mainEntity->move(0, -static_cast<int>(movementSpeed * deltaTime)); });

    eventManager.registerKeyAction(SDL_SCANCODE_S, [this]()
                                   { mainEntity->move(0, static_cast<int>(movementSpeed * deltaTime)); });

    eventManager.registerKeyAction(SDL_SCANCODE_A, [this]()
                                   { mainEntity->move(-static_cast<int>(movementSpeed * deltaTime), 0); });

    eventManager.registerKeyAction(SDL_SCANCODE_D, [this]()
                                   { mainEntity->move(static_cast<int>(movementSpeed * deltaTime), 0); });

    eventManager.registerQuitAction([this]()
                                    { quit = true; });
}

void Game::update()
{
    Uint32 currentTime = graphics.getTicks();
    deltaTime = (currentTime - lastTime) / 1000.0f; // Convert to seconds
    lastTime = currentTime;

    eventManager.handleEvents();
    spawn();
    handleEntityInteractions();
}

void Game::render() const
{
    graphics.startFrame(core::G_COLOR_DARK_GRAY, 255);

    graphics.draw(mainEntity->body);
    for (const auto &pair : entitiesMap)
    {
        graphics.draw(pair.second.body);
    }

    // TODO any way to further abstract away the need to start/end a render frame once here at the game level?
    graphics.render();
}

void Game::spawn()
{
    if (spawnWaitCount >= spawnWaitLimit)
    {
        spawnEntities();
        spawnWaitCount = 0;
    }
    else
    {
        spawnWaitCount++;
    }
}

void Game::spawnEntities()
{
    int rectsToSpawn = rng.generateUniformInt(0, 3);
    for (int i = 0; i < rectsToSpawn; ++i)
    {
        int x = rng.generateUniformInt(100, graphics.getWindowWidth() - 100);
        int y = rng.generateUniformInt(100, graphics.getWindowHeight() - 100);
        Coordinate coord = {x, y};

        if (!isWithinRange(coord, Coordinate{mainEntity->body.rect.x, mainEntity->body.rect.y}, mainEntity->body.rect.w, mainEntity->body.rect.h))
        {
            entitiesMap.emplace(coord, Entity(core::GRectangle(x, y, 25, 25, core::G_COLOR_PURPLE, 255)));
        }
    }
}

void Game::handleEntityInteractions()
{
    std::vector<Coordinate> toRemove;
    for (auto &pair : entitiesMap)
    {
        if (isWithinRange(pair.first, Coordinate{mainEntity->body.rect.x, mainEntity->body.rect.y}, mainEntity->body.rect.w, mainEntity->body.rect.h))
        {
            toRemove.push_back(pair.first);

            movementSpeed += 25;
            mainEntity->body.rect.w += 5;
            mainEntity->body.rect.h += 5;
        }
    }

    for (const auto &coord : toRemove)
    {
        entitiesMap.erase(coord);
    }
}

bool Game::isWithinRange(const Coordinate &coord, const Coordinate &center, int width, int height) const
{
    return coord.x >= center.x && coord.x <= center.x + width &&
           coord.y >= center.y && coord.y <= center.y + height;
}