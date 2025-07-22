#ifndef gCoin
#define gCoin
#include <entity.hpp>
#include <mix.hpp>

class Coin : public Entity {

    public:
        Coin(SDL_FRect spritePortion, SDL_FRect entityRect, std::string spriteSource);
        ~Coin();


    public:
        void render();
        void setMoving(bool running);
        void setPicked(bool picked);
        bool getPicked();

    private:
        void setSpeed(float speed);

    private:
        bool picked;
};

#endif