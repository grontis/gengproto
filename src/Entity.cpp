#include "Entity.h"

Entity::Entity(GRectangle r)
    : body(r)
{
}

void Entity::move(int dx, int dy) {
    body.rect.x += dx;
    body.rect.y += dy;
}