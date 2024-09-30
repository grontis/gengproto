#pragma once
#include <unordered_map>

#include <SDL2/SDL.h>

#include "Drawable.h"
#include "Coordinate.h"

namespace tetris
{
    class Grid
        : core::Drawable
    {
    public:
        Grid();

        int getGridX() const;
        int getGridY() const;
        int getGridWidth() const;
        int getGridHeight() const;

        void draw(const core::GraphicsManager *graphics) const override;

    private:
        int _padding;
        int _gridSquareSize;
        int _gridX, _gridY;
        int _gridWidth, _gridHeight;
        int _screenWidth, _screenHeight;

        void drawVerticalLines(const core::GraphicsManager *graphics) const;
        void drawHorizontalLines(const core::GraphicsManager *graphics) const;
    };
}
