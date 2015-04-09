#include "LayerSprite.h"
#include "../../model/MKCharacter.h"

LayerSprite::LayerSprite(SDL_Renderer *pRenderer, string path, float screenWidth, float screenHeight, float layerWidth) {
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
    crop.x = 0;
    crop.y = 0;
    crop.h = img_height;

    if(layerWidth <= screenWidth) {
        crop.x = 0;
        crop.w = img_width;
        //Llenar constante de ANCHOVENTAL con dato del json
        draw.w = (layerWidth / ANCHOVENTANAL) * screenWidth;
        draw.h = screenHeight;
    }
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

 //   if (img_width <= ANCHOVENTANAPX) {
     //   draw.x = shift;
   // } else {
        if (draw.h > img_height)
            crop.x = shift  * img_height / draw.h;
        else
            if (img_width < SCREEN_WIDTH ) {
                draw.x = -shift;
                draw.y = 230;
            }
            else
            crop.x = shift  * draw.h / img_height;
    //}
}