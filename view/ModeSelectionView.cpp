#include "ModeSelectionView.h"

ModeSelectionView::ModeSelectionView(SDL_Renderer* aRenderer, std::vector<Button*> buttons) {
	this->renderer = aRenderer;

    int scWidth = Util::getInstance()->getWindowWidth();
    int scHeight = Util::getInstance()->getWindowHeight();

	this->background = new LayerSprite(this->renderer, "data/background.png", scWidth, scHeight, Util::getInstance()->getLogicalWindowWidth());

    this->logo = new ImageSprite(this->renderer, "data/logo.png", 0.0714*scWidth, 0.06*scHeight, 0.85*scWidth, 0.17*scHeight);

    this->button1 = new ButtonSprite(this->renderer, buttons.at(0), 0.343*scWidth, 0.29*scHeight, 0.314*scWidth, 0.16*scHeight);

    this->button2 = new ButtonSprite(this->renderer, buttons.at(1), 0.343*scWidth, 0.51*scHeight, 0.314*scWidth, 0.16*scHeight);

    this->button3 = new ButtonSprite(this->renderer, buttons.at(2), 0.343*scWidth, 0.73*scHeight, 0.314*scWidth, 0.16*scHeight); 
}

ModeSelectionView::~ModeSelectionView() {
	delete button3;
    delete button2;
    delete button1;
    delete logo;
    delete background;
}

void ModeSelectionView::render() {

	SDL_RenderClear(renderer);
    this->background->Draw();
    this->logo->Draw();
    this->button1->Draw();
    this->button2->Draw();
    this->button3->Draw();
    SDL_RenderPresent(renderer);

}
