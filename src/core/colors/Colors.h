#pragma once

#include <SDL2/SDL.h>
#include <map>
#include <tuple>

namespace core
{

    typedef enum 
    {
        G_COLOR_BLUE,
        G_COLOR_GREEN,
        G_COLOR_PURPLE
    } G_COLOR;

    class Colors
    {
    public:
        static std::tuple<Uint8, Uint8, Uint8> getColor(G_COLOR color);

    private:
        static std::map<G_COLOR, std::tuple<Uint8, Uint8, Uint8>> colorsMap;

        static void initColorsMap();
    };

}
