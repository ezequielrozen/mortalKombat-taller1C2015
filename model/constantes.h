#ifndef CONSTANTES_H_
#define CONSTANTES_H_

#include "util/Util.h"

////ventana
//const int ANCHOVENTANAPX                    =  700;
//const int ALTOVENTANAPX                     =  500;
const float ANCHOVENTANAL                   =  200;

//escenario
const float ANCHOESCENARIO                  = 1000;
//const float ALTOESCENARIO                   =  150;
//const float ALTURAPISOESCENARIO             =   20;
//
//// capa
//
//const float VELOCIDAD_DESPLAZAMIENTO_CAPAS = 4;

//personaje
const float ANCHOPERSONAJE                  =   20;
const float ALTOPERSONAJE                   =   35;
//const float ZINDEXPERSONAJE                 =    1;
//
//const int OPONENTLEFT                       =    1;
//const int OPONENTRIGHT                      =    2;
//
//
//Constantes de fluidez del juego
//Fija el delay que tiene el personaje para mover por la pantalla. (A mayor, mas lento se mueve)
//const int MOVEMENTDELAY                     =   15;
//Fija el delay que tiene el personaje para cambiar de direccion. (A mayor, mas tarda en cambiar de direccion. Osea, a mayor, patina mas)
const int COMMANDDELAY                      =  150;
////Velocidad inicial del salto del personaje.
//const float SPEED                             =  0.04285*ANCHOVENTANAL;
////Aceleracion aplicada al salto del personaje.
//const float ACCELERATION                      =  1.2285*ANCHOVENTANAL;

const float INITIAL_POSITION_X = 0.2857*ANCHOVENTANAL;
const float INITIAL_POSITION_Y = 0.2857*ANCHOVENTANAL;


#endif /* CONSTANTES_H_ */
