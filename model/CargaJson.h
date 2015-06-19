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
                      double& initialH, double& finalH, double& offset, std::vector<Events>* combo1,
                      std::vector<Events>* combo2,std::vector<Events>* combo3,std::vector<Events>* combo4,
                      std::vector<Events>* combo5,std::vector<Events>* combo6, std::vector<Events>* fatality);

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

void cargarCombos(Json::Value combos,
                  vector<Events>* combo1,
                  vector<Events>* combo2,
                  vector<Events>* combo3,
                  vector<Events>* combo4,
                  vector<Events>* combo5,
                  vector<Events>* combo6,
                  vector<Events>* fatality);

void procesarComboBuilders(string builderCombo1,
                           string buildercombo2,
                           string buildercombo3,
                           string buildercombo4,
                           string buildercombo5,
                           string buildercombo6,
                           string builderfatality,
                           vector<Events>* combo1,
                           vector<Events>* combo2,
                           vector<Events>* combo3,
                           vector<Events>* combo4,
                           vector<Events>* combo5,
                           vector<Events>* combo6,
                           vector<Events>* fatality);


void cargarCombosDefaults(vector<Events>* combo1,
                          vector<Events>* combo2,
                          vector<Events>* combo3,
                          vector<Events>* combo4,
                          vector<Events>* combo5,
                          vector<Events>* combo6,
                          vector<Events>* fatality);

void buildCombo(string builderCombo, vector<Events>* combo);

bool sonPrefijos(vector<Events>* combo1, vector<Events>* combo2);
#endif /* CARGAJSON_H_ */
