#include "ComboManager.h"

Events ComboManager::checkCombo(Events originalEvent) {
    this->buffer->push_front(originalEvent);
    if (bufferMatchesCombo(this->combo1))
        return originalEvent; // SE EJECTUA EL COMBO 1: RETURN COMBO1EVENT
    else if (bufferMatchesCombo(this->combo2))
        return originalEvent; // SE EJECTUA EL COMBO 2: RETURN COMBO2EVENT

    return originalEvent;
}

void ComboManager::loadCombos(list<Events>* combo1, list<Events>* combo2) {
    this->combo1 = combo1;
    this->combo2 = combo2;
}



ComboManager::ComboManager() {
    this->combo1->push_front(MoveRight);
    this->combo1->push_front(MoveLeft);
    this->combo1->push_front(HighKick);
    this->buffer = new list<Events>();
    this->comboProgress = 0;
}

ComboManager::~ComboManager() {
    delete this->buffer;
}

bool ComboManager::bufferMatchesCombo(list<Events> *combo) {
    int i = 0;
    this->errorCounter = 0;
    this->comboProgress = 0;
    while (i < buffer->size() || this->errorCounter > COMBO_TOLERANCE) {
        if (comboProgress < combo->size() && combo[comboProgress] == buffer[i])
            this->comboProgress++;
        else {
            this->errorCounter++;
            if (i >= this->buffer->size())
                break;
            if (i < buffer->size() - 1)
                i++;
        }
        i++;
    }

    if (this->errorCounter <= COMBO_TOLERANCE && this->comboProgress == combo->size()) {
        cout << "COMBO DETECTADO" << endl;
        this->cleanBuffer();
        return true;
    }
}

void ComboManager::cleanBuffer() {
    delete this->buffer;
    buffer = new list<Events>();
}
