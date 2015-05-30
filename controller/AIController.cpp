#include "AIController.h"

AIController::AIController(MKStageController* stageController) {
    this->stageController = stageController;
}

AIController::~AIController() {

}

void AIController::update(MKCharacter* character1, MKCharacter* character2, SDL_Event* mainEvent) {
    switch (mainEvent->type){
        case SDL_KEYDOWN:
            switch(mainEvent->key.keysym.sym) {
                case SDLK_RIGHT:
                    this->stageController->setCharacterToMove(character1);
                    this->stageController->moveRight();
                    break;
                case SDLK_LEFT:
                    this->stageController->setCharacterToMove(character1);
                    this->stageController->moveLeft();
                    break;
                case SDLK_UP:
                    this->stageController->setCharacterToMove(character1);
                    this->stageController->moveUp();
                    break;
                case SDLK_DOWN:
                    this->stageController->setCharacterToMove(character1);
                    this->stageController->moveDown();
                    break;
                case SDLK_k:
                    this->stageController->setCharacterToMove(character1);
                    this->stageController->highKick();
                    break;
                case SDLK_l:
                    this->stageController->setCharacterToMove(character1);
                    this->stageController->lowKick();
                    break;
                case SDLK_p:
                    this->stageController->setCharacterToMove(character1);
                    this->stageController->highPunch();
                    break;
                case SDLK_i:
                    this->stageController->setCharacterToMove(character1);
                    this->stageController->lowPunch();
                    break;
                case SDLK_b:
                    this->stageController->setCharacterToMove(character1);
                    this->stageController->block();
                    break;
                case SDLK_u:
                    if (key_u_Released) {
                        key_u_Released = false;
                        this->stageController->setCharacterToMove(character1);
                        this->stageController->shoot();
                    }
                    break;
                case SDLK_o:
                    this->stageController->setCharacterToMove(character1);
                    this->stageController->duckPunch();
                    break;
                default:
//				previousKey = mainEvent->key.keysym.sym;
                    break;
            }
            break;

        case SDL_KEYUP:
            switch(mainEvent->key.keysym.sym){
                case SDLK_DOWN:
                    this->stageController->setCharacterToMove(character1);
                    this->stageController->moveDownRelease();
                    break;
                case SDLK_RIGHT:
                    this->stageController->setCharacterToMove(character1);
                    this->stageController->moveRightRelease();
                    break;
                case SDLK_LEFT:
                    this->stageController->setCharacterToMove(character1);
                    this->stageController->moveLeftRelease();
                    break;
                case SDLK_b:
                    this->stageController->setCharacterToMove(character1);
                    this->stageController->blockRelease();
                    break;
                case SDLK_u:
                    key_u_Released = true;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}
