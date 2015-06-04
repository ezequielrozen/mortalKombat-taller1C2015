//
// Created by mauri on 03/06/15.
//
using namespace std;

#ifndef MORTALKOMBAT_TALLER1C2015_COMBOMANAGER_H
#define MORTALKOMBAT_TALLER1C2015_COMBOMANAGER_H

#include "../constantes.h"

class ComboManager {
public:
    ComboManager();
    ~ComboManager();
    Events checkCombo(Events originalEvent);
    void loadCombos(list<Events>* combo1, list<Events>* combo2);

private:

    int errorCounter;
    int comboProgress;

    list<Events>* combo1;
    list<Events>* combo2;
    list<Events>* buffer;
};


#endif //MORTALKOMBAT_TALLER1C2015_COMBOMANAGER_H
