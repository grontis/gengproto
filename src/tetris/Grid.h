#pragma once

#include "Colors.h"

class Grid
{
    public:
        Grid(int w, int h, float cellWidth, float cellHeight, float screenWidth, float screenHeight, core::G_COLOR c);
        
    private:
        int width;
        int height;
        float cellWidth;// = screenWidth / gridWidth;
        float cellHeight;// = screenHeight / gridHeight;
        float cellSize;// = std::min(cellWidth, cellHeight);
        float totalWidth = cellSize * width;
        float totalHeight = cellSize * width;

        float offsetX;// = (screenWidth - gridTotalWidth) / 2;
        float offsetY;// = (screenHeight - gridTotalHeight) / 2;

        core::G_COLOR color;
};