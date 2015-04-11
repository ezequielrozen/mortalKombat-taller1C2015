#include "LayerSprite.h"
#include "../../model/MKCharacter.h"
#include "../../model/util/Util.h"

LayerSprite::LayerSprite(SDL_Renderer *pRenderer, string path, float screenWidth, float screenHeight, float layerWidth) {
    this->renderer = pRenderer;
    this->texture = NULL;
    this->texture = IMG_LoadTexture(this->renderer,path.c_str());

    if (this->texture == NULL)
    {
        cout << "Couldn't Load " << path.c_str() << endl;
        cout << IMG_GetError() << std::endl;
    }

    this->layerWidth = layerWidth;

    draw.x = 0;
    draw.y = 0;
    draw.w = (int) screenWidth;
    draw.h = (int) screenHeight;

    SDL_QueryTexture(texture,NULL,NULL, &img_width, &img_height);

    crop.w = /*(int) floor(screenWidth*img_height/screenHeight)*/ img_width * Util::getInstance()->getLogicalWindowWidth() / layerWidth;
    crop.x = img_width/2 - crop.w/2;
    crop.y = 0;
    crop.h = img_height;

    if(layerWidth <= Util::getInstance()->getLogicalWindowWidth()) {
        crop.w = img_width;
        //Llenar constante de ANCHOVENTAL con dato del json
        crop.x = 0;
        draw.w = (layerWidth / Util::getInstance()->getLogicalWindowWidth()) * screenWidth;
        draw.x = (Util::getInstance()->getLogicalWindowWidth() / 2 - layerWidth / 2) * (Util::getInstance()->getWindowWidth() / Util::getInstance()->getLogicalWindowWidth());
        draw.h = screenHeight;
    }
}

LayerSprite::~LayerSprite() {
    SDL_DestroyTexture(texture);
}

float LayerSprite::getCropWidthRelation() {
    return (float) img_width / (float) crop.w;
}

void LayerSprite::Draw() {
    SDL_RenderCopy(renderer,texture,&crop, &draw);
}

void LayerSprite::update(float shift) {
    // El shift es lógico, hay que pasarlo a píxeles (ahora la relación es 1 a 1 así que es como si fuera en píxeles
        if ( layerWidth > Util::getInstance()->getLogicalWindowWidth() )
                crop.x = shift * (img_width - crop.w)  / (layerWidth - Util::getInstance()->getLogicalWindowWidth());
        else
           draw.x = shift * (Util::getInstance()->getWindowWidth() / Util::getInstance()->getLogicalWindowWidth());
}