#include "ImageSprite.h"

ImageSprite::ImageSprite(SDL_Renderer* aRenderer, string path, int x, int y, int w, int h) {
	this->renderer = aRenderer;
    this->texture = NULL;
    this->texture = IMG_LoadTexture(this->renderer,path.c_str());

    if (this->texture == NULL)
    {
        cout << "Couldn't Load " << path.c_str() << endl;
        cout << IMG_GetError() << std::endl;
    }

    draw.x = x;
    draw.y = y;
    draw.w = w;
    draw.h = h;

    SDL_QueryTexture(texture,NULL,NULL, &img_width, &img_height);

    crop.w = img_width;
    crop.x = 0;
    crop.y = 0;
    crop.h = img_height;
}

ImageSprite::~ImageSprite() {
	SDL_DestroyTexture(texture);
}

void ImageSprite::Draw() {
	SDL_RenderCopy(renderer,texture,&crop, &draw);
}

void ImageSprite::setPosition(int x, int y) {
    this->draw.x = x;
    this->draw.y = y;
}

int ImageSprite::getX() {
    return this->draw.x;
}

int ImageSprite::getY() {
    return this->draw.y;
}

int ImageSprite::getWidth() {
    return this->draw.w;
}
