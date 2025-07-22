#include <iostream>
#include <deck.hpp>
#include <ctime>
#include <memory>
#include <algorithm>
#include "character.hpp"
#include "enemy.hpp"
#include "coin.hpp"
#include "utils/constants.hpp"

int ENTITY_AMOUNT = 0;
int COIN_AMOUNT = 5;

void setupCoins(std::vector<std::unique_ptr<Coin>>& coins, SDL_Renderer* renderer){
   for (int i = 0; i < COIN_AMOUNT; i++) {
        float rand1 = SDL_randf();
        float rand2 = SDL_randf();

        coins.push_back(std::make_unique<Coin>(
            SDL_FRect{0.0, 0.0, 15.0, 15.0},
            SDL_FRect{450 * rand1, 450 * rand2, 25, 25},
            std::string(SDL_GetBasePath()) + "assets/brackeys_platformer_assets/sprites/coin.png"
        ));

        coins[i]->init(renderer);
    }
}

void setupEnemies(std::vector<std::unique_ptr<Enemy>>& enemies, SDL_Renderer* renderer){
        for (int i = 0; i < ENTITY_AMOUNT; i++) {
        float rand1 = SDL_randf();
        float rand2 = SDL_randf();

        enemies.push_back(std::make_unique<Enemy>(
            SDL_FRect{0.0, 0.0, 25.0, 25.0},
            SDL_FRect{450 * rand1, 450 * rand2, 40, 40},
            std::string(SDL_GetBasePath()) + "assets/brackeys_platformer_assets/sprites/slime_green.png"
        ));

        enemies[i]->init(renderer);
    }
}

void growEnemies(std::vector<std::unique_ptr<Enemy>>& enemies, SDL_Renderer* renderer){
    float rand1 = SDL_randf();
    float rand2 = SDL_randf();

        enemies.push_back(std::make_unique<Enemy>(
            SDL_FRect{0.0, 0.0, 25.0, 25.0},
            SDL_FRect{450 * rand1, 450 * rand2, 40, 40},
            std::string(SDL_GetBasePath()) + "assets/brackeys_platformer_assets/sprites/slime_green.png"
        ));

        enemies.back()->init(renderer);
}


int main () {
    SDL_srand(static_cast<unsigned int>(time(nullptr)));

    SDL_Event event;
    Text scoreText;
    Text highscoreText;
    Mix music;
    int score = 0;
    int highscore = 0;

    Window window("Arching", windowConstants::width, windowConstants::height, SDL_WINDOW_RESIZABLE);
    window.setLogicalResolution(windowConstants::width, windowConstants::height, SDL_LOGICAL_PRESENTATION_STRETCH);

    Character character(
        {0.0, 0.0, 30.0, 30.0},
        {windowConstants::width/3, windowConstants::height/3, 50, 50},
        std::string(SDL_GetBasePath()) + "assets/brackeys_platformer_assets/sprites/knight.png"
    );

    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Coin>> coins;

    setupCoins(coins, window.getRenderer());
    setupEnemies(enemies, window.getRenderer());


    scoreText.start(
        std::string(SDL_GetBasePath()) + "assets/brackeys_platformer_assets/fonts/PixelOperator8.ttf",
        16,
        window.getRenderer()
    );
    scoreText.setText("Score: 0");
    scoreText.setTextColor({0, 0, 0, 255});
    scoreText.createText();

    highscoreText.start(
        std::string(SDL_GetBasePath()) + "assets/brackeys_platformer_assets/fonts/PixelOperator8.ttf",
        16,
        window.getRenderer()
    );
    highscoreText.setText("Highscore: 0");
    highscoreText.setTextColor({0,0,0,255});
    highscoreText.createText();

    music.loadMusic(
        std::string(SDL_GetBasePath()) + "assets/brackeys_platformer_assets/music/time_for_adventure.mp3"
    );
    music.playMusic();

    character.init(window.getRenderer());

    window.setRenderCallback([&]() {

        scoreText.renderText(window.getRenderer(), {10, 10, 100, 35});
        highscoreText.renderText(window.getRenderer(), {130,10,100,35});

        coins.erase(
            std::remove_if(coins.begin(), coins.end(),
                [](const std::unique_ptr<Coin>& coin) {
                    return coin->getPicked();
                }),
            coins.end()
        );

        if(coins.empty())
            setupCoins(coins, window.getRenderer());

        for (auto& enemy : enemies) {
            enemy->render();
            enemy->move(window.deltaTime);
        }

        for (auto& coin : coins) {
            coin->render();
        }

        character.render();

        SDL_Delay(1);
    });

    window.setLogicalLoop([&]() {
        character.handleMovement(window.deltaTime);
        for(auto& coin: coins){
            coin->bindHitbox();
            //coin->renderHitbox();

            if(character.handleCoinPickup(coin->getHitbox())){
                score++;
                if(score > highscore)
                    highscore++;
                scoreText.setText("Score: " + std::to_string(score));
                highscoreText.setText("Highcore: " + std::to_string(highscore));
                scoreText.createText();
                highscoreText.createText();

                coin->setPicked(true);

                growEnemies(enemies, window.getRenderer());
            }
        }

        for(auto& enemy: enemies){
            if(enemy){
            enemy->bindHitbox(0,5);
            //enemy->renderHitbox();
            }
            bool status = character.handleDeath(enemy->getHitbox());

            if(status){
                score = 0;
                scoreText.setText("Score: " + std::to_string(score));
                scoreText.createText();
                enemies.clear();
                coins.clear();
                setupCoins(coins, window.getRenderer());
                break;
            }
        }

        character.bindHitbox(0, 10);
       // character.renderHitbox();
    });

    window.setEventLoop([&]() {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    window.setRunning(false);
                    break;

                case SDL_EVENT_KEY_DOWN:
                    break;
                case SDL_EVENT_KEY_UP:
                    break;
            }
        }
    });

    window.run();
    scoreText.closeFont();
}