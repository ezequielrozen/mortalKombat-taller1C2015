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
    vector<Events> *getCombo1();
    vector<Events> *getCombo2();
    vector<Events> *getCombo3();
    vector<Events> *getCombo4();
    vector<Events> *getCombo5();
    vector<Events> *getCombo6();
    vector<Events> *getFatality();

private:
    float stageWidth;
    float stageHeight;
    float floor;
    string oponentSide;
    Painter* painter;
    list<Layer*>* layers;
    list<MKCharacter*>* characters;
    Stage* stage;
    vector<Events>* combo1;
    vector<Events>* combo2;
    vector<Events>* combo3;
    vector<Events>* combo4;
    vector<Events>* combo5;
    vector<Events>* combo6;
    vector<Events> *fatality;
};


#endif //MORTALKOMBAT_TALLER1C2015_GAMELOADER_H
