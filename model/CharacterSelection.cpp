#include "CharacterSelection.h"

CharacterSelection::CharacterSelection(SDL_Renderer* renderer) {
	this->view = new CharacterSelectionView(renderer);
}

CharacterSelection::~CharacterSelection() {
	delete view;
}

void CharacterSelection::loop() {

}