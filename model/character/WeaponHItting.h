#ifndef MORTALKOMBAT_TALLER1C2015_SHOOTING_H
#define MORTALKOMBAT_TALLER1C2015_SHOOTING_H

#include "../MKCharacter.h"

class WeaponHitting : public CharacterState {

public:
    WeaponHitting();
    ~WeaponHitting();
    void update(MKCharacter * character, Events aEvent );

    string getName();
    float getWidth();
    bool startThrowing();

private:
    int timer;
public:
    void refreshTimer(MKCharacter *character);
};


#endif //MORTALKOMBAT_TALLER1C2015_SHOOTING_H
