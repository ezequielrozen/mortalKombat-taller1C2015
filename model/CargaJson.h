#ifndef CARGAJSON_H_
#define CARGAJSON_H_
#include <string>
#include <fstream>
#include "constantes.h"


//Abre el archivo recibido por path, lo abre y carga el Json.
// Devuelve 1 si estuvo OK, Devuelve 0 si hubo error.
bool cargaArchivoJSON(char* filename, int &screenWidth, int &screenHeight,
                        float &charAncho, float &charAlto, float &stageWidth, float &stageHeight,
                        float &floor, string &oponentSide);



#endif /* CARGAJSON_H_ */
