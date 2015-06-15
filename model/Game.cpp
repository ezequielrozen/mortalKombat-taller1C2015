#include "Game.h"
#include "character/Dizzy.h"
#include "character/Victory.h"
#include "character/CharacterStance.h"
#include <SDL2/SDL_mixer.h>

Game::Game(GameLoader* aGameLoader, SDL_Renderer* renderer, InputController* inputController) {
    this->gameLoader = aGameLoader;
    this->timer = new Timer();
    this->practiceMode = false;
    this->initGame(renderer, inputController);
    this->diedTimeElapsed = 0;
    this->timeToResetRound = 0;
//    this->timeFightStart = 0;
}

void Game::initGame(SDL_Renderer* renderer, InputController* inputController) {
    //this->gameLoader->loadJSON(filePath);
    //this->ScreenWidth = Util::getInstance()->getWindowWidth();
    //this->ScreenHeight = Util::getInstance()->getWindowHeight();
    this->stage = this->gameLoader->getStage();
    this->oponentSide = this->gameLoader->getOponentSide();

    this->scorpion = this->gameLoader->getCharacters()->front();
    this->raiden = this->gameLoader->getCharacters()->back();
    if (this->scorpion->getX() == this->raiden->getX()) {
        this->scorpion->setInitialPosition(0.2*(Util::getInstance()->getLogicalWindowWidth()-this->scorpion->getWidth()));
        this->raiden->setInitialPosition(0.8*(Util::getInstance()->getLogicalWindowWidth()-this->scorpion->getWidth()));
    };
    //This is very important!
    this->scorpion->setPosY(this->stage->getFloor());
    this->scorpion->setStageFloor(this->stage->getFloor());
    this->raiden->setPosY(this->stage->getFloor());
    this->raiden->setStageFloor(this->stage->getFloor());

    this->gameView = new GameView(renderer, scorpion, raiden, stage, oponentSide, this->gameLoader->getPainter(), this->timer);
    this->inputController = inputController;
    this->inputController->setCharacters(scorpion, raiden);
    InputController::setVibrating(false);
    this->cameraController = new CameraController();
    this->collider = new Collider();
}

Game::~Game() {
    delete gameView;
    delete cameraController;
    delete collider;
    delete timer;
}

bool Game::GameLoop(GameModes mode) {

//    this->timeFightStart= SDL_GetTicks();
    if (mode != Practice) {
        this->timer->run();
    }
    bool cameraMoved;
    int roundCount = 1;

    while (inputController->getEvent()->type != SDL_QUIT && roundCount <= ROUNDS_TO_FIGHT && !endFightTime()) {
    	inputController->checkEvent();
        gameView->startRender();
        gameView->Render();
        inputController->update();
        updateGameState(roundCount);
        cameraMoved = cameraController->update(scorpion, raiden, stage->getLayers());
        collider->update(scorpion, raiden, cameraMoved);

        gameView->endRender();
        SDL_Delay(GAMEDELAY);

        if (peviousKey == SDLK_r && inputController->getEvent()->key.keysym.sym == SDLK_r) {
            return true;
        }
        else {
        	peviousKey = inputController->getEvent()->key.keysym.sym;
        }

    }
    return false;
}

void Game::updateGameState(int &roundCount) {
    if (!scorpion->isAlive()) {
        if (scorpion->getState() != "ReceivingFire") {
            if (!(scorpion->getState() == "Dizzy"))
                scorpion->setState(new Dizzy());
            scorpion->setPosY(this->stage->getFloor());
            if (diedTimeElapsed == 0) {
                diedTimeElapsed = SDL_GetTicks();
            }
            if ((SDL_GetTicks() - diedTimeElapsed >=  TIME_FOR_DOING_FATALITY) && !raiden->isJumping()) {
                raiden->setState(new Victory());
            }
            raiden->setPosY(this->stage->getFloor());
            if(this->timeToResetRound == 0) {
                this->timeToResetRound = SDL_GetTicks();
            } else if(endOfRound()) {
                this->restartRound();
                if(this->isRoundEnd) {
                    roundCount++;
                    this->isRoundEnd = false;
                }
            }
        }

    } else if (!raiden->isAlive()) {
    	if (raiden->getState() != "ReceivingFire") {
            if (!(raiden->getState() == "Dizzy"))
                raiden->setState(new Dizzy());
            raiden->setPosY(this->stage->getFloor());
            if (diedTimeElapsed == 0) {
                diedTimeElapsed = SDL_GetTicks();
            }
            if ((SDL_GetTicks() - diedTimeElapsed >=  TIME_FOR_DOING_FATALITY) && !scorpion->isJumping()) {
                scorpion->setState(new Victory());
            }
			scorpion->setPosY(this->stage->getFloor());
            if(this->timeToResetRound == 0) {
                this->timeToResetRound = SDL_GetTicks();
            } else if(endOfRound()) {
                this->restartRound();
                if(this->isRoundEnd) {
                    roundCount++;
                    this->isRoundEnd = false;
                }
            }
    	}
    }
}

void Game::restartRound() {
    this->diedTimeElapsed = 0;
    this->isRoundEnd = true;
    this->timeToResetRound = 0;
    this->timer->stop();
    this->timer->run();
    this->scorpion->setLife(FULL_LIFE);
    this->raiden->setLife(FULL_LIFE);
    if (this->scorpion->getCharacterNumber() == 0) {
        this->scorpion->setInitialPosition(0.2*(Util::getInstance()->getLogicalWindowWidth()-this->scorpion->getWidth()));
        this->raiden->setInitialPosition(0.8*(Util::getInstance()->getLogicalWindowWidth()-this->scorpion->getWidth()));
    } else {
        this->scorpion->setInitialPosition(0.8*(Util::getInstance()->getLogicalWindowWidth()-this->scorpion->getWidth()));
        this->raiden->setInitialPosition(0.2*(Util::getInstance()->getLogicalWindowWidth()-this->scorpion->getWidth()));
    }
    this->stage->resetLayers();
    this->scorpion->setState(new CharacterStance());
    this->raiden->setState(new CharacterStance());
    this->raiden->setFatalityEnable(false);
    this->scorpion->setFatalityEnable(false);
}

bool Game::endFightTime() {
    return this->timer->getCurrentTime() >= TIME_TO_FIGHT_ENDING;
}

bool Game::endOfRound() {
    return SDL_GetTicks() - this->timeToResetRound >= TIME_TO_RESTART_ROUND;
}

void Game::enablePracticeMode() {
        this->gameView->enablePracticeMode();
        this->scorpion->enablePracticeMode();
        this->raiden->enablePracticeMode();
}

void Game::disablePracticeMode() {
        this->gameView->disablePracticeMode();
        this->scorpion->disablePracticeMode();
        this->raiden->disablePracticeMode();
}
