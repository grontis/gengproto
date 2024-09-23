#include "PieceTemplates.h"

//TODO Tetris namespace
std::unordered_map<std::string, PieceTemplate> pieceTemplates;

void initializePieceTemplates() {
    pieceTemplates["T"] = {
        {
            {
                {0, 0}, {1, 0}, {2, 0}, {1, 1}
            },
            {
                {1, 0}, {1, 1}, {1, 2}, {2, 1}
            },
            {
                {1, 1}, {0, 1}, {2, 1}, {1, 0}
            },
            {
                {1, 0}, {1, 1}, {1, 2}, {0, 1}
            }
        }
    };

    pieceTemplates["O"] = {
        {
            // Only one rotation for a square piece
            {
                {0, 0}, {1, 0}, {0, 1}, {1, 1}
            }
        }
    };

    // TODO Add more pieces like L, I, S, Z, etc.
}
