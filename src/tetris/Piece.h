#pragma once

#include <vector>
#include "GRectangle.h"
#include "Drawable.h"
#include "Grid.h"
#include "PieceTemplates.h"

class Piece
    : Drawable
{
    public:
        Piece() = default;
        Piece(std::vector<core::GRectangle>& rects);
        void initializeFromTemplate(const PieceTemplate& pieceTemplate, int rotationIndex, int startX, int startY, int gridSquareSize);

        void addRectangle(const core::GRectangle& rect);
        void draw(const GraphicsManager* graphics) const override;
        void move(int dx, int dy, const Grid& grid);
        void rotate();
    private:
        std::vector<core::GRectangle> body;

        PieceTemplate pieceTemplate;

        int padding = 40;
        int screenWidth = 2560;
        int screenHeight = 1440;
        int gridSquareSize = (screenHeight - 2 * padding) / 22;
        int rotationIndex = 0;
};