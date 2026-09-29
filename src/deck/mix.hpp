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
        MIX_Mixer* mixer;
        MIX_Track* music_track;
        MIX_Track* sfx_track;
        MIX_Audio* sfx;
        MIX_Audio* music;
};

#endif
