//
// Created by mauri on 07/05/15.
//

#ifndef MORTALKOMBAT_TALLER1C2015_LIFEVIEW_H
#define MORTALKOMBAT_TALLER1C2015_LIFEVIEW_H

using namespace std;

#include <iostream>
#include <SDL2/SDL_render.h>

class LifeView {

    public:
        LifeView(SDL_Renderer* renderer, string filePath, float width, float height, bool inverted);
        LifeView(SDL_Renderer* renderer, string filePath, float width, bool inverted);
        ~LifeView();
        void Draw(float currentLife);
    private:
        SDL_Renderer* renderer;
        SDL_Texture* texture;
        SDL_Texture* insideTexture;
        SDL_Rect insideDraw;
        SDL_Rect draw;
        bool inverted;
};


#endif //MORTALKOMBAT_TALLER1C2015_LIFEVIEW_H
