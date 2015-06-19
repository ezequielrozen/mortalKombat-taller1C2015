using namespace std;

#ifndef MORTALKOMBAT_TALLER1C2015_COMBOMANAGER_H
#define MORTALKOMBAT_TALLER1C2015_COMBOMANAGER_H

#include "../constantes.h"

class ComboManager {
public:
    ComboManager();
    ~ComboManager();
    Events checkCombo(Events originalEvent, char side, string name);
    void loadCombos(std::vector<Events>* combo1,
                    std::vector<Events>* combo2,
                    std::vector<Events>* combo3,
                    std::vector<Events>* combo4,
                    std::vector<Events>* combo5,
                    std::vector<Events>* combo6,
                    std::vector<Events>* fatality);

private:

    int startTime;

    bool bufferMatchesCombo(std::vector<Events>* combo, char side);

    void cleanBuffer();
    std::vector<Events>* combo1;
    std::vector<Events>* combo2;
    std::vector<Events>* combo3;
    std::vector<Events>* combo4;
    std::vector<Events>* combo5;
    std::vector<Events>* combo6;

    std::vector<Events>* buffer;
    vector<Events> *fatality;
    bool isTimeOut();

    Events changeSideEvent(Events event, char side);
};


#endif //MORTALKOMBAT_TALLER1C2015_COMBOMANAGER_H
