#include "CharacterStance.h"

CharacterStance::CharacterStance() {

}

CharacterStance::~CharacterStance() {

}

void CharacterStance::update(Character* character, MoveRight* aEvent) {
    delete character->state; //no estoy seguro si está bien, pero la idea es que como se cambia de estado, liberamos la memoria del anterior. es costoso hacer estos news.
    character->state = new MovingRight();
    cout << "Estaba en Stance. Comienzo a moverme a la derecha." << endl;

}

void update(Character* character, MoveLeft* aEvent) {
    delete character->state; //no estoy seguro si está bien, pero la idea es que como se cambia de estado, liberamos la memoria del anterior. es costoso hacer estos news.
    character->state = new MovingLeft();
    cout << "Estaba en Stance. Comienzo a moverme a la izquierda." << endl;
}
