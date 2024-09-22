#include "Piece.h"

Piece::Piece(std::vector<core::GRectangle> &rects)
    : body(rects)
{
}

void Piece::addRectangle(const core::GRectangle& rect) 
{
    body.push_back(rect);
}

void Piece::draw(const GraphicsManager *graphics) const
{
    for (auto rect : body)
    {
        graphics->draw(rect);
    }
    // TODO each piece can be collection of rectangles, then draw for each
    // graphics->draw(body);
}