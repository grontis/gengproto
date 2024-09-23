#include "Grid.h"

Grid::Grid()
{
    // TODO set dynamically
    padding = 40;
    screenWidth = 2560;
    screenHeight = 1440;

    gridSquareSize = (screenHeight - 2 * padding) / 22;

    gridWidth = 10 * gridSquareSize;
    gridHeight = 20 * gridSquareSize;

    gridX = (screenWidth - gridWidth) / 2;   // Center horizontally
    gridY = (screenHeight - gridHeight) / 2; // Center vertically
}

int  Grid::getGridX() const { return gridX; }
int  Grid::getGridY() const { return gridY; }
int  Grid::getGridWidth() const { return gridWidth; }
int  Grid::getGridHeight() const { return gridHeight; }

void Grid::draw(const GraphicsManager *graphics) const
{
    drawVerticalLines(graphics);
    drawHorizontalLines(graphics);
}

void Grid::drawVerticalLines(const GraphicsManager *graphics) const
{
    for (int i = 0; i <= 10; ++i)
    {
        int x = gridX + i * gridSquareSize;
        graphics->drawLine(x, gridY, x, gridY + gridHeight);
    }
}

void Grid::drawHorizontalLines(const GraphicsManager *graphics) const
{
    for (int i = 0; i <= 20; ++i)
    {
        int y = gridY + i * gridSquareSize;
        graphics->drawLine(gridX, y, gridX + gridWidth, y);
    }
}
