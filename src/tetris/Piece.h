#pragma once

#include <vector>

#include "GRectangle.h"
#include "Drawable.h"

class Piece
    : Drawable
{
    public:
        Piece() = default;
        Piece(std::vector<core::GRectangle>& rects);

        void addRectangle(const core::GRectangle& rect);
        void draw(const GraphicsManager* graphics) const override;
        void move(int dx, int dy);
    private:
        std::vector<core::GRectangle> body;
};