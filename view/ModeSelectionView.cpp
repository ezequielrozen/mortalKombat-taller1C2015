#include "ModeSelectionView.h"

ModeSelectionView::ModeSelectionView(SDL_Renderer* aRenderer) {
	this->renderer = aRenderer;

	this->texture = NULL;
	this->texture = IMG_LoadTexture(this->renderer,"data/titleScreen.png");

	if (this->texture == NULL)
    {
        cout << "Couldn't Load " << "data/titleScreen.png" << endl;
        cout << IMG_GetError() << std::endl;
    }

    draw.x = 0;
    draw.y = 0;
    draw.w = Util::getInstance()->getWindowWidth();
    draw.h = Util::getInstance()->getWindowHeight();

    SDL_QueryTexture(texture,NULL,NULL, &img_width, &img_height);

    crop.w = img_width;
    crop.x = 0;
    crop.y = 0;
    crop.h = img_height;


}

ModeSelectionView::~ModeSelectionView() {
	SDL_DestroyTexture(texture);
}

void ModeSelectionView::render() {

	SDL_RenderClear(renderer);
    SDL_RenderCopy(this->renderer,this->texture,&crop, &draw);
    SDL_RenderPresent(renderer);

}
