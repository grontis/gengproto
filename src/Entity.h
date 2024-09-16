#pragma once

#include "GRectangle.h"

struct Entity
{
    GRectangle body;

    Entity(GRectangle r);
    void move(int dx, int dy);
};