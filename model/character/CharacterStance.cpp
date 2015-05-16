#include <iostream>
#include "CharacterStance.h"
#include "MovingRight.h"
#include "MovingLeft.h"

CharacterStance::CharacterStance() {
    eventMap = new map<Events, CharacterState>();
    eventMap->insert(pair<Events, CharacterState>(MoveRight, CharacterStance()));
   // CharacterState mr = eventMap.at(MoveRight);
}

CharacterStance::~CharacterStance() {

}

void CharacterStance::update(Character* character, MKEvent* aEvent) {
//    delete character->state; no estoy seguro si está bien, pero la idea es que como se cambia de estado, liberamos la memoria del anterior. no es costoso hacer estos news.
/*
    character->setState(new MovingRight());
*/    std::cout << "Update desde StanceState." << std::endl;
}

void CharacterStance::getState() {
    std::cout << "Stance State." << endl;
}

// Must define less than relative to Name objects.
bool operator<(CharacterState a, CharacterState b)
{
    return true;
}