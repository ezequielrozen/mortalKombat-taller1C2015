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
    int combo2Progress;

    bool bufferMatchesCombo(list<Events>* combo);

    void cleanBuffer();
    list<Events>* combo1;
    list<Events>* combo2;
    list<Events>* buffer;
};


#endif //MORTALKOMBAT_TALLER1C2015_COMBOMANAGER_H
