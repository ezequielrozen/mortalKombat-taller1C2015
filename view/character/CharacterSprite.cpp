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
