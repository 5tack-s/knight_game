#include "coin.hpp"

constexpr int spriteGridSize = 16;

Coin::Coin(SDL_FRect spritePortion, SDL_FRect entityRect, std::string spriteSource):
 Entity::Entity(
    spritePortion,
    entityRect,
    spriteSource
 )
{
    flip = SDL_FLIP_NONE;
    hitbox.w = 10;
    hitbox.h = 10;
}

Coin::~Coin(){}

void Coin::render(){
     
    int ticks = SDL_GetTicks();
    int animationSpeed = ticks / 100;
    int frame = animationSpeed % 12;
    int sprite = frame;
    
    spritePortion.x = spriteGridSize * sprite;


   bool status = SDL_RenderTextureRotated(renderer, spriteTexture, &spritePortion, &entityRect, 0, NULL, flip);

    if(!status){
    SDL_Log("Error rendering coin: %s", SDL_GetError());
   }
}

void Coin::setMoving(bool running){}

void Coin::setSpeed(float speed){}

void Coin::setPicked(bool picked){
    this->picked = picked;
}

bool Coin::getPicked(){
    return picked;
}
