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
bool cargaArchivoJSON(char* filename, int &screenWidth, int &screenHeight, float &LogicalScreenWidth,
                        float &charAncho, float &charAlto, float &stageWidth, float &stageHeight,
                        float &floor, string &oponentSide, std::list<Layer*> *layers, int &z_index);


#endif /* CARGAJSON_H_ */
