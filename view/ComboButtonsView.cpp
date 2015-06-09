//
// Created by mauri on 08/06/15.
//

#include "ComboButtonsView.h"

ComboButtonsView* ComboButtonsView::instance = 0;

ComboButtonsView::ComboButtonsView() {
    this->activated = false;
};

ComboButtonsView::~ComboButtonsView() {
    delete this->buttonSprites.at("MoveUp");
    delete instance;
}

void ComboButtonsView::draw() {
    if (activated) {
        for (int i; i < buffer.size(); i++) {

            buffer[i]->setPosition(positions[i].x, positions[i].y);
            buffer[i]->Draw();
        };
    }
}

void ComboButtonsView::addButton(Events button) {
    if (activated) {
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
                this->positions.push_back(Position(
                        (int) Util::getInstance()->getLogicalWindowWidth() * Util::getInstance()->getScalingConstant() * 0.5 - this->buffer[0]->getWidth() * 3.5, (int) Util::getInstance()->getLogicalWindowWidth() * Util::getInstance()->getScalingConstant() * 0.1));
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
    this->buttonSprites = {{"MoveUp", new ImageSprite(renderer, "data/buttons/joystick/up.png", 0,0, 32, 32)},
                           {"MoveDown", new ImageSprite(renderer, "data/buttons/joystick/down.png", 0,0, 32, 32)},
                           {"MoveLeft", new ImageSprite(renderer, "data/buttons/joystick/left.png", 0,0, 32, 32)},
                           {"MoveRight", new ImageSprite(renderer, "data/buttons/joystick/right.png", 0,0, 32, 32)},
                           {"LowPunch", new ImageSprite(renderer, "data/buttons/joystick/square.png", 0,0, 32, 32)},
                           {"HighPunch", new ImageSprite(renderer, "data/buttons/joystick/triangle.png", 0,0, 32, 32)},
                           {"LowKick", new ImageSprite(renderer, "data/buttons/joystick/x.png", 0,0, 32, 32)},
                           {"HighKick", new ImageSprite(renderer, "data/buttons/joystick/circle.png", 0,0, 32, 32)},
                           {"Block", new ImageSprite(renderer, "data/buttons/joystick/l1.png", 0,0, 32, 32)},
                           {"Weapon", new ImageSprite(renderer, "data/buttons/joystick/r1.png", 0,0, 32, 32)}
    };
}

void ComboButtonsView::shiftPositions() {
    for (int i = 0; i < buffer.size(); ++i) {
        this->positions[i].x -= this->buffer[1]->getWidth();
    }
}

void ComboButtonsView::activate() {
    this->activated = true;
}
