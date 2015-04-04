#include "GameController.h"

GameController::GameController()
{
    mainEvent = new SDL_Event();

    timer = SDL_GetTicks();
}


GameController::~GameController(void)
{
    delete mainEvent;
}

SDL_Event* GameController::getEvent() {
    return mainEvent;
}

void GameController::checkEvent() {
    SDL_PollEvent(mainEvent);    
}

void GameController::update(MKCharacter* character, std::list<Layer*>* layers) {
    
    if (mainEvent->type == SDL_KEYDOWN)
        {
            if (mainEvent->key.keysym.sym == SDLK_RIGHT)
            {
                list<Layer*>::iterator it = layers->begin();
                for(it; it != layers->end(); it++) {
                    (*it)->setMovement("RIGHT");
                }
                character->setMovement("WALKINGRIGHT");
                timer = SDL_GetTicks();
                //cout << "right" << endl;
            }
            else if (mainEvent->key.keysym.sym == SDLK_LEFT)
            {
                list<Layer*>::iterator it = layers->begin();
                for(it; it != layers->end(); it++) {
                    (*it)->setMovement("LEFT");
                }
                character->setMovement("WALKINGLEFT");
                timer = SDL_GetTicks();
                
            }
            else if (mainEvent->key.keysym.sym == SDLK_UP)
			{
//				command = "UP";
                character->setJump(true);
                //character->jump();
				//left = true;
			}
        }
        else if (timer + 500 < SDL_GetTicks()) {
            list<Layer*>::iterator it = layers->begin();
            for(it; it != layers->end(); it++) {
                (*it)->setMovement("NONE");
            }
            character->setMovement("NONE");
            timer = SDL_GetTicks();
        }

    character->Update();
    std::list<Layer*>::iterator it;
    for(it = layers->begin(); it != layers->end(); it++) {
        (*it)->update();
    }
}



