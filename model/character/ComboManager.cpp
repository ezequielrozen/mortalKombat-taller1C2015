#include "ComboManager.h"

Events ComboManager::checkCombo(Events originalEvent) {
    this->buffer->push_front(originalEvent);
    int i = 0;
    this->errorCounter = 0;
    this->comboProgress = 0;
    while (i < buffer->size()) {
        if (i < this->combo1->size() && this->combo1[comboProgress] == buffer[i])
            this->comboProgress++;
        else {
            if (i >= this->combo1->size() -1)
                break;
            this->errorCounter++;
            if (i < buffer->size() - 1)
                i++;
        }
        i++;
    }

    if (this->errorCounter < COMBO_TOLERANCE && this->comboProgress == this->combo1->size() - 1) {
        cout << "COMBO DETECTADO" << endl;
        return originalEvent;
    }
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
