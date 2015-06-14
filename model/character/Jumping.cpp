#include "Jumping.h"
#include "CharacterStance.h"
#include "ReceivingDuckingPunch.h"
#include "WeaponHItting.h"
#include "../../view/SoundManager.h"

Jumping::Jumping() {
    SoundManager::getInstance()->playSound("jump");

}

Jumping::~Jumping() {
}

void Jumping::update(MKCharacter * character, Events aEvent) {
    switch (aEvent) {
        case ReceiveHit:
            character->setState(new ReceivingDuckingPunch());
            break;
        case ReceiveDuckingPunch:
            character->setState(new ReceivingDuckingPunch());
            break;
        case JumpFinished:
            character->setState(new CharacterStance());
            break;
        case ReceiveWeapon:
            character->setState(new ReceivingDuckingPunch());
            break;
       /* case WeaponHit:
            if (!character->getWeapon()->isActive()) {
                character->setState(new WeaponHitting());
            }
            break;
       */ default:
            break;
    }
}

bool Jumping::isJumping() {
    return true;
}

string Jumping::getName() {
    return "Jumping";
}
