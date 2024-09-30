#include "Tetris.h"

namespace tetris
{
    Tetris::Tetris()
        : rng(), graphics("gengproto", 2560, 1440)
    {
        initializePieceTemplates();
        grid = std::make_unique<Grid>();
        currentPiece = std::make_unique<Piece>();

        const auto &pieceTemplate = pieceTemplates[getRandomPieceTemplate()];
        currentPiece->initializeFromTemplate(pieceTemplate, 0, gridX + (gridSquareSize * 3), gridY, gridSquareSize);

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
        eventManager.registerKeyAction(SDL_SCANCODE_W, KEY_EVENT_TYPE::KEYDOWN, [this]()
                                       { 
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - lastMoveTimes[CONTROLS_ROTATE] > rotationCooldown) {
                currentPiece->rotate();
                lastMoveTimes[CONTROLS_ROTATE] = currentTime;
            } });

        eventManager.registerKeyAction(SDL_SCANCODE_A, KEY_EVENT_TYPE::KEYHELD, [this]()
                                       {
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - lastMoveTimes[CONTROLS_X] > movementCooldown) {
                currentPiece->move(-gridSquareSize, 0, *grid);
                lastMoveTimes[CONTROLS_X] = currentTime;
            } });

        eventManager.registerKeyAction(SDL_SCANCODE_D, KEY_EVENT_TYPE::KEYHELD, [this]()
                                       {
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - lastMoveTimes[CONTROLS_X] > movementCooldown) {
                currentPiece->move(gridSquareSize, 0, *grid);
                lastMoveTimes[CONTROLS_X] = currentTime;
            } });

        eventManager.registerKeyAction(SDL_SCANCODE_S, KEY_EVENT_TYPE::KEYHELD, [this]()
                                       {
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - lastMoveTimes[CONTROLS_Y] > movementCooldown) {
                currentPiece->move(0, gridSquareSize, *grid);
                lastMoveTimes[CONTROLS_Y] = currentTime;
            } });

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
        eventManager.handleEvents();
    }
}
