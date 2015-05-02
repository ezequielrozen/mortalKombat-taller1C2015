#include "Collider.h"


Collider::Collider() {

}

Collider::~Collider() {

}

void Collider::update(MKCharacter* character1, MKCharacter* character2, bool cameraMoved) {

	if ((!((character1->getX()+character1->getWidth() >= character2->getX() && character1->getMovement() == "RIGHT" && character1->getX() < character2->getX()) || (character1->getX() <= character2->getX()+character2->getWidth() && character1->getMovement() == "LEFT" && character1->getX() > character2->getX()))) && !(cameraMoved))
	{
		character1->Update();
	}		

}