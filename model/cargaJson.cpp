#include "CargaJson.h"
#include <algorithm>

using namespace std;

bool cargaArchivoJSON(char* filename, float &stageWidth, float &stageHeight, float &floor, std::string &oponentSide,
						std::list<Layer*>* layers, std::list<MKCharacter*>* characters, double& initialH, double& finalH, double& offset) {

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
        cargaVentana(root["ventana"]);
    }else{
        cargarVentanaPorDefault();
    }

    controlErroresVentana();

	Mylog->Log("----------Escenario-------", ERROR_LEVEL_INFO);
	stageWidth = 0.0;
	stageHeight = 0.0;
	floor = 0.0;

    const Json::Value escenarios = root["escenario"];

	if(root.isMember("escenario")){
        cargaEscenario(escenarios, stageWidth, stageHeight,floor);
	}else{
        cargaEscenarioPorDefault(stageWidth, stageHeight,floor);
	}

	controlErroresEscenario(stageWidth, stageHeight, floor);

    //*****************************

	Mylog->Log("----------Capas-------", ERROR_LEVEL_INFO);

    if(root.isMember("capas") && root["capas"].isArray()){
        const Json::Value capas = root["capas"];
        for ( unsigned int index = 0; index < capas.size(); ++index ){

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

            float capaAncho = (capas[index].isMember("ancho") && capas[index]["ancho"].isNumeric()  && capas[index]["ancho"].asFloat()>0) ? capas[index]["ancho"].asFloat() : 0.0;


            if( capaAncho == 0.0){
            	capaAncho = ANCHOESCENARIO;
                   Mylog->Log("valor ancho de capa invalido: usando default", ERROR_LEVEL_WARNING);
               }

            strcpy(mensaje, "Capa ");
            strcat(mensaje, "%i");
            sprintf(mensaje, mensaje, index+1);
            strcat(mensaje, " imagen_fondo: ");
            strcat(mensaje, filenameIMG);
            strcat(mensaje, ", ancho: ");
            strcat(mensaje, capas[index]["ancho"].asString().c_str());

            Mylog->Log(mensaje, ERROR_LEVEL_INFO);

            Layer* aLayer = new Layer(capaAncho, filenameIMG);
            layers->push_back(aLayer);
        }

	}

    if(layers->empty()){//no hay capas en el archivo
        Mylog->Log("sin capas validas: usando default", ERROR_LEVEL_WARNING);

        Mylog->Log("Capa 1: imagen_fondo: data/stage2.jpg, ancho: 1280", ERROR_LEVEL_WARNING);
        Layer* aLayer = new Layer(1000, "data/bg_2.png");
        layers->push_back(aLayer);

        Mylog->Log("Capa 2: imagen_fondo: data/152.png, ancho: 266", ERROR_LEVEL_WARNING);
        Layer* subwayLayer = new Layer(600, "data/bg_1.png");
        layers->push_back(subwayLayer);
    }

	Mylog->Log("--------Personaje-------", ERROR_LEVEL_INFO);


	if(root.isMember("personaje") && root["personaje"].isArray()){

        const Json::Value personaje = root["personaje"];

        Mylog->Log("----------Seleccion de personaje--------", ERROR_LEVEL_INFO);
        unsigned int cantidadDePersonajes = personaje.size();
        int j1elige;
        int j2elige;
        //verifico si existe, es entero positivo y está en rango.
        if(root.isMember("j1elige") && root["j1elige"].isUInt() && root["j1elige"].asInt() < cantidadDePersonajes){
            j1elige = root["j1elige"].asInt();
        }else{
            j1elige = 0;
        }
        if(root.isMember("j2elige") && root["j2elige"].isUInt() && root["j2elige"].asInt() < cantidadDePersonajes){
            j2elige = root["j2elige"].asInt();
        }else{
            j2elige=1;
        }
//        int index2 = 0;
        for ( unsigned int index = 0; index < personaje.size(); index++ ){
            if(index == j1elige){
                cargaPersonaje(personaje[index], characters, index);
//                index2++;
            }
        }
        for ( unsigned int index = 0; index < personaje.size(); index++ ){
            if(index == j2elige){
                cargaPersonaje(personaje[index], characters, index);
//                index2++;
            }
        }
//        for ( unsigned int index = 0; index < personaje.size(); index++ ){
//            if(index != j1elige && index != j2elige){
//                cargaPersonaje(personaje[index], characters, index2);
//                index2++;
//            }
//        }
    }else{
        //CARGAR POR DEFAULT
        cargaPersonaje(root, characters, 0); //root tiene escenario, capas, personaje, etc.
        cargaPersonaje(root, characters, 1);                    //no tiene propiedades como ancho, alto, etc.
                                                                //ver si hay forma mejor de hacerlo
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
		Mylog->Log("Ubicacion del oponente invalida: usando default (RIGHT)", ERROR_LEVEL_WARNING);
		oponentSide="RIGHT";
	}

    Mylog->Log("----------ColorAlternativo--------", ERROR_LEVEL_INFO);
    if (root.isMember("color-alternativo")) {
        loadPainter(root["color-alternativo"], initialH, finalH, offset);
    } else {
        loadDefautPainter(initialH, finalH, offset);
    }

    errorPainterController(initialH, finalH, offset);

    Mylog->Log("----------Botones----------", ERROR_LEVEL_INFO);
    if(root.isMember("botones")){
        cargaMapbotones(root["botones"], 0);
    }else{
        Mylog->Log("Cargando botones por default por no estar presente seccion en JSON", ERROR_LEVEL_INFO);
        cargaMapbotones(root, 1);
    }

    Mylog->Log("Parseo completo", ERROR_LEVEL_INFO);
    return true;
}

void errorPainterController(double& initialH, double& finalH, double& offset) {
    extern logger* Mylog;
    char message[200];
    if (initialH == -1) {
        initialH = DEFAULT_INITIAL_H;
        Mylog->Log("valor h-inicial invalido: usando default", ERROR_LEVEL_WARNING);
    }
    if (finalH == -1) {
        finalH = DEFAULT_FINAL_H;
        Mylog->Log("valor h-final invalido: usando default", ERROR_LEVEL_WARNING);
    }
    if (offset == -1) {
        offset = DEFAULT_OFFSET;
        Mylog->Log("valor offset invalido: usando default", ERROR_LEVEL_WARNING);
    }
    sprintf(message, "h-inicial: %1.2f, h-final: %1.2f, offset: %1.2f", initialH, finalH, offset);
    Mylog->Log(message, ERROR_LEVEL_INFO);
}

void loadDefautPainter(double& initialH, double& finalH, double& offset) {
    initialH = 0;
    finalH = 0;
    offset = 0;
}

void loadPainter(Json::Value painterOptions, double& initialH, double& finalH, double& offset) {
    initialH = painterOptions.isMember("h-inicial") && painterOptions["h-inicial"].isNumeric() &&
            painterOptions["h-inicial"].asDouble() > 0 ? painterOptions["h-inicial"].asDouble() : -1;
    finalH = painterOptions.isMember("h-final") && painterOptions["h-final"].isNumeric() &&
                      painterOptions["h-final"].asDouble() > 0 ? painterOptions["h-final"].asDouble() : -1;
    offset = painterOptions.isMember("desplazamiento") && painterOptions["desplazamiento"].isNumeric() &&
                      painterOptions["desplazamiento"].asInt() >= 0 ? painterOptions["desplazamiento"].asInt() : painterOptions["desplazamiento"].asInt();
}

void cargaPersonaje(Json::Value personaje, std::list<MKCharacter*>* characters, int characterNumber) {
    extern logger* Mylog;
    char mensaje[2000];
    char* filenameWalk = new char[200] ;
    char* filenameStance = new char[200];
    char* filenameJump = new char[200];
    char* filenameSideJump = new char[200];
    char* filenameDuck = new char[200];
    char* filenameKick = new char[200];
    char* filenameLowKick = new char[200];
    char* filenameKickDown = new char[200];
    char* filenameJumpKick = new char[200];
    char* filenamePunchJump = new char[200];
    char* filenamePunchUp = new char[200];
    char* filenamePunch = new char[200];
    char* filenameLowPunch = new char[200];
    char* filenameWinner = new char[200];
    char* filenameShoot = new char[200];
    char* filenameDizzy = new char[200];
    char* filenameFall = new char[200];
    char* filenameBeingHit = new char[200];
    char* filenameBeingHitDown = new char[200];
    char* filenameBlock = new char[200];
    char* filenameBlockDown = new char[200];

    string name = (personaje.isMember("name") && personaje["name"].isString()) ? personaje["name"].asString() : "";
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);

    float charAlto = (personaje.isMember("alto") && personaje["alto"].isNumeric() && personaje["alto"].asFloat()>0) ?
                                                    personaje["alto"].asFloat() : 0.0;
    float charAncho = (personaje.isMember("ancho") && personaje["ancho"].isNumeric() && personaje["ancho"].asFloat()>0) ?
                                                personaje["ancho"].asFloat() : 0.0;
    int z_index = (personaje.isMember("z-index") && personaje["z-index"].isInt() && personaje["z-index"].asInt()>0) ?
                                                        personaje["z-index"].asInt() : 0;

    if(personaje.isMember("sprites")){

        const Json::Value sprites = personaje["sprites"];


        if(!sprites.isMember("walk") || !sprites.isMember("stance")
                || !sprites.isMember("jump") || !sprites.isMember("sideJump")){
            Mylog->Log("Archivo JSON invalido: sprites mal formadas. Usando default", ERROR_LEVEL_ERROR);

            //CARGAR DEFAULT
            filenameWalk = strdup(DEFAULT_WALK);
            filenameStance = strdup(DEFAULT_STANCE);
            filenameJump = strdup(DEFAULT_JUMP);
            filenameSideJump = strdup(DEFAULT_SIDEJUMP);
            filenameDuck = strdup(DEFAULT_DUCK);
            filenameKick = strdup(DEFAULT_HIGH_KICK);
            filenameLowKick = strdup(DEFAULT_LOW_KICK);
            filenameKickDown = strdup(DEFAULT_DUCKING_KICK);
            filenameJumpKick = strdup(DEFAULT_JUMPING_KICK);
            filenamePunchJump = strdup(DEFAULT_JUMPING_PUNCH);
            filenamePunchUp = strdup(DEFAULT_DUCK_PUNCH);
            filenamePunch = strdup(DEFAULT_HIGH_PUNCH);
            filenameLowPunch = strdup(DEFAULT_LOW_PUNCH);
            filenameWinner = strdup(DEFAULT_WINNER);
            filenameShoot = strdup(DEFAULT_SHOOT);
            filenameDizzy = strdup(DEFAULT_DIZZY);
            filenameFall = strdup(DEFAULT_FALL);
            filenameBeingHit = strdup(DEFAULT_BEINGHIT);
            filenameBeingHitDown = strdup(DEFAULT_BEINGHIT_DOWN);
            filenameBlock = strdup(DEFAULT_BLOCK);
            filenameBlockDown = strdup(DEFAULT_BLOCKDOWN);


        }else{
            filenameWalk = strdup(sprites[MOVE_NAME_WALK].asString().c_str());
            filenameStance = strdup(sprites[MOVE_NAME_STANCE].asString().c_str());
            filenameJump = strdup(sprites[MOVE_NAME_JUMP].asString().c_str());
            filenameSideJump = strdup(sprites[MOVE_NAME_SIDEJUMP].asString().c_str());
            filenameDuck  = strdup(sprites[MOVE_NAME_DUCK].asString().c_str());
            filenameKick  = strdup(sprites[MOVE_NAME_HIGH_KICK].asString().c_str());
            filenameLowKick  = strdup(sprites[MOVE_NAME_LOW_KICK].asString().c_str());
            filenameKickDown  = strdup(sprites[MOVE_NAME_DUCKING_KICK].asString().c_str());
            filenameJumpKick  = strdup(sprites[MOVE_NAME_JUMPING_KICK].asString().c_str());
            filenamePunchJump  = strdup(sprites[MOVE_NAME_PUNCHJUMP].asString().c_str());
            filenamePunchUp  = strdup(sprites[MOVE_NAME_DUCK_PUNCH].asString().c_str());
            filenamePunch  = strdup(sprites[MOVE_NAME_HIGH_PUNCH].asString().c_str());
            filenameLowPunch  = strdup(sprites[MOVE_NAME_LOW_PUNCH].asString().c_str());
            filenameWinner  = strdup(sprites[MOVE_NAME_WINNER].asString().c_str());
            filenameShoot  = strdup(sprites[MOVE_NAME_SHOOT].asString().c_str());
            filenameDizzy  = strdup(sprites[MOVE_NAME_DIZZY].asString().c_str());
            filenameFall  = strdup(sprites[MOVE_NAME_FALL].asString().c_str());
            filenameBeingHit  = strdup(sprites[MOVE_NAME_BEINGHIT].asString().c_str());
            filenameBeingHitDown  = strdup(sprites[MOVE_NAME_BEINGHIT_DOWN].asString().c_str());
            filenameBlock  = strdup(sprites[MOVE_NAME_BLOCK].asString().c_str());
            filenameBlockDown  = strdup(sprites[MOVE_NAME_BLOCKDOWN].asString().c_str());
        }
    }

    //verificar si existe filename
    validarExistenciaArchivo(DEFAULT_WALK,filenameWalk);
    validarExistenciaArchivo(DEFAULT_STANCE, filenameStance);
    validarExistenciaArchivo(DEFAULT_JUMP, filenameJump);
    validarExistenciaArchivo(DEFAULT_SIDEJUMP, filenameSideJump);
    validarExistenciaArchivo(DEFAULT_DUCK, filenameDuck);
    validarExistenciaArchivo(DEFAULT_HIGH_KICK, filenameKick);
    validarExistenciaArchivo(DEFAULT_HIGH_KICK, filenameLowKick);
    validarExistenciaArchivo(DEFAULT_DUCKING_KICK, filenameKickDown);
    validarExistenciaArchivo(DEFAULT_JUMPING_KICK, filenameJumpKick);
    validarExistenciaArchivo(DEFAULT_JUMPING_PUNCH, filenamePunchJump);
    validarExistenciaArchivo(DEFAULT_DUCK_PUNCH, filenamePunchUp);
    validarExistenciaArchivo(DEFAULT_HIGH_PUNCH, filenamePunch);
    validarExistenciaArchivo(DEFAULT_LOW_PUNCH, filenameLowPunch);
    validarExistenciaArchivo(DEFAULT_WINNER, filenameWinner);
    validarExistenciaArchivo(DEFAULT_SHOOT, filenameShoot);
    validarExistenciaArchivo(DEFAULT_DIZZY, filenameDizzy);
    validarExistenciaArchivo(DEFAULT_FALL, filenameFall);
    validarExistenciaArchivo(DEFAULT_BEINGHIT, filenameBeingHit);
    validarExistenciaArchivo(DEFAULT_BEINGHIT_DOWN, filenameBeingHitDown);
    validarExistenciaArchivo(DEFAULT_BLOCK, filenameBlock);
    validarExistenciaArchivo(DEFAULT_BLOCKDOWN, filenameBlockDown);

    Util::getInstance()->setCantidadPersonajes();

    Util::getInstance()->addMovement(MOVE_NAME_WALK, filenameWalk);
    Util::getInstance()->addMovement(MOVE_NAME_STANCE, filenameStance);
    Util::getInstance()->addMovement(MOVE_NAME_JUMP, filenameJump);
    Util::getInstance()->addMovement(MOVE_NAME_SIDEJUMP, filenameSideJump);
    Util::getInstance()->addMovement(MOVE_NAME_DUCK, filenameDuck);
    Util::getInstance()->addMovement(MOVE_NAME_HIGH_KICK, filenameKick);
    Util::getInstance()->addMovement(MOVE_NAME_LOW_KICK, filenameLowKick);
    Util::getInstance()->addMovement(MOVE_NAME_DUCKING_KICK, filenameKickDown);
    Util::getInstance()->addMovement(MOVE_NAME_JUMPING_KICK, filenameJumpKick);
    Util::getInstance()->addMovement(MOVE_NAME_PUNCHJUMP, filenamePunchJump);
    Util::getInstance()->addMovement(MOVE_NAME_DUCK_PUNCH, filenamePunchUp);
    Util::getInstance()->addMovement(MOVE_NAME_HIGH_PUNCH, filenamePunch);
    Util::getInstance()->addMovement(MOVE_NAME_LOW_PUNCH, filenameLowPunch);
    Util::getInstance()->addMovement(MOVE_NAME_WINNER, filenameWinner);
    Util::getInstance()->addMovement(MOVE_NAME_SHOOT, filenameShoot);
    Util::getInstance()->addMovement(MOVE_NAME_DIZZY, filenameDizzy);
    Util::getInstance()->addMovement(MOVE_NAME_DIZZY, filenameDizzy);
    Util::getInstance()->addMovement(MOVE_NAME_FALL, filenameFall);
    Util::getInstance()->addMovement(MOVE_NAME_BEINGHIT, filenameBeingHit);
    Util::getInstance()->addMovement(MOVE_NAME_BEINGHIT_DOWN, filenameBeingHitDown);
    Util::getInstance()->addMovement(MOVE_NAME_BLOCK, filenameBlock);
    Util::getInstance()->addMovement(MOVE_NAME_BLOCKDOWN, filenameBlockDown);



    if(charAlto == 0.0){
        charAlto  = ALTOPERSONAJE;
        Mylog->Log("valor alto del personaje invalido: usando default", ERROR_LEVEL_WARNING);
    }
    if(charAncho == 0.0){
        charAncho  = ANCHOPERSONAJE;
        Mylog->Log("valor ancho del personaje invalido: usando default", ERROR_LEVEL_WARNING);
    }
    if(z_index == 0){
    	z_index  = ZINDEXPERSONAJE;
        Mylog->Log("valor z-index del personaje invalido: usando default", ERROR_LEVEL_WARNING);
    }


    if (characterNumber == 0) {
        if (name == "") {
            name = NAME_CHARACTER_1;
            Mylog->Log("nombre del personaje 1 invalido: usando default", ERROR_LEVEL_WARNING);
        }
        MKCharacter* character = new MKCharacter(0.2*(Util::getInstance()->getLogicalWindowWidth()-charAncho),charAncho,
                                                charAlto,z_index, characterNumber, name);
        characters->push_back(character);
    } else {
        if (name == "") {
            name = NAME_CHARACTER_2;
            Mylog->Log("nombre del personaje 2 invalido: usando default", ERROR_LEVEL_WARNING);
        }
        MKCharacter* character = new MKCharacter(0.8*(Util::getInstance()->getLogicalWindowWidth()-charAncho),charAncho,
                                                 charAlto,z_index, characterNumber, name);
        characters->push_back(character);
    }

    //log
    sprintf(mensaje, "Ancho: %1.2f, Alto: %1.2f, z-index: %i,\n Jump: %s, Walk: %s, Side jump: %s, Stance: %s, Duck: %s, Kick: %s,\n KickDown: %s, PunchJump: %s, PunchUp: %s, Punch: %s,\n Winner: %s, Shoot: %s, Dizzy: %s, Fall: %s, BeingHit: %s, BeingHitDown: %s, Block: %s, BlockDown: %s ",
                    charAncho, charAlto, z_index,
                    filenameJump, filenameWalk, filenameSideJump, filenameStance, filenameDuck, filenameKick, filenameKickDown, filenamePunchJump, filenamePunchUp, filenamePunch, filenameWinner, filenameShoot,  filenameDizzy, filenameFall, filenameBeingHit, filenameBeingHitDown, filenameBlock, filenameBlockDown);

    Mylog->Log(mensaje, ERROR_LEVEL_INFO);
}

void validarExistenciaArchivo(const char* defaultFile,char* fileNameToValidate)
{
	extern logger* Mylog;
	char mensaje[200];
	if(!std::ifstream(fileNameToValidate)){
			sprintf(mensaje, "No existe el archivo %s. Usando archivo por defecto: %s", fileNameToValidate, defaultFile);
			Mylog->Log(mensaje, ERROR_LEVEL_ERROR);
			strcpy(fileNameToValidate, defaultFile);
	}
}

void cargaVentana(Json::Value ventana){
    Util::getInstance()->setWindowWidth( (ventana.isMember("ancho-px") && ventana["ancho-px"].isInt()  && ventana["ancho"].asInt()>0) ?
                                                        ventana["ancho-px"].asInt() : 0);
    Util::getInstance()->setWindowHeight( (ventana.isMember("alto-px") && ventana["alto-px"].isInt() && ventana["ancho"].asInt()>0) ?
                                                        ventana["alto-px"].asInt(): 0);
    Util::getInstance()->setLogicalWindowWidth( (ventana.isMember("ancho") && ventana["ancho"].isNumeric() && ventana["ancho"].asFloat()>0) ?
                                                        ventana["ancho"].asFloat() : 0.0);
}

void cargarVentanaPorDefault(){
    extern logger* Mylog;
    Mylog->Log("JSON invalido: falta nodo ventana. Usando default", ERROR_LEVEL_ERROR);
    Util::getInstance()->setWindowWidth(0);
    Util::getInstance()->setWindowHeight(0);
    Util::getInstance()->setLogicalWindowWidth(0.0);

}

void controlErroresVentana(){
    extern logger* Mylog;
    char mensaje[200];

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
        sprintf(mensaje, "ancho-px: %i, alto px: %i, ancho: %1.2f",
                    Util::getInstance()->getWindowWidth(),
                    Util::getInstance()->getWindowHeight(),
                    Util::getInstance()->getLogicalWindowWidth()
        );
        Mylog->Log(mensaje, ERROR_LEVEL_INFO);
 }

	void cargaEscenario(Json::Value escenarios, float &stageWidth, float &stageHeight, float &floor){

        stageWidth = (escenarios.isMember("ancho") && escenarios["ancho"].isNumeric() && escenarios["ancho"].asFloat()>0) ?
                                                        escenarios["ancho"].asFloat() : 0.0;

        stageHeight = (escenarios.isMember("alto") && escenarios["alto"].isNumeric()  && escenarios["alto"].asFloat()>0 ) ?
                                                        escenarios["alto"].asFloat() : 0.0;

        floor = (escenarios.isMember("y-piso") && escenarios["y-piso"].isNumeric()  && escenarios["y-piso"].asFloat()>0 ) ?
                                                        escenarios["y-piso"].asFloat() : 0.0;

	}

	void cargaEscenarioPorDefault(float &stageWidth, float &stageHeight, float &floor){
        extern logger* Mylog;
        Mylog->Log("JSON invalido: falta nodo ventana. Usando default", ERROR_LEVEL_ERROR);

        stageWidth = 0.0 ;
        stageHeight = 0.0;
        floor = 0.0;
    }

void controlErroresEscenario(float &stageWidth, float &stageHeight, float &floor){
    extern logger* Mylog;
    char mensaje[200];
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
    sprintf(mensaje, "ancho-px: %1.2f, alto-px: %1.2f, y-piso: %1.2f", stageWidth, stageHeight, floor);
    Mylog->Log(mensaje, ERROR_LEVEL_INFO);

    Util::getInstance()->setLogicalStageWidth(stageWidth);

    Util::getInstance()->setLogicalWindowHeight(stageHeight);

}

void cargaMapbotones(Json::Value botones, int default_){
    //inicializamos como Default
    extern logger* Mylog;
    Mylog->Log("Inicializando default botones joystick", ERROR_LEVEL_INFO);
    for(int i=0; i<20; ++i){
        Util::getInstance()->setMapaDeCaracteres(DEFAULT_KEY[i], i);
    }

    if(default_ == 1){return;}//salgo si no existe (pasé root)

    char mensaje[200];
    if(botones.isMember("c1jump") && botones["c1jump"].isUInt()){
        sprintf(mensaje, "Mapeando boton c1Jump: %d", botones["c1jump"].asUInt());
        Mylog->Log(mensaje, ERROR_LEVEL_INFO);
        Util::getInstance()->setMapaDeCaracteres(botones["c1jump"].asUInt(), 0);
    }
    if(botones.isMember("c1duck") && botones["c1duck"].isUInt()){
        sprintf(mensaje, "Mapeando boton c1duck: %d", botones["c1duck"].asUInt());
        Mylog->Log(mensaje, ERROR_LEVEL_INFO);
        Util::getInstance()->setMapaDeCaracteres(botones["c1duck"].asUInt(), 1);
    }
    if(botones.isMember("c1left") && botones["c1left"].isUInt()){
        sprintf(mensaje, "Mapeando boton c1left: %d", botones["c1left"].asUInt());
        Mylog->Log(mensaje, ERROR_LEVEL_INFO);
        Util::getInstance()->setMapaDeCaracteres(botones["c1left"].asUInt(), 2);
    }
    if(botones.isMember("c1right") && botones["c1right"].isUInt()){
        sprintf(mensaje, "Mapeando boton c1right: %d", botones["c1right"].asUInt());
        Mylog->Log(mensaje, ERROR_LEVEL_INFO);
        Util::getInstance()->setMapaDeCaracteres(botones["c1right"].asUInt(), 3);
    }
    if(botones.isMember("c1LowPunch") && botones["c1LowPunch"].isUInt()){
        sprintf(mensaje, "Mapeando boton c1LowPunch: %d", botones["c1LowPunch"].asUInt());
        Mylog->Log(mensaje, ERROR_LEVEL_INFO);
        Util::getInstance()->setMapaDeCaracteres(botones["c1LowPunch"].asUInt(), 4);
    }
    if(botones.isMember("c1HighPunch") && botones["c1HighPunch"].isUInt()){
        sprintf(mensaje, "Mapeando boton c1HighPunch: %d", botones["c1HighPunch"].asUInt());
        Mylog->Log(mensaje, ERROR_LEVEL_INFO);
        Util::getInstance()->setMapaDeCaracteres(botones["c1HighPunch"].asUInt(), 5);
    }
    if(botones.isMember("c1HighKick") && botones["c1HighKick"].isUInt()){
        sprintf(mensaje, "Mapeando boton c1HighKick: %d", botones["c1HighKick"].asUInt());
        Mylog->Log(mensaje, ERROR_LEVEL_INFO);
        Util::getInstance()->setMapaDeCaracteres(botones["c1HighKick"].asUInt(), 6);
    }
    if(botones.isMember("c1Lowkick") && botones["c1Lowkick"].isUInt()){
        sprintf(mensaje, "Mapeando boton c1LowKick: %d", botones["c1Lowkick"].asUInt());
        Mylog->Log(mensaje, ERROR_LEVEL_INFO);
        Util::getInstance()->setMapaDeCaracteres(botones["c1Lowkick"].asUInt(), 7);
    }
    if(botones.isMember("c1block") && botones["c1block"].isUInt()){
        sprintf(mensaje, "Mapeando boton c1block: %d", botones["c1block"].asUInt());
        Mylog->Log(mensaje, ERROR_LEVEL_INFO);
        Util::getInstance()->setMapaDeCaracteres(botones["c1block"].asUInt(), 8);
    }
    if(botones.isMember("c1shoot") && botones["c1shoot"].isUInt()){
        sprintf(mensaje, "Mapeando boton c1shoot: %d", botones["c1shoot"].asUInt());
        Mylog->Log(mensaje, ERROR_LEVEL_INFO);
        Util::getInstance()->setMapaDeCaracteres(botones["c1shoot"].asUInt(), 9);
    }

    if(botones.isMember("c2jump") && botones["c2jump"].isUInt()){
        sprintf(mensaje, "Mapeando boton c2jump: %d", botones["c2jump"].asUInt());
        Mylog->Log(mensaje, ERROR_LEVEL_INFO);
        Util::getInstance()->setMapaDeCaracteres(botones["c2jump"].asUInt(), 10);
    }
    if(botones.isMember("c2duck") && botones["c2duck"].isUInt()){
        sprintf(mensaje, "Mapeando boton c2duck: %d", botones["c2duck"].asUInt());
        Mylog->Log(mensaje, ERROR_LEVEL_INFO);
        Util::getInstance()->setMapaDeCaracteres(botones["c2duck"].asUInt(), 11);
    }
    if(botones.isMember("c2left") && botones["c2left"].isUInt()){
        sprintf(mensaje, "Mapeando boton c2left: %d", botones["c2left"].asUInt());
        Mylog->Log(mensaje, ERROR_LEVEL_INFO);
        Util::getInstance()->setMapaDeCaracteres(botones["c2left"].asUInt(), 12);
    }
    if(botones.isMember("c2right") && botones["c2right"].isUInt()){
        sprintf(mensaje, "Mapeando boton c2right: %d", botones["c2right"].asUInt());
        Mylog->Log(mensaje, ERROR_LEVEL_INFO);
        Util::getInstance()->setMapaDeCaracteres(botones["c2right"].asUInt(), 13);
    }
    if(botones.isMember("c2LowPunch") && botones["c2LowPunch"].isUInt()){
        sprintf(mensaje, "Mapeando boton c2LowPunch: %d", botones["c2LowPunch"].asUInt());
        Mylog->Log(mensaje, ERROR_LEVEL_INFO);
        Util::getInstance()->setMapaDeCaracteres(botones["c2LowPunch"].asUInt(), 14);
    }
    if(botones.isMember("c2HighPunch") && botones["c2HighPunch"].isUInt()){
        sprintf(mensaje, "Mapeando boton c2HighPunch: %d", botones["c2HighPunch"].asUInt());
        Mylog->Log(mensaje, ERROR_LEVEL_INFO);
        Util::getInstance()->setMapaDeCaracteres(botones["c2HighPunch"].asUInt(), 15);
    }
    if(botones.isMember("c2HighKick") && botones["c2HighKick"].isUInt()){
        sprintf(mensaje, "Mapeando boton c2HighKick: %d", botones["c2HighKick"].asUInt());
        Mylog->Log(mensaje, ERROR_LEVEL_INFO);
        Util::getInstance()->setMapaDeCaracteres(botones["c2HighKick"].asUInt(), 16);
    }
    if(botones.isMember("c2Lowkick") && botones["c2Lowkick"].isUInt()){
        sprintf(mensaje, "Mapeando boton c2Lowkick: %d", botones["c2Lowkick"].asUInt());
        Mylog->Log(mensaje, ERROR_LEVEL_INFO);
        Util::getInstance()->setMapaDeCaracteres(botones["c2Lowkick"].asUInt(), 17);
    }
    if(botones.isMember("c2block") && botones["c2block"].isUInt()){
        sprintf(mensaje, "Mapeando boton c2block: %d", botones["c2block"].asUInt());
        Mylog->Log(mensaje, ERROR_LEVEL_INFO);
        Util::getInstance()->setMapaDeCaracteres(botones["c2block"].asUInt(), 18);
    }
    if(botones.isMember("c2shoot") && botones["c2shoot"].isUInt()){
        sprintf(mensaje, "Mapeando boton c2shoot: %d", botones["c2shoot"].asUInt());
        Mylog->Log(mensaje, ERROR_LEVEL_INFO);
        Util::getInstance()->setMapaDeCaracteres(botones["c2shoot"].asUInt(), 19);
    }
    if(botones.isMember("c1duckPunch") && botones["c1duckPunch"].isUInt()){
            sprintf(mensaje, "Mapeando boton c1duckPunch: %d", botones["c1duckPunch"].asUInt());
            Mylog->Log(mensaje, ERROR_LEVEL_INFO);
            Util::getInstance()->setMapaDeCaracteres(botones["c1duckPunch"].asUInt(), 20);
    }
    if(botones.isMember("c2duckPunch") && botones["c2duckPunch"].isUInt()){
        sprintf(mensaje, "Mapeando boton c2duckPunch: %d", botones["c2duckPunch"].asUInt());
        Mylog->Log(mensaje, ERROR_LEVEL_INFO);
        Util::getInstance()->setMapaDeCaracteres(botones["c2duckPunch"].asUInt(), 21);
    }
}
