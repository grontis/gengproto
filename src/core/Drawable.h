#pragma once

#include "GraphicsManager.h"

class Drawable {
public:
    virtual void draw(const GraphicsManager* graphics) const = 0;
    virtual ~Drawable() = default;
};
