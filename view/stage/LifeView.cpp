//
// Created by mauri on 07/05/15.
//

#include <SDL2/SDL_image.h>
#include "LifeView.h"
#include "../../model/util/Util.h"

LifeView::LifeView(SDL_Renderer *renderer, string filePath, float width, bool inverted) {
    this->renderer = renderer;
    this->texture = NULL;
    this->texture = IMG_LoadTexture(this->renderer,filePath.c_str());
    this->inverted = inverted;
    this->draw.y = 0;
    
    int img_width;
    int img_height;
    SDL_QueryTexture(texture,NULL,NULL, &img_width, &img_height);

    float scale = (width / img_width);

    if (!inverted)
        this->draw.x = 0;
    else
        this->draw.x = (Util::getInstance()->getLogicalWindowWidth()  - width) * Util::getInstance()->getScalingConstant();

    this->draw.w = width * Util::getInstance()->getScalingConstant();
    this->draw.h = img_height * scale * Util::getInstance()->getScalingConstant();

    if (this->texture == NULL) {
        cout << "Couldn't Load " << filePath.c_str() << endl;
        cout << IMG_GetError() << std::endl;
    }

}

LifeView::~LifeView() {
    SDL_DestroyTexture(this->texture);
}

void LifeView::Draw() {
    if (!inverted)
        SDL_RenderCopy(this->renderer, this->texture, NULL, &draw);
    else {
        SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx(this->renderer, this->texture, NULL, &draw, NULL, NULL, flip);
    }
}
