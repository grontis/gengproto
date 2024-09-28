#pragma once
#include <unordered_map>
#include <vector>
#include <string>

#include "Coordinate.h"
#include "RandomGenerator.h"


// TODO Tetris namespace
struct PieceTemplate
{
    std::vector<std::vector<Coordinate>> rotations;
};

typedef enum
{
    PIECE_TEMPLATE_T,
    PIECE_TEMPLATE_O,
    PIECE_TEMPLATE_I,
    PIECE_TEMPLATE_L,
    PIECE_TEMPLATE_J,
    PIECE_TEMPLATE_S,
    PIECE_TEMPLATE_Z
} PIECE_TEMPLATE;

extern std::unordered_map<PIECE_TEMPLATE, PieceTemplate> pieceTemplates;

void initializePieceTemplates();
PIECE_TEMPLATE getRandomPieceTemplate();
