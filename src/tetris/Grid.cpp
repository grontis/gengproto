#include "Grid.h"

Grid::Grid(int w, int h, float cellWidth, float cellHeight, float screenWidth, float screenHeight, core::G_COLOR c)
{
        width = w;
        height = h;
        float cellSize = std::min(cellWidth, cellHeight);
        float totalWidth = cellSize * width;
        float totalHeight = cellSize * width;

        float offsetX = (screenWidth - totalWidth) / 2;
        float offsetY = (screenHeight - totalHeight) / 2;
}