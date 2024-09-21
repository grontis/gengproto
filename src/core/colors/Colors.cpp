#include "Colors.h"

namespace core
{
    std::map<G_COLOR, std::tuple<Uint8, Uint8, Uint8>> Colors::colorsMap;

    void Colors::initColorsMap()
    {
        if (colorsMap.empty())
        {
            colorsMap[G_COLOR_BLUE] = {0, 0, 255};
            colorsMap[G_COLOR_GREEN] = {0, 255, 0};
            colorsMap[G_COLOR_PURPLE] = {255, 0, 255};
        }
    }

    std::tuple<Uint8, Uint8, Uint8> Colors::getColor(G_COLOR color)
    {
        initColorsMap();
        return colorsMap[color];
    }

} // namespace core
