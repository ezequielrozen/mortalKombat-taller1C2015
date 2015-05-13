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

void Collider::checkHits(MKCharacter* character1, MKCharacter* character2) {
	if ((superpositionRight(character1,character2) || superpositionLeft(character1, character2)) &&
		(!(character1->getHit() == "NONE")) && (!(character1->getHit() == "DEFENSE")) && (!(character1->getHit() == "BEINGHIT"))
		&& ((character1->getHit() != "SHOOT")) && ((character2->getHit() != "SHOOT"))) {
			if (timer + 100 < SDL_GetTicks()) {
//				cout << "hitDelay: " << character1->getHitDelay() << endl;
				if (character1->getHitDelay() == 0) {
					character2->receiveBlow(DAMAGE.at(character1->getHit()));
//					cout << character1->getHit() << endl;
//					cout << character2->getLife() << endl;
				}
				character1->setHitDelay(character1->getHitDelay()-1);
				timer = SDL_GetTicks();
			}
		};


	//Esto trabaja igual q la funcion double GameView::shootWidthCalculate(). Si se modifica aca se debe modificar tb alla.
	//Veo si llego a hacer contacto con la soga teniendo en cuenta q la estiro y la contraigo segun la distancia entre los personajes.
	double distancia;
	double distanciaMaxima = character1->getHitWidth() * 2;
	if (character1->getHit() == "SHOOT")
	{
		if (character1->getX() < character2->getX()){
			distancia = character2->getX() - (character1->getX() + character1->getHitWidth()-15);
		}
		else{
			distancia = character1->getX() - (character2->getX() + character2->getHitWidth()-15);
		}

		if (distancia <= distanciaMaxima)
		{
			if (timer + 100 < SDL_GetTicks()) {
//				cout << "hitDelay: " << character1->getHitDelay() << endl;
				if (character1->getHitDelay() == 0) {
					character2->receiveBlow(DAMAGE.at(character1->getHit()));
//					cout << character1->getHit() << endl;
//					cout << character2->getLife() << endl;
				}
				character1->setHitDelay(character1->getHitDelay()-1);
				timer = SDL_GetTicks();
			}
		}
	}


	//Esto trabaja igual q la funcion double GameView::shootWidthCalculate(). Si se modifica aca se debe modificar tb alla.
	//Veo si llego a hacer contacto con la soga teniendo en cuenta q la estiro y la contraigo segun la distancia entre los personajes.
	distancia;
	distanciaMaxima = character1->getHitWidth() * 5;
	if (character2->getHit() == "SHOOT")
	{
		if (character1->getX() < character2->getX()){
			distancia = character2->getX() - (character1->getX() + character1->getHitWidth());
		}
		else{
			distancia = character1->getX() - (character2->getX() + character2->getHitWidth());
		}

		if (distancia <= distanciaMaxima)
		{
			if (timer + 67 < SDL_GetTicks()) {
//				cout << "hitDelay: " << character1->getHitDelay() << endl;
				if (character2->getHitDelay() == 0) {
					character1->receiveBlow(DAMAGE.at(character2->getHit()));
//					cout << character1->getHit() << endl;
//					cout << character2->getLife() << endl;
				}
				character2->setHitDelay(character2->getHitDelay()-1);
				timer = SDL_GetTicks();
			}
		}
	}
}

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
		character1->update();
		character2->update();

}
