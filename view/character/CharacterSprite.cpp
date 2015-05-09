#include "CharacterSprite.h"
#include "Painter.h"

CharacterSprite::CharacterSprite(SDL_Renderer* pRenderer, char* path, float x, float y, float w, float h,
								 int frames, string OponentSide, bool repearLastSp, bool colorAltered)
{
	oponentSide = OponentSide;
    this->renderer = pRenderer;
    this->texture = NULL;
	SDL_Surface* surface = IMG_Load(path);
	if (colorAltered) {
		Painter* painter = new Painter();
		SDL_LockSurface(surface);
		//paint here if it's necessary
		SDL_UnlockSurface(surface);
		delete painter;
	}
	this->texture = SDL_CreateTextureFromSurface(this->renderer,surface);
//    this->texture = IMG_LoadTexture(renderer,path);

    if (this->texture == NULL)
    {
        cout << "Couldn't Load " << path << endl;
        cout << IMG_GetError() << std::endl;
    }

    draw.x = x*Util::getInstance()->getScalingConstant();
    draw.y = y*Util::getInstance()->getScalingYConstant();
    draw.w = w*Util::getInstance()->getScalingConstant();
    draw.h = h*Util::getInstance()->getScalingYConstant();

    SDL_QueryTexture(texture,NULL,NULL, &img_width, &img_height);

    crop.x = 0;
    crop.y = 0;
    crop.w = img_width/frames;
    crop.h = img_height;

    CurrentFrame = 0;
    framesX = frames;

    animationDelay = 0;

    setRepeatLastSprite(repearLastSp);
}

void CharacterSprite::Play(float Speed)
{
    if (animationDelay+Speed < SDL_GetTicks())
    {

        if ((this->framesX - 1) <= CurrentFrame)
        {
        	if (this->getRepeatLastSprite())
        		CurrentFrame = this->framesX -1;
        	else
        		CurrentFrame = 0;
        }
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

void CharacterSprite::PlayShoot(float Speed) {

    if (animationDelay+Speed < SDL_GetTicks())
    {

        if ((this->framesX - 1) <= CurrentFrame)
        {
        	if (this->getRepeatLastSprite())
        		CurrentFrame = this->framesX -1;
        	else
        		CurrentFrame = 0;
        }
        else{
            CurrentFrame++;
        }

        if (CurrentFrame == 0)
        {
			crop.x = 0;
			crop.y = 0;
			crop.w = 140;
			crop.h = 135;
        }
        if (CurrentFrame == 1)
        {
			crop.x = 140;
			crop.y = 0;
			crop.w = 290-140;
			crop.h = 135;
        }
        if (CurrentFrame == 2)
        {
			crop.x = 290;
			crop.y = 0;
			crop.w = 425-290;
			crop.h = 135;
        }
        else if (CurrentFrame == 3)
        {
			crop.x = 425;
			crop.y = 0;
			crop.w = 803-425;
			crop.h = 135;
        }
        else if (CurrentFrame ==4)
        {
			crop.x = 803;
			crop.y = 0;
			crop.w = 1172-803;
			crop.h = 135;
        }
        else if (CurrentFrame == 5)
        {
			crop.x = 1172;
			crop.y = 0;
			crop.w = 1553-1172;
			crop.h = 135;
        }
        else if (CurrentFrame == 6)
        {
			crop.x = 1553;
			crop.y = 0;
			crop.w = 1922-1553;
			crop.h = 135;
        }
        else if (CurrentFrame == 7)
        {
			crop.x = 1922;
			crop.y = 0;
			crop.w = 2264-1922;
			crop.h = 135;
        }
        else if (CurrentFrame == 8)
        {
			crop.x = 2264;
			crop.y = 0;
			crop.w = 2565-2264;
			crop.h = 135;
        }

		draw.w = crop.w;

        animationDelay = SDL_GetTicks();

    }
}

void CharacterSprite::PlayFall(float Speed) {

	if (animationDelay+Speed < SDL_GetTicks())
	{
		if ((this->framesX - 1) <= CurrentFrame)
		{
			if (this->getRepeatLastSprite())
				CurrentFrame = this->framesX -1;
			else
				CurrentFrame = 0;
		}
		else
			CurrentFrame++;

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

void CharacterSprite::setX(float passedX) {
	draw.x = passedX*Util::getInstance()->getScalingConstant();
}

void CharacterSprite::setY(float passedY) {
	draw.y = passedY*Util::getInstance()->getScalingYConstant();

}

void CharacterSprite::reset() {
    CurrentFrame = 0;
    crop.x = 0;
    crop.y = 0;
}

void CharacterSprite::switchSide(const char c){
    this->oponentSide = (c == 'l') ? "LEFT" : "RIGHT";
}

bool CharacterSprite::getRepeatLastSprite()
{
	return this->repeatLastSprite;
}

void CharacterSprite::setRepeatLastSprite(bool repeat)
{
	this->repeatLastSprite = repeat;
}
