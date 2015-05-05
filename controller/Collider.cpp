#include "Collider.h"


Collider::Collider() {

}

Collider::~Collider() {

}

bool Collider::superpositionLeft(MKCharacter* character1, MKCharacter* character2) {
	return (character1->getX()+character1->getWidth() >= character2->getX() && character1->getX() < character2->getX());
};

bool Collider::superpositionRight(MKCharacter* character1, MKCharacter* character2) {
	return (character1->getX() <= character2->getX()+character2->getWidth() && character1->getX() > character2->getX());
};

bool Collider::superpositionUp(MKCharacter* character1, MKCharacter* character2) {
	return (character1->getY()+character1->getHeight() >= character2->getY());
}

void Collider::update(MKCharacter* character1, MKCharacter* character2, bool cameraMoved) {

	if (!cameraMoved) {
		if (!(this->superpositionLeft(character1, character2) && this->superpositionUp(character1, character2) && character1->getMovement() == "RIGHT" ||
			this->superpositionRight(character1, character2) && this->superpositionUp(character1, character2) && character1->getMovement() == "LEFT")) {
			character1->move();
			character2->move();
		} else if ((superpositionRight(character1,character2) || superpositionLeft(character1, character2)) &&
				character1->getMovement() == "KICK") {
			cout << "ENTRO" << endl;
			character2->receiveBlow(DAMAGE.at("KICK"));
			cout << character2->getLife() << endl;

		}
	}
}