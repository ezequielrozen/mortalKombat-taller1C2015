//
// Created by mauri on 14/06/15.
//

#ifndef MORTALKOMBAT_TALLER1C2015_SOUNDMANAGER_H
#define MORTALKOMBAT_TALLER1C2015_SOUNDMANAGER_H

#include <SDL2/SDL_mixer.h>
#include <string>
#include <map>

typedef std::map<std::string, Mix_Chunk*> SoundsMap;

class SoundManager {
public:
    static SoundManager* getInstance();
    void loadSounds();
    void freeSounds();
    void playSound(std::string soundId);
private:
    SoundManager();
    ~SoundManager();
    static SoundManager* instance;
    SoundsMap sounds;
    bool loaded;

};


#endif //MORTALKOMBAT_TALLER1C2015_SOUNDMANAGER_H
