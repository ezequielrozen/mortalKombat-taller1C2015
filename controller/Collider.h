#ifndef MORTALKOMBAT_TALLER1C2015_COLLIDER_H
#define MORTALKOMBAT_TALLER1C2015_COLLIDER_H

#include "../model/MKCharacter.h"

class Collider {

public:
    Collider();
    ~Collider();

    void update(MKCharacter* character1, MKCharacter* character2, bool cameraMoved);

private:

//    bool superpositionX(MKCharacter *character1, MKCharacter *character2);
    bool superpositionLeft(MKCharacter* character1, MKCharacter* character2);

    bool superpositionRight(MKCharacter *character1, MKCharacter *character2);

    bool superpositionUp(MKCharacter* character1, MKCharacter* character2);
};


#endif //MORTALKOMBAT_TALLER1C2015_COLLIDER_H
