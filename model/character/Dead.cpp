#include "Dead.h"

Dead::Dead() {

}

Dead::~Dead() {

}

void Dead::update(MKCharacter *character, Events aEvent) {
    switch (aEvent) {
        default:
            //si no recibe ninguno de los otros eventos, en principio no hay que hacer nada, porque no afectan a este estado
            break;
    }
}

string Dead::getName() {
    return "Dead";
}

float Dead::getWidth() {
	return 1.71;
}
