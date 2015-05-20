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

    std::list<Layer*>::iterator it = this->stage->getLayers()->begin();

    int i = 0;

    // We load the sprites and put them into an array
    for(it; it != this->stage->getLayers()->end(); it++) {
        layerSprites[i] = new LayerSprite(this->renderer,(*it)->getPath(),screenWidth,screenHeight, (*it)->getWidth());
        //cout << "paths; " << (*it)->getPath() << endl;

        i++;
    }
    SDL_Rect characterOneNameDraw;
    characterOneNameDraw.x = 5;
    string charName = character->getName();
    transform(charName.begin(), charName.end(), charName.begin(), ::toupper);
    characterName = new Text(charName.c_str(), this->renderer, "left");

    SDL_Rect characterTwoNameDraw;
    characterOneNameDraw.x = 5;
    string charTwoName = character2->getName();
    transform(charTwoName.begin(), charTwoName.end(), charTwoName.begin(), ::toupper);
    characterTwoName = new Text(charTwoName.c_str(), this->renderer, "right");

    this->currenFramePrevious = 0;
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
    if (scorpionShootOne != NULL ) delete  scorpionShootOne;
    if (scorpionShootTwo != NULL ) delete  scorpionShootTwo;
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
    if (raidenShootOne != NULL ) delete  raidenShootOne;
    if (raidenShootTwo != NULL ) delete  raidenShootTwo;
    if (raidenShootThree != NULL ) delete  raidenShootThree;
    if (raidenShootFour != NULL ) delete  raidenShootFour;
    if (raidenShootFive != NULL ) delete  raidenShootFive;
    if (raidenShootSix != NULL ) delete  raidenShootSix;
    if (raidenShootSeven != NULL ) delete  raidenShootSeven;
    if (raidenShootEight != NULL ) delete  raidenShootEight;
    if (raidenShootNine != NULL ) delete  raidenShootNine;
    if (raidenShootTen != NULL ) delete  raidenShootTen;
    if (raidenShootEleven != NULL ) delete 	raidenShootEleven;
    if (raidenShootZero != NULL ) delete	raidenShootZero;
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
            this->runCharacter();
            layerSprites[i]->update((*it)->getLeft_border());
            layerSprites[i]->Draw();
            painted = true;
        } else {
            layerSprites[i]->update((*it)->getLeft_border());
            layerSprites[i]->Draw();
        }
        //if(GameController::isVibrating())
        if(InputController::isVibrating())
            if (!layerSprites[i]->vibrationFinished())
                layerSprites[i]->vibrate();
            else
                //GameController::setVibrating(false);
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
        this->runCharacter();
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
            					scorpionDuckKick,scorpionJumpKick,scorpionPunchJump,scorpionDuckPunch,scorpionHighPunch,scorpionLowPunch,scorpionWinner,
                                scorpionBodyParts,scorpionFinisher,scorpionShoot,scorpionShootOne, scorpionShootTwo,
                                scorpionDizzy,scorpionFall,scorpionBeingHit,scorpionBeingHitDown, scorpionBlockDown,
                                scorpionBlock,scorpionHead,false);
            this->loadAsScorpion(raidenWalk,raidenStance,raidenJump,raidenDuck,raidenSideJump,raidenHighKick,raidenLowKick,
            		raidenDuckKick,raidenJumpKick,raidenPunchJump,raidenDuckPunch,raidenPunch,raidenLowPunch,raidenWinner,
                                raidenBodyParts,raidenFinisher,raidenShoot,raidenShootOne, raidenShootTwo,
                                raidenDizzy,raidenFall,raidenBeingHit,raidenBeingHitDown, raidenBlockDown,
                                raidenBlock,raidenHead,colorAltered);
        } else {
            this->loadAsRaiden(scorpionWalk,scorpionStance,scorpionJump,scorpionSideJump,scorpionDuck,scorpionHighKick,scorpionLowKick,
            					scorpionDuckKick,scorpionJumpKick, scorpionPunchJump,scorpionDuckPunch,scorpionHighPunch,scorpionLowPunch,scorpionWinner,scorpionBodyParts,
                                scorpionFinisher,scorpionShoot,scorpionShootZero,scorpionShootOne,scorpionShootTwo,scorpionShootThree,
                                scorpionShootFour,scorpionShootFive,scorpionShootSix,scorpionShootSeven,scorpionShootEight,
                                scorpionShootNine,scorpionShootTen,scorpionShootEleven,scorpionDizzy,scorpionFall,scorpionBeingHit,
                                scorpionBeingHitDown,scorpionBlockDown,scorpionBlock,scorpionHead, false);
            this->loadAsRaiden(raidenWalk,raidenStance,raidenJump,raidenSideJump,raidenDuck,raidenHighKick,raidenLowKick,
            		raidenDuckKick,raidenJumpKick,raidenPunchJump,raidenDuckPunch,raidenPunch,raidenLowPunch,raidenWinner,raidenBodyParts,
                                raidenFinisher,raidenShoot,raidenShootZero,raidenShootOne,raidenShootTwo,raidenShootThree,
                                raidenShootFour,raidenShootFive,raidenShootSix,raidenShootSeven,raidenShootEight,
                                raidenShootNine,raidenShootTen,raidenShootEleven,raidenDizzy,raidenFall,raidenBeingHit,
                                raidenBeingHitDown,raidenBlockDown,raidenBlock,raidenHead, colorAltered);
        }
    }

    if (name1 == "scorpion" && name2 == "raiden") {
        this->loadAsScorpion(scorpionWalk,scorpionStance,scorpionJump,scorpionDuck,scorpionSideJump,scorpionHighKick,scorpionLowKick,
							 scorpionDuckKick,scorpionJumpKick, scorpionPunchJump,scorpionDuckPunch,scorpionHighPunch,scorpionLowPunch,scorpionWinner,
							 scorpionBodyParts,scorpionFinisher,scorpionShoot,scorpionShootOne, scorpionShootTwo,
							 scorpionDizzy,scorpionFall,scorpionBeingHit,scorpionBeingHitDown, scorpionBlockDown,
							 scorpionBlock,scorpionHead,false);
        this->loadAsRaiden(raidenWalk,raidenStance,raidenJump,raidenSideJump,raidenDuck,raidenHighKick,raidenLowKick,
        		raidenDuckKick,raidenJumpKick,raidenPunchJump,raidenDuckPunch,raidenPunch,raidenLowPunch,raidenWinner,raidenBodyParts,
                           raidenFinisher,raidenShoot,raidenShootZero,raidenShootOne,raidenShootTwo,raidenShootThree,
                           raidenShootFour,raidenShootFive,raidenShootSix,raidenShootSeven,raidenShootEight,
                           raidenShootNine,raidenShootTen,raidenShootEleven,raidenDizzy,raidenFall,raidenBeingHit,
                           raidenBeingHitDown,raidenBlockDown,raidenBlock,raidenHead, false);
    } else if (name1 == "raiden" && name2 == "scorpion") {
        this->loadAsRaiden(scorpionWalk,scorpionStance,scorpionJump,scorpionSideJump,scorpionDuck,scorpionHighKick,scorpionLowKick,
        					scorpionDuckKick,scorpionJumpKick,scorpionPunchJump,scorpionDuckPunch,scorpionHighPunch,scorpionLowPunch,scorpionWinner,scorpionBodyParts,
                           scorpionFinisher,scorpionShoot,scorpionShootZero,scorpionShootOne,scorpionShootTwo,scorpionShootThree,
                           scorpionShootFour,scorpionShootFive,scorpionShootSix,scorpionShootSeven,scorpionShootEight,
                           scorpionShootNine,scorpionShootTen,scorpionShootEleven,scorpionDizzy,scorpionFall,scorpionBeingHit,
                           scorpionBeingHitDown,scorpionBlockDown,scorpionBlock,scorpionHead, false);
        this->loadAsScorpion(raidenWalk,raidenStance,raidenJump,raidenDuck,raidenSideJump,raidenHighKick,raidenLowKick,
        		raidenDuckKick,raidenJumpKick,raidenPunchJump,raidenDuckPunch,raidenPunch,raidenLowPunch,raidenWinner,
                             raidenBodyParts,raidenFinisher,raidenShoot,raidenShootOne, raidenShootTwo,
                             raidenDizzy,raidenFall,raidenBeingHit,raidenBeingHitDown, raidenBlockDown,
                             raidenBlock,raidenHead,false);
    }

    scorpionSprites = {{"Stance", scorpionStance},{"MovingRight", scorpionWalk},{"MovingLeft", scorpionWalk},{"Jumping", scorpionJump},{"JumpingRight", scorpionSideJump},
    {"JumpingLeft", scorpionSideJump},{"Ducking", scorpionDuck},{"HighKickHitting", scorpionHighKick},{"DuckingKickHitting", scorpionDuckKick},{"PunchLeftJumping", scorpionPunchJump},
    {"PunchRightJumping", scorpionPunchJump},{"HighPunchHitting", scorpionHighPunch},{"Victory", scorpionWinner},{"LowPunchHitting", scorpionDuckPunch},
    {"FINISHER", scorpionFinisher},{"Blocking", scorpionBlock},{"WeaponHitting", scorpionShoot},{"Dizzy", scorpionDizzy},{"ReceivingDuckingPunch", scorpionFall},
    {"RecevingHit", scorpionBeingHit},{"BEINGHITDOWN", scorpionBeingHitDown},{"BLOCKDOWN", scorpionBlockDown}, {"LowKickHitting",scorpionLowKick},
    {"JumpKickHitting",scorpionJumpKick},{"LowPunchHitting",scorpionLowPunch}, {"LowKickHitting", scorpionLowKick}};

    raidenSprites = {{"Stance", raidenStance},{"MovingRight", raidenWalk},{"MovingLeft", raidenWalk},{"Jumping", raidenJump},{"JumpingRight", raidenSideJump},
	{"JumpingLeft", raidenSideJump},{"Ducking", raidenDuck},{"HighKickHitting", raidenHighKick},{"DuckingKickHitting", raidenDuckKick},{"PunchLeftJumping", raidenPunchJump},
	{"PunchRightJumping", raidenPunchJump},{"HighPunchHitting", raidenPunch},{"Victory", raidenWinner},{"DuckPunchHitting", raidenDuckPunch},
	{"FINISHER", raidenFinisher},{"Blocking", raidenBlock},{"SHOOT", raidenShoot},{"Dizzy", raidenDizzy},{"FALLING", raidenFall},
	{"RecevingHit", raidenBeingHit},{"BEINGHITDOWN", raidenBeingHitDown},{"BLOCKDOWN", raidenBlockDown},{"LowKickHitting",raidenLowKick},
    {"JumpKickHitting",raidenJumpKick},{"LowPunchHitting",raidenLowPunch},{"LowKickHitting", raidenLowKick}};

}

void GameView::loadAsScorpion(CharacterSprite*& walk, CharacterSprite*& stance, CharacterSprite*& jump, CharacterSprite*& duck, CharacterSprite*& sideJump,
                              CharacterSprite*& highKick,CharacterSprite*& lowKick, CharacterSprite*& dukKick,CharacterSprite*& jumpKick, CharacterSprite*& punchJump, CharacterSprite*& duckPunch,
                              CharacterSprite*& highPunch,CharacterSprite*& lowPunch, CharacterSprite*& winner, CharacterSprite*& bodyParts, CharacterSprite*& finisher,
                              CharacterSprite*& shoot, CharacterSprite*& shootOne, CharacterSprite*& shootTwo, CharacterSprite*& dizzy,
                              CharacterSprite*& fall, CharacterSprite*& beingHit, CharacterSprite*& beingHitDown, CharacterSprite*& blockDown,
                              CharacterSprite*& block, CharacterSprite*& head, bool colorAltered) {

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
    shoot = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_SHOOT), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 9, oponentSide, false, colorAltered, this->painter);
    shootOne = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_SHOOT_ONE), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 7, oponentSide, false, colorAltered, this->painter);
    shootTwo = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_SHOOT_TWO), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 4, oponentSide, true, colorAltered, this->painter);
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
                            CharacterSprite*& jumpKick,CharacterSprite*& punchJump,
                            CharacterSprite*& duckPunch, CharacterSprite*& highPunch,CharacterSprite*& lowPunch, CharacterSprite*& winner, CharacterSprite*& bodyParts,
                            CharacterSprite*& finisher, CharacterSprite*& shoot, CharacterSprite*& shootZero, CharacterSprite*& shootOne,
                            CharacterSprite*& shootTwo, CharacterSprite*& sootThree, CharacterSprite*& shootFour, CharacterSprite*& shootFive,
                            CharacterSprite*& shootSix, CharacterSprite*& shootSeven, CharacterSprite*& shootEight, CharacterSprite*& shootNine,
                            CharacterSprite*& shootTen, CharacterSprite*& shootEleven, CharacterSprite*& dizzy, CharacterSprite*& fall,
                            CharacterSprite*& beingHit, CharacterSprite*& beingHitDown, CharacterSprite*& blockDown, CharacterSprite*& block,
                            CharacterSprite*& head, bool colorAltered) {
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
    highPunch = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_HIGH_PUNCH), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 9, oponentSide, false, colorAltered, this->painter);
    lowPunch = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_LOW_PUNCH), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 9, oponentSide, false, colorAltered, this->painter);
    winner = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_WINNER), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 14, oponentSide, false, colorAltered, this->painter);
    bodyParts = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_BODYPARTS), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 8, oponentSide, false, colorAltered, this->painter);
    finisher = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_FINISHER), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 26, oponentSide, false, colorAltered, this->painter);
    shoot = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_SHOOT), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 4, oponentSide, true, colorAltered, this->painter);
    shootZero = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_SHOOT_ZERO), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 1, oponentSide, false, colorAltered, this->painter);
    shootOne = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_SHOOT_ONE), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 1, oponentSide, false, colorAltered, this->painter);
    shootTwo = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_SHOOT_TWO), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 1, oponentSide, false, colorAltered, this->painter);
    sootThree = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_SHOOT_THREE), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 1, oponentSide, false, colorAltered, this->painter);
    shootFour = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_SHOOT_FOUR), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 1, oponentSide, false, colorAltered, this->painter);
    shootFive = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_SHOOT_FIVE), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 1, oponentSide, false, colorAltered, this->painter);
    shootSix = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_SHOOT_SIX), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 1, oponentSide, false, colorAltered, this->painter);
    shootSeven = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_SHOOT_SEVEN), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 1, oponentSide, false, colorAltered, this->painter);
    shootEight = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_SHOOT_EIGHT), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 1, oponentSide, false, colorAltered, this->painter);
    shootNine = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_SHOOT_NINE), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 1, oponentSide, false, colorAltered, this->painter);
    shootTen = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_SHOOT_TEN), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 1, oponentSide, false, colorAltered, this->painter);
    shootEleven = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_SHOOT_ELEVEN), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 1, oponentSide, false, colorAltered, this->painter);
    dizzy = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_DIZZY), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 7, oponentSide, false, colorAltered, this->painter);
    fall = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_FALL), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 12, oponentSide, true, colorAltered, this->painter);
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
	scorpionShootOne->reset();
	scorpionShootTwo->reset();
	scorpionDizzy->reset();
	scorpionBeingHit->reset();
    scorpionBeingHitDown->reset();
	scorpionBlockDown->reset();
	scorpionBlock->reset();
}

void GameView::restartRaidenShootSprites() {
	raidenShoot->reset();
	raidenShootOne->reset();
	raidenShootTwo->reset();
    if (raidenShootThree != NULL) raidenShootThree->reset();
    if (raidenShootFour != NULL) raidenShootFour->reset();
    if (raidenShootFive != NULL) raidenShootFive->reset();
    if (raidenShootSix != NULL) raidenShootSix->reset();
    if (raidenShootSeven != NULL) raidenShootSeven->reset();
    if (raidenShootEight != NULL) raidenShootEight->reset();
    if (raidenShootNine != NULL) raidenShootNine->reset();
    if (raidenShootTen != NULL) raidenShootTen->reset();
    if (raidenShootEleven != NULL) raidenShootEleven->reset();
    if (raidenShootZero != NULL) raidenShootZero->reset();
	this->currenFramePrevious = 0;
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

	restartRaidenShootSprites();
}
void GameView::startRender() {
    SDL_RenderClear(renderer);
}

void GameView::endRender() {
    SDL_RenderPresent(renderer);
}

//Segun la distancia entre los oponentnes muestro el sprite mas ancho o lo contraigo.
//Esto trabaja igual q el codigo del Collider::checkHits para el bloque del SHOOT. Si se modifica aca se debe modificar tb alla.
double GameView::shootWidthCalculatedDistance() {
	double distancia;
	double distanciaMaxima = scorpion->getHitWidth() * 2;

	if(scorpion->getX() < raiden->getX()){
		distancia = raiden->getX() - (scorpion->getX() + scorpion->getHitWidth()-15);

		if (distancia>= distanciaMaxima)
		{
			return distanciaMaxima;
		}
		else
		{
			return distancia + 30;
		}
	}
	else
	{
		distancia = scorpion->getX() - (raiden->getX() + raiden->getHitWidth()-15);

		if (distancia>= distanciaMaxima)
		{
			return distanciaMaxima;
		}
		else
		{
			return distancia + 30;
		}
	}
}

//Segun la distancia entre los oponentnes muestro el sprite mas ancho o lo contraigo.
//Esto trabaja igual q el codigo del Collider::checkHits para el bloque del SHOOT. Si se modifica aca se debe modificar tb alla.
double GameView::shootWidthCalculatedDistanceRaiden() {
	double distancia;
	double distanciaMaxima = scorpion->getHitWidth() * 5;

	//si raiden esta en la derecha de la pantalla
	if(scorpion->getX() < raiden->getX()){
		distancia = raiden->getX() - (scorpion->getX() + scorpion->getHitWidth());

		if (distancia>= distanciaMaxima)
		{
			//cout << "max" << endl;
			return distanciaMaxima;
		}
		else
		{
			//cout << "30_1" << endl;
			return distancia + 30;
		}
	}
	else
	{
		distancia = scorpion->getX() - (raiden->getX() + raiden->getHitWidth());

		if (distancia>= distanciaMaxima)
		{
			//cout << "max2" << endl;
			return distanciaMaxima;
		}
		else
		{
			//cout << "30_2" << endl;
			return distancia + 30;
		}
	}
}
void GameView::runCharacter() {
    CharacterSprite* sprite = NULL;
    CharacterSprite* sprite2 = NULL;
    CharacterSprite* shootChar1 = NULL;
    CharacterSprite* shootChar2 = NULL;
    int currentFrame=-1;
    int currentFrame2=-1;
         
    bool aux = (scorpion->getX() < raiden->getX());

    if (scorpion->getState() != "WeaponHitting" && scorpion->getState() != "MovingRight" && scorpion->getState() != "MovingLeft") {
        sprite = scorpionSprites.at(scorpion->getState());
        sprite->Play(100, scorpion->getStateWidth());
    }
    else if ((scorpion->getState() == "MovingRight" && aux) || (scorpion->getState() == "MovingLeft" && !aux)) {
        sprite = scorpionSprites.at(scorpion->getState());
        sprite->Play(100, scorpion->getStateWidth());
    }
    else if ((scorpion->getState() == "MovingRight" && !aux) || (scorpion->getState() == "MovingLeft" && aux)) {
        sprite = scorpionSprites.at(scorpion->getState());
        sprite->PlayBack(100);
    }else if (scorpion->getState() == "WeaponHitting"){
    	sprite = scorpionSprites.at("Stance");
		sprite->Play(100, scorpion->getStateWidth());

    	shootChar1 = scorpionSprites.at(scorpion->getState());
    	shootChar1->Play(100, scorpion->getStateWidth());
    	cout << "shoot" << endl;
    }
    
    aux = (raiden->getX() < scorpion->getX());

    if (raiden->getState() != "WeaponHitting" && raiden->getState() != "MovingRight" && raiden->getState() != "MovingLeft") {
        sprite2 = raidenSprites.at(raiden->getState());
        sprite2->Play(100, raiden->getStateWidth());
    }
    else if ((raiden->getState() == "MovingRight" && aux) || (raiden->getState() == "MovingLeft" && !aux)) {
        sprite2 = raidenSprites.at(raiden->getState());
        sprite2->Play(100, raiden->getStateWidth());
    }
    else if ((raiden->getState() == "MovingRight" && !aux) || (raiden->getState() == "MovingLeft" && aux)) {
        sprite2 = raidenSprites.at(raiden->getState());
        sprite2->PlayBack(100);
    }

    /*
    else if (raiden->getHit() == "SHOOT") {
    		sprite2 = raidenShoot;

    		currentFrame2 = sprite2->PlayShoot(200, raiden->getHitWidth());
    		float aux = 0;
    		float prop = aux/3;
//    		cout << currentFrame2 << " - " << currenFramePrevious << " - " << prop << endl;

    		//*****************************Sprites de salida del disparo*****************************
			if (currentFrame2 == 0 && (currenFramePrevious == 0 )){
				shootChar2 = raidenShootZero;
				shootChar2->PlayShoot2(100*prop, 50);
				currenFramePrevious = 0;
			}else if (currentFrame2 == 1 && currenFramePrevious == 0){
				shootChar2 = raidenShootOne;
				shootChar2->PlayShoot2(100*prop, 50);
				currenFramePrevious = 0;
			}else if (currentFrame2 == 2 && currenFramePrevious == 0){
				shootChar2 = raidenShootTwo;
				shootChar2->PlayShoot2(100*prop, 50);
				currenFramePrevious = 0;
			}else if (currentFrame2 == 3 && currenFramePrevious == 0){
				shootChar2 = raidenShootThree;
				shootChar2->PlayShoot2(100*prop, 50);
				currenFramePrevious = 0;
			}else if (currentFrame2 == 4 && currenFramePrevious == 0){
					shootChar2 = raidenShootFour;
					shootChar2->PlayShoot2(100*prop, shootWidthCalculatedDistanceRaiden());
					currenFramePrevious = 5;
			//*****************************Sprites de desplazamiento del disparo*********************
			}else if (currenFramePrevious >= 5 && currenFramePrevious <= 7){
				shootChar2 = raidenShootFive;
				shootChar2->PlayShoot2(70*prop, shootWidthCalculatedDistanceRaiden());
				currenFramePrevious++;
			}else if (currenFramePrevious == 8){
				shootChar2 = raidenShootSix;
				shootChar2->PlayShoot2(150*prop, shootWidthCalculatedDistanceRaiden());
				currenFramePrevious++;
			//*****************************Sprites de llegada del disparo****************************
			}else if (currenFramePrevious >= 9 && currenFramePrevious <= 15){
				shootChar2 = raidenShootSeven;
				shootChar2->PlayShoot2(150*prop, scorpion->getWidth());
				currenFramePrevious++;
			}else if (currenFramePrevious >= 16 && currenFramePrevious <= 20){
				shootChar2 = raidenShootEight;
				shootChar2->PlayShoot2(150*prop, scorpion->getWidth());
				currenFramePrevious++;
			}else if (currenFramePrevious >= 15 && currenFramePrevious <= 20){
				shootChar2 = raidenShootNine;
				shootChar2->PlayShoot2(150*prop, scorpion->getWidth());
				currenFramePrevious++;
			}else if (currenFramePrevious >= 21 && currenFramePrevious <= 25){
				shootChar2 = raidenShootTen;
				shootChar2->PlayShoot2(150*prop, scorpion->getWidth());
				currenFramePrevious++;
			}else if (currenFramePrevious >= 26 && currenFramePrevious <= 35){
				shootChar2 = raidenShootEleven;
				shootChar2->PlayShoot2(150*prop, scorpion->getWidth());
				currenFramePrevious++;
			}else
			{
				if (currenFramePrevious > 35){
					shootChar2 = NULL;
					this->currenFramePrevious = 0;
//					restartRaidenShootSprites();
				}
			}
    }
   
    */

    if(scorpion->getX() < raiden->getX()){
        sprite->switchSide('r');
        sprite2->switchSide('l');

        if (shootChar1 != NULL) {
        	shootChar1->switchSide('r');
			shootChar1->setX(scorpion->getX() + scorpion->getHitWidth()-15);
			shootChar1->setY(scorpion->getY()+20);
        }
        if (shootChar2 != NULL) {
			shootChar2->switchSide('l');
			shootChar2->setY(raiden->getY()+20);
			RaidenShootSetPosX(currentFrame2, shootChar2);

		}
    }else{
        sprite->switchSide('l');
        sprite2->switchSide('r');

        if (shootChar1 != NULL) {
        	shootChar1->switchSide('l');
        	shootChar1->setX(scorpion->getX() - (shootWidthCalculatedDistance())+15);
			shootChar1->setY(scorpion->getY()+20);
        }

        if (shootChar2 != NULL) {
			shootChar2->switchSide('r');
			shootChar2->setY(raiden->getY()+20);
			RaidenShootSetPosX(currentFrame2, shootChar2);
		}
    }

	sprite->setX(scorpion->getX());
    sprite->setY(scorpion->getY());

    //if (GameController::isVibrating())
    if(InputController::isVibrating())
        if(!sprite->vibrationFinished())
            sprite->vibrate();
        else
        	//GameController::setVibrating(false);
			InputController::setVibrating(false);
    else
        sprite->resetFinished();


    sprite2->setX(raiden->getX());
    sprite2->setY(raiden->getY());

    //if (GameController::isVibrating())
	if(InputController::isVibrating())
        if(!sprite2->vibrationFinished())
           sprite2->vibrate();
        else
        	//GameController::setVibrating(false);
			InputController::setVibrating(false);
    else
        sprite2->resetFinished();

    if (raiden->isHitting()) {
        sprite->Draw();
        sprite2->Draw();
    }
    else {
        sprite2->Draw();
        sprite->Draw();
    }

    if (shootChar1 != NULL) {
    	shootChar1->Draw();
    }

    if (shootChar2 != NULL) {
    	shootChar2->Draw();
    }

}

void GameView::RaidenShootSetPosX(int currentFrame2, CharacterSprite* shootChar2 )
{
	int signo =  (scorpion->getX() < raiden->getX()) ? -1 : 1;
	if (currentFrame2 <= 4)
		shootChar2->setX(raiden->getX());
	if (currenFramePrevious >= 5 && currenFramePrevious <= 9 )
		//estos son los sprites del desplazamiento del tiro, los estiro un poco para q parece q lo traspasan algunas "esquirlas"
		shootChar2->setX(raiden->getX() + (signo * (shootWidthCalculatedDistanceRaiden())/*+(signo*scorpion->getWidth()*5/2)*/));
	if (this->currenFramePrevious >= 10)
		shootChar2->setX(raiden->getX() + signo * shootWidthCalculatedDistanceRaiden());
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
    scorpionShootOne=NULL;
    scorpionShootTwo=NULL;
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
    raidenShootOne=NULL;
    raidenShootTwo=NULL;
    raidenShootThree=NULL;
    raidenShootFour=NULL;
    raidenShootFive=NULL;
    raidenShootSix=NULL;
    raidenShootSeven=NULL;
    raidenShootEight=NULL;
    raidenShootNine=NULL;
    raidenShootTen=NULL;
    raidenShootEleven=NULL;
    raidenShootZero=NULL;
    raidenDizzy=NULL;
    raidenFall=NULL;
    raidenBeingHit=NULL;
    scorpionBeingHitDown=NULL;
    raidenBlockDown=NULL;
    raidenBlock=NULL;
    raidenHead=NULL;
}
