#include <iostream>
#include "CharacterStance.h"
#include "MovingRight.h"
#include "MovingLeft.h"
#include "Jumping.h"
#include "Ducking.h"
#include "HittingPunch.h"
#include "LowPunchHitting.h"
#include "HighKickHitting.h"
#include "Blocking.h"
#include "Shooting.h"
#include "RecevingHit.h"
#include "LowKickHitting.h"

CharacterStance::CharacterStance() {
//    this->timer = -1
}

CharacterStance::~CharacterStance() {

}

void CharacterStance::update(MKCharacter * character, Events aEvent) {

//    std::cout << "Update desde StanceState." << std::endl;

    switch (aEvent) {
        case MoveRight:
            character->setState(new MovingRight());
            break;
        case MoveLeft:
            character->setState(new MovingLeft());
            break;
        case Jump:
            character->setState(new Jumping());
            break;
        case Duck:
            character->setState(new Ducking());
            break;
        case HighPunch:
            character->setState(new HittingPunch());
            break;
        case LowPunch:
            character->setState(new LowPunchHitting());
            break;
        case HighKick:
            character->setState(new HighKickHitting());
            break;
        case LowKick:
            character->setState(new LowKickHitting());
            break;
        case Block:
            character->setState(new Blocking());
            break;
        case Shoot:
            character->setState(new Shooting());
            break;
        case ReceiveHit:
            character->setState(new RecevingHit());
            break;
        default:
            //si no recibe ninguno de los otros eventos, en principio no hay que hacer nada, porque no afectan a este estado

            break;

    }
}

string CharacterStance::getName() {
    return "Stance";
}

float CharacterStance::getWidth() {
    return 0;
}