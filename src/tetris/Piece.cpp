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

void Piece::move(int dx, int dy, const Grid& grid)
{
    int gridLeft = grid.getGridX();
    int gridRight = grid.getGridX() + grid.getGridWidth();
    int gridTop = grid.getGridY();
    int gridBottom = grid.getGridY() + grid.getGridHeight();

    for (const auto& part : body) {
        int newX = part.rect.x + dx;
        int newY = part.rect.y + dy;

        if (newX < gridLeft || newX + part.rect.w > gridRight || newY < gridTop || newY + part.rect.h > gridBottom) {
            return;
        }
    }

    for (auto& part : body)
    {
        part.rect.x += dx;
        part.rect.y += dy;
    }
}