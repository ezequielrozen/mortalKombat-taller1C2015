#include "json/json.h"
#include "constantes.h"
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>


bool cargaArchivoJSON(char* filename, int &screenWidth, int &screenHeight,
                        float &charAncho, float &charAlto, float &stageWidth,
						float &stageHeight, float &floor, std::string &oponentSide){


	Json::Value root;   // will contains the root value after parsing.
	Json::Reader reader;
	std::ifstream test(filename, std::ifstream::binary);
	bool parsingSuccessful = reader.parse( test, root, false );
	if ( !parsingSuccessful )
	{
		//report to the user the failure and their locations in the document.
		std::cout  << reader.getFormatedErrorMessages() << "\n";

		return false;
	}

	std::string encoding = root.get("encoding", "UTF-8" ).asString();
	std::cout << encoding << "\n";

	std::cout << "----------Ventana-------" << "\n";
	const Json::Value ventana = root["ventana"];

//		std::cout << ventana["ancho-px"] << "\n";
//		std::cout << ventana["alto-px"] << "\n";
	screenWidth = ventana["ancho-px"].asInt();
	screenHeight = ventana["alto-px"].asInt();

	std::cout << ventana["ancho"] << "\n";

	std::cout << "----------Escenario-------" << "\n";
	const Json::Value escenarios = root["escenario"];
	stageHeight = escenarios["alto"].asFloat();
	stageWidth = escenarios["ancho"].asFloat();
	floor = escenarios["y-piso"].asFloat();
	std::cout << escenarios["alto"] << "\n";
	std::cout << escenarios["ancho"] << "\n";
	std::cout << escenarios["y-piso"] << "\n";

	std::cout << "----------Capas-------" << "\n";

	//std::cout << root["capas"] << "\n";
	const Json::Value capas = root["capas"];
	for ( unsigned int index = 0; index < capas.size(); ++index ){
		std::cout << capas[index]["imagen_fondo"] << "\n";
		std::cout << capas[index]["ancho"] << "\n";
	}

	std::cout << "--------Personaje-------" << "\n";

	const Json::Value personaje = root["personaje"];
//		std::cout << personaje["ancho"] << "\n";
//		std::cout << personaje["alto"] << "\n";

	charAncho = personaje["ancho"].asFloat();
	charAlto  = personaje["alto"].asFloat();

	if(charAncho == 0.0){
		std::cout << "valor ancho del personaje invalido: usando default" << std::endl;
		charAncho = ANCHOPERSONAJE;
	}
	if(charAlto  == 0.0){
		std::cout << "valor alto del personaje invalido: usando default" << std::endl;
		charAlto  = ALTOPERSONAJE;
	}

	std::cout << personaje["z-index"] << "\n";
	std::cout << personaje["sprites"] << "\n";

	std::cout << "--------oponente-------" << "\n";
	std::string side;
	const Json::Value oponente = root["oponente"];
	side = oponente["side"].asString();
	std::transform(side.begin(), side.end(),side.begin(), ::toupper);
	if (side == "LEFT")
	{
		oponentSide="LEFT";
	}
	else if (side == "RIGHT")
	{
		oponentSide="RIGHT";
	}
	else
	{
		std::cout << "Ubicacion del oponente invalida: usando default (RIGHT)" << std::endl;
		oponentSide="RIGHT";
	}
	return true;

}



