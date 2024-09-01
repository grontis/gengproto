#include "Entity.h"

Entity::Entity(int x, int y, int w, int h, SDL_Color c)
    : color(c)
{
    rect = {x, y, w, h};
}

void Entity::move(int dx, int dy) {
    rect.x += dx;
    rect.y += dy;
}