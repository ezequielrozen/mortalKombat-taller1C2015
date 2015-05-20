#include "Ducking.h"
#include "CharacterStance.h"
#include "LowPunchHitting.h"
#include "DuckingKickHitting.h"
#include "RecevingHit.h"
#include "ReceivingDuckingKick.h"
#include "DuckingPunch.h"

Ducking::Ducking() {
    this->timer = 10;
}

Ducking::~Ducking() {
}

void Ducking::update(MKCharacter * character, Events aEvent) {

    switch (aEvent) {
        case LowPunch:
            character->setState(new DuckingPunch());
            break;
        case HighKick:
            character->setState(new DuckingKickHitting());
            break;
        case ReceiveHit:
            character->setState(new ReceivingDuckingKick());
            break;
        case DuckRelease:
            character->setState(new CharacterStance());
            break;
        default:
            //si no recibe ninguno de los otros eventos, en principio no hay que hacer nada, porque no afectan a este estado
            break;

    }
}

string Ducking::getName() {
    return "Ducking";
}

bool Ducking::isDucking() {
    return true;
}