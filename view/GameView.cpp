#include <bits/algorithmfwd.h>
#include "GameView.h"
//#include "../controller/GameController.h"
#include "../controller/InputController.h"
#include "Text.h"
#include "SDL2/SDL.h"
#include "SoundManager.h"

GameView::GameView(SDL_Renderer* aRenderer, MKCharacter* character, MKCharacter* character2, Stage* pStage,
                   string OponentSide, Painter* painter, Timer* timer) {
	oponentSide = OponentSide;

    this->renderer = aRenderer;

    this->screenWidth = Util::getInstance()->getWindowWidth();
    this->screenHeight = Util::getInstance()->getWindowHeight();
    this->painter = painter;
    this->stage = pStage;
    this->scorpion = character;
    this->raiden = character2;

    initializeCharactersSprites();

 	this->LoadSprites(this->scorpion->getName(), this->raiden->getName());

    layerCount = this->stage->getLayers()->size();
    layerSprites = new LayerSprite*[layerCount-1];


    this->characterOneLifebarView = new LifeView(this->renderer, "data/lifebar.png", Util::getInstance()->getLogicalWindowWidth() * LIFEBAR_RELATIVE_WIDTH, false);
    this->characterTwoLifebarView = new LifeView(this->renderer, "data/lifebar.png", Util::getInstance()->getLogicalWindowWidth() * LIFEBAR_RELATIVE_WIDTH, true);

    // We load the sprites and put them into an array
    std::list<Layer*>::iterator it = this->stage->getLayers()->begin();
    int i = 0;
    for(it; it != this->stage->getLayers()->end(); it++) {
        layerSprites[i] = new LayerSprite(this->renderer,(*it)->getPath(),screenWidth,screenHeight, (*it)->getWidth());
        i++;
    }

    characterName = NULL;
    characterTwoName = NULL;
    this->setCharacterNames(character->getName(), character2->getName());

    this->timer = timer;
    int timeToShow = (TIME_TO_FIGHT_ENDING - this->timer->getCurrentTime()) / 1000;
    this->timerText = new Text((std::to_string(timeToShow).c_str()), this->renderer,"center");

    this->comboButtons = ComboButtonsView::getInstance();
    this->comboButtons->init(this->renderer);
    //this->comboButtons->addButton("asd");
    //this->comboButtons->addButton("asd");

    this->practiceMode = false;

    SoundManager::getInstance()->loadSounds();
    // Here we initialize SDL_mixer and then load each sound and music
}

GameView::~GameView() {
    cout << "init: " << scorpionSprites.size() << endl;
    if (timerText != NULL ) delete timerText;
    if (characterTwoName != NULL ) delete characterTwoName;
    if (characterName != NULL ) delete characterName;

    if (characterOneLifebarView != NULL ) delete characterOneLifebarView;
    if (characterTwoLifebarView != NULL ) delete characterTwoLifebarView;

    if (scorpionJump != NULL ) delete scorpionJump;
    if (scorpionWalk != NULL ) delete scorpionWalk;
    if (scorpionStance != NULL ) delete scorpionStance;
    if (scorpionSideJump != NULL ) delete scorpionSideJump;
    if (scorpionDuck != NULL ) delete scorpionDuck;
    if (scorpionHighKick != NULL ) delete  scorpionHighKick;
    if (scorpionLowKick != NULL ) delete  scorpionLowKick;
    if (scorpionDuckKick != NULL ) delete  scorpionDuckKick;
    if (scorpionJumpKick != NULL ) delete  scorpionJumpKick;
    if (scorpionPunchJump != NULL ) delete  scorpionPunchJump;
    if (scorpionDuckPunch != NULL ) delete  scorpionDuckPunch;
    //if (scorpionPunch != NULL ) delete  scorpionPunch;
    if (scorpionHighPunch != NULL ) delete  scorpionHighPunch;
    if (scorpionLowPunch != NULL ) delete  scorpionLowPunch;
    if (scorpionWinner != NULL ) delete  scorpionWinner;
    if (scorpionShoot != NULL ) delete  scorpionShoot;
    if (scorpionDizzy != NULL ) delete  scorpionDizzy;
    if (scorpionFall != NULL ) delete  scorpionFall;
    if (scorpionBeingHit != NULL ) delete  scorpionBeingHit;
    if (scorpionBeingHitDown != NULL ) delete scorpionBeingHitDown;
    if (scorpionBlockDown != NULL ) delete  scorpionBlockDown;
    if (scorpionBlock != NULL ) delete  scorpionBlock;
    if (scorpionFatalityHit != NULL ) delete  scorpionFatalityHit;
    if (scorpionFatalityFire != NULL ) delete  scorpionFatalityFire;
    if (scorpionReceivingFire != NULL ) delete  scorpionReceivingFire;
    if (scorpionTeleportation != NULL ) delete  scorpionTeleportation;
    if (scorpionShootIce != NULL ) delete  scorpionShootIce;
    if (scorpionWeaponIce != NULL ) delete  scorpionWeaponIce;
    if (scorpionWeaponIceImpacting != NULL) delete scorpionWeaponIceImpacting;


    if (raidenJump != NULL ) delete  raidenJump;
    if (raidenWalk != NULL ) delete raidenWalk;
    if (raidenStance != NULL) delete  raidenStance;
    if (raidenSideJump != NULL ) delete  raidenSideJump;
    if (raidenDuck != NULL ) delete  raidenDuck;
    if (raidenHighKick != NULL ) delete  raidenHighKick;
    if (raidenLowKick != NULL ) delete  raidenLowKick;
    if (raidenDuckKick != NULL ) delete  raidenDuckKick;
    if (raidenJumpKick != NULL ) delete  raidenJumpKick;
    if (raidenPunchJump != NULL ) delete  raidenPunchJump;
    if (raidenDuckPunch != NULL ) delete  raidenDuckPunch;
    if (raidenPunch != NULL ) delete  raidenPunch;
    //if (raidenHighPunch != NULL ) delete raidenHighPunch;
    if (raidenLowPunch != NULL ) delete  raidenLowPunch;
    if (raidenWinner != NULL ) delete  raidenWinner;
    if (raidenShoot != NULL ) delete  raidenShoot;
    if (raidenDizzy != NULL ) delete  raidenDizzy;
    if (raidenFall != NULL ) delete  raidenFall;
    if (raidenBeingHit != NULL ) delete  raidenBeingHit;
    if (raidenBeingHitDown != NULL ) delete  raidenBeingHitDown;
    if (raidenBlockDown != NULL ) delete  raidenBlockDown;
    if (raidenBlock != NULL ) delete  raidenBlock;
    if (raidenFatalityHit != NULL ) delete  raidenFatalityHit;
    if (raidenFatalityFire != NULL ) delete  raidenFatalityFire;
    if (raidenReceivingFire != NULL ) delete  raidenReceivingFire;
    if (raidenTeleportation != NULL ) delete  raidenTeleportation;
    if (raidenShootIce != NULL ) delete  raidenShootIce;
    if (raidenWeaponIce != NULL ) delete  raidenWeaponIce;
    if (raidenWeaponIceImpacting != NULL) delete raidenWeaponIceImpacting;


    for (int i = 0 ; i < layerCount ; i++) {
        delete layerSprites[i];
    }
    if (layerSprites != NULL ) delete layerSprites;

    cout << "END "  << endl;
    scorpionSprites.clear();
    raidenSprites.clear();
    scorpionSprites.~map();
    raidenSprites.~map();
    //cout << "end: " << scorpionSprites.size() << endl;

}

void GameView::Render() {
    int i = 0;
    bool painted = false;
    // We render the layers' sprites iterating through the layerSprites' array
    
    std::list<Layer*>::iterator it = this->stage->getLayers()->begin();
    for(it; it != this->stage->getLayers()->end(); it++) {
        if (scorpion->getZ_index() == i+1) {
            
            if (this->raiden->isHitting()) {
                this->runCharacter(this->scorpion, this->raiden, this->scorpionSprites);
                this->runCharacter(this->raiden, this->scorpion, this->raidenSprites);
            }
            else {
                this->runCharacter(this->raiden, this->scorpion, this->raidenSprites);
                this->runCharacter(this->scorpion, this->raiden, this->scorpionSprites);
            }

            //this->runCharacter();
            layerSprites[i]->update((*it)->getLeft_border());
            layerSprites[i]->Draw();
            painted = true;
        } else {
            layerSprites[i]->update((*it)->getLeft_border());
            layerSprites[i]->Draw();
        }

        if(InputController::isVibrating())
            if (!layerSprites[i]->vibrationFinished())
                layerSprites[i]->vibrate();
            else
            	InputController::setVibrating(true);
        else
            layerSprites[i]->resetFinished();
        i++;
    }

    if (!practiceMode) {
        characterOneLifebarView->Draw(FULL_LIFE - this->scorpion->getLife());
        characterTwoLifebarView->Draw(FULL_LIFE - this->raiden->getLife());
        characterName->Draw();
        characterTwoName->Draw();
    }
    comboButtons->draw();
    
    int timeToShow = (TIME_TO_FIGHT_ENDING - this->timer->getCurrentTime()) / 1000;
    this->timerText->update((std::to_string(timeToShow).c_str()));
    this->timerText->Draw();
    
    if (!painted) {
        if (this->raiden->isHitting()) {
            this->runCharacter(this->scorpion, this->raiden, this->scorpionSprites);
            this->runCharacter(this->raiden, this->scorpion, this->raidenSprites);
        }
        else {
            this->runCharacter(this->raiden, this->scorpion, this->raidenSprites);
            this->runCharacter(this->scorpion, this->raiden, this->scorpionSprites);
        }
        //this->runCharacter();
    }
    
}

void GameView::LoadSprites(string name1, string name2) {
    bool colorAltered = false;
    string name = "";

    if (name1 == name2) {
        colorAltered = true;
        name = name1;
    }
    if (name != "") {
        if (name == "scorpion") {
            this->loadAsScorpion(scorpionWalk,scorpionStance,scorpionJump,scorpionDuck,scorpionSideJump,scorpionHighKick,scorpionLowKick,
            					scorpionDuckKick,scorpionJumpKick,scorpionPunchJump,scorpionDuckPunch,scorpionHighPunch,scorpionLowPunch,
            					scorpionWinner, scorpionShoot, scorpionDizzy,scorpionFall,scorpionBeingHit,
            					scorpionBeingHitDown, scorpionBlockDown, scorpionBlock, scorpionFatalityHit, scorpionFatalityFire,
            					scorpionReceivingFire, scorpionTeleportation,scorpionShootIce,scorpionWeaponIce,scorpionWeaponIceImpacting, false);

            this->loadAsScorpion(raidenWalk,raidenStance,raidenJump,raidenDuck,raidenSideJump,raidenHighKick,raidenLowKick,
            		raidenDuckKick,raidenJumpKick,raidenPunchJump,raidenDuckPunch,raidenPunch,raidenLowPunch,raidenWinner,
                                raidenShoot, raidenDizzy,raidenFall,raidenBeingHit,raidenBeingHitDown,
                                raidenBlockDown, raidenBlock,raidenFatalityHit, raidenFatalityFire,raidenReceivingFire, raidenTeleportation,
                                 raidenShootIce,raidenWeaponIce, raidenWeaponIceImpacting,colorAltered);
        } else {
            this->loadAsRaiden(scorpionWalk,scorpionStance,scorpionJump,scorpionSideJump,scorpionDuck,scorpionHighKick,scorpionLowKick,
            					scorpionDuckKick,scorpionJumpKick, scorpionPunchJump,scorpionDuckPunch,scorpionHighPunch,scorpionLowPunch,
            					scorpionWinner, scorpionShoot,scorpionDizzy,scorpionFall,scorpionBeingHit,
                                scorpionBeingHitDown,scorpionBlockDown,scorpionBlock,scorpionFatalityHit, scorpionFatalityFire,
                                scorpionReceivingFire, scorpionTeleportation,scorpionShootIce,scorpionWeaponIce,scorpionWeaponIceImpacting, false);

            this->loadAsRaiden(raidenWalk,raidenStance,raidenJump,raidenSideJump,raidenDuck,raidenHighKick,raidenLowKick,
            		raidenDuckKick,raidenJumpKick,raidenPunchJump,raidenDuckPunch,raidenPunch,raidenLowPunch,raidenWinner,
                                raidenShoot,raidenDizzy,raidenFall,raidenBeingHit, raidenBeingHitDown,raidenBlockDown,raidenBlock,
                                raidenFatalityHit, raidenFatalityFire,raidenReceivingFire,raidenTeleportation,raidenShootIce,raidenWeaponIce,
                                raidenWeaponIceImpacting,colorAltered);
        }
    }

    if (name1 == "scorpion" && name2 == "raiden") {
        this->loadAsScorpion(scorpionWalk,scorpionStance,scorpionJump,scorpionDuck,scorpionSideJump,scorpionHighKick,scorpionLowKick,
							 scorpionDuckKick,scorpionJumpKick, scorpionPunchJump,scorpionDuckPunch,scorpionHighPunch,scorpionLowPunch,scorpionWinner,
							 scorpionShoot, scorpionDizzy,scorpionFall,scorpionBeingHit,scorpionBeingHitDown,
							 scorpionBlockDown, scorpionBlock,scorpionFatalityHit, scorpionFatalityFire,scorpionReceivingFire,
							 scorpionTeleportation,scorpionShootIce,scorpionWeaponIce,scorpionWeaponIceImpacting,false);

        this->loadAsRaiden(raidenWalk,raidenStance,raidenJump,raidenSideJump,raidenDuck,raidenHighKick,raidenLowKick,
        					raidenDuckKick,raidenJumpKick,raidenPunchJump,raidenDuckPunch,raidenPunch,raidenLowPunch,raidenWinner,
                           raidenShoot,raidenDizzy,raidenFall,raidenBeingHit,
                           raidenBeingHitDown,raidenBlockDown,raidenBlock,raidenFatalityHit, raidenFatalityFire,raidenReceivingFire,
                           raidenTeleportation, raidenShootIce,raidenWeaponIce,raidenWeaponIceImpacting,false);

    } else if (name1 == "raiden" && name2 == "scorpion") {

        this->loadAsRaiden(scorpionWalk,scorpionStance,scorpionJump,scorpionSideJump,scorpionDuck,scorpionHighKick,scorpionLowKick,
        					scorpionDuckKick,scorpionJumpKick,scorpionPunchJump,scorpionDuckPunch,scorpionHighPunch,scorpionLowPunch,scorpionWinner,
        					scorpionShoot,scorpionDizzy,scorpionFall,scorpionBeingHit,
        					scorpionBeingHitDown,scorpionBlockDown,scorpionBlock,scorpionFatalityHit, scorpionFatalityFire,scorpionReceivingFire,
        					scorpionTeleportation,raidenShootIce,raidenWeaponIce,raidenWeaponIceImpacting, false);

        this->loadAsScorpion(raidenWalk,raidenStance,raidenJump,raidenDuck,raidenSideJump,raidenHighKick,raidenLowKick,
        					raidenDuckKick,raidenJumpKick,raidenPunchJump,raidenDuckPunch,raidenPunch,raidenLowPunch,raidenWinner,
                             raidenShoot, raidenDizzy,raidenFall,raidenBeingHit,raidenBeingHitDown, raidenBlockDown,
                             raidenBlock,raidenFatalityHit, raidenFatalityFire,raidenReceivingFire,raidenTeleportation,
                             raidenShootIce,raidenWeaponIce, raidenWeaponIceImpacting,false);
    }

    scorpionSprites = {{"Stance", scorpionStance},{"MovingRight", scorpionWalk},{"MovingLeft", scorpionWalk},{"Jumping", scorpionJump},
    {"JumpingRight", scorpionSideJump}, {"JumpingLeft", scorpionSideJump},{"Ducking", scorpionDuck},{"HighKickHitting", scorpionHighKick},
    {"DuckingKickHitting", scorpionDuckKick},{"PunchLeftJumping", scorpionPunchJump}, {"PunchRightJumping", scorpionPunchJump},
    {"HighPunchHitting", scorpionHighPunch},{"Victory", scorpionWinner},{"DuckingPunch", scorpionDuckPunch},
    {"Blocking", scorpionBlock},{"WeaponHitting", scorpionShoot},{"Dizzy", scorpionDizzy},{"ReceivingDuckingPunch", scorpionFall},
    {"RecevingHit", scorpionBeingHit},{"ReceivingDuckingKick", scorpionFall},{"BLOCKDOWN", scorpionBlockDown}, {"LowKickHitting",scorpionLowKick},
    {"KickLeftJumpingHitting",scorpionJumpKick},{"KickRightJumpingHitting",scorpionJumpKick},{"LowPunchHitting",scorpionLowPunch},
    {"LowKickHitting", scorpionLowKick},{"FatalityHitting", scorpionFatalityHit},{"FireHitting", scorpionFatalityFire},
    {"ReceivingFire", scorpionReceivingFire},{"TeleportationDoing", scorpionTeleportation},{"WeaponHittingIce", scorpionShootIce},
                       {"WeaponIce", scorpionWeaponIce}, {"WeaponIceImpacting", scorpionWeaponIceImpacting}, {"ReceivingIce", scorpionDizzy}};

    raidenSprites = {{"Stance", raidenStance},{"MovingRight", raidenWalk},{"MovingLeft", raidenWalk},{"Jumping", raidenJump},
	{"JumpingRight", raidenSideJump},{"JumpingLeft", raidenSideJump},{"Ducking", raidenDuck},{"HighKickHitting", raidenHighKick},
	{"DuckingKickHitting", raidenDuckKick},{"PunchLeftJumping", raidenPunchJump},  {"PunchRightJumping", raidenPunchJump},
	{"HighPunchHitting", raidenPunch},{"Victory", raidenWinner},{"DuckingPunch", raidenDuckPunch},
	{"Blocking", raidenBlock},{"WeaponHitting", raidenShoot},{"Dizzy", raidenDizzy},{"ReceivingDuckingPunch", raidenFall},
	{"RecevingHit", raidenBeingHit},{"ReceivingDuckingKick", raidenFall},{"BLOCKDOWN", raidenBlockDown},{"LowKickHitting",raidenLowKick},
    {"KickLeftJumpingHitting",raidenJumpKick},{"KickRightJumpingHitting",raidenJumpKick},{"LowPunchHitting",raidenLowPunch},
    {"LowKickHitting", raidenLowKick},{"FatalityHitting", raidenFatalityHit},{"FireHitting", raidenFatalityFire},
    {"ReceivingFire", raidenReceivingFire},{"TeleportationDoing", raidenTeleportation},{"WeaponHittingIce", raidenShootIce},
    {"WeaponIce", raidenWeaponIce}, {"WeaponIceImpacting", raidenWeaponIceImpacting}, {"ReceivingIce", raidenDizzy}};

}

void GameView::loadAsScorpion(CharacterSprite*& walk, CharacterSprite*& stance, CharacterSprite*& jump, CharacterSprite*& duck,
							 CharacterSprite*& sideJump, CharacterSprite*& highKick,CharacterSprite*& lowKick, CharacterSprite*& dukKick,
							 CharacterSprite*& jumpKick, CharacterSprite*& punchJump, CharacterSprite*& duckPunch, CharacterSprite*& highPunch,
							 CharacterSprite*& lowPunch, CharacterSprite*& winner,
							 CharacterSprite*& shoot, CharacterSprite*& dizzy,CharacterSprite*& fall, CharacterSprite*& beingHit,
							 CharacterSprite*& beingHitDown, CharacterSprite*& blockDown, CharacterSprite*& block,
							 CharacterSprite*& fatalityHit, CharacterSprite*& fatalityFire, CharacterSprite*& onFire, CharacterSprite*& teleportation,
                              CharacterSprite*& shootIce,CharacterSprite*& weaponIce,CharacterSprite*&  weaponIceImpacting,
							 bool colorAltered) {

    walk = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_WALK) , scorpion->getX(),scorpion->getY(), scorpion->getWidth(),scorpion->getHeight(), 9, oponentSide, false, colorAltered, this->painter);
    stance = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_STANCE), scorpion->getX(),scorpion->getY(), scorpion->getWidth(),scorpion->getHeight(), 7, oponentSide, false, colorAltered,this->painter);
    jump = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_JUMP), scorpion->getX(),scorpion->getY(), scorpion->getWidth(),scorpion->getHeight(), 9, oponentSide, false, colorAltered, this->painter);
    sideJump = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_SIDEJUMP), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 8, oponentSide, false, colorAltered, this->painter);
    duck = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_DUCK), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 6, oponentSide, true, colorAltered, this->painter);
    highKick = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_HIGH_KICK), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 6, oponentSide, false, colorAltered, this->painter);
    lowKick = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_LOW_KICK), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 6, oponentSide, false, colorAltered, this->painter);
    dukKick = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_DUCKING_KICK), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 5, oponentSide, false, colorAltered, this->painter);
    jumpKick = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_JUMPING_KICK), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 1, oponentSide, false, colorAltered, this->painter);
    punchJump = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_PUNCHJUMP), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 1, oponentSide, false, colorAltered, this->painter);
    duckPunch = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_DUCK_PUNCH), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 5, oponentSide, false, colorAltered, this->painter);
    highPunch = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_HIGH_PUNCH), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 6, oponentSide, false, colorAltered, this->painter);
    lowPunch = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_LOW_PUNCH), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 6, oponentSide, false, colorAltered, this->painter);
    winner = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_WINNER), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 4, oponentSide, false, colorAltered, this->painter);
    shoot = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_SHOOT), scorpion->getX(), scorpion->getY(), scorpion->getWeapon()->getWidth(), scorpion->getWeapon()->getHeight(), 1, oponentSide, true, colorAltered, this->painter);
    dizzy = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_DIZZY), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 7, oponentSide, false, colorAltered, this->painter);
    fall = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_FALL), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 9, oponentSide, false, colorAltered, this->painter);
    beingHit = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_BEINGHIT), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 3, oponentSide, false, colorAltered, this->painter);
    beingHitDown = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_BEINGHIT_DOWN), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 3, oponentSide, false, colorAltered, this->painter);
    blockDown = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_BLOCKDOWN), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 2, oponentSide, true, colorAltered, this->painter);
    block = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_BLOCK), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 3, oponentSide, true, colorAltered, this->painter);

    fatalityHit = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_FATALITY_HIT), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 17, oponentSide, true, colorAltered, this->painter);
    fatalityFire = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_FALTALITY_FIRE), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 4, oponentSide, false, colorAltered, this->painter);
    onFire = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_ON_FIRE), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 14, oponentSide, true, colorAltered, this->painter);
    teleportation = new CharacterSprite(this->renderer, "data/characterTeleportation.png", scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 6, oponentSide, false, colorAltered, this->painter);
    shootIce = new CharacterSprite(this->renderer, "data/raiden/raidenShootingIce.png", scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 4, oponentSide, true, colorAltered, this->painter);
    weaponIce = new CharacterSprite(this->renderer, "data/raiden/raidenWeaponIce.png", scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 6, oponentSide, false, colorAltered, this->painter);
    weaponIceImpacting  = new CharacterSprite(this->renderer, "data/raiden/raidenWeaponIceImpacting.png", scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 5, oponentSide, false, colorAltered, this->painter);
}

void GameView::loadAsRaiden(CharacterSprite*& walk, CharacterSprite*& stance, CharacterSprite*& jump, CharacterSprite*& sideJump,
                            CharacterSprite*& duck, CharacterSprite*& highKick, CharacterSprite*& lowKick, CharacterSprite*& dukKick,
                            CharacterSprite*& jumpKick,CharacterSprite*& punchJump, CharacterSprite*& duckPunch, CharacterSprite*& highPunch,
                            CharacterSprite*& lowPunch, CharacterSprite*& winner,
                            CharacterSprite*& shoot, CharacterSprite*& dizzy, CharacterSprite*& fall, CharacterSprite*& beingHit,
                            CharacterSprite*& beingHitDown, CharacterSprite*& blockDown, CharacterSprite*& block,
                            CharacterSprite*& fatalityHit, CharacterSprite*& fatalityFire, CharacterSprite*& onFire,CharacterSprite*& teleportation,
                            CharacterSprite*& shootIce,CharacterSprite*& weaponIce, CharacterSprite*&  weaponIceImpacting,
                            bool colorAltered) {

    walk = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_WALK) , raiden->getX(),raiden->getY(), raiden->getWidth(),raiden->getHeight(), 9, oponentSide, false, colorAltered, this->painter);
    stance = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_STANCE), raiden->getX(),raiden->getY(), raiden->getWidth(),raiden->getHeight(), 10, oponentSide, false, colorAltered, this->painter);
    jump = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_JUMP), raiden->getX(),raiden->getY(), raiden->getWidth(),raiden->getHeight(), 4, oponentSide, false, colorAltered, this->painter);
    sideJump = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_SIDEJUMP), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 8, oponentSide, false, colorAltered, this->painter);
    duck = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_DUCK), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 6, oponentSide, true, colorAltered, this->painter);
    highKick = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_HIGH_KICK), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 6, oponentSide, false, colorAltered, this->painter);
    lowKick = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_LOW_KICK), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 6, oponentSide, false, colorAltered, this->painter);
    dukKick = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_DUCKING_KICK), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 5, oponentSide, false, colorAltered, this->painter);
    jumpKick = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_JUMPING_KICK), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 1, oponentSide, false, colorAltered, this->painter);
    punchJump = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_PUNCHJUMP), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 1, oponentSide, false, colorAltered, this->painter);
    duckPunch = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_DUCK_PUNCH), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 5, oponentSide, false, colorAltered, this->painter);
    highPunch = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_HIGH_PUNCH), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 6, oponentSide, false, colorAltered, this->painter);
    lowPunch = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_LOW_PUNCH), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 6, oponentSide, false, colorAltered, this->painter);
    winner = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_WINNER), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 14, oponentSide, false, colorAltered, this->painter);
    shoot = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_SHOOT), raiden->getX(), raiden->getY(), raiden->getWeapon()->getWidth(), raiden->getWeapon()->getHeight(), 1, oponentSide, true, colorAltered, this->painter);
    dizzy = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_DIZZY), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 7, oponentSide, false, colorAltered, this->painter);
    fall = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_FALL), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 12, oponentSide, false, colorAltered, this->painter);
    beingHit = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_BEINGHIT), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 4, oponentSide, false, colorAltered, this->painter);
    beingHitDown = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_BEINGHIT_DOWN), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 3, oponentSide, false, colorAltered, this->painter);
    blockDown = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_BLOCKDOWN), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 2, oponentSide, true, colorAltered, this->painter);
    block = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_BLOCK), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 3, oponentSide, true, colorAltered, this->painter);

    fatalityHit = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_FATALITY_HIT), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 17, oponentSide, true, colorAltered, this->painter);
	fatalityFire = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_FALTALITY_FIRE), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 4, oponentSide, false, colorAltered, this->painter);
	onFire = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_ON_FIRE), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 14, oponentSide, true, colorAltered, this->painter);
	teleportation = new CharacterSprite(this->renderer, "data/characterTeleportation.png", raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 6, oponentSide, false, colorAltered, this->painter);
	shootIce = new CharacterSprite(this->renderer, "data/raiden/raidenShootingIce.png", raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 4, oponentSide, true, colorAltered, this->painter);
	weaponIce = new CharacterSprite(this->renderer, "data/raiden/raidenWeaponIce.png", raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 6, oponentSide, false, colorAltered, this->painter);
	weaponIceImpacting  = new CharacterSprite(this->renderer, "data/raiden/raidenWeaponIceImpacting.png", raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 5, oponentSide, false, colorAltered, this->painter);
}

void GameView::restartAllScorpionSprites()
{
	scorpionFall->reset();
	scorpionDuck->reset();
	scorpionJump->reset();
	scorpionSideJump->reset();
	scorpionHighKick->reset();
	scorpionLowKick->reset();
	scorpionDuckKick->reset();
	scorpionJumpKick->reset();
	scorpionDuckPunch->reset();
	scorpionHighPunch->reset();
	scorpionLowPunch->reset();
	scorpionPunchJump->reset();
	scorpionShoot->reset();
	scorpionDizzy->reset();
	scorpionBeingHit->reset();
    scorpionBeingHitDown->reset();
	scorpionBlockDown->reset();
	scorpionBlock->reset();

	scorpionFatalityHit->reset();
	scorpionFatalityFire->reset();
	scorpionReceivingFire->reset();

}

void GameView::restartAllRaidenSprites()
{
	raidenFall->reset();
	raidenDuck->reset();
	raidenJump->reset();
	raidenSideJump->reset();
	raidenHighKick->reset();
	raidenDuckKick->reset();
	raidenJumpKick->reset();
	raidenDuckPunch->reset();
	raidenPunchJump->reset();
	raidenPunch->reset();
	raidenDizzy->reset();
	raidenBeingHit->reset();
	raidenBeingHitDown->reset();
	raidenBlockDown->reset();
	raidenBlock->reset();
	raidenShoot->reset();
	raidenShootIce->reset();
	raidenFatalityHit->reset();
	raidenFatalityFire->reset();
	raidenReceivingFire->reset();
	raidenWeaponIce->reset();
}

void GameView::startRender() {
    SDL_RenderClear(renderer);
}

void GameView::endRender() {
    SDL_RenderPresent(renderer);
}

void GameView::runCharacter(MKCharacter* character1, MKCharacter* character2, SpriteMap characterSprites) {
    CharacterSprite* sprite = NULL;
    CharacterSprite* shootChar = NULL;

    bool aux = (character1->getX() < character2->getX());

    if (character1->getState() != "WeaponHitting" && character1->getState() != "FireHitting" && character1->getState() != "WeaponHittingIce"
    		&& character1->getState() != "MovingRight" && character1->getState() != "MovingLeft"
            && character1->getState() != "FatalityHitting") {
        sprite = characterSprites.at(character1->getState());
        sprite->Play(6.66*GAMEDELAY, character1->getStateWidth());
    }
    else if ((character1->getState() == "MovingRight" && aux) || (character1->getState() == "MovingLeft" && !aux)) {
        sprite = characterSprites.at(character1->getState());
        sprite->Play(6.66*GAMEDELAY, character1->getStateWidth());
    }
    else if ((character1->getState() == "MovingRight" && !aux) || (character1->getState() == "MovingLeft" && aux)) {
        sprite = characterSprites.at(character1->getState());
        sprite->PlayBack(6.66*GAMEDELAY);
    }
    else if (character1->getState() == "WeaponHitting"){
        sprite = characterSprites.at("Stance");
        sprite->Play(6.66*GAMEDELAY, character1->getStateWidth());
    }
    else if (character1->getState() == "WeaponHittingIce"){
        sprite = characterSprites.at("WeaponHittingIce");
        sprite->Play(6.66*GAMEDELAY, character1->getStateWidth());
    }
    else if (character1->getState() == "FatalityHitting"){
        sprite = characterSprites.at("FatalityHitting");
        sprite->PlayFatality(6.66*GAMEDELAY, character1->getStateWidth());
    }

    if (character1->getWeapon()->isActive()) {
        shootChar = characterSprites.at("WeaponHitting");
        shootChar->PlayShoot2(6.66*GAMEDELAY, character1->getWeapon()->getWidth(), character1->getWeapon()->getHeight());
    }
    else if (character1->getWeaponFire()->isActive()) {
		shootChar = characterSprites.at("FireHitting");
		shootChar->PlayShootFire(9*GAMEDELAY, character1->getWeaponFire()->getWidth(), character1->getWeaponFire()->getHeight());
    }
    else if (character1->getWeaponIce()->isActive()) {
    	shootChar = characterSprites.at("WeaponIce");
		shootChar->PlayShootIce(4*GAMEDELAY, character1->getWeaponIce()->getWidth(), character1->getWeaponIce()->getHeight(), character1->getWeaponIce()->isStarting());
    }
    else if (character1->getWeaponIce()->getImpactingWeaponIce()){
    	shootChar = characterSprites.at("WeaponIceImpacting");
		shootChar->PlayShootFire(6*GAMEDELAY, character1->getWeaponIce()->getWidth()*1.8, character1->getWeaponIce()->getHeight()*4);
	}
	else {
		shootChar = NULL;
	}


    if(character1->getX() < character2->getX()) {
        sprite->switchSide('r');

        if (shootChar != NULL) {
            shootChar->switchSide('r');
            if (character1->getWeapon()->isActive()){
				shootChar->setX(character1->getWeapon()->getPositionX());
				shootChar->setY(character1->getWeapon()->getPositionY());
            }else if (character1->getWeaponFire()->isActive()) {
				shootChar->setX(character1->getWeaponFire()->getPositionX());
				shootChar->setY(character1->getWeaponFire()->getPositionY());
            }else if (character1->getWeaponIce()->isActive()) {
				shootChar->setX(character1->getWeaponIce()->getPositionX());
				shootChar->setY(character1->getWeaponIce()->getPositionY());
            }else if (character1->getWeaponIce()->getImpactingWeaponIce()){
            	shootChar->setX(character1->getWeaponIce()->getPositionX()+(character2->getWidth()*0.8));
				shootChar->setY(character1->getWeaponIce()->getPositionY());
            }
        }
    } 
    else {
        sprite->switchSide('l');

        if (shootChar != NULL) {
            shootChar->switchSide('l');
            if (character1->getWeapon()->isActive()){
            	shootChar->setX(character1->getWeapon()->getPositionX());
            	shootChar->setY(character1->getWeapon()->getPositionY());
            }else if (character1->getWeaponFire()->isActive()) {
				shootChar->setX(character1->getWeaponFire()->getPositionX());
				shootChar->setY(character1->getWeaponFire()->getPositionY());
            }else if (character1->getWeaponIce()->isActive()) {
				shootChar->setX(character1->getWeaponIce()->getPositionX());
				shootChar->setY(character1->getWeaponIce()->getPositionY());
            }else if (character1->getWeaponIce()->getImpactingWeaponIce()){
            	shootChar->setX(character1->getWeaponIce()->getPositionX()-character2->getWidth()*0.8);
				shootChar->setY(character1->getWeaponIce()->getPositionY());
            }
        }
    }

    sprite->setX(character1->getX());
    sprite->setY(character1->getY());

    //si esta pegando desde la derecha muevo el sprite un poco a la izqueierda para que impacte
    if(character1->getX() > character2->getX() && character1->isHitting()){
        sprite->setX(character1->getX() - (character1->getWidth()/2));
    }

    if(InputController::isVibrating())
        if(!sprite->vibrationFinished())
            sprite->vibrate();
        else
            InputController::setVibrating(false);
        else
            sprite->resetFinished();

    if (shootChar != NULL) {

        shootChar->Draw();
    }

    sprite->Draw();

}

void GameView::initializeCharactersSprites() {
    scorpionJump=NULL;
    scorpionWalk=NULL;
    scorpionStance=NULL;
    scorpionSideJump=NULL;
    scorpionDuck=NULL;
    scorpionHighKick=NULL;
    scorpionLowKick=NULL;
    scorpionDuckKick=NULL;
    scorpionJumpKick=NULL;
    scorpionPunchJump=NULL;
    scorpionDuckPunch=NULL;
    scorpionHighPunch=NULL;
    scorpionLowPunch=NULL;
    scorpionWinner=NULL;
    scorpionShoot=NULL;
    scorpionDizzy=NULL;
    scorpionFall=NULL;
    scorpionBeingHit=NULL;
    scorpionBlockDown=NULL;
    scorpionBlock=NULL;
    scorpionFatalityHit=NULL;
    scorpionFatalityFire=NULL;
    scorpionReceivingFire=NULL;
    scorpionShootIce = NULL;
    scorpionWeaponIce = NULL;
    scorpionWeaponIceImpacting = NULL;

    raidenWalk=NULL;
    raidenStance=NULL;
    raidenJump=NULL;
    raidenSideJump=NULL;
    raidenDuck=NULL;
    raidenHighKick=NULL;
    raidenDuckKick=NULL;
    raidenJumpKick=NULL;
    raidenPunchJump=NULL;
    raidenDuckPunch=NULL;
    raidenPunch=NULL;
    raidenWinner=NULL;
    raidenShoot=NULL;
    raidenDizzy=NULL;
    raidenFall=NULL;
    raidenBeingHit=NULL;
    scorpionBeingHitDown=NULL;
    raidenBlockDown=NULL;
    raidenBlock=NULL;
    raidenFatalityHit=NULL;
    raidenFatalityFire=NULL;
    raidenReceivingFire=NULL;
    raidenShootIce = NULL;
    raidenWeaponIce = NULL;
    raidenWeaponIceImpacting = NULL;
}

void GameView::loadMusicAndSounds() {
    //Initialize SDL_mixer
    stageBackgroundMusic = NULL;
//Initialize SDL
    if( SDL_Init((uint)SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        // Loggear
    } else {
        fx = Mix_LoadWAV( "data/Sounds/mk3-00100.wav");
        if( fx == NULL ) {
            printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
            // Cargar sonido "vacio" por default?
        }
    }

}

void GameView::enablePracticeMode() {
    this->practiceMode = true;
}

void GameView::disablePracticeMode() {
    this->practiceMode = true;
}

void GameView::setCharacterNames(string name1, string name2) {
    if (this->characterName != NULL) {
        delete this->characterName;
    }
    if (this->characterTwoName != NULL) {
        delete this->characterTwoName;
    }
    string charName = name1;
    transform(charName.begin(), charName.end(), charName.begin(), ::toupper);
    characterName = new Text(charName.c_str(), this->renderer, "left");

    string charTwoName = name2;
    transform(charTwoName.begin(), charTwoName.end(), charTwoName.begin(), ::toupper);
    characterTwoName = new Text(charTwoName.c_str(), this->renderer, "right");
}
