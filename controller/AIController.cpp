#include "AIController.h"
#include <time.h>

AIController::AIController(MKStageController* stageController) {
    this->stageController = stageController;
    this->waiting = true;
    this->weaponThrown = false;
    this->practiceMode = false;
}

AIController::~AIController() {

}



void AIController::setStageController(MKStageController* stageController) {
    this->stageController = stageController;
}

void AIController::update(MKCharacter* character1, MKCharacter* character2, SDL_Event* mainEvent) {
    if (!this->practiceMode)
        this->updateAIPlayer(character1, character2);
}

Events AIController::makeRandomGroundHit() {
    srand (time(NULL));

    switch (rand() % 4 + 1) {
        case 1:
            return LowKick;
            break;
        case 2:
            return HighKick;
            break;
        case 3:
            return LowPunch;
            break;
        case 4:
            return HighPunch;
            break;
    }
}

void AIController::updateAIPlayer(MKCharacter *character1, MKCharacter *character2) {
    if (!this->waiting) {
        if (character1->isHitting()) {
            character2->update(Block);
        } else if (character2->getState() == "Blocking")
            character2->update(BlockRelease);

        if (character1->getCharacterSide() == 'l' && !character1->isHitting())
            character2->update(MoveLeft);
        else if (character1->getCharacterSide() == 'r')
            character2->update(MoveRight);

        if (abs((int) character1->getX() - (int) character2->getX()) < character1->getWidth()) {
            if (character2->isMovingLeft()) {
                character2->update(MoveLeftRelease);
                character2->update(makeRandomGroundHit());
            } else if (character2->isMovingRight()) {
                character2->update(makeRandomGroundHit());
                character2->update(MoveRightRelease);

                makeRandomGroundHit();
            }
        }
    }

    if (abs((int)character1->getX() - (int)character2->getX()) < character1->getWidth() * 4 && !character2->isReceivingHit()) {
        this->waiting = false;
    } else {
        this->waiting = true;
        if (character2->isMovingRight())
            character2->update(MoveRightRelease);
        else if (character2->isMovingLeft())
            character2->update(MoveLeftRelease);
    }

    if (character1->getState() == "WeaponHitting") {
        if (character2->getCharacterSide() == 'r') {
            character2->update(MoveLeft);
            character2->update(Jump);
        } else {
            character2->update(MoveRight);
            character2->update(Jump);
        }
    }
    if (this->waiting && !this->weaponThrown && character1->isJumping()) {
        character2->update(WeaponHit);
        this->weaponThrown = true;
    }
}

void AIController::enablePracticeAI() {
    this->practiceMode = true;
}
