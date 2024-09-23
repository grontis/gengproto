#pragma once

#include <vector>
#include "GRectangle.h"
#include "Drawable.h"
#include "Grid.h"

class Piece
    : Drawable
{
    public:
        Piece() = default;
        Piece(std::vector<core::GRectangle>& rects);

        void addRectangle(const core::GRectangle& rect);
        void draw(const GraphicsManager* graphics) const override;
        void move(int dx, int dy, const Grid& grid);
    private:
        std::vector<core::GRectangle> body;

        int padding = 40;
        int screenWidth = 2560;
        int screenHeight = 1440;
        int gridSquareSize = (screenHeight - 2 * padding) / 22;
};