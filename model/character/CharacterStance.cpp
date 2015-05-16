#include <iostream>
#include "CharacterStance.h"
#include "MovingRight.h"
#include "MovingLeft.h"

CharacterStance::CharacterStance() {
    eventMap = map<Events, CharacterState>();
    eventMap.insert(pair<Events, CharacterState>(MoveRight, MovingRight()));
    map<Events, CharacterState>::iterator p;
    //p = eventMap.find(MoveRight);
    p = eventMap.find(MoveRight);
    if(p != eventMap.end())
        cout << "Phone number: " << p->second.getState() << endl;
    else
        cout << "Name not in directory.\n";

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