#ifndef MORTALKOMBAT_TALLER1C2015_LAYERSPRITE_H
#define MORTALKOMBAT_TALLER1C2015_LAYERSPRITE_H

#include <iostream>
#include <SDL2/SDL_render.h>

using namespace std;

class LayerSprite {

public:
    LayerSprite(SDL_Renderer* passed_renderer, string FilePath, int screenWidth, int screenHeight);
    ~LayerSprite();
    void Draw();
    void update(int);

private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect draw;

    SDL_Rect crop;
    int img_width;
    int img_height;
};


#endif //MORTALKOMBAT_TALLER1C2015_LAYERSPRITE_H
