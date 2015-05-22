#include <bits/algorithmfwd.h>
#include "GameView.h"
//#include "../controller/GameController.h"
#include "../controller/InputController.h"
#include "Text.h"

GameView::GameView(float ScreenWidth, float ScreenHeight, MKCharacter* character, MKCharacter* character2, Stage* pStage, string OponentSide, Painter* painter) {
	oponentSide = OponentSide;
	this->window = NULL;
    this->window = SDL_CreateWindow("Mortal Kombat", 0, 0, (int) ScreenWidth, (int) ScreenHeight, SDL_WINDOW_SHOWN);

    if (this->window == NULL) {

        std::cout << "Window couldn't be created" << std::endl;
    }

    this->renderer = NULL;
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_TARGETTEXTURE);

    this->screenWidth = ScreenWidth;
    this->screenHeight = ScreenHeight;
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

    string charName = character->getName();
    transform(charName.begin(), charName.end(), charName.begin(), ::toupper);
    characterName = new Text(charName.c_str(), this->renderer, "left");

    string charTwoName = character2->getName();
    transform(charTwoName.begin(), charTwoName.end(), charTwoName.begin(), ::toupper);
    characterTwoName = new Text(charTwoName.c_str(), this->renderer, "right");
}

GameView::~GameView() {
    delete characterOneLifebarView;
    delete characterTwoLifebarView;

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
    if (scorpionHighPunch != NULL ) delete  scorpionHighPunch;
    if (scorpionLowPunch != NULL ) delete  scorpionLowPunch;
    if (scorpionWinner != NULL ) delete  scorpionWinner;
    if (scorpionBodyParts != NULL ) delete  scorpionBodyParts;
    if (scorpionFinisher != NULL ) delete  scorpionFinisher;
    if (scorpionShoot != NULL ) delete  scorpionShoot;
    if (scorpionDizzy != NULL ) delete  scorpionDizzy;
    if (scorpionFall != NULL ) delete  scorpionFall;
    if (scorpionBeingHit != NULL ) delete  scorpionBeingHit;
    if (scorpionBlockDown != NULL ) delete  scorpionBlockDown;
    if (scorpionBlock != NULL ) delete  scorpionBlock;
    if (scorpionHead != NULL ) delete  scorpionHead;
    if (raidenWalk != NULL ) delete  raidenWalk;

    if (raidenStance != NULL) delete  raidenStance;
    if (raidenJump != NULL ) delete  raidenJump;
    if (raidenSideJump != NULL ) delete  raidenSideJump;
    if (raidenDuck != NULL ) delete  raidenDuck;
    if (raidenHighKick != NULL ) delete  raidenHighKick;
    if (raidenDuckKick != NULL ) delete  raidenDuckKick;
    if (raidenJumpKick != NULL ) delete  raidenJumpKick;
    if (raidenPunchJump != NULL ) delete  raidenPunchJump;
    if (raidenDuckPunch != NULL ) delete  raidenDuckPunch;
    if (raidenPunch != NULL ) delete  raidenPunch;
    if (raidenWinner != NULL ) delete  raidenWinner;
    if (raidenBodyParts != NULL ) delete  raidenBodyParts;
    if (raidenFinisher != NULL ) delete  raidenFinisher;
    if (raidenShoot != NULL ) delete  raidenShoot;
    if (raidenDizzy != NULL ) delete  raidenDizzy;
    if (raidenFall != NULL ) delete  raidenFall;
    if (raidenBeingHit != NULL ) delete  raidenBeingHit;
    if (scorpionBeingHitDown != NULL ) delete  scorpionBeingHitDown;
    if (raidenBlockDown != NULL ) delete  raidenBlockDown;
    if (raidenBlock != NULL ) delete  raidenBlock;
    if (raidenHead != NULL ) delete  raidenHead;

    for (int i = 1 ; i < layerCount ; i++) {
        delete layerSprites[i];
    }
    delete layerSprites;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
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

    characterOneLifebarView->Draw(FULL_LIFE - this->scorpion->getLife());
    characterTwoLifebarView->Draw(FULL_LIFE - this->raiden->getLife());

    characterName->Draw();
    characterTwoName->Draw();
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
            					scorpionWinner, scorpionBodyParts,scorpionFinisher,scorpionShoot, scorpionDizzy,scorpionFall,scorpionBeingHit,
            					scorpionBeingHitDown, scorpionBlockDown, scorpionBlock,scorpionHead,false);

            this->loadAsScorpion(raidenWalk,raidenStance,raidenJump,raidenDuck,raidenSideJump,raidenHighKick,raidenLowKick,
            		raidenDuckKick,raidenJumpKick,raidenPunchJump,raidenDuckPunch,raidenPunch,raidenLowPunch,raidenWinner,
                                raidenBodyParts,raidenFinisher,raidenShoot, raidenDizzy,raidenFall,raidenBeingHit,raidenBeingHitDown,
                                raidenBlockDown, raidenBlock,raidenHead,colorAltered);
        } else {
            this->loadAsRaiden(scorpionWalk,scorpionStance,scorpionJump,scorpionSideJump,scorpionDuck,scorpionHighKick,scorpionLowKick,
            					scorpionDuckKick,scorpionJumpKick, scorpionPunchJump,scorpionDuckPunch,scorpionHighPunch,scorpionLowPunch,
            					scorpionWinner,scorpionBodyParts, scorpionFinisher,scorpionShoot,scorpionDizzy,scorpionFall,scorpionBeingHit,
                                scorpionBeingHitDown,scorpionBlockDown,scorpionBlock,scorpionHead, false);

            this->loadAsRaiden(raidenWalk,raidenStance,raidenJump,raidenSideJump,raidenDuck,raidenHighKick,raidenLowKick,
            		raidenDuckKick,raidenJumpKick,raidenPunchJump,raidenDuckPunch,raidenPunch,raidenLowPunch,raidenWinner,raidenBodyParts,
                                raidenFinisher,raidenShoot,raidenDizzy,raidenFall,raidenBeingHit, raidenBeingHitDown,raidenBlockDown,raidenBlock,
                                raidenHead, colorAltered);
        }
    }

    if (name1 == "scorpion" && name2 == "raiden") {
        this->loadAsScorpion(scorpionWalk,scorpionStance,scorpionJump,scorpionDuck,scorpionSideJump,scorpionHighKick,scorpionLowKick,
							 scorpionDuckKick,scorpionJumpKick, scorpionPunchJump,scorpionDuckPunch,scorpionHighPunch,scorpionLowPunch,scorpionWinner,
							 scorpionBodyParts,scorpionFinisher,scorpionShoot, scorpionDizzy,scorpionFall,scorpionBeingHit,scorpionBeingHitDown,
							 scorpionBlockDown, scorpionBlock,scorpionHead,false);

        this->loadAsRaiden(raidenWalk,raidenStance,raidenJump,raidenSideJump,raidenDuck,raidenHighKick,raidenLowKick,
        					raidenDuckKick,raidenJumpKick,raidenPunchJump,raidenDuckPunch,raidenPunch,raidenLowPunch,raidenWinner,raidenBodyParts,
                           raidenFinisher,raidenShoot,raidenDizzy,raidenFall,raidenBeingHit,
                           raidenBeingHitDown,raidenBlockDown,raidenBlock,raidenHead, false);

    } else if (name1 == "raiden" && name2 == "scorpion") {

        this->loadAsRaiden(scorpionWalk,scorpionStance,scorpionJump,scorpionSideJump,scorpionDuck,scorpionHighKick,scorpionLowKick,
        					scorpionDuckKick,scorpionJumpKick,scorpionPunchJump,scorpionDuckPunch,scorpionHighPunch,scorpionLowPunch,scorpionWinner,
        					scorpionBodyParts, scorpionFinisher,scorpionShoot,scorpionDizzy,scorpionFall,scorpionBeingHit,
        					scorpionBeingHitDown,scorpionBlockDown,scorpionBlock,scorpionHead, false);

        this->loadAsScorpion(raidenWalk,raidenStance,raidenJump,raidenDuck,raidenSideJump,raidenHighKick,raidenLowKick,
        					raidenDuckKick,raidenJumpKick,raidenPunchJump,raidenDuckPunch,raidenPunch,raidenLowPunch,raidenWinner,
                             raidenBodyParts,raidenFinisher,raidenShoot, raidenDizzy,raidenFall,raidenBeingHit,raidenBeingHitDown, raidenBlockDown,
                             raidenBlock,raidenHead,false);
    }

    scorpionSprites = {{"Stance", scorpionStance},{"MovingRight", scorpionWalk},{"MovingLeft", scorpionWalk},{"Jumping", scorpionJump},
    {"JumpingRight", scorpionSideJump}, {"JumpingLeft", scorpionSideJump},{"Ducking", scorpionDuck},{"HighKickHitting", scorpionHighKick},
    {"DuckingKickHitting", scorpionDuckKick},{"PunchLeftJumping", scorpionPunchJump}, {"PunchRightJumping", scorpionPunchJump},
    {"HighPunchHitting", scorpionHighPunch},{"Victory", scorpionWinner},{"DuckingPunch", scorpionDuckPunch}, {"FINISHER", scorpionFinisher},
    {"Blocking", scorpionBlock},{"WeaponHitting", scorpionShoot},{"Dizzy", scorpionDizzy},{"ReceivingDuckingPunch", scorpionFall},
    {"RecevingHit", scorpionBeingHit},{"ReceivingDuckingKick", scorpionFall},{"BLOCKDOWN", scorpionBlockDown}, {"LowKickHitting",scorpionLowKick},
    {"KickLeftJumpingHitting",scorpionJumpKick},{"KickRightJumpingHitting",scorpionJumpKick},{"LowPunchHitting",scorpionLowPunch},
    {"LowKickHitting", scorpionLowKick}};

    raidenSprites = {{"Stance", raidenStance},{"MovingRight", raidenWalk},{"MovingLeft", raidenWalk},{"Jumping", raidenJump},
	{"JumpingRight", raidenSideJump},{"JumpingLeft", raidenSideJump},{"Ducking", raidenDuck},{"HighKickHitting", raidenHighKick},
	{"DuckingKickHitting", raidenDuckKick},{"PunchLeftJumping", raidenPunchJump},  {"PunchRightJumping", raidenPunchJump},
	{"HighPunchHitting", raidenPunch},{"Victory", raidenWinner},{"DuckingPunch", raidenDuckPunch},{"FINISHER", raidenFinisher},
	{"Blocking", raidenBlock},{"WeaponHitting", raidenShoot},{"Dizzy", raidenDizzy},{"ReceivingDuckingPunch", raidenFall},
	{"RecevingHit", raidenBeingHit},{"ReceivingDuckingKick", raidenFall},{"BLOCKDOWN", raidenBlockDown},{"LowKickHitting",raidenLowKick},
    {"KickLeftJumpingHitting",raidenJumpKick},{"KickRightJumpingHitting",raidenJumpKick},{"LowPunchHitting",raidenLowPunch},
    {"LowKickHitting", raidenLowKick}};

}

void GameView::loadAsScorpion(CharacterSprite*& walk, CharacterSprite*& stance, CharacterSprite*& jump, CharacterSprite*& duck,
							 CharacterSprite*& sideJump, CharacterSprite*& highKick,CharacterSprite*& lowKick, CharacterSprite*& dukKick,
							 CharacterSprite*& jumpKick, CharacterSprite*& punchJump, CharacterSprite*& duckPunch, CharacterSprite*& highPunch,
							 CharacterSprite*& lowPunch, CharacterSprite*& winner, CharacterSprite*& bodyParts, CharacterSprite*& finisher,
							 CharacterSprite*& shoot, CharacterSprite*& dizzy,CharacterSprite*& fall, CharacterSprite*& beingHit,
							 CharacterSprite*& beingHitDown, CharacterSprite*& blockDown, CharacterSprite*& block, CharacterSprite*& head,
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
    bodyParts = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_BODYPARTS), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 8, oponentSide, false, colorAltered, this->painter);
    finisher = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_FINISHER), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 26, oponentSide, false, colorAltered, this->painter);
    shoot = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_SHOOT), scorpion->getX(), scorpion->getY(), scorpion->getWeapon()->getWidth(), scorpion->getWeapon()->getHeight(), 1, oponentSide, true, colorAltered, this->painter);
    dizzy = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_DIZZY), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 7, oponentSide, false, colorAltered, this->painter);
    fall = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_FALL), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 9, oponentSide, false, colorAltered, this->painter);
    beingHit = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_BEINGHIT), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 3, oponentSide, false, colorAltered, this->painter);
    beingHitDown = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_BEINGHIT_DOWN), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 3, oponentSide, false, colorAltered, this->painter);
    blockDown = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_BLOCKDOWN), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 2, oponentSide, true, colorAltered, this->painter);
    block = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_BLOCK), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 3, oponentSide, true, colorAltered, this->painter);
    head = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_HEAD), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 9, oponentSide, false, colorAltered, this->painter);
}

void GameView::loadAsRaiden(CharacterSprite*& walk, CharacterSprite*& stance, CharacterSprite*& jump, CharacterSprite*& sideJump,
                            CharacterSprite*& duck, CharacterSprite*& highKick, CharacterSprite*& lowKick, CharacterSprite*& dukKick,
                            CharacterSprite*& jumpKick,CharacterSprite*& punchJump, CharacterSprite*& duckPunch, CharacterSprite*& highPunch,
                            CharacterSprite*& lowPunch, CharacterSprite*& winner, CharacterSprite*& bodyParts, CharacterSprite*& finisher,
                            CharacterSprite*& shoot, CharacterSprite*& dizzy, CharacterSprite*& fall, CharacterSprite*& beingHit,
                            CharacterSprite*& beingHitDown, CharacterSprite*& blockDown, CharacterSprite*& block, CharacterSprite*& head,
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
    bodyParts = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_BODYPARTS), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 8, oponentSide, false, colorAltered, this->painter);
    finisher = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_FINISHER), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 26, oponentSide, false, colorAltered, this->painter);
    shoot = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_SHOOT), raiden->getX(), raiden->getY(), raiden->getWeapon()->getWidth(), raiden->getWeapon()->getHeight(), 1, oponentSide, true, colorAltered, this->painter);
    dizzy = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_DIZZY), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 7, oponentSide, false, colorAltered, this->painter);
    fall = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_FALL), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 12, oponentSide, false, colorAltered, this->painter);
    beingHit = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_BEINGHIT), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 4, oponentSide, false, colorAltered, this->painter);
    beingHitDown = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_BEINGHIT_DOWN), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 3, oponentSide, false, colorAltered, this->painter);
    blockDown = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_BLOCKDOWN), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 2, oponentSide, true, colorAltered, this->painter);
    block = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_BLOCK), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 3, oponentSide, true, colorAltered, this->painter);
    head = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_HEAD), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 9, oponentSide, false, colorAltered, this->painter);
}
void GameView::RestartAllScorpionSprites()
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
}


void GameView::RestartAllRaidenSprites()
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

    if (character1->getState() != "WeaponHitting" && character1->getState() != "MovingRight" && character1->getState() != "MovingLeft") {
        sprite = characterSprites.at(character1->getState());
        sprite->Play(100, character1->getStateWidth());
    }
    else if ((character1->getState() == "MovingRight" && aux) || (character1->getState() == "MovingLeft" && !aux)) {
        sprite = characterSprites.at(character1->getState());
        sprite->Play(100, character1->getStateWidth());
    }
    else if ((character1->getState() == "MovingRight" && !aux) || (character1->getState() == "MovingLeft" && aux)) {
        sprite = characterSprites.at(character1->getState());
        sprite->PlayBack(100);
    }
    else if (character1->getState() == "WeaponHitting"){
        sprite = characterSprites.at("Stance");
        sprite->Play(100, character1->getStateWidth());

        shootChar = characterSprites.at("WeaponHitting");
        shootChar->PlayShoot2(100, character1->getWeapon()->getWidth(), character1->getWeapon()->getHeight());
    }

    if (!character1->getWeapon()->isActive()) {
        shootChar = NULL;
    }

    if(character1->getX() < character2->getX()) {
        sprite->switchSide('r');

        if (shootChar != NULL) {
            shootChar->switchSide('r');
            shootChar->setX(character1->getWeapon()->getPositionX());
            shootChar->setY(character1->getWeapon()->getPositionY());
        }
    } 
    else {
        sprite->switchSide('l');

        if (shootChar != NULL) {
            shootChar->switchSide('l');
            shootChar->setX(character1->getWeapon()->getPositionX());
            shootChar->setY(character1->getWeapon()->getPositionY());
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

    sprite->Draw();

    if (shootChar != NULL) {
        shootChar->Draw();
    }

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
    scorpionBodyParts=NULL;
    scorpionFinisher=NULL;
    scorpionShoot=NULL;
    scorpionDizzy=NULL;
    scorpionFall=NULL;
    scorpionBeingHit=NULL;
    scorpionBlockDown=NULL;
    scorpionBlock=NULL;
    scorpionHead=NULL;
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
    raidenBodyParts=NULL;
    raidenFinisher=NULL;
    raidenShoot=NULL;
    raidenDizzy=NULL;
    raidenFall=NULL;
    raidenBeingHit=NULL;
    scorpionBeingHitDown=NULL;
    raidenBlockDown=NULL;
    raidenBlock=NULL;
    raidenHead=NULL;
}

