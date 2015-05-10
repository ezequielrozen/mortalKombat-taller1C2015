#include "CharacterSprite.h"
#include "Painter.h"
#include "../../controller/GameController.h"

CharacterSprite::CharacterSprite(SDL_Renderer* pRenderer, char* path, float x, float y, float w, float h,
								 int frames, string OponentSide, bool repearLastSp, bool colorAltered, Painter* painter)
{
	oponentSide = OponentSide;
    this->renderer = pRenderer;
    this->texture = NULL;
    yPosition = 0;
    initiated = false;
    finished = false;
	SDL_Surface* surface = IMG_Load(path);
	if (colorAltered) {
		SDL_LockSurface(surface);
		painter->paint(surface);
		SDL_UnlockSurface(surface);
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

void CharacterSprite::Play(float Speed, float width)
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

        draw.w = width*Util::getInstance()->getScalingConstant();

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

        int vec[framesX+1];
        vec[0] =0;
        vec[1] =92;
        vec[2] =204;
        vec[3] =308;
        vec[4] =582;
        vec[5] =850;
        vec[6] =1124;
        vec[7] =1394;
        vec[8] =1643;
        vec[9] =1860;

        crop.x = vec[CurrentFrame];
        crop.w = vec[CurrentFrame+1] - vec[CurrentFrame];

        draw.w = crop.w * Util::getInstance()->getScalingConstant();



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
    if (!initiated) {
        draw.y = passedY * Util::getInstance()->getScalingYConstant();
    }
}

void CharacterSprite::reset() {
    CurrentFrame = 0;
    crop.x = 0;
    crop.y = 0;
}

void CharacterSprite::switchSide(const char c) {
    this->oponentSide = (c == 'l') ? "LEFT" : "RIGHT";
}

void CharacterSprite::vibrate() {
    if (!initiated) {
        yPosition = draw.y;
        initiated = true;
    } else {
        draw.y = yPosition + Util::getInstance()->getLogicalWindowHeight() * Util::getInstance()->getScalingYConstant() * 0.05 * (-1) * sin(vibrateProgress);
        vibrateProgress += VIBRATION_SPEED;
    }

    if (vibrateProgress >= VIBRATION_DURATION) {
        draw.y = yPosition;
        vibrateProgress = 0;
        initiated = false;
        finished = true;
    }
}

bool CharacterSprite::vibrationFinished() {
    return finished;
}

void CharacterSprite::resetFinished() {
    finished = false;
    vibrateProgress = 0;
    initiated = false;
}

bool CharacterSprite::getRepeatLastSprite()
{
	return this->repeatLastSprite;
}

void CharacterSprite::setRepeatLastSprite(bool repeat)
{
	this->repeatLastSprite = repeat;
}
