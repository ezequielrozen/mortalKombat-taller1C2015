//
// Created by her on 16/06/15.
//

#ifndef MORTALKOMBAT_TALLER1C2015_FLYHITTING_H
#define MORTALKOMBAT_TALLER1C2015_FLYHITTING_H

#include "CharacterState.h"

class FlyHitting : public CharacterState {
public:
    FlyHitting();
    virtual ~FlyHitting();
    string getName();
    void refreshTimer(MKCharacter* character);
    bool isHitting();
    bool impact();
    float getWidth();
    float getHeight();
    char getSideWhenInit();
    bool getCheckSide();
    void setCheckSide(bool value);
private:
    int timer;
    char sideWhenInit;
    bool checkSide;
};


#endif //MORTALKOMBAT_TALLER1C2015_FLYHITTING_H
