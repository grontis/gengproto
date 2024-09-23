#pragma once
#include <unordered_map>

#include <SDL2/SDL.h>
#include "Drawable.h"
#include "Coordinate.h"

class Grid
    : Drawable
{
public:
    Grid();

    int getGridX() const;
    int getGridY() const;
    int getGridWidth() const;
    int getGridHeight() const;

    void draw(const GraphicsManager *graphics) const override;

private:
    int padding;
    int gridSquareSize;
    int gridX, gridY;
    int gridWidth, gridHeight;
    int screenWidth, screenHeight;

    void drawVerticalLines(const GraphicsManager *graphics) const;
    void drawHorizontalLines(const GraphicsManager *graphics) const;
};
