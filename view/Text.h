//
// Created by mauri on 12/05/15.
//

#ifndef MORTALKOMBAT_TALLER1C2015_TEXT_H
#define MORTALKOMBAT_TALLER1C2015_TEXT_H
using namespace std;

#include <SDL2/SDL_render.h>
#include <string>

class Text {
    public:
        Text(const char* text, SDL_Renderer* renderer, string position);
        Text(const char* text, SDL_Renderer* renderer, string position, SDL_Color colour);
        ~Text();
        void Draw();
        void update(const char *text);
        void setPosition(int x, int y);
        int getWidth();
        int getHeight();
        void setDimensions(int width, int height);
    private:
        SDL_Texture* textTexture;
        SDL_Renderer* renderer;
        SDL_Rect draw;
        const char* text;
        void initText(string position, SDL_Color colour);

};


#endif //MORTALKOMBAT_TALLER1C2015_TEXT_H
