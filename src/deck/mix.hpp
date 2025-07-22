#ifndef eMix
#define eMix
#include <SDL3_mixer/SDL_mixer.h>
#include <iostream>

class Mix {
    public:
        Mix();
        ~Mix();

    public:
        void loadMusic(std::string path);
        void loadWAV(std::string path);
        void playMusic();
        void playWAV(int loops);

    private:
        Mix_Music* music;
        Mix_Chunk* sfx;
};

#endif