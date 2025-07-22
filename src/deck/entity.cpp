#include "entity.hpp"

Entity::Entity(SDL_FRect spritePortion, SDL_FRect entityRect, std::string spriteSource):
    spriteSource(spriteSource),
    spritePortion(spritePortion),
    entityRect(entityRect)
{}

Entity::~Entity(){
    SDL_DestroyTexture(spriteTexture);
}

void Entity::init(SDL_Renderer* renderer){
    this->renderer = renderer;
    spriteTexture = IMG_LoadTexture(renderer, spriteSource.c_str());

    if(!spriteTexture){
        SDL_Log("Failed to load texture: %s", SDL_GetError());
        SDL_Quit();
    }
}

int Entity::detectCollision(SDL_FRect rect1, SDL_FRect rect2){

    if(rect1.x + rect1.w <= rect2.x || rect2.x + rect2.w <= rect1.x)
        return 0;
    
    if(rect1.y + rect1.w <= rect2.y || rect2.y + rect2.w <= rect1.y)
        return 0;

    return 1;
}

void Entity::bindHitbox(float offsetX, float offsetY){
    hitbox.x = entityRect.x + (entityRect.w - hitbox.w) /2 + offsetX;
    hitbox.y = entityRect.y + (entityRect.h - hitbox.h) /2 + offsetY;
}

void Entity::bindHitbox(){
    hitbox.y = entityRect.y + (entityRect.h - hitbox.h) /2;
    hitbox.x = entityRect.x + (entityRect.w - hitbox.w) /2;
}

SDL_FRect Entity::getHitbox(){
    return hitbox;
}

void Entity::renderHitbox(){
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderRect(renderer, &hitbox);
}
