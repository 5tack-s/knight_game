#include "mix.hpp"
#include "SDL3/SDL_audio.h"
#include "SDL3/SDL_properties.h"
#include "SDL3_mixer/SDL_mixer.h"

Mix::Mix():
mixer(nullptr),
music_track(nullptr),
sfx_track(nullptr),
sfx(nullptr),
music(nullptr)

{
    if(!MIX_Init()){
        SDL_Log("Error initializing SDL_mixer: %s", SDL_GetError());
        return;
    }

    mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
    music_track = MIX_CreateTrack(mixer);
    sfx_track = MIX_CreateTrack(mixer);
    if(!mixer){
        SDL_Log("Error creating mixer: %s", SDL_GetError());
        MIX_Quit();
    }
}

Mix::~Mix(){
    if(music) MIX_DestroyAudio(music);
    if(sfx) MIX_DestroyAudio(sfx);
    if(mixer) MIX_DestroyMixer(mixer);
    if(music_track) MIX_DestroyTrack(music_track);
    if(sfx_track) MIX_DestroyTrack(sfx_track);
    MIX_Quit();
}

void Mix::loadMusic(std::string path){
    if(music){
        MIX_DestroyAudio(music);
    }
    music = MIX_LoadAudio(mixer, path.c_str(), false);

    if(!music)
        SDL_Log("Error loading music: %s", SDL_GetError());

    MIX_SetTrackAudio(music_track, music);
}

void Mix::loadWAV(std::string path){
    if(sfx)
        MIX_DestroyAudio(sfx);


    sfx = MIX_LoadAudio(mixer, path.c_str(), false);

    if(!sfx)
        SDL_Log("Error loading WAV: %s", SDL_GetError());

    MIX_SetTrackAudio(sfx_track, sfx);
}

void Mix::playMusic(){
    SDL_PropertiesID props = SDL_CreateProperties();
    if(props){
        SDL_SetNumberProperty(props, MIX_PROP_PLAY_LOOPS_NUMBER, -1);
        MIX_PlayTrack(music_track, props);
    }
}


void Mix::playWAV(int loops){
    SDL_PropertiesID props = SDL_CreateProperties();
    if(props){
    if(sfx){
            SDL_SetNumberProperty(props, MIX_PROP_PLAY_LOOPS_NUMBER, loops);
            MIX_PlayTrack(sfx_track, props);
        }
    }
}
