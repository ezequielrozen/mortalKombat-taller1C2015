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
	//return (character1->getY()/*+character1->getHeight()*/ >= character2->getY());

	if (character1->isAscending()) {
		return (character1->getY()/*+character1->getHeight()*/ >= character2->getY());
	}
	else {
		return (character1->getY()+character1->getHeight() >= character2->getY());
	}
}

bool Collider::superpositionDown(MKCharacter* character1, MKCharacter* character2) {
	return (character1->getY()+(character1->getHeight()-character1->getStateHeight()) < character2->getY()+character2->getHeight());
}

bool Collider::superpositionDown(Weapon* weapon, MKCharacter* character2) {
	return (weapon->getPositionY() < character2->getY()+character2->getHeight());
}

bool Collider::superpositionLeft(Weapon* weapon, MKCharacter* character2) {
	return (weapon->getPositionX()+weapon->getWidth() >= character2->getX() && weapon->getPositionX() < character2->getX());
}

bool Collider::superpositionRight(Weapon* weapon, MKCharacter* character2) {
	return (weapon->getPositionX() <= character2->getX()+character2->getWidth() && weapon->getPositionX() > character2->getX());
}

void Collider::checkHits(MKCharacter* character1, MKCharacter* character2) {

	if (((superpositionRight(character1,character2) || superpositionLeft(character1, character2)) && (character1->isHitting()) && superpositionDown(character1, character2))
	|| ((superpositionRight(character1->getWeapon(), character2) || superpositionLeft(character1->getWeapon(), character2)) && character1->getWeapon()->isActive() && superpositionDown(character1->getWeapon(), character2))){
		if (character1->impacts()) {
			if (character1->getState() == "DuckingKickHitting" || (!character2->isBlocking() && !character2->isDucking())) {
				character2->receiveBlow(DAMAGE.at(character1->getState()),0);
				if (character1->getWeapon()->isActive()) {
					character1->getWeapon()->destroy();
					character1->getWeapon()->setImpact(false);
				}
			}
		}
	}
}
/*
			if (timer + 100 < SDL_GetTicks()) {
				if (character1->getHitDelay() == 0 && (!(character2->getHit() == "DEFENSE") || character1->getHit() == "KICKDOWN")) {
					if (!((character1->getHit() == "PUNCH" || character1->getHit() == "KICK" || character1->getHit() == "PUNCHUP") &&
						(character2->getMovement() == "DUCK"))) 
					{ 
						character2->receiveBlow(DAMAGE.at(character1->getHit()), 0);
					}
				}
				character1->setHitDelay(character1->getHitDelay()-1);
				timer = SDL_GetTicks();
			}
		}
	};
*/
	
/*
void Collider::update(MKCharacter* character1, MKCharacter* character2, bool cameraMoved) {

	if (!cameraMoved) {
		if (!(this->superpositionLeft(character1, character2) && this->superpositionUp(character1, character2) &&
																 character1->getMovement() == "RIGHT" ||
			  this->superpositionRight(character1, character2) && this->superpositionUp(character1, character2) &&
			  character1->getMovement() == "LEFT")) {
			character1->move();
		};
		if (!(this->superpositionLeft(character2, character1) && this->superpositionUp(character2, character1) &&
																 character2->getMovement() == "RIGHT" ||
			  this->superpositionRight(character2, character1) && this->superpositionUp(character2, character1) &&
			  character2->getMovement() == "LEFT")) {
			character2->move();
		};

		if ((this->superpositionLeft(character1, character2) && this->superpositionUp(character1, character2) &&
																character1->getMovement() == "RIGHT" ||
			 this->superpositionRight(character1, character2) && this->superpositionUp(character1, character2) &&
			 character1->getMovement() == "LEFT") &&
			character1->isJumping()) {
			if (character1->getX() + character1->getWidth() <= character2->getX() + (character2->getWidth() / 2)) {
				character1->moveLeft();
				character1->moveLeft();
			}
			else {
				character1->moveRight();
				character1->moveRight();
			}
		}

		if ((this->superpositionLeft(character2, character1) && this->superpositionUp(character2, character1) &&
																character2->getMovement() == "RIGHT" ||
			 this->superpositionRight(character2, character1) && this->superpositionUp(character2, character1) &&
			 character2->getMovement() == "LEFT") &&
			character2->isJumping()) {
			if (character2->getX() + character2->getWidth() <= character1->getX() + (character1->getWidth() / 2)) {
				character2->moveLeft();
				character2->moveLeft();
			}
			else {
				character2->moveRight();
				character2->moveRight();
			}
		}
	}

	//En caso de que los dos golpeen al mismo tiempo, se decide aleatoriamente quien pega primero.
	//En caso de que no golpeen al mismo tiempo, no tiene importancia.
	if (character1->isAlive() && character2->isAlive()) {
		int randomizer = rand() % 2;

		if (randomizer == 0) {
			this->checkHits(character1, character2);
			this->checkHits(character2, character1);
		}
		else {
			this->checkHits(character2, character1);
			this->checkHits(character1, character2);
		}
	}
	character1->characterUpdate();
	character2->characterUpdate();

}
*/

void Collider::update(MKCharacter* character1, MKCharacter* character2, bool cameraMoved) {

	if (!cameraMoved) {
		if (!(this->superpositionLeft(character1, character2) && this->superpositionUp(character1, character2) &&
			character1->isMovingRight() || this->superpositionRight(character1, character2) &&
			this->superpositionUp(character1, character2) &&  character1->isMovingLeft())) {
				character1->move();
		};
		if (!(this->superpositionLeft(character2, character1) && this->superpositionUp(character2, character1) &&
			 character2->isMovingRight() || this->superpositionRight(character2, character1) &&
			 this->superpositionUp(character2, character1) && character2->isMovingLeft())) {
				character2->move();
		};

		if ((this->superpositionLeft(character1, character2) && this->superpositionUp(character1, character2) &&
				character1->isMovingRight() || this->superpositionRight(character1, character2) &&
				this->superpositionUp(character1, character2) && character1->isMovingLeft()) &&	character1->isJumping()) {
				if (character1->getX() + character1->getWidth() <= character2->getX() + (character2->getWidth() / 2)) {
					character1->moveLeft();
					character1->moveLeft();
				}
				else {
					character1->moveRight();
					character1->moveRight();
				}
		}

		if ((this->superpositionLeft(character2, character1) && this->superpositionUp(character2, character1) &&
				character2->isMovingRight() || this->superpositionRight(character2, character1) &&
				this->superpositionUp(character2, character1) && character2->isMovingLeft()) &&	character2->isJumping()) {
				if (character2->getX() + character2->getWidth() <= character1->getX() + (character1->getWidth() / 2)) {
					character2->moveLeft();
					character2->moveLeft();
				}
				else {
					character2->moveRight();
					character2->moveRight();
				}
		}
	}

	//En caso de que los dos golpeen al mismo tiempo, se decide aleatoriamente quien pega primero.
	//En caso de que no golpeen al mismo tiempo, no tiene importancia.
	if (character1->isAlive() && character2->isAlive()) {
		int randomizer = rand() % 2;

		if (randomizer == 0) {
			this->checkHits(character1, character2);
			this->checkHits(character2, character1);
		}
		else {
			this->checkHits(character2, character1);
			this->checkHits(character1, character2);
		}
	}
	character1->characterUpdate();
	character2->characterUpdate();

}

