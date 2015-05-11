#include "Collider.h"


Collider::Collider() {
	timer = 0;
	beingHitTimer = 0;
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

void Collider::checkHits(MKCharacter* character1, MKCharacter* character2) {
	if ((superpositionRight(character1,character2) || superpositionLeft(character1, character2)) &&
		(!(character1->getHit() == "NONE")) && (!(character1->getHit() == "BEINGHIT"))) {
		if (timer + 100 < SDL_GetTicks()) {
			cout << "hitDelay: " << character1->getHitDelay() << endl;
			if (character1->getHitDelay() == 0) {
				character2->receiveBlow(DAMAGE.at(character1->getHit()));
				cout << character1->getHit() << endl;
				cout << character2->getLife() << endl;
			}
			character1->setHitDelay(character1->getHitDelay()-1);
			timer = SDL_GetTicks();
		}

	};
}

void Collider::update(MKCharacter* character1, MKCharacter* character2, bool cameraMoved) {

	if (!cameraMoved) {
		if (!(this->superpositionLeft(character1, character2) && this->superpositionUp(character1, character2) && character1->getMovement() == "RIGHT" ||
			this->superpositionRight(character1, character2) && this->superpositionUp(character1, character2) && character1->getMovement() == "LEFT")) {
			character1->move();
		};
		if (!(this->superpositionLeft(character2, character1) && this->superpositionUp(character2, character1) && character2->getMovement() == "RIGHT" ||
			this->superpositionRight(character2, character1) && this->superpositionUp(character2, character1) && character2->getMovement() == "LEFT")) {
			character2->move();
		};
	}

	this->checkHits(character1, character2);
	this->checkHits(character2, character1);
	
}
