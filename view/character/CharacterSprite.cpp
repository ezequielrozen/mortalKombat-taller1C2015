#include "CharacterSprite.h"
#include "../../model/util/Util.h"

CharacterSprite::CharacterSprite(SDL_Renderer* pRenderer, char* path, float x, float y, float w, float h, int frames, string OponentSide, bool repearLastSp)
{
	oponentSide = OponentSide;
    this->renderer = pRenderer;
    this->texture = NULL;
    this->texture = IMG_LoadTexture(renderer,path);

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
