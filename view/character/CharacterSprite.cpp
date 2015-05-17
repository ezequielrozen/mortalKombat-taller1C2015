#include "CharacterSprite.h"
#include "Painter.h"
//#include "../../controller/GameController.h"
#include "../../controller/InputController.h"

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

//void CharacterSprite::PlayShoot(float Speed, float characterWidth) {
//
//    if (animationDelay+Speed < SDL_GetTicks())
//    {
//        if ((this->framesX - 1) <= CurrentFrame)
//        {
//        	if (this->getRepeatLastSprite())
//        		CurrentFrame = this->framesX -1;
//        	else
//        		CurrentFrame = 0;
//        }
//        else{
//            CurrentFrame++;
//        }
//
//        if (CurrentFrame == 0)
//        {
//        	shootInitialPosX = draw.x;
//        }
//
//        //vector con las posiciones X de donde comienza cada sprite en el spriteSheet.
//        int vec[framesX+1][framesX+1];
//        vec[0][0] =0; 		vec[0][1] = 0;
//        vec[1][0] =92; 		vec[1][1] = -4;
//        vec[2][0] =204;		vec[2][1] = 50;
//        vec[3][0] =308;		vec[3][1] = -3;
//        vec[4][0] =582;		vec[4][1] = 3;
//        vec[5][0] =850;		vec[5][1] = -2;
//        vec[6][0] =1124;		vec[6][1] = 3;
//        vec[7][0] =1394;		vec[7][1] = -1;
//        vec[8][0] =1643;		vec[8][1] = -10;
//        vec[9][0] =1860;		vec[9][1] = 0;
//
//
//
//        crop.x = vec[CurrentFrame][0];
//        crop.w = vec[CurrentFrame+1][0] - vec[CurrentFrame][0];
//
//        //Seteo el ancho para el render segun el ancho de la imagen
//        draw.w = crop.w * Util::getInstance()->getScalingConstant();
//
//        //Lo escalo para q se ajuste dependiendo del ancho del personaje. El spritesheet se hizo para el ancho default: ANCHOPERSONAJE=68.
//        draw.w = draw.w * ((characterWidth * Util::getInstance()->getScalingConstant()) / (ANCHOPERSONAJE * Util::getInstance()->getScalingConstant()));
//
//
////        if (CurrentFrame <= 1)
////        {
////        	this->lastDraw_w = draw.w;
////        	this->lastDraw_x = draw.x;
////        }
////
////        cout << "w: " << draw.w  << endl;
////        cout << "x: " << draw.x  << endl;
////
////        if (lastDraw_w >= draw.w){
////        	this->draw.x -= (lastDraw_w - draw.w) * 0.3;
////        }else{
////        	this->draw.x += (draw.w - lastDraw_w)* 0.3;
////        }
////
////        this->lastDraw_x = draw.x;
////        this->lastDraw_w = draw.w;
//
//        draw.x += vec[CurrentFrame][1];
//        cout << draw.x  << endl;
//
//        animationDelay = SDL_GetTicks();
//
//    }
//}

int CharacterSprite::PlayShoot(float Speed, float characterWidth) {

    if (animationDelay+Speed < SDL_GetTicks())
    {
        if ((this->framesX ) <= CurrentFrame)
        {
        	if (this->getRepeatLastSprite()){
        		CurrentFrame = this->framesX -1;
        	}else{
        		CurrentFrame = 0;
        	}
        }
        else{
			draw.w = characterWidth*Util::getInstance()->getScalingConstant();

			crop.x = CurrentFrame * (img_width/this->framesX);
			crop.y = 0;
			crop.w = img_width/framesX;
			crop.h = img_height;

            CurrentFrame++;
        }
        animationDelay = SDL_GetTicks();
    }
//    cout << "shoot1 " << CurrentFrame << endl;
    return CurrentFrame;
}

void CharacterSprite::PlayShoot2(float Speed, float width)
{
    if (animationDelay+Speed < SDL_GetTicks())
    {
        if ((this->framesX) <= CurrentFrame)
        {
			CurrentFrame = 0;
        }
        else
            CurrentFrame++;

        draw.w = width*Util::getInstance()->getScalingConstant();
        draw.h= 30;

        crop.x = CurrentFrame * (img_width/framesX);
        crop.y = 0;
        crop.w = img_width/framesX;
        crop.h = img_height;

        animationDelay = SDL_GetTicks();
    }
//    cout << "shoot2 " << CurrentFrame << endl;
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
