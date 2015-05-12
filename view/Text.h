//
// Created by mauri on 12/05/15.
//

#ifndef MORTALKOMBAT_TALLER1C2015_TEXT_H
#define MORTALKOMBAT_TALLER1C2015_TEXT_H
using namespace std;

#include <SDL2/SDL_render.h>

class Text {
    public:
        Text(const char* text, SDL_Renderer* renderer, string position);
        ~Text();
        void Draw();
    private:
        SDL_Texture* textTexture;
        SDL_Renderer* renderer;
        SDL_Rect draw;
};


#endif //MORTALKOMBAT_TALLER1C2015_TEXT_H
