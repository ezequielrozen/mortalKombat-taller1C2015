#include "json/json.h"
#include <fstream>
#include <iostream>

bool cargaArchivoJSON(char* filename, int &screenWidth, int &screenHeight,
                        float &charAncho, float &charAlto){


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

		std::cout << escenarios["alto"] << "\n";
		std::cout << escenarios["ancho"] << "\n";
		std::cout << escenarios["y-piso"] << "\n";

		std::cout << "----------Capas-------" << "\n";

		//std::cout << root["capas"] << "\n";
		const Json::Value capas = root["capas"];
		for ( int index = 0; index < capas.size(); ++index ){
			std::cout << capas[index]["imagen_fondo"] << "\n";
			std::cout << capas[index]["ancho"] << "\n";
		}

		std::cout << "--------Personaje-------" << "\n";

		const Json::Value personaje = root["personaje"];
//		std::cout << personaje["ancho"] << "\n";
//		std::cout << personaje["alto"] << "\n";

		charAncho = personaje["ancho"].asFloat();
		charAlto  = personaje["alto"].asFloat();

		std::cout << personaje["z-index"] << "\n";
		std::cout << personaje["sprites"] << "\n";

		return true;

    }



