//
// Created by mauri on 12/05/15.
//

#include "../model/json/json.h"
#include "Text.h"
#include <SDL_ttf.h>
#include <iostream>
#include "../model/util/Util.h"
using namespace std;

Text::Text(const char* text, SDL_Renderer *renderer, string position) {

    this->renderer = renderer;
    if( TTF_Init() == -1 ) {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    //Open the font

    TTF_Font* font = TTF_OpenFont("data/Fonts/mortalkombat3.ttf", 20);
    if (font == NULL) {
        cout << "No se pudo carga la tipografía." << endl;
    }

    //We need to first render to a surface as that's what TTF_RenderText
    //returns, then load that surface into a texture
    SDL_Color colour = { 255, 255, 255 };

    SDL_Surface *surface = TTF_RenderText_Blended(font, text, colour);
    if (surface == NULL){
        TTF_CloseFont(font);
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL){
        cout << "No se pudo cargar la textura." << endl;
    }

    this->textTexture = texture;
    if (position == "left")
        this->draw.x = 5;
    else
        this->draw.x = Util::getInstance()->getLogicalWindowWidth() * Util::getInstance()->getScalingConstant() - surface->w - 5;
    this->draw.y = 5;
    this->draw.w = surface->w;
    this->draw.h = surface->h;
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}

Text::~Text(){
    SDL_DestroyTexture(this->textTexture);
}

void Text::Draw() {
    SDL_RenderCopy(this->renderer, this->textTexture, NULL, &draw);
}
