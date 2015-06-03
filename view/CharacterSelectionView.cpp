#include "CharacterSelectionView.h"

CharacterSelectionView::CharacterSelectionView(SDL_Renderer* aRenderer) {
	this->renderer = aRenderer;

	int scWidth = Util::getInstance()->getWindowWidth();
    int scHeight = Util::getInstance()->getWindowHeight();

	this->background = new LayerSprite(this->renderer, "data/background.png", scWidth, scHeight, Util::getInstance()->getLogicalWindowWidth());

	this->title = new ImageSprite(this->renderer, "data/CharacterSelection/chooseYourFighter.png", 0.175*scWidth, 0.02*scHeight, 0.65*scWidth, 0.11*scHeight);

	this->characters = new ImageSprite(this->renderer, "data/CharacterSelection/characters.png", 0.175*scWidth, 0.14*scHeight, 0.65*scWidth, 0.65*scHeight);

	float scaledScWidth = scWidth/Util::getInstance()->getScalingConstant();
	float scaledScHeight = scHeight/Util::getInstance()->getScalingYConstant();

	this->character1 = new CharacterSprite(this->renderer, "data/CharacterSelection/barakaStance.png", 0.025*scaledScWidth,0.615*scaledScHeight, 0.17*scaledScWidth,0.345*scaledScHeight, 9, "RIGHT", false, false, NULL);
    
}

CharacterSelectionView::~CharacterSelectionView() {
	delete character1;
	delete characters;
	delete title;
	delete background;
}

void CharacterSelectionView::render() {
	float scaledScWidth = Util::getInstance()->getWindowWidth()/Util::getInstance()->getScalingConstant();

	SDL_RenderClear(renderer);
    this->background->Draw();
    this->title->Draw();
    this->characters->Draw();
    this->character1->Draw();
    this->character1->Play(6.66*GAMEDELAY, 0.124*scaledScWidth);
    SDL_RenderPresent(renderer);
}