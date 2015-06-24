#include "SDL2/SDL_events.h"
#include <SDL2/SDL_timer.h>
#include "ComboManager.h"
#include "../../view/ComboButtonsView.h"

Events ComboManager::checkCombo(Events originalEvent, char side, string name) {
    ComboButtonsView::getInstance()->addButton(originalEvent);

    if (this->startTime == 0) {
        this->startTime = SDL_GetTicks();
    }
    this->buffer->push_back(originalEvent);

    if (this->isTimeOut()) {
        this->cleanBuffer();
        ComboButtonsView::getInstance()->reset();
    }
        if (bufferMatchesCombo(this->combo1, side)) {
            return Teleportation; // SE EJECTUA EL COMBO 1: RETURN COMBO1EVENT
        }
        else if (name == "raiden" && bufferMatchesCombo(this->combo2, side)) {
            return WeaponHitIce; // SE EJECTUA EL COMBO 2: RETURN COMBO2EVENT
        }

        else if (name == "raiden" && bufferMatchesCombo(this->combo3, side)) {
            return FlyHit;
        }
        else if (name == "scorpion" && bufferMatchesCombo(this->fatality, side)) {
            return FatalityHit;
        }
            /*else if (name == "raiden" && bufferMatchesCombo(this->combo4, side)) {
        return WeaponHitIce; // SE EJECTUA EL COMBO4: RETURN COMBO2EVENT
    }
    else if (name == "raiden" && bufferMatchesCombo(this->combo5, side)) {
        return WeaponHitIce; // SE EJECTUA EL COMBO 5: RETURN COMBO2EVENT
    }
    else if (name == "raiden" && bufferMatchesCombo(this->combo6, side)) {
        return WeaponHitIce; // SE EJECTUA EL COMBO 6: RETURN COMBO2EVENT
    }*/



        return originalEvent;
}

void ComboManager::loadCombos(std::vector<Events>* combo1, std::vector<Events>* combo2,
                              std::vector<Events>* combo3,
                              std::vector<Events>* combo4,
                              std::vector<Events>* combo5,
                              std::vector<Events>* combo6, std::vector<Events>* fatality) {
    this->combo1 = combo1;
    this->combo2 = combo2;
    this->combo3 = combo3;
    this->combo4 = combo4;
    this->combo5 = combo5;
    this->combo6 = combo6;
    this->fatality = fatality;
}

ComboManager::ComboManager() {
    this->buffer = new std::vector<Events>();
    this->startTime = 0;
}

ComboManager::~ComboManager() {
    delete this->buffer;
}

bool ComboManager::bufferMatchesCombo(std::vector<Events>* combo, char side) {
    int i = 0;
    int errorCounter = 0;
    unsigned int comboProgress = 0;
    std::vector<int> errors;
    std::vector<int> asserts;

    if (this->buffer->size() < combo->size())
        return false;

    i = (int) this->buffer->size() - (int) combo->size() - 1;

    if (i < 0)
        i = 0;

    while (i  < this->buffer->size() && errorCounter <= COMBO_TOLERANCE) {
        if (comboProgress < combo->size() && combo->at(comboProgress) == this->changeSideEvent(this->buffer->at(i),side)) {
            comboProgress++;
            asserts.push_back(i);
        }
        else if (comboProgress < combo->size()) {
            errorCounter++;
            errors.push_back(i);
        } else
            break;
        i++;
    }

    //cout << "ERRORES COMETIDOS: " << errorCounter << " COMBO PROGRESS: " << comboProgress << endl;

    if (errorCounter <= COMBO_TOLERANCE && comboProgress == combo->size()) {
        cout << "COMBO DETECTADO" << endl;
        ComboButtonsView::getInstance()->comboDetected(this->buffer, errors, asserts);
        this->cleanBuffer();
        return true;
    }
    return false;
}

void ComboManager::cleanBuffer() {
    delete this->buffer;
    this->buffer = new std::vector<Events>();
    this->startTime = 0;
}

bool ComboManager::isTimeOut() {
    return  SDL_GetTicks() - this->startTime > COMBO_TIMER*this->combo1->size() &&
            SDL_GetTicks() - this->startTime > COMBO_TIMER*this->combo2->size() &&
            SDL_GetTicks() - this->startTime > COMBO_TIMER*this->combo3->size() &&
            SDL_GetTicks() - this->startTime > COMBO_TIMER*this->combo4->size() &&
            SDL_GetTicks() - this->startTime > COMBO_TIMER*this->combo5->size() &&
            SDL_GetTicks() - this->startTime > COMBO_TIMER*this->combo6->size() &&
            SDL_GetTicks() - this->startTime > COMBO_TIMER*this->fatality->size();
}

Events ComboManager::changeSideEvent(Events event, char side) {
    if (side == 'r') {
        switch(event) {
            case MoveRight:
                return MoveLeft;
            case MoveLeft:
                return MoveRight;
            default:
                break;
        }
    }
    return event;
}
