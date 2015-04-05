#include "CargaJson.h"
using namespace std;



bool cargaArchivoJSON(char* filename, int &screenWidth, int &screenHeight, float &logicalScreenWidth,
                        float &charAncho, float &charAlto, float &stageWidth,
						float &stageHeight, float &floor, std::string &oponentSide,
						std::list<Layer*>* layers){

    extern logger* Mylog;
    char mensaje[200];
    strcpy(mensaje, "Intentando parsear archivo ");
    strcat(mensaje, filename);
    Mylog->Log(mensaje, ERROR_LEVEL_INFO);

    //verificar si existe filename
    if(!std::ifstream(filename)){
        strcpy(mensaje, "No existe el archivo ");
        strcat(mensaje, filename);
        Mylog->Log(mensaje, ERROR_LEVEL_ERROR);
        return false;
    }


	Json::Value root;   // will contains the root value after parsing.
	Json::Reader reader;
	std::ifstream test(filename, std::ifstream::binary);
	bool parsingSuccessful = reader.parse( test, root, false );
	if ( !parsingSuccessful )
	{
		//report to the user the failure and their locations in the document.
		Mylog->Log(reader.getFormatedErrorMessages().c_str(), ERROR_LEVEL_ERROR);
		return false;
	}

	Mylog->Log("----------Ventana-------", ERROR_LEVEL_INFO);
	const Json::Value ventana = root["ventana"];

	screenWidth = ventana["ancho-px"].asInt();
	screenHeight = ventana["alto-px"].asInt();
	logicalScreenWidth = ventana["ancho"].asFloat();

    strcpy(mensaje, "ancho-px: ");
    strcat(mensaje, ventana["ancho-px"].asString().c_str());
    strcat(mensaje, ", alto-px: ");
    strcat(mensaje, ventana["alto-px"].asString().c_str());
    strcat(mensaje, ", ancho logico: ");
    strcat(mensaje, ventana["ancho"].asString().c_str());
    Mylog->Log(mensaje, ERROR_LEVEL_INFO);

	Mylog->Log("----------Escenario-------", ERROR_LEVEL_INFO);
	const Json::Value escenarios = root["escenario"];
	stageHeight = escenarios["alto"].asFloat();
	stageWidth = escenarios["ancho"].asFloat();
	floor = escenarios["y-piso"].asFloat();

    strcpy(mensaje, "alto: ");
    strcat(mensaje, escenarios["alto"].asString().c_str());
    strcat(mensaje, ", ancho: ");
    strcat(mensaje, escenarios["ancho"].asString().c_str());
    strcat(mensaje, ", y-piso: ");
    strcat(mensaje, escenarios["y-piso"].asString().c_str());
    Mylog->Log(mensaje, ERROR_LEVEL_INFO);


	Mylog->Log("----------Capas-------", ERROR_LEVEL_INFO);

	const Json::Value capas = root["capas"];
	for ( unsigned int index = 0; index < capas.size(); ++index ){
        strcpy(mensaje, "Capa ");
        strcat(mensaje, "%i");
        sprintf(mensaje, mensaje, index+1);

        strcat(mensaje, " imagen_fondo: ");
        strcat(mensaje, capas[index]["imagen_fondo"].asString().c_str());
        strcat(mensaje, ", ancho: ");
        strcat(mensaje, capas[index]["ancho"].asString().c_str());

        Mylog->Log(mensaje, ERROR_LEVEL_INFO);

		Layer* aLayer = new Layer(capas[index]["ancho"].asFloat(), capas[index]["imagen_fondo"].asCString());
		layers->push_back(aLayer);
	}

    if(layers->empty()){//no hay capas en el archivo
        Mylog->Log("sin capas validas: usando default", ERROR_LEVEL_ERROR);

        Mylog->Log("Capa 1: imagen_fondo: data/stage2.jpg, ancho: 1280", ERROR_LEVEL_ERROR);
        Layer* aLayer = new Layer(1280, "data/stage2.jpg");
        layers->push_back(aLayer);

        Mylog->Log("Capa 2: imagen_fondo: data/152.png, ancho: 266", ERROR_LEVEL_ERROR);
        Layer* subwayLayer = new Layer(266, "data/152.png");
        layers->push_back(subwayLayer);
    }

	Mylog->Log("--------Personaje-------", ERROR_LEVEL_INFO);

	const Json::Value personaje = root["personaje"];

	charAncho = personaje["ancho"].asFloat();
	charAlto  = personaje["alto"].asFloat();

    strcpy(mensaje, "alto: ");
    strcat(mensaje, personaje["alto"].asString().c_str());
    strcat(mensaje, ", ancho: ");
    strcat(mensaje, personaje["ancho"].asString().c_str());
    strcat(mensaje, ", z-index: ");
    strcat(mensaje, personaje["z-index"].asString().c_str());
    strcat(mensaje, ", sprites: ");
    strcat(mensaje, personaje["sprites"].asString().c_str());
    Mylog->Log(mensaje, ERROR_LEVEL_INFO);


	if(charAncho == 0.0){
		Mylog->Log("valor ancho del personaje invalido: usando default", ERROR_LEVEL_ERROR);
		charAncho = ANCHOPERSONAJE;
	}
	if(charAlto  == 0.0){
		Mylog->Log("valor alto del personaje invalido: usando default", ERROR_LEVEL_ERROR);
		charAlto  = ALTOPERSONAJE;
	}


	Mylog->Log("--------oponente-------", ERROR_LEVEL_INFO);
	std::string side;
	const Json::Value oponente = root["oponente"];
	side = oponente["side"].asString();
	std::transform(side.begin(), side.end(),side.begin(), ::toupper);
	if (side == "LEFT")
	{
		oponentSide="LEFT";
		Mylog->Log("Lado Izquierdo", ERROR_LEVEL_INFO);
	}
	else if (side == "RIGHT")
	{
		oponentSide="RIGHT";
		Mylog->Log("Lado Derecho", ERROR_LEVEL_INFO);
	}
	else
	{
		Mylog->Log("Ubicacion del oponente invalida: usando default (RIGHT)", ERROR_LEVEL_ERROR);
		oponentSide="RIGHT";
	}

	Mylog->Log("Parseo completo", ERROR_LEVEL_INFO);
	return true;

}



