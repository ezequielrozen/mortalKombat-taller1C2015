#include "Ducking.h"
#include "CharacterStance.h"
#include "LowPunchHitting.h"
#include "LowKickHitting.h"
#include "RecevingHit.h"

Ducking::Ducking() {
    this->timer = 10;
}

Ducking::~Ducking() {
}

void Ducking::update(MKCharacter * character, Events aEvent) {

    switch (aEvent) {
        case LowPunch:
            character->setState(new LowPunchHitting());
            break;
        case LowKick:
            character->setState(new LowKickHitting());
            break;
        case ReceiveHit:
            character->setState(new RecevingHit());
            break;
        case DuckRelease:
            character->setState(new CharacterStance());
        default:
            //si no recibe ninguno de los otros eventos, en principio no hay que hacer nada, porque no afectan a este estado
            break;

    }
}

