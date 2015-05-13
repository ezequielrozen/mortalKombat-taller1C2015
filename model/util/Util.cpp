#include "Util.h"

using namespace std;

Util* Util::instance = 0;
unsigned char Util::cantidadPersonajes = 0;

Util* Util::getInstance() {

    if (!instance) {
        instance = new Util();
    }
    return instance;
}

Util::Util()
{
	characterMovements = new list<charactersFile*>();
}

Util::~Util()
{
	std::list<Util::charactersFile*>::iterator it = characterMovements->begin();

	for(it; it != characterMovements->end(); it++) {

			delete (*it)->fileName;
			delete (*it)->movementName;

		delete (*it);
	}

	delete characterMovements;
}

unsigned char Util::getCantidadPersonajes()
{
	return cantidadPersonajes - 1;
}

void Util::setCantidadPersonajes()
{
	cantidadPersonajes++;
}

int Util::getWindowWidth() {
    return this->windowWidth;
}

int Util::getWindowHeight() {
    return this->windowHeight;
}

float Util::getLogicalWindowWidth() {
    return this->logicalWindowWidth;
}

float Util::getLogicalWindowHeight() {
    return this->logicalWindowHeight;
}

void Util::setWindowWidth(int width) {
    this->windowWidth = width;
}

void Util::setWindowHeight(int height) {
    this->windowHeight = height;
}

void Util::setLogicalWindowWidth(float logicalWidth) {
    this->logicalWindowWidth = logicalWidth;
}

void Util::setLogicalWindowHeight(float logicalHeight) {
    this->logicalWindowHeight = logicalHeight;
}

float Util::getScalingConstant() {
    return this->windowWidth/this->logicalWindowWidth;
}

float Util::getScalingYConstant() {
    return this->windowHeight/this->logicalWindowHeight;
}

float Util::getLogicalStageWidth() {
    return this->logicalStageWidth;
}

void Util::setLogicalStageWidth(float stageWidth) {
    this->logicalStageWidth = stageWidth;
}

void Util::addMovement(const char* moveName, const char* p)
{
	charactersFile *file = new charactersFile();
	file->movementName = new char();
	file->movementName = moveName;
	file->fileName = strdup(p);
	file->characterNumber = getCantidadPersonajes();
	characterMovements->push_back(file);
}

std::list<Util::charactersFile*>* Util::getCharacterMovements()
{
	return this->characterMovements;
}


unsigned char Util::getMapaDeCaracteres(int i){
    return this->mapaDeCaracteres[i];
}
void Util::setMapaDeCaracteres(unsigned char m, int i){
    this->mapaDeCaracteres[i] = m;
}

void Util::setInitialH(double d) {
    initialH = d;
}

void Util::setFinalH(double d) {
    finalH = d;
}

void Util::setOffset(double d) {
    offset = d;
}

double Util::getInitialH() {
    return initialH;
}

double Util::getFinalH() {
    return finalH;
}

double Util::getOffset() {
    return offset;
}
