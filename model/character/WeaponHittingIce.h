#ifndef MORTALKOMBAT_TALLER1C2015_WeaponHittingIce_H
#define MORTALKOMBAT_TALLER1C2015_WeaponHittingIce_H

#include "../MKCharacter.h"

class WeaponHittingIce : public CharacterState {

public:
    WeaponHittingIce();
    ~WeaponHittingIce();
    void update(MKCharacter * character, Events aEvent );

    string getName();
    bool startThrowing();

private:
    int timer;
public:
    void refreshTimer(MKCharacter *character);
};


#endif //MORTALKOMBAT_TALLER1C2015_WeaponHittingIce_H
