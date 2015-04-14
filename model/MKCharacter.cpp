#include "MKCharacter.h"

MKCharacter::MKCharacter(float initialPosX, float initialPosY, float ancho, float alto, int z_index,
                            char* walkFile, char* stanceFile, char* jumpFile, char* sideJumpFile)
{

	//tamaño del png = 87*136
	//timeCheck = SDL_GetTicks();

	this->z_index = z_index;
	posX = initialPosX;
	posY = initialPosY;
	stageFloor = initialPosY;

	step = 0.00714*Util::getInstance()->getLogicalWindowWidth();

	this->alto = alto;
	this->ancho = ancho;

	proporcionVel = 0.04285;
	RestartSpeed();
//	velY = 0.04285*Util::getInstance()->getLogicalWindowWidth();
	accY = 1.2285*Util::getInstance()->getLogicalWindowHeight();;

	movement = "NONE";
	jumpMovement = "NONE";

	jumping = false;

	this->walk = walkFile;
    this->stance = stanceFile;
    this->jump = jumpFile;
    this->sideJump = sideJumpFile;

}

MKCharacter::~MKCharacter(void)
{
}

void MKCharacter::Update()
{
	if (movement == "RIGHT") {
		this->moveRight();
	}
	else if (movement == "LEFT") {
		this->moveLeft();
	}
}

void MKCharacter::UpdateJump() {

	if(this->isJumping()) {
		this->moveUp();
	}
}

void MKCharacter::moveRight() {
    //Verifico que no se vaya de la pantalla por derecha
    if(( posX + step + getWidth() < Util::getInstance()->getLogicalWindowWidth() ) )
    {
    	posX = posX + step;
    }

}

void MKCharacter::moveLeft() {
	//Verifico que no se vaya de la pantalla por izquierda
	if(( posX - step + getWidth() > getWidth() ) )
	{
		posX = posX - step;
	}

}

void MKCharacter::RestartSpeed()
{
	velY = proporcionVel*Util::getInstance()->getLogicalWindowHeight();
}

void MKCharacter::moveUp() {

	//El numero 0.4954 salió de la proporcion entre la altura logica de la ventana y el y-piso del escenario (PosY inicial del psje)
	//encontrada en varios casos en los que saltaba bien.
	float proporcion = (Util::getInstance()->getLogicalWindowHeight() - stageFloor) * 0.4954;

	//uso esta variable para controlar que no se vaya de la pantalla por arriba cuando ponen valores raros: "alto-px": 300; "alto": 300; y-piso: 50
	float limiteSuperior;

	if (stageFloor-proporcion < 0)
		limiteSuperior = 0;
	else
		limiteSuperior = stageFloor-proporcion;

	if (posY > (limiteSuperior) && posY <= (stageFloor+1))
	{
		float time = 0.003;
//		cout << "PosY:" << posY << " Vel: " << velY << " accY: " << accY << " limitePosY: " << stageFloor-proporcion  << endl;

		velY = velY - accY * time;

		posY = posY - velY;
	}
	else
	{
		posY = this->stageFloor;
		RestartSpeed();
		this->setJump(false);
	}
}

//void MKCharacter::moveUp() {
//
//	if (posY > (0.0571*Util::getInstance()->getLogicalWindowWidth()) && posY <= (0.2871*Util::getInstance()->getLogicalWindowWidth()))
//	{
//		float time = 0.003;
//
//		//cout << "PosY:" << posY << "  Vel: " << velY << "   Time: " << time << " movement: " << movement << endl;
//		char buffer[500];
//        snprintf(buffer, sizeof(buffer), "personaje salta : PosY: %g, vel: %g, Time: %g, Movement: %s", posY, velY, time, movement.c_str());
//        extern logger* Mylog;
//    	Mylog->Log(buffer, ERROR_LEVEL_INFO);
//
//		velY = velY - accY * time;
//
//		posY = posY - velY;
//	}
//
//	if (velY <= (0.04285*Util::getInstance()->getLogicalWindowWidth()*0.04 - 0.04285*Util::getInstance()->getLogicalWindowWidth())) {
//		posY = this->stageFloor;
//		velY = 0.04285*Util::getInstance()->getLogicalWindowWidth();
//		this->setJump(false);
//	}
//}

//PASAR A FLOAT
float MKCharacter::getWidth(){
	return this->ancho;
}

//PASAR A FLOAT
float MKCharacter::getHeight(){
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


char* MKCharacter::getWalk(){return this->walk;}
char* MKCharacter::getStance(){return this->stance;}
char* MKCharacter::getJump(){return this->jump;}
char* MKCharacter::getSideJump(){return this->sideJump;}
