#include "Dizzy.h"
#include "ReceivingFire.h"
Dizzy::Dizzy() {

}

Dizzy::~Dizzy() {

}

void Dizzy::update(MKCharacter *character, Events aEvent) {
    switch (aEvent) {
        case ReceiveFire:
            character->setState(new ReceivingFire());
            break;
        default:
            //si no recibe ninguno de los otros eventos, en principio no hay que hacer nada, porque no afectan a este estado
            break;
    }

}

string Dizzy::getName() {
	return "Dizzy";
}
