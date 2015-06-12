#include "MouseController.h"

MouseController::MouseController(MKStageController* stageController) {
	this->stageController = stageController;
	this->buttonPressed = false;
}

MouseController::~MouseController() {

}

void MouseController::update(SDL_Event* mainEvent) {

	switch (mainEvent->type){
    	case SDL_MOUSEBUTTONDOWN:
			if (mainEvent->button.button == SDL_BUTTON_LEFT) {
				if (!this->buttonPressed) {
					this->stageController->select();
					this->buttonPressed = true;
				}
			}
			
			break;

		case SDL_MOUSEBUTTONUP:
			if (mainEvent->button.button == SDL_BUTTON_LEFT) {
				this->buttonPressed = false;
			}	
			
			break;

		case SDL_MOUSEMOTION:
			this->stageController->updateMousePosition(mainEvent->motion.x, mainEvent->motion.y);
			break;

    	default:
    		break;
	}
}

void MouseController::setStageController(MKStageController* stageController) {
	this->stageController = stageController;
}

