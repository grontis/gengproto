#include "GRectangle.h"

GRectangle::GRectangle(int x, int y, int w, int h, SDL_Color c)
    : color(c)
{
    rect = {x, y, w, h};
}