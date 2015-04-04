#include "LayerSprite.h"
#include "../../model/MKCharacter.h"

LayerSprite::LayerSprite(SDL_Renderer *pRenderer, string path, float screenWidth, float screenHeight) {
    this->renderer = pRenderer;
    this->texture = NULL;
    this->texture = IMG_LoadTexture(this->renderer,path.c_str());

    if (this->texture == NULL)
    {
        cout << "Couldn't Load " << path.c_str() << endl;
        cout << IMG_GetError() << std::endl;
    }

    draw.x = 0;
    draw.y = 0;
    draw.w = (int) screenWidth;
    draw.h = (int) screenHeight;

    SDL_QueryTexture(texture,NULL,NULL, &img_width, &img_height);

    crop.w = (int) floor(screenWidth*img_height/screenHeight);
    crop.x = img_width/2 - crop.w/2;
    crop.y = 0;
    crop.h = img_height;
}

LayerSprite::~LayerSprite() {
    SDL_DestroyTexture(texture);
}

float LayerSprite::getCropWidthRelation() {
    return (float) img_width / (float)crop.w;
}

void LayerSprite::Draw() {
    SDL_RenderCopy(renderer,texture,&crop, &draw);
}

void LayerSprite::update(float shift) {
    crop.x = (int) shift  * img_height / draw.h;
}