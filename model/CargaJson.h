#ifndef CARGAJSON_H_
#define CARGAJSON_H_
#include <string>
#include <fstream>


//Abre el archivo recibido por path, lo abre y carga el Json.
// Devuelve 1 si estuvo OK, Devuelve 0 si hubo error.
bool cargaArchivoJSON(char* filename);



#endif /* CARGAJSON_H_ */
