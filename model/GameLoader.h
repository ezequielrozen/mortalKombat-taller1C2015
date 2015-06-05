#ifndef MORTALKOMBAT_TALLER1C2015_GAMELOADER_H
#define MORTALKOMBAT_TALLER1C2015_GAMELOADER_H

#include "stage/Layer.h"
#include "stage/Stage.h"
#include "MKCharacter.h"
#include "../view/character/Painter.h"

class GameLoader {

public:
    GameLoader();
    ~GameLoader();
    void loadJSON(char* file);
    string getOponentSide();
    Stage* getStage();
    list<MKCharacter*>* getCharacters();
    Painter* getPainter();
    list<Events> *getCombo1();
    list<Events> *getCombo2();

private:
    float stageWidth;
    float stageHeight;
    float floor;
    string oponentSide;
    Painter* painter;
    list<Layer*>* layers;
    list<MKCharacter*>* characters;
    Stage* stage;
    list<Events>* combo1;
    list<Events>* combo2;
};


#endif //MORTALKOMBAT_TALLER1C2015_GAMELOADER_H
