#include "Entity.h"

Entity::Entity(int x, int y, int w, int h, SDL_Color c)
    : color(c)
{
    rect = {x, y, w, h};
}

//TODO refactor SDL specific code out of here
void Entity::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

void Entity::move(int dx, int dy) {
    rect.x += dx;
    rect.y += dy;
}