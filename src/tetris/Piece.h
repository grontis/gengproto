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
    private:
        std::vector<core::GRectangle> body;
};