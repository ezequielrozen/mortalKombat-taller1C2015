//#include <iostream>
//#include "CharacterStance.h"
//#include "MovingRight.h"
//#include "MovingLeft.h"
//
//CharacterStance::CharacterStance() {
//
//}
//
//CharacterStance::~CharacterStance() {
//
//}
//
//void CharacterStance::update(Character* character, MoveRight* aEvent) {
////    delete character->state; no estoy seguro si está bien, pero la idea es que como se cambia de estado, liberamos la memoria del anterior. es costoso hacer estos news.
//    character->setState(new MovingRight());
//    std::cout << "Estaba en Stance. Comienzo a moverme a la derecha." << std::endl;
//
//}
//
//void CharacterStance::update(Character* character, MoveLeft* aEvent) {
////    delete character->state; no estoy seguro si está bien, pero la idea es que como se cambia de estado, liberamos la memoria del anterior. es costoso hacer estos news.
//    character->setState(new MovingLeft());
//    std::cout << "Estaba en Stance. Comienzo a moverme a la izquierda." << std::endl;
//}
