#ifndef eEntity
#define eEntity
#include <SDL3_image/SDL_image.h>
#include <iostream>

class Entity {
    public:
        Entity(SDL_FRect spritePortion, SDL_FRect entityRect, std::string spriteSource);
        ~Entity();

    public:
        void init(SDL_Renderer* renderer);
    
    protected:
        SDL_Renderer* renderer;
        SDL_Texture* spriteTexture;
        SDL_FRect spritePortion;
        SDL_FRect entityRect;
        SDL_FRect hitbox;
        std::string spriteSource;
        bool moving;
        SDL_FlipMode flip;
    
    protected:
        float speed;
        int currentSprite;
    
    public:
        void bindHitbox(float offsetX, float offsetY);
        void bindHitbox();
        void renderHitbox();
        SDL_FRect getHitbox();
    
    public:
        int detectCollision(SDL_FRect rect1, SDL_FRect rect2);
};
#endif