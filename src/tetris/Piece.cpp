#include "Piece.h"

namespace tetris
{
    Piece::Piece(std::vector<core::GRectangle> &rects)
        : _body(rects)
    {
    }

    void Piece::initializeFromTemplate(const PieceTemplate &pieceTemplate, int rotationIndex, int startX, int startY, int gridSquareSize)
    {
        _pieceTemplate = pieceTemplate;
        _body.clear();
        const auto &rotation = pieceTemplate.rotations[rotationIndex];

        for (const auto &coord : rotation)
        {
            int x = startX + coord.x * gridSquareSize;
            int y = startY + coord.y * gridSquareSize;
            _body.push_back(core::GRectangle(x, y, gridSquareSize, gridSquareSize, core::G_COLOR_ORANGE, 100));
        }
    }

    void Piece::addRectangle(const core::GRectangle &rect)
    {
        _body.push_back(rect);
    }

    void Piece::draw(const core::GraphicsManager *graphics) const
    {
        for (auto &rect : _body)
        {
            graphics->draw(rect);
        }
    }

    void Piece::move(int dx, int dy, const Grid &grid)
    {
        int gridLeft = grid.getGridX();
        int gridRight = grid.getGridX() + grid.getGridWidth();
        int gridTop = grid.getGridY();
        int gridBottom = grid.getGridY() + grid.getGridHeight();

        for (const auto &part : _body)
        {
            int newX = part.rect.x + dx;
            int newY = part.rect.y + dy;

            if (newX < gridLeft || newX + part.rect.w > gridRight || newY < gridTop || newY + part.rect.h > gridBottom)
            {
                return;
            }
        }

        for (auto &part : _body)
        {
            part.rect.x += dx;
            part.rect.y += dy;
        }

        _currentX += dx;
        _currentY += dy;
    }

    void Piece::rotate()
    {
        int newRotationIndex = (_rotationIndex + 1 + _pieceTemplate.rotations.size()) % _pieceTemplate.rotations.size();
        initializeFromTemplate(_pieceTemplate, newRotationIndex, _currentX, _currentY, _gridSquareSize);
        _rotationIndex = newRotationIndex;
    }
}
