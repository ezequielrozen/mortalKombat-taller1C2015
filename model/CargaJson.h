#ifndef CARGAJSON_H_
#define CARGAJSON_H_
#include <string>
#include <fstream>
#include "constantes.h"
#include "json/json.h"
#include <list>
#include "Game.h"
#include <iostream>
#include <algorithm>
#include "logger.h"

using namespace std;


//Abre el archivo recibido por path, lo abre y carga el Json.
// Devuelve 1 si estuvo OK, Devuelve 0 si hubo error.
bool cargaArchivoJSON(char* filename, float &stageWidth, float &stageHeight, float &floor,
                      string &oponentSide, std::list<Layer*> *layers, std::list<MKCharacter*>* characters,
                      double& initialH, double& finalH, double& offset, std::list<Events>* combo1, std::list<Events>* combo2);

void cargaPersonaje(Json::Value personaje, std::list<MKCharacter*>* characters, int characterNumber);

void cargaVentana(Json::Value ventana);

void cargarVentanaPorDefault();

void controlErroresVentana();

void cargaEscenario(Json::Value escenarios, float &stageWidth, float &stageHeight, float &floor);

void cargaEscenarioPorDefault(float &stageWidth, float &stageHeight, float &floor);

void controlErroresEscenario(float &stageWidth, float &stageHeight, float &floor);

void validarExistenciaArchivo(const char* defaultFile,char* fileNameToValidate);

void loadPainter(Json::Value value, double& initialH, double& finalH, double& offset);

void loadDefautPainter(double& initialH, double& finalH, double& offset);

void errorPainterController(double& initialH, double& finalH, double& offset);

void cargaMapbotones(Json::Value botones, int default_);

void cargarCombos(Json::Value combos, list<Events>* combo1, list<Events>* combo2);

void procesarComboBuilders(string builderCombo1, string buildercombo2, list<Events>* combo1, list<Events>* combo2);

void cargarCombosDefaults(list<Events>* combo1, list<Events>* combo2);

void buildCombo(string builderCombo, list<Events>* combo);

bool sonPrefijos(list<Events>* combo1, list<Events>* combo2);
#endif /* CARGAJSON_H_ */
