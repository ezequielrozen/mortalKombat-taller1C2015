using namespace std;

#ifndef MORTALKOMBAT_TALLER1C2015_COMBOMANAGER_H
#define MORTALKOMBAT_TALLER1C2015_COMBOMANAGER_H

#include "../constantes.h"

class ComboManager {
public:
    ComboManager();
    ~ComboManager();
    Events checkCombo(Events originalEvent);
    void loadCombos(std::vector<Events>* combo1, std::vector<Events>* combo2);

private:

    int combo2Progress;

    bool bufferMatchesCombo(std::vector<Events>* combo);

    void cleanBuffer();
    std::vector<Events>* combo1;
    std::vector<Events>* combo2;
    std::vector<Events>* buffer;
};


#endif //MORTALKOMBAT_TALLER1C2015_COMBOMANAGER_H
