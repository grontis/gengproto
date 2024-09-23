#include "Tetris.h"

Tetris::Tetris()
    : rng(), graphics("gengproto", 2560, 1440)
{
    grid = std::make_unique<Grid>();
    currentPiece = std::make_unique<Piece>();

    //TODO define objects that represent templates for tetris shapes. 
        // Rectangles to construct, color
        //put in a map and then randomly select

    currentPiece->addRectangle(core::GRectangle(gridX + (gridSquareSize * 3), gridY, gridSquareSize, gridSquareSize, core::G_COLOR_ORANGE, 100));
    currentPiece->addRectangle(core::GRectangle(gridX + (gridSquareSize * 2), gridY, gridSquareSize, gridSquareSize, core::G_COLOR_ORANGE, 100));
    currentPiece->addRectangle(core::GRectangle(gridX + (gridSquareSize * 4), gridY, gridSquareSize, gridSquareSize, core::G_COLOR_ORANGE, 100));
    currentPiece->addRectangle(core::GRectangle(gridX + (gridSquareSize * 4), gridY + gridSquareSize, gridSquareSize, gridSquareSize, core::G_COLOR_ORANGE, 100));


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

Uint32 lastMoveTime = 0;   // Store the last time the piece moved
Uint32 moveInterval = 150; // Move every 150 milliseconds

void Tetris::setupEventHandlers()
{
    
    eventManager.registerKeyAction(SDL_SCANCODE_S, [this]()
                                   {
                                       Uint32 currentTime = SDL_GetTicks();
                                       if (currentTime - lastMoveTime > moveInterval) {
                                           currentPiece->move(0, gridSquareSize, *grid);
                                           lastMoveTime = currentTime;
                                       }
                                   });

    eventManager.registerKeyAction(SDL_SCANCODE_A, [this]()
                                   {
                                       Uint32 currentTime = SDL_GetTicks();
                                       if (currentTime - lastMoveTime > moveInterval) {
                                           currentPiece->move(-gridSquareSize, 0, *grid);
                                           lastMoveTime = currentTime;
                                       }
                                   });

    eventManager.registerKeyAction(SDL_SCANCODE_D, [this]()
                                   {
                                       Uint32 currentTime = SDL_GetTicks();
                                       if (currentTime - lastMoveTime > moveInterval) {
                                           currentPiece->move(gridSquareSize, 0, *grid);
                                           lastMoveTime = currentTime;
                                       }
                                   });

    eventManager.registerQuitAction([this]()
                                    { quit = true; });
}

// TODO any way to further abstract away the need to start/end a render frame once here at the game level?
void Tetris::render() const
{
    graphics.startFrame(core::G_COLOR_BLACK, 255);
    grid->draw(&graphics);
    currentPiece->draw(&graphics);
    graphics.render();
}

void Tetris::update()
{
    //TODO refactor this time management into a core geng class
    Uint32 currentTime = graphics.getTicks();
    deltaTime = (currentTime - lastTime) / 1000.0f; // Convert to seconds
    lastTime = currentTime;

    eventManager.handleEvents();
}
