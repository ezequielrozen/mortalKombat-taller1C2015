#ifndef MORTALKOMBAT_TALLER1C2015_GAMELOADER_H
#define MORTALKOMBAT_TALLER1C2015_GAMELOADER_H

#include "stage/Layer.h"
#include "stage/Stage.h"
#include "MKCharacter.h"

class GameLoader {

public:
    GameLoader();
    ~GameLoader();
    void loadJSON(char* file);
    string getOponentSide();
    Stage* getStage();
    list<MKCharacter*>* getCharacters();


private:
    float stageWidth;
    float stageHeight;
    float floor;
    string oponentSide;
    list<Layer*>* layers;
    list<MKCharacter*>* characters;
    Stage* stage;
};


#endif //MORTALKOMBAT_TALLER1C2015_GAMELOADER_H
