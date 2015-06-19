#include "ModeSelectionView.h"

ModeSelectionView::ModeSelectionView(SDL_Renderer* aRenderer, Button** buttons) {
	this->renderer = aRenderer;

    int scWidth = Util::getInstance()->getWindowWidth();
    int scHeight = Util::getInstance()->getWindowHeight();

	this->background = new LayerSprite(this->renderer, "data/background.png", scWidth, scHeight, Util::getInstance()->getLogicalWindowWidth());

    this->splashScreen = new ImageSprite(this->renderer, "data/titleScreen.png", 0, 0, scWidth, scHeight);

    this->logo = new ImageSprite(this->renderer, "data/logo.png", 0.0714*scWidth, 0.06*scHeight, 0.85*scWidth, 0.17*scHeight);

    this->button1 = new ButtonSprite(this->renderer, buttons[0]);

    this->button2 = new ButtonSprite(this->renderer, buttons[1]);

    this->button3 = new ButtonSprite(this->renderer, buttons[2]); 

    this->splashScreenShown = true;
}

ModeSelectionView::~ModeSelectionView() {
	delete button3;
    delete button2;
    delete button1;
    delete logo;
    delete splashScreen;
    delete background;
}

void ModeSelectionView::setSplashScreen(bool show) {
    this->splashScreenShown = show;
}

void ModeSelectionView::render() {

	SDL_RenderClear(renderer);
    if (this->splashScreenShown) {
        this->splashScreen->Draw();
    } else {
        this->background->Draw();
        this->logo->Draw();
        this->button1->Draw();
        this->button2->Draw();
        this->button3->Draw();
    }   
    SDL_RenderPresent(renderer);

}
