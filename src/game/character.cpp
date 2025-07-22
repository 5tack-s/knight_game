


#include "character.hpp"

constexpr int spriteGridSize = 32;

Character::Character(SDL_FRect spritePortion, SDL_FRect entityRect, std::string spriteSource)
    : Entity::Entity(spritePortion, entityRect, spriteSource)
{
    moving = false;
    flip = SDL_FLIP_NONE;
    rollDuration = 500;
    speed = 100;
    rollSpeed = 300;
    rollCooldown = 1000;
    isOnRollCooldown = false;
    rollStartTime = 0;
    lastRollTime = 0;
    rolling = false;
    rollDirection = {0, 0};
    hitbox.w = 10;
    hitbox.h = 10;
    isAlive = true;
    deathFrames = 4;
    lockMovement = false;

    rollSfx.loadWAV(
        std::string(SDL_GetBasePath()) + "assets/brackeys_platformer_assets/sounds/tap.wav"
    );

    hurtSfx.loadWAV(
        std::string(SDL_GetBasePath()) + "assets/brackeys_platformer_assets/sounds/hurt.wav"
    );

    deathSfx.loadWAV(
        std::string(SDL_GetBasePath()) + "assets/brackeys_platformer_assets/sounds/explosion.wav"
    );

    coinPickupSfx.loadWAV(
        std::string(SDL_GetBasePath()) + "assets/brackeys_platformer_assets/sounds/coin.wav"
    );
    
}

Character::~Character() {}

void Character::render() {
    int ticks = SDL_GetTicks();
    int animationSpeed = ticks / 100;

if(isAlive){
    if (rolling && moving) {
        spritePortion.y = spriteGridSize * 5;
        frame = animationSpeed % ROLL;
        sprite = frame;
    }
    else if (moving && !rolling) {
        spritePortion.y = spriteGridSize * 3;
        frame = animationSpeed % RUN;
        sprite = frame;
    }
    else if(!moving) {
        spritePortion.y = 0; 
        frame = animationSpeed % IDLE;
        sprite = frame;
    }
}
else{
    animationSpeed = ticks/500;
    lockMovement = true;
    spritePortion.y = spriteGridSize * 7;
    frame = animationSpeed % DEATH;
    sprite = frame;

    if(sprite % deathFrames == 0){
        lockMovement = false;
        isAlive = true;
        animationSpeed = ticks/100;
    }
}

    spritePortion.x = sprite * spriteGridSize;

    bool status = SDL_RenderTextureRotated(renderer, spriteTexture, &spritePortion, &entityRect, 0, NULL, flip);
    if (!status) {
        SDL_Log("Error rendering character: %s", SDL_GetError());
    }
}

void Character::handleMovement(double deltaTime) {
    if(lockMovement) return;

    const bool* keys = SDL_GetKeyboardState(NULL);
    int now = SDL_GetTicks();

    if (rolling) {
        entityRect.x += rollDirection.x * rollSpeed * deltaTime;
        entityRect.y += rollDirection.y * rollSpeed * deltaTime;

    if (now - rollStartTime >= rollDuration) {
            rolling = false;
            isOnRollCooldown = true;
            lastRollTime = now;
            rollDirection = {0, 0};
    }
        return;
    }

    if (isOnRollCooldown && (now - lastRollTime >= rollCooldown)) {
        isOnRollCooldown = false;
    }

    float dx = 0.0f, dy = 0.0f;
    moving = false;

    if (keys[SDL_SCANCODE_A]) {
        dx = -1;
        flip = SDL_FLIP_HORIZONTAL;
    }
    if (keys[SDL_SCANCODE_D]) {
        dx = 1;
        flip = SDL_FLIP_NONE;
    }
    if (keys[SDL_SCANCODE_W]) {
        dy = -1;
    }
    if (keys[SDL_SCANCODE_S]) {
        dy = 1;
    }

    if (dx != 0 || dy != 0) {
        float length = SDL_sqrt(dx * dx + dy * dy);
        dx /= length;
        dy /= length;

        entityRect.x += dx * speed * deltaTime;
        entityRect.y += dy * speed * deltaTime;
        moving = true;

    if (keys[SDL_SCANCODE_LSHIFT] && !isOnRollCooldown && !rolling) {
            frame = 0;
            rollSfx.playWAV(1);
            rolling = true;
            rollStartTime = now;
            rollDirection = {dx, dy};
    }
}
}

void Character::setMoving(bool moving) {
    this->moving = moving;
}

void Character::setSpeed(float speed) {
    this->speed = speed;
}

bool Character::handleCoinPickup(SDL_FRect target){

    bool status = detectCollision(hitbox, target);

    if(status){
        coinPickupSfx.playWAV(0);
        return true;
    }

    return false;

}

bool Character::handleDeath(SDL_FRect target){
    bool status = detectCollision(hitbox, target);

    if(status){
        deathSfx.playWAV(0);
        isAlive = false;
        frame = 0;
        entityRect.x = windowConstants::width/2;
        entityRect.y = windowConstants::height/2;
        return true;
    }

return false;
        
}

bool Character::getIsAlive(){
    return isAlive;
}