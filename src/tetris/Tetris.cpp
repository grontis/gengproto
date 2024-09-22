#include "Tetris.h"
#include "Grid.h"

Tetris::Tetris()
    : rng(), graphics("gengproto", 2560, 1440)
{
    currentPiece = std::make_unique<Piece>();
    currentPiece->addRectangle(core::GRectangle(500, 500, 200, 50, core::G_COLOR_ORANGE, 100));
    setupEventHandlers();
}

void Tetris::run()
{
    lastTime = graphics.getTicks();



    while (!quit)
    {
        update();
        render();
        graphics.delay(16);
    }
}

void Tetris::setupEventHandlers()
{
    //TODO define input events

    //TODO refactor/encapsulate SDL scancodes into wrapper implementation so games class dont need to touch SDL

    eventManager.registerKeyAction(SDL_SCANCODE_S, [this]()
                                   { currentPiece->move(0, static_cast<int>(movementSpeed * deltaTime)); });

    eventManager.registerKeyAction(SDL_SCANCODE_A, [this]()
                                   { currentPiece->move(-static_cast<int>(movementSpeed * deltaTime), 0); });

    eventManager.registerKeyAction(SDL_SCANCODE_D, [this]()
                                   { currentPiece->move(static_cast<int>(movementSpeed * deltaTime), 0); });

    eventManager.registerQuitAction([this]()
                                    { quit = true; });
}

void Tetris::render() const
{
    graphics.startFrame(core::G_COLOR_BLACK, 255);

    currentPiece->draw(&graphics);

    // TODO any way to further abstract away the need to start/end a render frame once here at the game level?
    graphics.render();
}

void Tetris::update()
{
    //TODO refactor this time management into a core geng class
    Uint32 currentTime = graphics.getTicks();
    deltaTime = (currentTime - lastTime) / 1000.0f; // Convert to seconds
    lastTime = currentTime;


    //Grid grid = Grid(10, 20, 100, 100, 2560, 1440, core::G_COLOR_DARK_GRAY);



    eventManager.handleEvents();
}
