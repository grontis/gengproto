#include "Piece.h"

Piece::Piece(std::vector<core::GRectangle> &rects)
    : body(rects)
{
}

void Piece::initializeFromTemplate(const PieceTemplate &pieceTemplate, int rotationIndex, int startX, int startY, int gridSquareSize)
{
    this->pieceTemplate = pieceTemplate;
    body.clear();
    const auto& rotation = pieceTemplate.rotations[rotationIndex];

    // Add squares based on the template's rotation
    for (const auto& coord : rotation) {
        int x = startX + coord.x * gridSquareSize;
        int y = startY + coord.y * gridSquareSize;
        body.push_back(core::GRectangle(x, y, gridSquareSize, gridSquareSize, core::G_COLOR_ORANGE, 100));
    }
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

void Piece::rotate() {
    int newRotationIndex = (rotationIndex + 1 + pieceTemplate.rotations.size()) % pieceTemplate.rotations.size();
    //TODO, need to get current x and y for the template to be drawn at.
    //initializeFromTemplate(pieceTemplate, newRotationIndex, startX, startY, gridSquareSize);
    initializeFromTemplate(pieceTemplate, newRotationIndex, 975 + (61 * 3), 110, gridSquareSize);
    rotationIndex = newRotationIndex;
}