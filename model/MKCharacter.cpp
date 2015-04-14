#include "MKCharacter.h"

MKCharacter::MKCharacter(float initialPosX, float initialPosY, float ancho, float alto, int z_index,
                            char* walkFile, char* stanceFile, char* jumpFile, char* sideJumpFile)
{

	//tamaño del png = 87*136

	this->z_index = z_index;
	posX = initialPosX;
	posY = initialPosY;
	stageFloor = initialPosY;

	step = 0.00714*Util::getInstance()->getLogicalWindowWidth();

	this->alto = alto;
	this->ancho = ancho;

	proporcionVel = 0.04285;
	accY = 1.2285*Util::getInstance()->getLogicalWindowHeight();;
	RestartJump();

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

void MKCharacter::RestartJump()
{
	velY = proporcionVel*Util::getInstance()->getLogicalWindowHeight();

	float winHeight = Util::getInstance()->getLogicalWindowHeight();

	//El numero 0.4954 salió de la proporcion entre la altura logica de la ventana y el y-piso del escenario (PosY inicial del psje)
	//encontrada en varios casos en los que saltaba bien.
	//cuanto mas abajo ponga el piso, mayor recorrido disponible dentro del escenario tendre.
	float proporcion = (winHeight - (winHeight - stageFloor)) * 0.4954;

	//para q no se vaya por arriba de la pantalla.
	if (stageFloor-proporcion < 0){
		limiteSuperior = 0;
	}
	else{
		limiteSuperior = stageFloor-proporcion;
	}

	//si quedo un limite sup menor a 60 es porq el salto es muy cortito. Lo agrando lo mas q pueda subiendo el limiteSup
	if (limiteSuperior < 90)
	{
		limiteSuperior = 0;
	}
}

void MKCharacter::moveUp() {

	if (posY > (limiteSuperior) && posY <= (stageFloor+1))
	{
		float time = 0.003;
//		cout << "PosY:" << posY << " Vel: " << velY << " accY: " << accY << " limiteSuperior: " << limiteSuperior  << " stageFloor - limiteSup: " << stageFloor - limiteSuperior << " y-pisp px: " << stageFloor * Util::getInstance()->getScalingYConstant() << endl;

		velY = velY - accY * time;

		posY = posY - velY;
	}
	else if (posY <= limiteSuperior)
	{
		velY = (-1)* velY;
		posY = limiteSuperior + 1;
	}
	else
	{
		posY = this->stageFloor;
		RestartJump();
		this->setJump(false);
	}
}

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
