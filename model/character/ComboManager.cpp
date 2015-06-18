#include "SDL2/SDL_events.h"
#include <SDL2/SDL_timer.h>
#include "ComboManager.h"
#include "../../view/ComboButtonsView.h"

Events ComboManager::checkCombo(Events originalEvent, char side, string name) {
    ComboButtonsView::getInstance()->addButton(originalEvent);

    if (this->startTime == 0) {
        this->startTime = SDL_GetTicks();
    }
    if (this->isTimeOut()) {
        this->cleanBuffer();
    }
    this->buffer->push_back(originalEvent);

    if (bufferMatchesCombo(this->combo1, side)) {
        return Teleportation; // SE EJECTUA EL COMBO 1: RETURN COMBO1EVENT
    }
    else if (name == "raiden" && bufferMatchesCombo(this->combo2, side)) {
        return WeaponHitIce; // SE EJECTUA EL COMBO 2: RETURN COMBO2EVENT
    }
    else if (name == "scorpion" && bufferMatchesCombo(this->fatality, side))
        return FatalityHit;

    return originalEvent;
}

void ComboManager::loadCombos(std::vector<Events>* combo1, std::vector<Events>* combo2, std::vector<Events>* fatality) {
    this->combo1 = combo1;
    this->combo2 = combo2;
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

    if (this->buffer->size() < combo->size())
        return false;

    i = (int) this->buffer->size() - (int) combo->size() - 1;
    if (i < 0)
        i = 0;
    while (i  < this->buffer->size() && errorCounter <= COMBO_TOLERANCE) {
        if (comboProgress < combo->size() && combo->at(comboProgress) == this->changeSideEvent(this->buffer->at(i),side)) {
            comboProgress++;
        }
        else if (comboProgress < combo->size()) {
            errorCounter++;
            errors.push_back(i);
        } else
            break;
        i++;
    }

    cout << "ERRORES COMETIDOS: " << errorCounter << " COMBO PROGRESS: " << comboProgress << endl;

    if (errorCounter <= COMBO_TOLERANCE && comboProgress == combo->size()) {
        cout << "COMBO DETECTADO" << endl;
        ComboButtonsView::getInstance()->comboDetected(this->buffer, errors);
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
    return SDL_GetTicks() - this->startTime > COMBO_TIMER*this->combo1->size()
            && SDL_GetTicks() - this->startTime > COMBO_TIMER*this->combo2->size() && SDL_GetTicks() - this->startTime > COMBO_TIMER*this->fatality->size();
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
