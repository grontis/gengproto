#include "PieceTemplates.h"

namespace tetris
{
    std::unordered_map<PIECE_TEMPLATE, PieceTemplate> pieceTemplates;

    void initializePieceTemplates()
    {
        pieceTemplates[PIECE_TEMPLATE_T] = {
            {{{0, 0}, {1, 0}, {2, 0}, {1, 1}},
             {{1, 0}, {1, 1}, {1, 2}, {2, 1}},
             {{1, 1}, {0, 1}, {2, 1}, {1, 0}},
             {{1, 0}, {1, 1}, {1, 2}, {0, 1}}}};

        pieceTemplates[PIECE_TEMPLATE_O] = {
            {{{0, 0}, {1, 0}, {0, 1}, {1, 1}}}};

        pieceTemplates[PIECE_TEMPLATE_I] = {
            {{{0, 1}, {1, 1}, {2, 1}, {3, 1}},
             {{1, 0}, {1, 1}, {1, 2}, {1, 3}}}};

        pieceTemplates[PIECE_TEMPLATE_L] = {
            {{{1, 0}, {1, 1}, {1, 2}, {2, 2}},
             {{0, 1}, {1, 1}, {2, 1}, {0, 2}},
             {{1, 0}, {2, 0}, {1, 1}, {1, 2}},
             {{0, 1}, {1, 1}, {2, 1}, {2, 0}}}};

        pieceTemplates[PIECE_TEMPLATE_J] = {
            {{{1, 0}, {1, 1}, {1, 2}, {0, 2}},
             {{0, 1}, {1, 1}, {2, 1}, {2, 2}},
             {{1, 0}, {2, 0}, {1, 1}, {1, 2}},
             {{0, 0}, {0, 1}, {1, 1}, {2, 1}}}};

        pieceTemplates[PIECE_TEMPLATE_S] = {
            {{{1, 1}, {2, 1}, {0, 2}, {1, 2}},
             {{1, 0}, {1, 1}, {2, 1}, {2, 2}}}};

        pieceTemplates[PIECE_TEMPLATE_Z] = {
            {{{0, 1}, {1, 1}, {1, 2}, {2, 2}},
             {{2, 0}, {1, 1}, {2, 1}, {1, 2}}}};
    }

    PIECE_TEMPLATE getRandomPieceTemplate()
    {
        core::RandomGenerator rng = core::RandomGenerator();
        return static_cast<PIECE_TEMPLATE>(rng.generateUniformInt(PIECE_TEMPLATE_T, PIECE_TEMPLATE_Z));
    }
}
