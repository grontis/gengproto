#include "GRectangle.h"
// TODO need to rethink folder namespace structure now that the Rectangle class here depends on colors.
// maybe a "Primitives" folder that they can all live under?

namespace core
{
    GRectangle::GRectangle(int x, int y, int w, int h, G_COLOR c, Uint8 a)
    {
        rect = {x, y, w, h};
        color = c;
        alpha = a;
    }
}
