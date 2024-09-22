#include "Piece.h"

Piece::Piece(std::vector<core::GRectangle> &rects)
    : body(rects)
{
}

void Piece::addRectangle(const core::GRectangle &rect)
{
    body.push_back(rect);
}

void Piece::draw(const GraphicsManager *graphics) const
{
    for (auto& rect : body)
    {
        graphics->draw(rect);
    }
}

void Piece::move(int dx, int dy)
{
    for (auto& part : body)
    {
        part.rect.x += dx;
        part.rect.y += dy;
    }
}