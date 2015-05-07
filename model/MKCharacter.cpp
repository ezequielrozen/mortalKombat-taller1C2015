#include "MKCharacter.h"

MKCharacter::MKCharacter(float initialPosX, float initialPosY, float ancho, float alto, int z_index, int pCharacterNumber) {

	this->z_index = z_index;
	posX = initialPosX;
	posY = initialPosY;
	stageFloor = initialPosY;

	step = 0.00714 * Util::getInstance()->getLogicalWindowWidth();

	this->alto = alto;
	this->ancho = ancho;

	//proporcionVel = 0.04285;
	//accY = 1.2285 * Util::getInstance()->getLogicalWindowHeight();

	//RestartJump();

	jumpTime = 0;
	//El 1.20 esta para que el personaje salte al otro personaje y 0.2 mas, para tener un margen.
	yMax = stageFloor - (this->alto)*1.20;
	//Se dedujo empiricamente
	velY = 6.4 * (this->alto);
	//Parte de la ecuacion de tiro vertical. El 0.5 sale de que el salto total dura 1seg, por lo cual al punto maximo del salto llega en 0.5seg
	accY = (-2*(yMax-stageFloor+velY*0.5))/(pow(0.5,2));

	movement = "NONE";
	jumpMovement = "NONE";
	jumping = false;

	this->life = 100;

	this->characterNumber = pCharacterNumber;

}

MKCharacter::~MKCharacter(void) {
}

void MKCharacter::move() {
	if (movement == "RIGHT" || movement == "PUNCHJUMPRIGHT") {
		this->moveRight();
	} else if (movement == "LEFT"  || movement == "PUNCHJUMPLEFT") {
		this->moveLeft();
	}
}

void MKCharacter::UpdateJump() {

	if (this->isJumping()) {
		this->moveUp();
	}
}

void MKCharacter::moveRight() {
	//Verifico que no se vaya de la pantalla por derecha
	if ((posX + step + getWidth() < Util::getInstance()->getLogicalWindowWidth())) {
		posX = posX + step;
	}
}

void MKCharacter::moveLeft() {
	//Verifico que no se vaya de la pantalla por izquierda
	if ((posX - step + getWidth() > getWidth())) {
		posX = posX - step;
	}
}
/*
void MKCharacter::RestartJump() {
	velY = proporcionVel * Util::getInstance()->getLogicalWindowHeight();

	float winHeight = Util::getInstance()->getLogicalWindowHeight();

	//El numero 0.4954 salió de la proporcion entre la altura logica de la ventana y el y-piso del escenario (PosY inicial del psje)
	//encontrada en varios casos en los que saltaba bien.
	//cuanto mas abajo ponga el piso, mayor recorrido disponible dentro del escenario tendre.
	float proporcion = (winHeight - (winHeight - stageFloor)) * 0.4954;

	//para q no se vaya por arriba de la pantalla.
	if (stageFloor - proporcion < 0) {
		limiteSuperior = 0;
	} else {
		limiteSuperior = stageFloor - proporcion;
	}

	//si quedo un limite sup menor a 60 es porq el salto es muy cortito. Lo agrando lo mas q pueda subiendo el limiteSup
	if (limiteSuperior < 90) {
		limiteSuperior = 0;
	}
}

void MKCharacter::moveUp() {

	if (posY > (limiteSuperior) && posY <= (stageFloor + 1)) {
		float time = 0.003;
//		cout << "PosY:" << posY << " Vel: " << velY << " accY: " << accY << " limiteSuperior: " << limiteSuperior  << " stageFloor - limiteSup: " << stageFloor - limiteSuperior << " y-pisp px: " << stageFloor * Util::getInstance()->getScalingYConstant() << endl;

		velY = velY - accY * time;

		posY = posY - velY;
	} else if (posY <= limiteSuperior) {
		velY = (-1) * velY;
		posY = limiteSuperior + 1;
	} else {
		posY = this->stageFloor;
		RestartJump();
		this->setJump(false);
	}
}
*/

void MKCharacter::moveUp() {
	jumpTime = jumpTime + 0.015;

	//double velPrev = actualVel;
	//double yMaxShow;

	posY = stageFloor - velY*jumpTime - (accY*pow(jumpTime,2))/2;
	//actualVel = velY + accY*jumpTime;
	//cout << "PosY: " << posY << " velY: " << actualVel << " time: " << jumpTime << endl;

	/*if (velPrev >= 0 && actualVel <= 0) {
		yMaxShow = posY;
		cout << "yMaxShow: " << yMaxShow << endl;
	}*/
	if (posY <= 0) {
		double time1;
		double time2;

		time1 = (velY + sqrt(pow(velY,2)-4*(-accY/2)*stageFloor))/(-accY);
		time2 = (velY - sqrt(pow(velY,2)-4*(-accY/2)*stageFloor))/(-accY);

		jumpTime = fmax(time1, time2);
	}
	
	if (posY > stageFloor) {
		this->setJump(false);
		posY = stageFloor;
		jumpTime = 0;
		//cout << "yMax: " << yMax << endl;
	}
}

//PASAR A FLOAT
float MKCharacter::getWidth() {
	return this->ancho;
}

//PASAR A FLOAT
float MKCharacter::getHeight() {
	return this->alto;
}

double MKCharacter::getX() {
	return posX;
}

double MKCharacter::getY() {
	return posY;
}

string MKCharacter::getMovement() {
	return movement;
}

void MKCharacter::setMovement(string newMovement) {

	if (!this->isJumping()) {
		this->movement = newMovement;
	}
}

void MKCharacter::setJump(bool jump) {
	this->jumping = jump;

	this->setJumpMovement(this->movement);
}

bool MKCharacter::isJumping() {
	return this->jumping;
}

string MKCharacter::getJumpMovement() {
	return this->jumpMovement;
}

void MKCharacter::setJumpMovement(string jumpMove) {
	this->jumpMovement = jumpMove;
}

int MKCharacter::getZ_index() {
	return this->z_index;
}


int MKCharacter::getLife() {
	return this->life;
}

void MKCharacter::setLife(int life) {
	if (life > 0)
		this->life = life;
	else
		this->life = 100;
}

char* MKCharacter::getFileMovement(const char* moveName){
	std::list<Util::charactersFile*>::iterator it = Util::getInstance()->getCharacterMovements()->begin();

	for(it; it != Util::getInstance()->getCharacterMovements()->end(); it++) {

		if (strcmp(((*it)->movementName),moveName) == 0 && (*it)->characterNumber == this->characterNumber)		{
			return ((*it)->fileName);
		}
	}
}

bool MKCharacter::isAlive() {
	return this->life > 0;

}
void MKCharacter::receiveBlow(int force) {
	extern logger* Mylog;
	this->life = this->life - force;
	Mylog->Log("Personaje (PONERLE NOMBRE) recibe golpe", ERROR_LEVEL_INFO); //FALTA: nombre, vida restada, vida restante.
	if (this->life <= 0) {
		//marcar fin de juego. Preferentemente donde se invoca esta función (control de colisión y golpe)
	}
}
