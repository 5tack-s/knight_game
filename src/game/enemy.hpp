#ifndef gEnemy
#define gEnemy

#include <entity.hpp>
#include "utils/constants.hpp"

class Enemy: public Entity {

    public:
        Enemy(SDL_FRect spritePortion, SDL_FRect entityRect, std::string spriteSource);
        ~Enemy();
    
    public:
        void render();
        void setMoving(bool running);
        void move(float deltaTime);

    private:
        void setSpeed(float speed);

    private:
        int interval;
        int lastTick;
        SDL_FPoint lastPosition;
        SDL_FPoint randomPosition;
        float moveTimer;
};

#endif