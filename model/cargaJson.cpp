#include "CargaJson.h"

using namespace std;

bool cargaArchivoJSON(char* filename, float &charAncho, float &charAlto, float &stageWidth,
						float &stageHeight, float &floor, std::string &oponentSide,
						std::list<Layer*>* layers, int &z_index/*, std::list<Layer*> *charSprites*/){

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

	if(root.isMember("ventana")){
        const Json::Value ventana = root["ventana"];

        Util::getInstance()->setWindowWidth( (ventana.isMember("ancho-px") && ventana["ancho-px"].isInt() ) ?
                                                        ventana["ancho-px"].asInt() : 0);
        Util::getInstance()->setWindowHeight( (ventana.isMember("alto-px") && ventana["alto-px"].isInt()) ?
                                                        ventana["alto-px"].asInt(): 0);
        Util::getInstance()->setLogicalWindowWidth( (ventana.isMember("ancho") && ventana["ancho"].isNumeric()) ?
                                                        ventana["ancho"].asFloat() : 0.0);
    }else{ //se usan 0s para que control de errores (abajo) se encargue de cargar default values
        Mylog->Log("JSON invalido: falta nodo ventana. Usando default", ERROR_LEVEL_ERROR);
        Util::getInstance()->setWindowWidth(0);
        Util::getInstance()->setWindowHeight(0);
        Util::getInstance()->setLogicalWindowWidth(0.0);
    }

    //control de errores ventana
    if( Util::getInstance()->getLogicalWindowWidth() == 0.0){
        Util::getInstance()->setLogicalWindowWidth(ANCHOVENTANAL);
        Mylog->Log("valor ancho logico de la ventana invalido: usando default", ERROR_LEVEL_WARNING);
    }
    if( Util::getInstance()->getWindowHeight() <= 0){
        Util::getInstance()->setWindowHeight(ALTOVENTANAPX);
        Mylog->Log("valor alto de la ventana invalido: usando default", ERROR_LEVEL_WARNING);
    }
    if( Util::getInstance()->getWindowWidth() <= 0){
        Util::getInstance()->setWindowWidth(ANCHOVENTANAPX);
        Mylog->Log("valor ancho de la ventana invalido: usando default", ERROR_LEVEL_WARNING);
    }
    sprintf(mensaje, "ancho-px: %i, alto px: %i, ancho: %f",
                Util::getInstance()->getWindowWidth(),
                Util::getInstance()->getWindowHeight(),
                Util::getInstance()->getLogicalWindowWidth()
    );
    Mylog->Log(mensaje, ERROR_LEVEL_INFO);



	Mylog->Log("----------Escenario-------", ERROR_LEVEL_INFO);
	if(root.isMember("escenario")){
        const Json::Value escenarios = root["escenario"];

        stageWidth = (escenarios.isMember("ancho") && escenarios["ancho"].isNumeric() ) ?
                                                        escenarios["ancho"].asFloat() : 0.0;

        stageHeight = (escenarios.isMember("alto") && escenarios["alto"].isNumeric() ) ?
                                                        escenarios["alto"].asFloat() : 0.0;

        floor = (escenarios.isMember("y-piso") && escenarios["y-piso"].isNumeric() ) ?
                                                        escenarios["y-piso"].asFloat() : 0.0;
	}else{ //se usan 0s para que control de errores (abajo) se encargue de cargar default values
        Mylog->Log("JSON invalido: falta nodo ventana. Usando default", ERROR_LEVEL_ERROR);

        stageWidth = 0.0 ;
        stageHeight = 0.0;
        floor = 0.0;
    }

    //control de errores escenario
    if( stageWidth == 0.0){
        stageWidth = ANCHOESCENARIO;
        Mylog->Log("valor ancho de escenario invalido: usando default", ERROR_LEVEL_WARNING);
    }
    if( stageHeight <= 0){
        stageHeight = ALTOESCENARIO;
        Mylog->Log("valor alto de escenario invalido: usando default", ERROR_LEVEL_WARNING);
    }
    if( floor <= 0){
        floor = ALTURAPISOESCENARIO;
        Mylog->Log("valor altura piso invalido: usando default", ERROR_LEVEL_WARNING);
    }
    sprintf(mensaje, "ancho-px: %f, alto px: %f, ancho: %f", stageWidth, stageHeight, floor);
    Mylog->Log(mensaje, ERROR_LEVEL_INFO);


    //*****************************

	Mylog->Log("----------Capas-------", ERROR_LEVEL_INFO);

    if(root.isMember("capas") && root["capas"].isArray()){
        const Json::Value capas = root["capas"];
        for ( unsigned int index = 0; index < capas.size(); ++index ){

            //*****************************

            // VALIDAR QUE EL ANCHO Y LA IMAGEN SEAN CORRECTAS (QUE SEA NUMERO VALIDO EL ANCHO O QUE LA IMAGEN EXISTA
            // DE LO CONTRARIO, PONER POR DEFECTO)

            //*****************************
            if(!capas[index].isMember("imagen_fondo") || !capas[index].isMember("ancho")){
                Mylog->Log("Archivo JSON invalido: capas mal formadas", ERROR_LEVEL_ERROR);
                break;
            }

            const char* filenameIMG = capas[index]["imagen_fondo"].asCString();

            //verificar si existe filename
            if(!std::ifstream(filenameIMG)){
                sprintf(mensaje, "No existe el archivo %s. Usando fileNotFound.png", filenameIMG);
                Mylog->Log(mensaje, ERROR_LEVEL_ERROR);
                filenameIMG = "data/fileNotFound.png";
            }
            strcpy(mensaje, "Capa ");
            strcat(mensaje, "%i");
            sprintf(mensaje, mensaje, index+1);
            strcat(mensaje, " imagen_fondo: ");
            strcat(mensaje, filenameIMG);
            strcat(mensaje, ", ancho: ");
            strcat(mensaje, capas[index]["ancho"].asString().c_str());

            Mylog->Log(mensaje, ERROR_LEVEL_INFO);

            Layer* aLayer = new Layer(capas[index]["ancho"].asFloat(), filenameIMG);
            layers->push_back(aLayer);
        }

	}

    if(layers->empty()){//no hay capas en el archivo
        Mylog->Log("sin capas validas: usando default", ERROR_LEVEL_WARNING);

        Mylog->Log("Capa 1: imagen_fondo: data/stage2.jpg, ancho: 1280", ERROR_LEVEL_WARNING);
        Layer* aLayer = new Layer(1280, "data/stage2.jpg");
        layers->push_back(aLayer);

        Mylog->Log("Capa 2: imagen_fondo: data/152.png, ancho: 266", ERROR_LEVEL_WARNING);
        Layer* subwayLayer = new Layer(266, "data/152.png");
        layers->push_back(subwayLayer);
    }

	Mylog->Log("--------Personaje-------", ERROR_LEVEL_INFO);

	if(root.isMember("personaje")){
        const Json::Value personaje = root["personaje"];
        //*****************************
        // AGREGAR LO DE LOS SPRITES. VA A VENIRME UN ARRAY CON PATH A LOS SPRITES DEL PERSONAJE. CUANDO SE LEVANTAN
        // DEL JSON HAY QUE CARGARLOS EN SDL EN VEZ DEL PATH QUE ESTA HARCODEADO AHORA (MODIFICARLO).
        // VALIDAR QUE LA RUTA EXISTE, SINO PONER POR DEFECTO LA IMAGEN DE UN SIGNO DE PREGUNTA...PORQUE VAN A HACER LA PRUEBA DE PONER
        // UNA RUTA QUE NO EXISTE. LOGUEAR TODO ESTO TAMBIEN.
        //*****************************

         charAlto = (personaje.isMember("alto") && personaje["alto"].isNumeric() ) ?
                                                        personaje["alto"].asFloat() : 0.0;
         charAncho = (personaje.isMember("ancho") && personaje["ancho"].isNumeric() ) ?
                                                        personaje["ancho"].asFloat() : 0.0;
         z_index = (personaje.isMember("z-index") && personaje["z-index"].isInt() ) ?
                                                        personaje["z-index"].asFloat() : 0;

//        if(personaje.isMember("sprites"){
//            const Json::Value sprites = personaje["sprites"];
//             if(!sprites.isMember("walk")){
//                Mylog->Log("Archivo JSON invalido: capas mal formadas", ERROR_LEVEL_ERROR);
//                break;
//            }
//
//            const char* filenameIMG = sprites[index]["imagen"].asCString();
//
//            //verificar si existe filename
//            if(!std::ifstream(filenameIMG)){
//                sprintf(mensaje, "No existe el archivo %s. Usando fileNotFound.png", filenameIMG);
//                Mylog->Log(mensaje, ERROR_LEVEL_ERROR);
//                filenameIMG = "data/fileNotFound.png";
//            }
//            strcpy(mensaje, "Sprite ");
//            strcat(mensaje, "%i");
//            sprintf(mensaje, mensaje, index+1);
//            strcat(mensaje, " imagen: ");
//            strcat(mensaje, filenameIMG);
//
//            Mylog->Log(mensaje, ERROR_LEVEL_INFO);
//
//            //TODO: pasar al generador de escenario
//            Layer* aLayer = new Layer(charWidth, filenameIMG);
//            charSprites->push_back(aLayer);
//        }
    }




    //*****************************
    // ANTES DE LOGGEAR ESTO, TAL VEZ ES MEJOR VERIFICAR QUE LOS NUMEROS SON ALGO VALIDO, PQ SINO ES MEJOR
    // AVISAR QUE POR EJ EL ANCHO ES INVALIDO, Y QUE SE VA A USAR EL DEFAULT, Y DESPUES LOGUEAR LA INFO CORRECTA
    // CON TODO ESTO.
//
//    strcpy(mensaje, "alto: ");
//    strcat(mensaje, charAlto);
//    strcat(mensaje, ", ancho: ");
//    strcat(mensaje, charAncho);
//    strcat(mensaje, ", z-index: ");
//    strcat(mensaje, z_index);
//    strcat(mensaje, ", sprites: ");
//    strcat(mensaje, personaje["sprites"].asString().c_str());
//    Mylog->Log(mensaje, ERROR_LEVEL_INFO);
    //*****************************


    if(charAlto == 0.0 || charAncho == 0.0){
        Mylog->Log("--------Personaje-------", ERROR_LEVEL_ERROR);
        Mylog->Log("--------Personaje-------", ERROR_LEVEL_WARNING);

        if(charAncho == 0.0){
            charAncho = ANCHOPERSONAJE;

            // LOGGEO NIVEL DEBUG
            Mylog->Log("valor ancho del personaje invalido: usando default", ERROR_LEVEL_INFO);
            strcpy(mensaje, "ancho : ");
            strcat(mensaje, "%charAncho");
            Mylog->Log(mensaje, ERROR_LEVEL_INFO);

            // LOGGEO NIVEL WARNING
            Mylog->Log("----------Capas-------", ERROR_LEVEL_WARNING);
            Mylog->Log("valor ancho del personaje invalido: usando default", ERROR_LEVEL_WARNING);
            strcpy(mensaje, "ancho : ");
            strcat(mensaje, "%charAncho");
            Mylog->Log(mensaje, ERROR_LEVEL_WARNING);

            //LOGGEO NIVEL ERRORES
            Mylog->Log("valor ancho del personaje invalido: usando default", ERROR_LEVEL_ERROR);

        }
        if(charAlto  == 0.0){
            charAlto  = ALTOPERSONAJE;

            // LOGGEO NIVEL DEBUG
            Mylog->Log("valor alto del personaje invalido: usando default", ERROR_LEVEL_INFO);
            strcpy(mensaje, "alto : ");
            strcat(mensaje, "%charAlto");
            Mylog->Log(mensaje, ERROR_LEVEL_INFO);

            // LOGGEO NIVEL WARNING
            Mylog->Log("----------Capas-------", ERROR_LEVEL_WARNING);
            Mylog->Log("valor ancho del personaje invalido: usando default", ERROR_LEVEL_WARNING);
            strcpy(mensaje, "alto : ");
            strcat(mensaje, "%charAlto");
            Mylog->Log(mensaje, ERROR_LEVEL_WARNING);

            //LOGGEO NIVEL ERRORES
            Mylog->Log("valor alto del personaje invalido: usando default", ERROR_LEVEL_ERROR);

        }

        //*****************************
        // FALTA HACER LAS VALIDACIONES DEL Z-INDEX Y DEL SPRITES
        //*****************************

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
        Mylog->Log("Ubicacion del oponente invalida: usando default (RIGHT)", ERROR_LEVEL_INFO);
        Mylog->Log("Ubicacion del oponente invalida: usando default (RIGHT)", ERROR_LEVEL_WARNING);
		oponentSide="RIGHT";
	}

	Mylog->Log("Parseo completo", ERROR_LEVEL_INFO);
	return true;

}



