#include "CharacterSprite.h"

CharacterSprite::CharacterSprite(SDL_Renderer* pRenderer, string path, int x, int y, int w, int h, int frames, string OponentSide)
{
	oponentSide = OponentSide;
    this->renderer = pRenderer;
    this->texture = NULL;
    this->texture = IMG_LoadTexture(renderer,path.c_str());

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

    crop.x = 0;
    crop.y = 0;
    crop.w = img_width/frames;
    crop.h = img_height;

    CurrentFrame = 0;
    framesX = frames;

    animationDelay = 0;
}

void CharacterSprite::Play(float Speed)
{
    if (animationDelay+Speed < SDL_GetTicks())
    {

        if ((this->framesX - 1) <= CurrentFrame)
            CurrentFrame = 0;
        else
            CurrentFrame++;

        crop.x = CurrentFrame * (img_width/framesX);
        crop.y = 0;
        crop.w = img_width/framesX;
        crop.h = img_height;

        animationDelay = SDL_GetTicks();

    }
}

void CharacterSprite::PlayBack(float Speed) {

	if (animationDelay+Speed < SDL_GetTicks())
	{

		if (CurrentFrame <= 0)
			CurrentFrame = (this->framesX - 1);
	    else
	        CurrentFrame--;

		crop.x = CurrentFrame * (img_width/framesX);
		crop.y = 0;
	    crop.w = img_width/framesX;
	    crop.h = img_height;

	    animationDelay = SDL_GetTicks();
	}
}

CharacterSprite::~CharacterSprite(void)
{
    SDL_DestroyTexture(texture);
}

void CharacterSprite::Draw()
{
	SDL_RendererFlip flipType = SDL_FLIP_NONE;

	if (oponentSide == "LEFT")
	{
		flipType = SDL_FLIP_HORIZONTAL;
	}

	SDL_RenderCopyEx(renderer,texture,&crop, &draw,0,NULL,flipType);
}

int CharacterSprite::getX() {
	return draw.x;
}

void CharacterSprite::setX(int passedX) {
	draw.x = passedX;
}

void CharacterSprite::setY(int passedY) {
	draw.y = passedY;
}

void CharacterSprite::reset() {
    CurrentFrame = 0;
    crop.x = 0;
    crop.y = 0;
}
