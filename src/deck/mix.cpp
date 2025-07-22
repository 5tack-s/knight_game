#include "mix.hpp"

Mix::Mix():
music(nullptr),
sfx(nullptr)
{
    bool status = Mix_OpenAudio(0,NULL);
    if(!status)
        SDL_Log("Error opening audio: %s", SDL_GetError());
}

Mix::~Mix(){
    Mix_CloseAudio();
    if(music) Mix_FreeMusic(music);
    if(sfx) Mix_FreeChunk(sfx);
}

void Mix::loadMusic(std::string path){
    if(music)
        Mix_FreeMusic(music);
    
    music = Mix_LoadMUS(path.c_str());

    if(!music)
        SDL_Log("Error loading music: %s", SDL_GetError());
}

void Mix::loadWAV(std::string path){
    if(sfx)
        Mix_FreeChunk(sfx);

    sfx = Mix_LoadWAV(path.c_str());

    if(!sfx)
        SDL_Log("Error loading WAV: %s", SDL_GetError());   
}

void Mix::playMusic(){
    Mix_PlayMusic(music, -1);
}


void Mix::playWAV(int loops){
    Mix_PlayChannel(-1, sfx, loops);

}
