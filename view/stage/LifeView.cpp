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
    this->insideTexture = NULL;
    this->insideTexture = IMG_LoadTexture(this->renderer, "data/lifebarInside.png");
    this->inverted = inverted;
    this->draw.y = 0;

    int img_width;
    int img_height;
    SDL_QueryTexture(texture,NULL,NULL, &img_width, &img_height);

    float scale = (width / img_width);
    draw.y = 0;
    insideDraw.y = 0;
    if (!inverted) {
        this->draw.x = 0;
        this->insideDraw.x = 0;
    }
    else {
        this->draw.x = (Util::getInstance()->getLogicalWindowWidth() - width) * Util::getInstance()->getScalingConstant();
        this->insideDraw.x = (Util::getInstance()->getLogicalWindowWidth() - width) * Util::getInstance()->getScalingConstant();
    }
    this->draw.w = width * Util::getInstance()->getScalingConstant();
    this->draw.h = img_height * scale * Util::getInstance()->getScalingConstant();

    this->insideDraw.w = width * Util::getInstance()->getScalingConstant();
    this->insideDraw.h = img_height * scale * Util::getInstance()->getScalingConstant();

    if (this->texture == NULL) {
        cout << "Couldn't Load " << filePath.c_str() << endl;
        cout << IMG_GetError() << std::endl;
    }

    if (this->insideTexture == NULL) {
        cout << "Couldn't Load data/libegarInside.png" << endl;
        cout << IMG_GetError() << std::endl;
    }

}

LifeView::~LifeView() {
    SDL_DestroyTexture(this->texture);
    SDL_DestroyTexture(this->insideTexture);
}

void LifeView::Draw(float currentLifePercentage) {
    if (!inverted) {
        SDL_RenderCopy(this->renderer, this->texture, NULL, &draw);
        insideDraw.w = draw.w * currentLifePercentage / 100;
        SDL_RenderCopy(this->renderer, this->insideTexture, NULL, &insideDraw);

    } else {
        SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx(this->renderer, this->texture, NULL, &draw, NULL, NULL, flip);
        insideDraw.w = draw.w * currentLifePercentage / 100;
        insideDraw.x = draw.x + (draw.w - insideDraw.w);
        SDL_RenderCopy(this->renderer, this->insideTexture, NULL, &insideDraw);

    }
}
