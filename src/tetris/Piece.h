#pragma once

#include <vector>

#include "GRectangle.h"
#include "Drawable.h"
#include "Grid.h"
#include "PieceTemplates.h"

namespace tetris
{
    class Piece
        : core::Drawable
    {
    public:
        Piece() = default;
        Piece(std::vector<core::GRectangle> &rects);

        void initializeFromTemplate(const PieceTemplate &pieceTemplate, int rotationIndex, int startX, int startY, int gridSquareSize);
        void addRectangle(const core::GRectangle &rect);
        void draw(const core::GraphicsManager *graphics) const override;
        void move(int dx, int dy, const Grid &grid);
        void rotate();

    private:
        std::vector<core::GRectangle> _body;
        PieceTemplate _pieceTemplate;
        int _padding = 40;
        int _screenWidth = 2560;
        int _screenHeight = 1440;
        int _gridSquareSize = (_screenHeight - 2 * _padding) / 22;
        int _rotationIndex = 0;
        int _currentX = 975 + (61 * 3);
        int _currentY = 110;
    };
}
