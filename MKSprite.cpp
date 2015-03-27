#include "MKSprite.h"

MKSprite::MKSprite(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h)
{
    renderer = passed_renderer;
    image = NULL;
    image = IMG_LoadTexture(renderer,FilePath.c_str());

    if (image == NULL)
    {
        std::cout << "Couldn't Load " << FilePath.c_str() << std::endl;
        std::cout << IMG_GetError() << std::endl;
    }

    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    SDL_QueryTexture(image,NULL,NULL, &img_width, &img_height);

    crop.x = 0;
    crop.y = 0;
    crop.w = 87;
    crop.h = 136;

    CurrentFrame = 0;
    Amount_Frame_X = 0;
    Amount_Frame_Y = 0;

    animationDelay = 0;
}

void MKSprite::SetUpAnimation(int passed_Amount_X, int passed_Amount_Y)
{
    Amount_Frame_X = passed_Amount_X;
    Amount_Frame_Y = passed_Amount_Y;
}

void MKSprite::Walk(int BeginFrame, int EndFrame, float Speed)
{
    if (animationDelay+Speed < SDL_GetTicks())
    {

        if (EndFrame <= CurrentFrame)
            CurrentFrame = BeginFrame;
        else
            CurrentFrame++;

        crop.x = CurrentFrame * (img_width/Amount_Frame_X);
        crop.y = 0;
        crop.w = img_width/Amount_Frame_X;
        crop.h = img_height/Amount_Frame_Y;

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

		crop.x = CurrentFrame * (img_width/Amount_Frame_X);
		crop.y = 0;
	    crop.w = img_width/Amount_Frame_X;
	    crop.h = img_height/Amount_Frame_Y;

	    animationDelay = SDL_GetTicks();
	}
}

MKSprite::~MKSprite(void)
{
    SDL_DestroyTexture(image);
}

void MKSprite::DrawSteady()
{
    SDL_RenderCopy(renderer,image,&crop, &rect);
}

int MKSprite::getX() {
	return rect.x;
}

void MKSprite::setX(int passedX) {
	rect.x = passedX;
}

