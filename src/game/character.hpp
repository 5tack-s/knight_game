#ifndef gCharacter
#define gCharacter
#include <entity.hpp>
#include <mix.hpp>
#include "utils/constants.hpp"

class Character: public Entity {

    public:
         enum SpriteFrames{
            IDLE=4, 
            RUN=8,
            ROLL=7, 
            HIT=4,
            DEATH=4,
        };

    public:
        Character(SDL_FRect spritePortion, SDL_FRect entityRect, std::string spriteSource);
        ~Character();
    
    public:
        void render();
        void setMoving(bool running);
        void handleMovement(double deltaTime);
        bool handleCoinPickup(SDL_FRect target);
        bool handleDeath(SDL_FRect target);

    public:
        SDL_FRect getHitbox();
        bool getIsAlive();

    private:
        void setSpeed(float speed);

    private:
        bool rolling;
        int rollDuration;
        float rollSpeed;
        int rollStartTime;
        int lastRollTime;
        float rollCooldown;
        bool isOnRollCooldown;
        SDL_FPoint rollDirection;

    private:
        Mix hurtSfx;
        Mix rollSfx;
        Mix coinPickupSfx;
        Mix deathSfx;

    private:
        bool isAlive;
        bool lockMovement;
        int deathFrames;
        int frame;
        int sprite;
        


};

#endif