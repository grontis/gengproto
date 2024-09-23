#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include "Coordinate.h"

struct PieceTemplate {
    std::vector<std::vector<Coordinate>> rotations;
};

extern std::unordered_map<std::string, PieceTemplate> pieceTemplates;

void initializePieceTemplates();
