#pragma once

#include "GraphicsManager.h"

namespace core
{
    class Drawable
    {
    public:
        virtual void draw(const GraphicsManager *graphics) const = 0;
        virtual ~Drawable() = default;
    };
}