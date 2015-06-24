//
// Created by mauri on 08/06/15.
//

#include <algorithm>
#include "ComboButtonsView.h"
#include "Text.h"

ComboButtonsView* ComboButtonsView::instance = 0;

ComboButtonsView::ComboButtonsView() {
    this->activated = false;
    this->timer = new Timer();
    this->comboShowTimer = new Timer();
    this->highLightingCombo = false;
    this->buffer = {};
};

ComboButtonsView::~ComboButtonsView() {
   
}

void ComboButtonsView::clear() {
    /*delete this->buttonSprites.at("MoveUp");
    delete this->buttonSprites.at("MoveDown");
    delete this->buttonSprites.at("MoveLeft");
    delete this->buttonSprites.at("MoveRight");
    delete this->buttonSprites.at("LowPunch");
    delete this->buttonSprites.at("LowKick");
    delete this->buttonSprites.at("HighKick");
    delete this->buttonSprites.at("HighPunch");
    delete this->buttonSprites.at("Block");
    delete this->buttonSprites.at("Weapon");
    */
    this->buttonSprites.clear();
    delete this->timer;
    delete this->comboShowTimer;
    delete this->comboText;
    /*
    buffer.clear();
    buffer.shrink_to_fit();
    selectedButtons.clear();
    selectedButtons.shrink_to_fit();
    positions.clear();
    positions.shrink_to_fit();
    */
}

void ComboButtonsView::draw() {
    if (this->timer->getCurrentTime() >= TIME_TO_SHOW_BUTTONS) {
        this->timer->stop();
        //this->buffer.clear();
        //this->selectedButtons.clear();
       // this->positions.clear();
        this->highLightingCombo = false;
    } else {
        if (activated) {
            for (int i; i < buffer.size(); i++) {

                if (this->highLightingCombo) {
                    buffer[i]->setPosition(positions[i].x, positions[i].y);

                    if (this->selectedButtons.at(i) == 1) {
                        buffer[i]->DrawAlternate();
                        comboText->Draw();
                    } else {
                        buffer[i]->Draw();
                    }
                } else {
                    buffer[i]->setPosition(positions[i].x, positions[i].y);
                    buffer[i]->Draw();
                }
            }
        }
    }

    /*if (this->comboShowTimer->getCurrentTime() >= TIME_TO_SHOW_BUTTONS) {
        this->comboShowTimer->stop();
        if (this->highLightingCombo) {
            this->buffer.clear();
            this->positions.clear();
            this->selectedButtons.clear();
            this->highLightingCombo = false;
        }
    }*/
}

void ComboButtonsView::addButton(Events button) {
    if (activated && !highLightingCombo) {
        this->timer->run();
        string spriteName;
        switch (button) {
            case Jump:
                spriteName = "MoveUp";
                break;
            case Duck:
                spriteName = "MoveDown";
                break;
            case MoveLeft:
                spriteName = "MoveLeft";
                break;
            case MoveRight:
                spriteName = "MoveRight";
                break;
            case LowPunch:
                spriteName = "LowPunch";
                break;
            case HighPunch:
                spriteName = "HighPunch";
                break;
            case LowKick:
                spriteName = "LowKick";
                break;
            case HighKick:
                spriteName = "HighKick";
                break;
            case Block:
                spriteName = "Block";
                break;
            case WeaponHit:
                spriteName = "Weapon";
                break;
            default:
                spriteName = "None";
                break;
        }
        if (spriteName != "None") {
            ImageSprite *sprite = this->buttonSprites.at(spriteName);
            this->buffer.push_back(sprite);
            if (this->buffer.size() == 1)
                this->positions.push_back(Position((int) Util::getInstance()->getLogicalWindowWidth() * Util::getInstance()->getScalingConstant() * 0.5 - this->buffer[0]->getWidth() * 5, (int) Util::getInstance()->getLogicalWindowWidth() * Util::getInstance()->getScalingConstant() * 0.1));
            else
                this->positions.push_back(Position(this->positions[this->positions.size() - 1].x + this->buffer[this->buffer.size() - 1]->getWidth(), this->positions[this->positions.size() - 1].y));
            if (buffer.size() >= BUTTONS_BUFFER_PRACTICE_MAX) {
                shiftPositions();
                buffer.erase(buffer.begin());
                positions.erase(positions.begin());

            }
        }
    }
}

ComboButtonsView *ComboButtonsView::getInstance() {
    if (!instance)
        instance = new ComboButtonsView();
    return instance;
}

void ComboButtonsView::init(SDL_Renderer *renderer) {
    this->buttonSprites = {{"MoveUp", new ImageSprite(renderer, "data/buttons/joystick/up.png", "data/buttons/joystick/up_selected.png", 0,0, 32, 32)},
                           {"MoveDown", new ImageSprite(renderer, "data/buttons/joystick/down.png", "data/buttons/joystick/down_selected.png", 0,0, 32, 32)},
                           {"MoveLeft", new ImageSprite(renderer, "data/buttons/joystick/left.png", "data/buttons/joystick/left_selected.png",0,0, 32, 32)},
                           {"MoveRight", new ImageSprite(renderer, "data/buttons/joystick/right.png", "data/buttons/joystick/right_selected.png",0,0, 32, 32)},
                           {"LowPunch", new ImageSprite(renderer, "data/buttons/joystick/square.png", "data/buttons/joystick/square_selected.png",0,0, 32, 32)},
                           {"HighPunch", new ImageSprite(renderer, "data/buttons/joystick/triangle.png", "data/buttons/joystick/triangle_selected.png",0,0, 32, 32)},
                           {"LowKick", new ImageSprite(renderer, "data/buttons/joystick/x.png", "data/buttons/joystick/x_selected.png",0,0, 32, 32)},
                           {"HighKick", new ImageSprite(renderer, "data/buttons/joystick/circle.png", "data/buttons/joystick/circle_selected.png",0,0, 32, 32)},
                           {"Block", new ImageSprite(renderer, "data/buttons/joystick/l1.png", "data/buttons/joystick/l1_selected.png",0,0, 32, 32)},
                           {"Weapon", new ImageSprite(renderer, "data/buttons/joystick/r1.png", "data/buttons/joystick/r1_selected.png",0,0, 32, 32)}
    };
    this->comboText = new Text("COMBO DETECTED", renderer, "center", {255, 0, 0});
    this->comboText->setDimensions(this->comboText->getWidth() * 32 / this->comboText->getHeight(), 32);
    this->comboText->setPosition(Util::getInstance()->getLogicalWindowWidth() * Util::getInstance()->getScalingConstant() * 0.5 - this->comboText->getWidth() * 0.5, (int) Util::getInstance()->getLogicalWindowWidth() * Util::getInstance()->getScalingConstant() * 0.1 + 32 * 1.2);
}

void ComboButtonsView::shiftPositions() {
    for (int i = 0; i < buffer.size(); ++i) {
        this->positions[i].x -= this->buffer[1]->getWidth();
    }
}

void ComboButtonsView::activate() {
    this->buffer.clear();
    this->activated = true;
}

void ComboButtonsView::deactivate() {
    this->activated = false;
}

void ComboButtonsView::comboDetected(std::vector<Events>* comboBuffer, std::vector<int> errors, std::vector<int> asserts) {
    if (activated && !highLightingCombo) {
        int j = 0;
        this->selectedButtons.clear();


        /*for (int i = comboBuffer->size() - 1; i >= 0 && j < BUTTONS_BUFFER_PRACTICE_MAX; i--) {
            //if (errorIndex != -1 && i == errorIndex)
            //  this->selectedButtons.push_back(0);
            //else
            this->selectedButtons.push_back(0);
            j++;
        }*/

        for (int i = 0; i < this->buffer.size() ; i++) {
            this->selectedButtons.push_back(0);
        }

        int extra;
        ((int) comboBuffer->size() - BUTTONS_BUFFER_PRACTICE_MAX) <= 0 ? extra = 0 : extra = (int) comboBuffer->size() - BUTTONS_BUFFER_PRACTICE_MAX + 1;

        for (int l = 0; l < asserts.size() ; l++) {
            this->selectedButtons.at(asserts.at(l) - extra) = 1;
        }
/*
        for (int k = 0; k < (int) this->buffer.size() - j; k++) {
            this->selectedButtons.push_back(0);
        }
*/
        highLightingCombo = true;
        //std::reverse(this->selectedButtons.begin(), this->selectedButtons.end());

        if (this->comboShowTimer->getCurrentTime() == 0)
            this->comboShowTimer->run();
    }
}
void ComboButtonsView::reset() {
    this->timer->stop();
    this->buffer.clear();
    this->selectedButtons.clear();
    this->positions.clear();
    highLightingCombo = false;
}

bool ComboButtonsView::isShowingCombo() {
    return this->highLightingCombo;
}
