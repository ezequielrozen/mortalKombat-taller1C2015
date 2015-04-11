#ifndef MORTALKOMBAT_TALLER1C2015_GAMELOADER_H
#define MORTALKOMBAT_TALLER1C2015_GAMELOADER_H

#include "stage/Layer.h"
#include "stage/Stage.h"

class GameLoader {

public:
    GameLoader();
    ~GameLoader();
    void loadJSON(char* file);
    float getCharacterWidth();
    float getCharacterHeight();
    int getZ_index();
    string getOponentSide();
    Stage* getStage();

private:
    float stageWidth;
    float stageHeight;
    float characterWidth;
    float characterHeight;
    float floor;
    int z_index;
    string oponentSide;
    list<Layer*>* layers;
    Stage* stage;
};


#endif //MORTALKOMBAT_TALLER1C2015_GAMELOADER_H
