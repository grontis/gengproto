#pragma once

#include <map>
#include <tuple>

#include <SDL2/SDL.h>

namespace core
{
    // TODO instead of G_ prefix use a colors namespace
    typedef enum
    {
        G_COLOR_RED,
        G_COLOR_GREEN,
        G_COLOR_BLUE,
        G_COLOR_YELLOW,
        G_COLOR_CYAN,
        G_COLOR_MAGENTA,

        G_COLOR_BLACK,
        G_COLOR_WHITE,
        G_COLOR_GRAY,
        G_COLOR_LIGHT_GRAY,
        G_COLOR_DARK_GRAY,

        G_COLOR_ORANGE,
        G_COLOR_PINK,
        G_COLOR_PURPLE,
        G_COLOR_BROWN,

        G_COLOR_DARK_RED,
        G_COLOR_LIGHT_RED,
        G_COLOR_INDIAN_RED,
        G_COLOR_FIREBRICK,
        G_COLOR_CRIMSON,

        G_COLOR_DARK_GREEN,
        G_COLOR_LIGHT_GREEN,
        G_COLOR_LIME_GREEN,
        G_COLOR_FOREST_GREEN,
        G_COLOR_SEA_GREEN,

        G_COLOR_DARK_BLUE,
        G_COLOR_LIGHT_BLUE,
        G_COLOR_SKY_BLUE,
        G_COLOR_STEEL_BLUE,
        G_COLOR_NAVY_BLUE,

        G_COLOR_GOLD,
        G_COLOR_KHAKI,
        G_COLOR_PALE_GOLDENROD,

        G_COLOR_LAVENDER,
        G_COLOR_VIOLET,
        G_COLOR_ORCHID,

        G_COLOR_CORAL,
        G_COLOR_DARK_ORANGE,
        G_COLOR_SADDLE_BROWN,
        G_COLOR_CHOCOLATE,

        G_COLOR_SALMON,
        G_COLOR_TURQUOISE,
        G_COLOR_MAROON,
        G_COLOR_OLIVE,
        G_COLOR_TEAL

    } G_COLOR;

    class Colors
    {
    public:
        static std::tuple<Uint8, Uint8, Uint8> getColor(G_COLOR color);

    private:
        static std::map<G_COLOR, std::tuple<Uint8, Uint8, Uint8>> _colorsMap;

        static void initColorsMap();
    };

} // namespace core
