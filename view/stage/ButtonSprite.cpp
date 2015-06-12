#include "ButtonSprite.h"

ButtonSprite::ButtonSprite(SDL_Renderer* aRenderer, Button* aButton) {

	this->button = aButton;
	string pathSelected = "data/buttons/"+button->getName()+"Selected.png";
	string pathNotSelected = "data/buttons/"+button->getName()+"NotSelected.png";

    selectedSprite = new ImageSprite(aRenderer, pathSelected, this->button->getX(), this->button->getY(), this->button->getWidth(), this->button->getHeight());
    notSelectedSprite = new ImageSprite(aRenderer, pathNotSelected, this->button->getX(), this->button->getY(), this->button->getWidth(), this->button->getHeight());

}

ButtonSprite::~ButtonSprite() {
	delete notSelectedSprite;
	delete selectedSprite;
}

void ButtonSprite::Draw() {
	if (this->button->isSelected()) {
		this->selectedSprite->Draw();
	}
	else {
		this->notSelectedSprite->Draw();
	}
}

bool ButtonSprite::isSelected() {
	return this->button->isSelected();
}