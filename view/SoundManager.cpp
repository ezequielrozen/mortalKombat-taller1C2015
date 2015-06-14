//
// Created by mauri on 14/06/15.
//

#include <SDL2/SDL.h>
#include "SoundManager.h"

SoundManager* SoundManager::instance = 0;


SoundManager* SoundManager::getInstance() {
    if (!instance)
        instance = new SoundManager();
    return instance;
}



void SoundManager::loadSounds() {
    if (!this->loaded) {
        if (SDL_Init((uint) SDL_INIT_AUDIO) < 0) {
            printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        }
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
            // Loggear
        } else {
            sounds = {{"hit1",           Mix_LoadWAV("data/Sounds/hit1.wav")},
                      {"hit2",        Mix_LoadWAV("data/Sounds/hit2.wav")},
                      {"select",        Mix_LoadWAV("data/Sounds/select.wav")},
                      {"select2",       Mix_LoadWAV("data/Sounds/select2.wav")},
                      {"receivehit", Mix_LoadWAV("data/Sounds/receivehit.wav")},
                      {"confirmselection", Mix_LoadWAV("data/Sounds/confirmselection.wav")},
                      {"jump", Mix_LoadWAV("data/Sounds/jump.wav")},
                      {"fall", Mix_LoadWAV("data/Sounds/fall.wav")},
                      {"burn", Mix_LoadWAV("data/Sounds/burn.wav")},
                      {"weapon", Mix_LoadWAV("data/Sounds/weapon.wav")},
                      {"teleport", Mix_LoadWAV("data/Sounds/teleport.wav")},
                      {"ray", Mix_LoadWAV("data/Sounds/ray.wav")},
                      {"getoverhere", Mix_LoadWAV("data/Sounds/getoverhere.wav")},
                      {"finishhim", Mix_LoadWAV("data/Sounds/finishhim.wav")},

            };

            this->loaded = true;
            /*
        fx = Mix_LoadWAV( "data/Sounds/mk3-00100.wav");
        if( fx == NULL ) {
            printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
            // Cargar sonido "vacio" por default?
        }*/
        }
    }
}

void SoundManager::freeSounds() {
    Mix_FreeChunk(sounds.at("hit"));
    Mix_FreeChunk(sounds.at("hit2"));
    Mix_FreeChunk(sounds.at("select"));
    Mix_FreeChunk(sounds.at("select2"));
    Mix_FreeChunk(sounds.at("receivehit"));
    Mix_FreeChunk(sounds.at("confirmselection"));
    Mix_FreeChunk(sounds.at("jump"));
    Mix_FreeChunk(sounds.at("fall"));
    Mix_FreeChunk(sounds.at("burn"));
    Mix_FreeChunk(sounds.at("weapon"));
    Mix_FreeChunk(sounds.at("teleport"));
    Mix_FreeChunk(sounds.at("ray"));
    Mix_FreeChunk(sounds.at("getoverhere"));
    Mix_FreeChunk(sounds.at("finishhim"));
}

void SoundManager::playSound(std::string soundId) {
    Mix_PlayChannel (-1, sounds.at(soundId) , 0);
}

SoundManager::SoundManager() {
    this->loaded = false;
}

SoundManager::~SoundManager() {
    freeSounds();
}
