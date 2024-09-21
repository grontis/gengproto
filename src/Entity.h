#pragma once

#include "GRectangle.h"

struct Entity
{
    core::GRectangle body;

    Entity(core::GRectangle r);
    void move(int dx, int dy);
};