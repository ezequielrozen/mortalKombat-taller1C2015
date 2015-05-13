#ifndef GAMEVIEW_H_
#define GAMEVIEW_H_

#include "../view/character/CharacterSprite.h"
#include "../model/MKCharacter.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../model/stage/Layer.h"
#include "stage/LayerSprite.h"
#include "../model/stage/Stage.h"
#include "stage/LifeView.h"
#include "character/Painter.h"
#include "Text.h"
#include <string>
#include <math.h>

using namespace std;

class GameView
{
public:
    GameView(float ScreenWidth, float ScreenHeight, MKCharacter* character, MKCharacter* character2,
             Stage* stage, string OponentSide, Painter* painter);
    ~GameView();
    void Render();
    void LoadSprites(string name1, string name2);

    void loadAsScorpion(CharacterSprite*& walk, CharacterSprite*& stance, CharacterSprite*& jump, CharacterSprite*& duck, CharacterSprite*& sideJump,
                        CharacterSprite*& kick, CharacterSprite*& kickDown, CharacterSprite*& punchJump, CharacterSprite*& punchUp,
                        CharacterSprite*& punch, CharacterSprite*& winner, CharacterSprite*& bodyParts, CharacterSprite*& finisher,
                        CharacterSprite*& shoot, CharacterSprite*& shootOne, CharacterSprite*& shootTwo, CharacterSprite*& dizzy,
                        CharacterSprite*& fall, CharacterSprite*& beingHit, CharacterSprite*& beingHitDown, CharacterSprite*& blockDown,
                        CharacterSprite*& block, CharacterSprite*& head, bool colorAltered);
    void loadAsRaiden(CharacterSprite*& walk, CharacterSprite*& stance, CharacterSprite*& jump, CharacterSprite*& sideJump,
                      CharacterSprite*& duck, CharacterSprite*& kick, CharacterSprite*& kickDown, CharacterSprite*& punchJump,
                      CharacterSprite*& punchUp, CharacterSprite*& punch, CharacterSprite*& winner, CharacterSprite*& bodyParts,
                      CharacterSprite*& finisher, CharacterSprite*& shoot, CharacterSprite*& shootZero, CharacterSprite*& shootOne,
                      CharacterSprite*& shootTwo, CharacterSprite*& sootThree, CharacterSprite*& shootFour, CharacterSprite*& shootFive,
                      CharacterSprite*& shootSix, CharacterSprite*& shootSeven, CharacterSprite*& shootEight, CharacterSprite*& shootNine,
                      CharacterSprite*& shootTen, CharacterSprite*& shootEleven, CharacterSprite*& dizzy, CharacterSprite*& fall,
                      CharacterSprite*& beingHit, CharacterSprite*& beingHitDown, CharacterSprite*& blockDown, CharacterSprite*& block,
                      CharacterSprite*& head, bool colorAltered);
    void startRender();
    void endRender();
    void initializeCharactersSprites();

private:

    MKCharacter* scorpion;
    MKCharacter* raiden;
    Stage* stage;

    Text* characterName;
    Text *characterTwoName;

    LifeView* characterOneLifebarView;
    LifeView* characterTwoLifebarView;
    CharacterSprite* scorpionWalk;
    CharacterSprite* scorpionStance;
    CharacterSprite* scorpionJump;
    CharacterSprite* scorpionDuck;
    CharacterSprite* scorpionSideJump;
    CharacterSprite* scorpionKick;
    CharacterSprite* scorpionKickDown;
    CharacterSprite* scorpionPunchJump;
    CharacterSprite* scorpionPunchUp;
    CharacterSprite* scorpionPunch;
    CharacterSprite* scorpionWinner;
    CharacterSprite* scorpionBodyParts;
    CharacterSprite* scorpionFinisher;
    CharacterSprite* scorpionShoot;
    CharacterSprite* scorpionShootZero;
    CharacterSprite* scorpionShootOne;
    CharacterSprite* scorpionShootTwo;
    CharacterSprite* scorpionShootThree;
    CharacterSprite* scorpionShootFour;
    CharacterSprite* scorpionShootFive;
    CharacterSprite* scorpionShootSix;
    CharacterSprite* scorpionShootSeven;
    CharacterSprite* scorpionShootEight;
    CharacterSprite* scorpionShootNine;
    CharacterSprite* scorpionShootTen;
    CharacterSprite* scorpionShootEleven;
    CharacterSprite* scorpionDizzy;
    CharacterSprite* scorpionFall;
    CharacterSprite* scorpionBeingHit;
    CharacterSprite* scorpionBeingHitDown;
    CharacterSprite* scorpionBlockDown;
    CharacterSprite* scorpionBlock;
    CharacterSprite* scorpionHead;


    CharacterSprite* raidenWalk;
    CharacterSprite* raidenStance;
    CharacterSprite* raidenJump;
    CharacterSprite* raidenDuck;
    CharacterSprite* raidenSideJump;
    CharacterSprite* raidenKick;
    CharacterSprite* raidenKickDown;
	CharacterSprite* raidenPunchJump;
	CharacterSprite* raidenPunchUp;
	CharacterSprite* raidenPunch;
	CharacterSprite* raidenWinner;
	CharacterSprite* raidenBodyParts;
	CharacterSprite* raidenFinisher;
	CharacterSprite* raidenShoot;
	CharacterSprite* raidenShootOne;
	CharacterSprite* raidenShootTwo;
	CharacterSprite* raidenShootThree;
	CharacterSprite* raidenShootFour;
	CharacterSprite* raidenShootFive;
	CharacterSprite* raidenShootSix;
	CharacterSprite* raidenShootSeven;
	CharacterSprite* raidenShootEight;
	CharacterSprite* raidenShootNine;
	CharacterSprite* raidenShootTen;
	CharacterSprite* raidenShootEleven;
	CharacterSprite* raidenShootZero;
	CharacterSprite* raidenDizzy;
	CharacterSprite* raidenFall;
	CharacterSprite* raidenBeingHit;
    CharacterSprite* raidenBeingHitDown;
    CharacterSprite* raidenBlockDown;
    CharacterSprite* raidenBlock;
	CharacterSprite* raidenHead;

    //list<LayerSprite*>* layerSprites = new list<LayerSprite*>();
    LayerSprite** layerSprites;
    int layerCount;

    SDL_Window* window;
    SDL_Renderer* renderer;
    float screenWidth;
    float screenHeight;
    string oponentSide;

    void runCharacter();
	void RestartAllScorpionSprites();
	void RestartAllRaidenSprites();
	double shootWidthCalculatedDistance();
	double shootWidthCalculatedDistanceRaiden();
	void restartRaidenShootSprites();
	void RaidenShootSetPosX(int currentFrame2, CharacterSprite* shootChar2);
    Painter* painter;

    int currenFramePrevious;

    void loadAsRaiden();
};

#endif /* GAMEVIEW_H_ */
