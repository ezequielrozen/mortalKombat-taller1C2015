#include "ButtonSprite.h"

ButtonSprite::ButtonSprite(SDL_Renderer* aRenderer, Button* aButton, int x, int y, int w, int h) {

	this->button = aButton;
	string pathSelected = "data/buttons/"+button->getName()+"Selected.png";
	string pathNotSelected = "data/buttons/"+button->getName()+"NotSelected.png";

    selectedSprite = new ImageSprite(aRenderer, pathSelected, x, y, w, h);
    notSelectedSprite = new ImageSprite(aRenderer, pathNotSelected, x, y, w, h);

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