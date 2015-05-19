#include "MovingLeft.h"
#include "CharacterStance.h"
#include "JumpingLeft.h"

MovingLeft::MovingLeft() {
    this->timer = 10;
}

MovingLeft::~MovingLeft() {
}

void MovingLeft::update(MKCharacter * character, Events aEvent) {
    // me estoy moviendo para la izquierda y aprieto para la derecha. tengo que cambiar de estado a movingRight
    //delete character->state;
    //character->state = new MovingRight();
//    std::cout << "MovingLeft." << std::endl;
    switch (aEvent) {
        case Jump:
            character->setState(new JumpingLeft());
            break;
        case LowPunch:
            //cambiar a estado a lowPunching
            break;
        case HighPunch:
            //cambiar a estado a lowPunching
            break;
        case LowKick:
            //cambiar a estado a lowKicking
            break;
        case HighKick:
            //cambiar a estado a lowPunching
            break;
        case ReceiveHit:
            //cambiar a estado a beingHit
            break;
        case MoveRight:
            character->setState(new MovingRight());
            break;
        case MoveLeftRelease:
            // cambiar a estado stance
        	character->setState(new CharacterStance());
        	break;
        default:
            //si no recibe ninguno de los otros eventos, en principio no hay que hacer nada, porque no afectan a este estado
            break;

    }
}

bool MovingLeft::isMovingLeft() {
    return true;
}

string MovingLeft::getName() {
    return "MovingLeft";
}

