#include "enemy.hpp"

constexpr int spriteGridSize = 25;

Enemy::Enemy(SDL_FRect spritePortion, SDL_FRect entityRect, std::string spriteSource):
Entity::Entity(
    spritePortion, 
    entityRect, 
    spriteSource
)
{
    moving = false;
    flip = SDL_FLIP_NONE;
    interval = 5;
    lastTick = SDL_GetTicks();
    hitbox.w = 10;
    hitbox.h = 10;
}

Enemy::~Enemy(){}

void Enemy::render(){
    
    int ticks = SDL_GetTicks();
    int animationSpeed = ticks / 100;
    int frame = animationSpeed % 6;
    int sprite;

    if(frame <= 3)
        sprite = frame;
    else
        sprite = 6 - frame;
    spritePortion.x = spriteGridSize * sprite;
    
    spritePortion.y = spriteGridSize * 1;


   bool status = SDL_RenderTextureRotated(renderer, spriteTexture, &spritePortion, &entityRect, 0, NULL, flip);

   if(!status){
    SDL_Log("Error rendering enemy: %s", SDL_GetError());
   }
}

void Enemy::setMoving(bool running){

}

void Enemy::setSpeed(float speed){

}

SDL_FPoint lerp(SDL_FPoint start, SDL_FPoint end, float t){
    SDL_FPoint result;
    
    result.x = start.x + (end.x - start.x) * t;
    result.y = start.y + (end.y - start.y) * t;
    return result;
}
void Enemy::move(float deltaTime){
    if (!moving) {
        moving = true;
        moveTimer = 0.0f;
        lastPosition = {entityRect.x, entityRect.y};
        randomPosition = {
            SDL_randf() * windowConstants::width,
            SDL_randf() * windowConstants::height
        };
    }

    if (moving) {
        moveTimer += deltaTime;

        float t = moveTimer / interval;

        if (t >= 1.0f) {
            t = 1.0f;
            moving = false;
        }

        SDL_FPoint newPosition = lerp(lastPosition, randomPosition, t);
        entityRect.x = newPosition.x;
        entityRect.y = newPosition.y;

        if(randomPosition.x > entityRect.x)
            flip = SDL_FLIP_NONE;
        else
            flip = SDL_FLIP_HORIZONTAL;
    }
}
