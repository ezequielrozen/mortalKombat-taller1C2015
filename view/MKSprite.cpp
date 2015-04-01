#include "MKSprite.h"

MKSprite::MKSprite(SDL_Renderer* pRenderer, string path, int x, int y, int w, int h, int frames)
{
    renderer = pRenderer;
    texture = NULL;
    texture = IMG_LoadTexture(renderer,path.c_str());

    if (texture == NULL)
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

void MKSprite::Play(int BeginFrame, int EndFrame, float Speed)
{
    if (animationDelay+Speed < SDL_GetTicks())
    {

        if (EndFrame <= CurrentFrame)
            CurrentFrame = BeginFrame;
        else
            CurrentFrame++;

        crop.x = CurrentFrame * (img_width/framesX);
        crop.y = 0;
        crop.w = img_width/framesX;
        crop.h = img_height;

        animationDelay = SDL_GetTicks();

    }
}

void MKSprite::WalkBack(int BeginFrame, int EndFrame, float Speed) {

	if (animationDelay+Speed < SDL_GetTicks())
	{

		if (EndFrame >= CurrentFrame)
			CurrentFrame = BeginFrame;
	    else
	        CurrentFrame--;

		crop.x = CurrentFrame * (img_width/framesX);
		crop.y = 0;
	    crop.w = img_width/framesX;
	    crop.h = img_height;

	    animationDelay = SDL_GetTicks();
	}
}

MKSprite::~MKSprite(void)
{
    SDL_DestroyTexture(texture);
}

void MKSprite::Draw()
{
    SDL_RenderCopy(renderer,texture,&crop, &draw);
}

int MKSprite::getX() {
	return draw.x;
}

void MKSprite::setX(int passedX) {
	draw.x = passedX;
}

void MKSprite::reset() {
    CurrentFrame = 0;
    crop.x = 0;
    crop.y = 0;
}
