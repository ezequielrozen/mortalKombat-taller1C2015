#ifndef MKSPRITE_H_
#define MKSPRITE_H_

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../../model/constantes.h"
#include "Painter.h"

using namespace std;

class CharacterSprite {
public:
	CharacterSprite(SDL_Renderer* passed_renderer, char* FilePath, float x,
			float y, float w, float h, int frames, string OponentSide,
			bool repearLastSprite, bool colorAltered, Painter* painter);

	~CharacterSprite(void);
	void Draw();

	void Play(float Speed, float width);
	void PlayBack(float Speed);
	float getX();
	void setX(float passedX);
	void setY(float passedY);
	void reset();
	void switchSide(const char c);
	bool getRepeatLastSprite();
	void setRepeatLastSprite(bool repeat);
	int PlayShootFire(float Speed, float width, float height);
	void PlayShoot2(float, float, float);
	void PlayShootIce(float Speed, float width, float height, bool isStarting);
	void PlayFall(float);
	void vibrate();
	bool vibrationFinished();
	void playBlock(float speed, float width);
	void PlayFatality(float Speed, float width);

	void resetFinished();

private:
	SDL_Texture* texture;

	SDL_Rect draw;

	SDL_Rect crop;
	int img_width;
	int img_height;
	int CurrentFrame;
	int animationDelay;
	int yPosition;
	int framesX;
	bool initiated;
	bool finished;

	float scalingConstant;

	string oponentSide;

	SDL_Renderer* renderer;

	bool repeatLastSprite;

	float vibrateProgress;
};

#endif /* MKSPRITE_H_ */
