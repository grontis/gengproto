#include "Colors.h"

namespace core
{
    std::map<G_COLOR, std::tuple<Uint8, Uint8, Uint8>> Colors::colorsMap;

    void Colors::initColorsMap()
    {
        if (colorsMap.empty())
        {
            colorsMap[G_COLOR_RED] = {255, 0, 0};
            colorsMap[G_COLOR_GREEN] = {0, 255, 0};
            colorsMap[G_COLOR_BLUE] = {0, 0, 255};
            colorsMap[G_COLOR_YELLOW] = {255, 255, 0};
            colorsMap[G_COLOR_CYAN] = {0, 255, 255};
            colorsMap[G_COLOR_MAGENTA] = {255, 0, 255};

            colorsMap[G_COLOR_BLACK] = {0, 0, 0};
            colorsMap[G_COLOR_WHITE] = {255, 255, 255};
            colorsMap[G_COLOR_GRAY] = {128, 128, 128};
            colorsMap[G_COLOR_LIGHT_GRAY] = {211, 211, 211};
            colorsMap[G_COLOR_DARK_GRAY] = {64, 64, 64};

            colorsMap[G_COLOR_ORANGE] = {255, 165, 0};
            colorsMap[G_COLOR_PINK] = {255, 192, 203};
            colorsMap[G_COLOR_PURPLE] = {128, 0, 128};
            colorsMap[G_COLOR_BROWN] = {165, 42, 42};

            colorsMap[G_COLOR_DARK_RED] = {139, 0, 0};
            colorsMap[G_COLOR_LIGHT_RED] = {255, 102, 102};
            colorsMap[G_COLOR_INDIAN_RED] = {205, 92, 92};
            colorsMap[G_COLOR_FIREBRICK] = {178, 34, 34};
            colorsMap[G_COLOR_CRIMSON] = {220, 20, 60};

            colorsMap[G_COLOR_DARK_GREEN] = {0, 100, 0};
            colorsMap[G_COLOR_LIGHT_GREEN] = {144, 238, 144};
            colorsMap[G_COLOR_LIME_GREEN] = {50, 205, 50};
            colorsMap[G_COLOR_FOREST_GREEN] = {34, 139, 34};
            colorsMap[G_COLOR_SEA_GREEN] = {46, 139, 87};

            colorsMap[G_COLOR_DARK_BLUE] = {0, 0, 139};
            colorsMap[G_COLOR_LIGHT_BLUE] = {173, 216, 230};
            colorsMap[G_COLOR_SKY_BLUE] = {135, 206, 235};
            colorsMap[G_COLOR_STEEL_BLUE] = {70, 130, 180};
            colorsMap[G_COLOR_NAVY_BLUE] = {0, 0, 128};

            colorsMap[G_COLOR_GOLD] = {255, 215, 0};
            colorsMap[G_COLOR_KHAKI] = {240, 230, 140};
            colorsMap[G_COLOR_PALE_GOLDENROD] = {238, 232, 170};

            colorsMap[G_COLOR_LAVENDER] = {230, 230, 250};
            colorsMap[G_COLOR_VIOLET] = {238, 130, 238};
            colorsMap[G_COLOR_ORCHID] = {218, 112, 214};

            colorsMap[G_COLOR_CORAL] = {255, 127, 80};
            colorsMap[G_COLOR_DARK_ORANGE] = {255, 140, 0};
            colorsMap[G_COLOR_SADDLE_BROWN] = {139, 69, 19};
            colorsMap[G_COLOR_CHOCOLATE] = {210, 105, 30};

            colorsMap[G_COLOR_SALMON] = {250, 128, 114};
            colorsMap[G_COLOR_TURQUOISE] = {64, 224, 208};
            colorsMap[G_COLOR_MAROON] = {128, 0, 0};
            colorsMap[G_COLOR_OLIVE] = {128, 128, 0};
            colorsMap[G_COLOR_TEAL] = {0, 128, 128};
        }
    }

    std::tuple<Uint8, Uint8, Uint8> Colors::getColor(G_COLOR color)
    {
        initColorsMap();
        return colorsMap[color];
    }

} // namespace core
