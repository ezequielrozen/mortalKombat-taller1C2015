#ifndef MORTALKOMBAT_TALLER1C2015_LAYERSPRITE_H
#define MORTALKOMBAT_TALLER1C2015_LAYERSPRITE_H

#include <iostream>
#include <SDL2/SDL_render.h>
#include <math.h>
#include <SDL2/SDL_image.h>

using namespace std;

class LayerSprite {

public:
    LayerSprite(SDL_Renderer* passed_renderer, string FilePath, float screenWidth, float screenHeight, float layerWidth);
    ~LayerSprite();
    void Draw();
    void update(float);
    void vibrate();
    float getCropWidthRelation();
    void vibrate(float vibrateProgress);
    bool vibrationFinished();
    void resetFinished();

private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect draw;
    SDL_Rect crop;
    int img_width;
    int img_height;
    float layerWidth;
    float vibrateProgress;
    bool finished;
};


#endif //MORTALKOMBAT_TALLER1C2015_LAYERSPRITE_H
