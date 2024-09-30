#include "Tetris.h"

namespace tetris
{
    Tetris::Tetris()
        : _rng(), _graphics("gengproto", 2560, 1440)
    {
        initializePieceTemplates();
        _grid = std::make_unique<Grid>();
        _currentPiece = std::make_unique<Piece>();

        const auto &pieceTemplate = pieceTemplates[getRandomPieceTemplate()];
        _currentPiece->initializeFromTemplate(pieceTemplate, 0, _gridX + (_gridSquareSize * 3), _gridY, _gridSquareSize);

        setupEventHandlers();
    }

    void Tetris::run()
    {
        _lastTime = _graphics.getTicks();

        while (!_quit)
        {
            update();
            render();
            _graphics.delay(16);
        }
    }

    void Tetris::setupEventHandlers()
    {
        _eventManager.registerKeyAction(SDL_SCANCODE_W, core::KEY_EVENT_TYPE::KEYDOWN, [this]()
                                        { 
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - _lastMoveTimes[CONTROLS_ROTATE] > _rotationCooldown) {
                _currentPiece->rotate(*_grid);
                _lastMoveTimes[CONTROLS_ROTATE] = currentTime;
            } });

        _eventManager.registerKeyAction(SDL_SCANCODE_A, core::KEY_EVENT_TYPE::KEYHELD, [this]()
                                        {
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - _lastMoveTimes[CONTROLS_X] > _movementCooldown) {
                _currentPiece->move(-_gridSquareSize, 0, *_grid);
                _lastMoveTimes[CONTROLS_X] = currentTime;
            } });

        _eventManager.registerKeyAction(SDL_SCANCODE_D, core::KEY_EVENT_TYPE::KEYHELD, [this]()
                                        {
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - _lastMoveTimes[CONTROLS_X] > _movementCooldown) {
                _currentPiece->move(_gridSquareSize, 0, *_grid);
                _lastMoveTimes[CONTROLS_X] = currentTime;
            } });

        _eventManager.registerKeyAction(SDL_SCANCODE_S, core::KEY_EVENT_TYPE::KEYHELD, [this]()
                                        {
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - _lastMoveTimes[CONTROLS_Y] > _movementCooldown) {
                _currentPiece->move(0, _gridSquareSize, *_grid);
                _lastMoveTimes[CONTROLS_Y] = currentTime;
            } });

        _eventManager.registerQuitAction([this]()
                                         { _quit = true; });
    }

    // TODO any way to further abstract away the need to start/end a render frame once here at the game level?
    void Tetris::render() const
    {
        _graphics.startFrame(core::G_COLOR_BLACK, 255);
        _grid->draw(&_graphics);
        _currentPiece->draw(&_graphics);
        _graphics.render();
    }

    void Tetris::update()
    {
        _eventManager.handleEvents();
    }
}
