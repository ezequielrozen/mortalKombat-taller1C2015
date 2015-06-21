#include "Game.h"
#include "character/Dizzy.h"
#include "character/Victory.h"
#include "character/CharacterStance.h"
#include "character/Dead.h"
#include "../view/SoundManager.h"
#include <SDL2/SDL_mixer.h>

Game::Game(GameLoader* aGameLoader, SDL_Renderer* renderer, InputController* inputController) {
    this->gameLoader = aGameLoader;
    this->timer = new Timer();
    this->practiceMode = false;
    this->initGame(renderer, inputController);
    this->diedTimeElapsed = 0;
    this->timeToResetRound = 0;
    this->roundsWonByCharacter = {{"scorpion", 0}, {"raiden",0}};
    this->countWinnerIncreased = false;
    this->startSoundRang = false;
}

void Game::initGame(SDL_Renderer* renderer, InputController* inputController) {
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
    } else {
        this->scorpion->setFatalityEnable(true);
        this->raiden->setState(new CharacterStance());
        this->scorpion->setState(new CharacterStance());
    }
    bool cameraMoved;
    int roundCount = 1;
    bool endFight = false;

    gameView->resetFightSprite();

    while (inputController->getEvent()->type != SDL_QUIT && roundCount <= ROUNDS_TO_FIGHT && !endFightTime() && !endFight) {
        ringRoundStartSound(roundCount);
        inputController->checkEvent();
        gameView->startRender();
        gameView->Render();
        inputController->update();
        endFight = updateGameState(roundCount);
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
    if (endFightTime()) {
        this->restartRound(roundCount);
    }
    return false;
}

bool Game::updateGameState(int &roundCount) {
    bool aux = false;
    if (!scorpion->isAlive()) {
        if (scorpion->getState() != "ReceivingFire" && scorpion->getState() != "Dead") {
            if (!(scorpion->getState() == "Dizzy"))
                scorpion->setState(new Dizzy());
            scorpion->setPosY(this->stage->getFloor());
            if (diedTimeElapsed == 0) {
                diedTimeElapsed = SDL_GetTicks();
            }
            if ((SDL_GetTicks() - diedTimeElapsed >=  TIME_FOR_DOING_FATALITY) && !raiden->isJumping() && !(raiden->getState() == "FatalityHitting")) {
                raiden->setState(new Victory());
                scorpion->setState(new Dead());
            }
            raiden->setPosY(this->stage->getFloor());
        }
        if(this->timeToResetRound == 0) {
            this->timeToResetRound = SDL_GetTicks();
        } if (!this->countWinnerIncreased) {
            this->roundsWonByCharacter.at("raiden")++;
            this->countWinnerIncreased = true;
        }
        if (this->roundsWonByCharacter.at("raiden") == ROUNDS_TO_FIGHT - 1) {
            raiden->setFatalityEnable(true);
        }
        if(endOfRound()) {
            aux = this->restartRound(roundCount);
            if(this->isRoundEnd) {
                roundCount++;
                this->isRoundEnd = false;
            }
        }

    } else if (!raiden->isAlive()) {
    	if (raiden->getState() != "ReceivingFire" && raiden->getState() != "Dead") {
            if (!(raiden->getState() == "Dizzy"))
                raiden->setState(new Dizzy());
            raiden->setPosY(this->stage->getFloor());
            if (diedTimeElapsed == 0) {
                diedTimeElapsed = SDL_GetTicks();
            }
            if ((SDL_GetTicks() - diedTimeElapsed >=  TIME_FOR_DOING_FATALITY) && !scorpion->isJumping() && !(scorpion->getState() == "FatalityHitting")) {
                scorpion->setState(new Victory());
                raiden->setState(new Dead());
            }
			scorpion->setPosY(this->stage->getFloor());
    	}
        if(this->timeToResetRound == 0) {
            this->timeToResetRound = SDL_GetTicks();
        } else {
            if (!this->countWinnerIncreased) {
                this->roundsWonByCharacter.at("scorpion")++;
                this->countWinnerIncreased = true;
            }
            if (this->roundsWonByCharacter.at("scorpion") == ROUNDS_TO_FIGHT - 1) {
                scorpion->setFatalityEnable(true);
            }
            if(endOfRound()) {
                aux = this->restartRound(roundCount);
                if(this->isRoundEnd) {
                    roundCount++;
                    this->isRoundEnd = false;
                }
            }
        }
    }
    return aux;
}

bool Game::restartRound(int roundCount) {
    bool aux = false;
    if (roundCount == ROUNDS_TO_FIGHT || thereIsAWinner() || endFightTime()) {
        this->restartRoundCounts();
        this->timeToResetRound = 0;
        this->timer->stop();
        aux = true;
    } else {
        this->timeToResetRound = 0;
        this->timer->stop();
        this->timer->run();
    }
    this->countWinnerIncreased = false;
    this->diedTimeElapsed = 0;
    this->isRoundEnd = true;
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
    this->gameView->restartAllScorpionSprites();
    this->gameView->restartAllRaidenSprites();
    this->gameView->resetFightSprite();    
    this->scorpion->setState(new CharacterStance());
    this->raiden->setState(new CharacterStance());
    this->raiden->setFatalityEnable(false);
    this->scorpion->setFatalityEnable(false);
    this->scorpion->setWeaponFireUsed(false);
    this->raiden->setWeaponFireUsed(false);
    this->startSoundRang = false;
    return aux;
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

void Game::setCharacterNames(string name1, string name2) {
    string name1aux, name2aux;

    name1aux = name1;
    name2aux = name2;

    if (name1.empty()) {
        name1aux = "PLAYER1";
    }
    if (name2.empty()) {
        name2aux = "PLAYER2";
    }

    this->gameView->setCharacterNames(name1aux, name2aux);
}

bool Game::thereIsAWinner() {
    return ( this->roundsWonByCharacter.at("scorpion") == ROUNDS_TO_FIGHT - 1 && this->roundsWonByCharacter.at("raiden") < ROUNDS_TO_FIGHT - 1
            || this->roundsWonByCharacter.at("raiden") == ROUNDS_TO_FIGHT - 1 && this->roundsWonByCharacter.at("scorpion") < ROUNDS_TO_FIGHT - 1);
}

void Game::restartRoundCounts() {
    this->roundsWonByCharacter.at("scorpion") = 0;
    this->roundsWonByCharacter.at("raiden") = 0;
}

void Game::ringRoundStartSound(int roundCount) {
    if (!this->startSoundRang) {
        switch (roundCount) {
            case 1:
                SoundManager::getInstance()->playSound("roundOneFight");
                this->startSoundRang = true;
                break;
            case 2:
                SoundManager::getInstance()->playSound("roundTwoFight");
                this->startSoundRang = true;
                break;
            case 3:
                SoundManager::getInstance()->playSound("roundThreeFight");
                this->startSoundRang = true;
                break;
            default:
                break;
        }
    }
}
