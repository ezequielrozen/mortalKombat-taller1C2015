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
#include "ComboButtonsView.h"
#include "../model/util/Timer.h"
#include <string>
#include <math.h>
#include <map>
#include <SDL2/SDL_mixer.h>

using namespace std;

typedef std::map<std::string, CharacterSprite*> SpriteMap;

class GameView
{
public:
    GameView(SDL_Renderer* aRenderer, MKCharacter* character, MKCharacter* character2,
             Stage* stage, string OponentSide, Painter* painter, Timer* timer);
    ~GameView();
    void Render();
    void LoadSprites(string name1, string name2);

    void loadAsScorpion(CharacterSprite*& walk, CharacterSprite*& stance, CharacterSprite*& jump, CharacterSprite*& duck, CharacterSprite*& sideJump,
                                  CharacterSprite*& highKick,CharacterSprite*& lowKick, CharacterSprite*& dukKick,CharacterSprite*& jumpKick, CharacterSprite*& punchJump, CharacterSprite*& duckPunch,
                                  CharacterSprite*& highPunch,CharacterSprite*& lowPunch, CharacterSprite*& winner,
                                  CharacterSprite*& shoot, CharacterSprite*& dizzy,  CharacterSprite*& fall, CharacterSprite*& beingHit,
                                  CharacterSprite*& beingHitDown, CharacterSprite*& blockDown,
                                  CharacterSprite*& block,CharacterSprite*& fatalityHit, CharacterSprite*& fatalityFire, CharacterSprite*& onFire,
                                  CharacterSprite*& teleportation, CharacterSprite*& shootIce,CharacterSprite*& weaponIce,CharacterSprite*&  weaponIceImpacting,
                                  bool colorAltered);
    void loadAsRaiden(CharacterSprite*& walk, CharacterSprite*& stance, CharacterSprite*& jump, CharacterSprite*& sideJump,
								CharacterSprite*& duck, CharacterSprite*& highKick, CharacterSprite*& lowKick, CharacterSprite*& dukKick,
								CharacterSprite*& punchJump, CharacterSprite*& duckPunch,CharacterSprite*& jumpKick, CharacterSprite*& highPunch,
								CharacterSprite*& lowPunch, CharacterSprite*& winner,
								CharacterSprite*& shoot,  CharacterSprite*& dizzy, CharacterSprite*& fall,
								CharacterSprite*& beingHit, CharacterSprite*& beingHitDown, CharacterSprite*& blockDown, CharacterSprite*& block,
								CharacterSprite*& fatalityHit, CharacterSprite*& fatalityFire, CharacterSprite*& onFire, CharacterSprite*& teleportation,
								CharacterSprite*& shootIce,CharacterSprite*& weaponIce,CharacterSprite*&  weaponIceImpacting, bool colorAltered);
    void startRender();
    void endRender();
    void initializeCharactersSprites();

    void enablePracticeMode();
    void disablePracticeMode();

private:

    MKCharacter* scorpion;
    MKCharacter* raiden;
    Stage* stage;

    Text* characterName;
    Text *characterTwoName;
    Text* timerText;
    Timer* timer;

    ComboButtonsView* comboButtons;

    SpriteMap scorpionSprites;
    SpriteMap raidenSprites;

    LifeView* characterOneLifebarView;
    LifeView* characterTwoLifebarView;
    CharacterSprite* scorpionWalk;
    CharacterSprite* scorpionStance;
    CharacterSprite* scorpionJump;
    CharacterSprite* scorpionDuck;
    CharacterSprite* scorpionSideJump;
    CharacterSprite* scorpionHighKick;
    CharacterSprite* scorpionLowKick;
    CharacterSprite* scorpionDuckKick;
    CharacterSprite* scorpionJumpKick;
    CharacterSprite* scorpionPunchJump;
    CharacterSprite* scorpionDuckPunch;
    CharacterSprite* scorpionHighPunch;
    CharacterSprite* scorpionLowPunch;
    CharacterSprite* scorpionWinner;
    CharacterSprite* scorpionShoot;
    CharacterSprite* scorpionDizzy;
    CharacterSprite* scorpionFall;
    CharacterSprite* scorpionBeingHit;
    CharacterSprite* scorpionBeingHitDown;
    CharacterSprite* scorpionBlockDown;
    CharacterSprite* scorpionBlock;
    CharacterSprite* scorpionFatalityHit;
    CharacterSprite* scorpionFatalityFire;
    CharacterSprite* scorpionReceivingFire;
    CharacterSprite* scorpionTeleportation;
    CharacterSprite* scorpionShootIce;
    CharacterSprite* scorpionWeaponIce;
    CharacterSprite* scorpionWeaponIceImpacting;

    CharacterSprite* raidenWalk;
    CharacterSprite* raidenStance;
    CharacterSprite* raidenJump;
    CharacterSprite* raidenDuck;
    CharacterSprite* raidenSideJump;
    CharacterSprite* raidenHighKick;
    CharacterSprite* raidenLowKick;
    CharacterSprite* raidenDuckKick;
    CharacterSprite* raidenJumpKick;
	CharacterSprite* raidenPunchJump;
	CharacterSprite* raidenDuckPunch;
	CharacterSprite* raidenPunch;
	CharacterSprite* raidenLowPunch;
	CharacterSprite* raidenWinner;
	CharacterSprite* raidenShoot;
	CharacterSprite* raidenDizzy;
	CharacterSprite* raidenFall;
	CharacterSprite* raidenBeingHit;
    CharacterSprite* raidenBeingHitDown;
    CharacterSprite* raidenBlockDown;
    CharacterSprite* raidenBlock;
    CharacterSprite* raidenFatalityHit;
    CharacterSprite* raidenFatalityFire;
    CharacterSprite* raidenReceivingFire;
    CharacterSprite* raidenTeleportation;
    CharacterSprite* raidenShootIce;
    CharacterSprite* raidenWeaponIce;
    CharacterSprite* raidenWeaponIceImpacting;

    LayerSprite** layerSprites;
    int layerCount;

    SDL_Renderer* renderer;
    float screenWidth;
    float screenHeight;
    string oponentSide;

    void runCharacter(MKCharacter* character1, MKCharacter* character2, SpriteMap characterSprites);
/*	void RestartAllScorpionSprites();
	void RestartAllRaidenSprites();*/
    Painter* painter;

    Mix_Music* stageBackgroundMusic;

    bool practiceMode;

    void loadMusicAndSounds();
};

#endif /* GAMEVIEW_H_ */
