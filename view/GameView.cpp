#include <bits/algorithmfwd.h>
#include "GameView.h"
#include "../controller/GameController.h"
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

    delete scorpionJump;
	delete scorpionWalk;
    delete scorpionStance;
    delete scorpionSideJump;
    delete scorpionDuck;
    delete  scorpionKick;
    delete  scorpionKickDown;
    delete  scorpionPunchJump;
    delete  scorpionPunchUp;
    delete  scorpionPunch;
    delete  scorpionWinner;
    delete  scorpionBodyParts;
    delete  scorpionFinisher;
    delete  scorpionShoot;
    delete  scorpionShootOne;
    delete  scorpionShootTwo;
    delete  scorpionDizzy;
    delete  scorpionFall;
    delete  scorpionBeingHit;
    delete  scorpionBlockDown;
    delete  scorpionBlock;
    delete  scorpionHead;
    delete  raidenWalk;

    delete  raidenStance;
    delete  raidenJump;
    delete  raidenSideJump;
    delete  raidenDuck;
    delete  raidenKick;
    delete  raidenKickDown;
    delete  raidenPunchJump;
    delete  raidenPunchUp;
    delete  raidenPunch;
    delete  raidenWinner;
    delete  raidenBodyParts;
    delete  raidenFinisher;
    delete  raidenShoot;
    delete  raidenShootOne;
    delete  raidenShootTwo;
    delete  raidenShootThree;
    delete  raidenShootFour;
    delete  raidenShootFive;
    delete  raidenShootSix;
    delete  raidenShootSeven;
    delete  raidenShootEight;
    delete  raidenShootNine;
    delete  raidenShootTen;
    delete 	raidenShootEleven;
    delete	raidenShootZero;
    delete  raidenDizzy;
    delete  raidenFall;
    delete  raidenBeingHit;
    delete  scorpionBeingHitDown;
    delete  raidenBlockDown;
    delete  raidenBlock;
    delete  raidenHead;

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
        if(GameController::isVibrating())
            if (!layerSprites[i]->vibrationFinished())
                layerSprites[i]->vibrate();
            else
                GameController::setVibrating(false);
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
    if (name1 == name2) {
        colorAltered = true;
    }
	scorpionWalk = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_WALK) , scorpion->getX(),scorpion->getY(), scorpion->getWidth(),scorpion->getHeight(), 9, oponentSide, false, false, NULL);
    scorpionStance = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_STANCE), scorpion->getX(),scorpion->getY(), scorpion->getWidth(),scorpion->getHeight(), 7, oponentSide, false, false,NULL);
    scorpionJump = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_JUMP), scorpion->getX(),scorpion->getY(), scorpion->getWidth(),scorpion->getHeight(), 9, oponentSide, false, false, NULL);
    scorpionSideJump = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_SIDEJUMP), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 8, oponentSide, false, false, NULL);
    scorpionDuck = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_DUCK), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 6, oponentSide, true, false, NULL);
    scorpionKick = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_KICK), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 6, oponentSide, false, false, NULL);
    scorpionKickDown = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_KICKDOWN), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 5, oponentSide, false, false, NULL);
    scorpionPunchJump = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_PUNCHJUMP), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 3, oponentSide, false, false, NULL);
    scorpionPunchUp = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_PUNCHUP), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 5, oponentSide, false, false, NULL);
    scorpionPunch = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_PUNCH), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 6, oponentSide, false, false, NULL);
    scorpionWinner = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_WINNER), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 4, oponentSide, false, false, NULL);
    scorpionBodyParts = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_BODYPARTS), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 8, oponentSide, false, false, NULL);
    scorpionFinisher = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_FINISHER), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 26, oponentSide, false, false, NULL);
    scorpionShoot = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_SHOOT), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 9, oponentSide, false, false, NULL);
    scorpionShootOne = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_SHOOT_ONE), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 7, oponentSide, false, false, NULL);
    scorpionShootTwo = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_SHOOT_TWO), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 4, oponentSide, true, false, NULL);
    scorpionDizzy = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_DIZZY), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 7, oponentSide, false, false, NULL);
    scorpionFall = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_FALL), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 7, oponentSide, true, false, NULL);
    scorpionBeingHit = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_BEINGHIT), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 3, oponentSide, false, false, NULL);
    scorpionBeingHitDown = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_BEINGHIT_DOWN), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 3, oponentSide, false, false, NULL);
    scorpionBlockDown = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_BLOCKDOWN), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 2, oponentSide, true, false, NULL);
    scorpionBlock = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_BLOCK), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 3, oponentSide, true, false, NULL);
    scorpionHead = new CharacterSprite(this->renderer, scorpion->getFileMovement(MOVE_NAME_HEAD), scorpion->getX(), scorpion->getY(), scorpion->getWidth(), scorpion->getHeight(), 9, oponentSide, false, false, NULL);

    raidenWalk = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_WALK) , raiden->getX(),raiden->getY(), raiden->getWidth(),raiden->getHeight(), 9, oponentSide, false, colorAltered, this->painter);
	raidenStance = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_STANCE), raiden->getX(),raiden->getY(), raiden->getWidth(),raiden->getHeight(), 10, oponentSide, false, colorAltered, this->painter);
	raidenJump = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_JUMP), raiden->getX(),raiden->getY(), raiden->getWidth(),raiden->getHeight(), 4, oponentSide, false, colorAltered, this->painter);
	raidenSideJump = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_SIDEJUMP), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 8, oponentSide, false, colorAltered, this->painter);
	raidenDuck = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_DUCK), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 6, oponentSide, true, colorAltered, this->painter);
	raidenKick = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_KICK), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 5, oponentSide, false, colorAltered, this->painter);
	raidenKickDown = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_KICKDOWN), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 5, oponentSide, false, colorAltered, this->painter);
	raidenPunchJump = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_PUNCHJUMP), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 3, oponentSide, false, colorAltered, this->painter);
	raidenPunchUp = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_PUNCHUP), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 5, oponentSide, false, colorAltered, this->painter);
	raidenPunch = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_PUNCH), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 9, oponentSide, false, colorAltered, this->painter);
	raidenWinner = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_WINNER), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 14, oponentSide, false, colorAltered, this->painter);
	raidenBodyParts = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_BODYPARTS), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 8, oponentSide, false, colorAltered, this->painter);
	raidenFinisher = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_FINISHER), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 26, oponentSide, false, colorAltered, this->painter);
	raidenShoot = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_SHOOT), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 4, oponentSide, true, colorAltered, this->painter);
	raidenShootZero = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_SHOOT_ZERO), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 1, oponentSide, false, colorAltered, this->painter);
	raidenShootOne = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_SHOOT_ONE), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 1, oponentSide, false, colorAltered, this->painter);
	raidenShootTwo = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_SHOOT_TWO), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 1, oponentSide, false, colorAltered, this->painter);
	raidenShootThree = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_SHOOT_THREE), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 1, oponentSide, false, colorAltered, this->painter);
	raidenShootFour = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_SHOOT_FOUR), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 1, oponentSide, false, colorAltered, this->painter);
	raidenShootFive = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_SHOOT_FIVE), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 1, oponentSide, false, colorAltered, this->painter);
	raidenShootSix = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_SHOOT_SIX), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 1, oponentSide, false, colorAltered, this->painter);
	raidenShootSeven = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_SHOOT_SEVEN), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 1, oponentSide, false, colorAltered, this->painter);
	raidenShootEight = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_SHOOT_EIGHT), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 1, oponentSide, false, colorAltered, this->painter);
	raidenShootNine = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_SHOOT_NINE), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 1, oponentSide, false, colorAltered, this->painter);
	raidenShootTen = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_SHOOT_TEN), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 1, oponentSide, false, colorAltered, this->painter);
	raidenShootEleven = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_SHOOT_ELEVEN), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 1, oponentSide, false, colorAltered, this->painter);
	raidenDizzy = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_DIZZY), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 7, oponentSide, false, colorAltered, this->painter);
	raidenFall = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_FALL), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 12, oponentSide, true, colorAltered, this->painter);
	raidenBeingHit = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_BEINGHIT), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 4, oponentSide, false, colorAltered, this->painter);
	raidenBeingHitDown = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_BEINGHIT_DOWN), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 3, oponentSide, false, colorAltered, this->painter);
	raidenBlockDown = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_BLOCKDOWN), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 2, oponentSide, true, colorAltered, this->painter);
	raidenBlock = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_BLOCK), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 3, oponentSide, true, colorAltered, this->painter);
	raidenHead = new CharacterSprite(this->renderer, raiden->getFileMovement(MOVE_NAME_HEAD), raiden->getX(), raiden->getY(), raiden->getWidth(), raiden->getHeight(), 9, oponentSide, false, colorAltered, this->painter);

}
void GameView::RestartAllScorpionSprites()
{
	scorpionFall->reset();
	scorpionDuck->reset();
	scorpionJump->reset();
	scorpionSideJump->reset();
	scorpionKick->reset();
	scorpionKickDown->reset();
	scorpionPunchUp->reset();
	scorpionPunch->reset();
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
	raidenShootThree->reset();
	raidenShootFour->reset();
	raidenShootFive->reset();
	raidenShootSix->reset();
	raidenShootSeven->reset();
	raidenShootEight->reset();
	raidenShootNine->reset();
	raidenShootTen->reset();
	raidenShootEleven->reset();
	raidenShootZero->reset();
	this->currenFramePrevious = 0;
}

void GameView::RestartAllRaidenSprites()
{
	raidenFall->reset();
	raidenDuck->reset();
	raidenJump->reset();
	raidenSideJump->reset();
	raidenKick->reset();
	raidenKickDown->reset();
	raidenPunchUp->reset();
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
    CharacterSprite* shootChar1 = NULL;
    CharacterSprite* shootChar2 = NULL;
    int currentFrame=-1;
    int currentFrame2=-1;

    if (scorpion->isJumping() && scorpion->getJumpMovement() == "NONE" && scorpion->getHit() == "NONE") {
        sprite = scorpionJump;
        sprite->Play(300, scorpion->getWidth());
    }
    //HA: Aca hay q preguntar de q lado esta el oponente para ver si gira para un lado o el otro
    else if (scorpion->isJumping() && scorpion->getJumpMovement() == "RIGHT" && scorpion->getHit() == "NONE") {
        sprite = scorpionSideJump;
        sprite->Play(50, scorpion->getWidth());
    }
    else if (scorpion->isJumping() && scorpion->getJumpMovement() == "LEFT" && scorpion->getHit() == "NONE") {
        sprite = scorpionSideJump;
        sprite->PlayBack(50);
    }
    else if (scorpion->getHitReception() == "BEINGHIT") {
            sprite = scorpionBeingHit;
//            cout << "BEINGHIT" << endl;
            sprite->Play(150, scorpion->getWidth());
    } else if (scorpion->getHitReception() == "BEINGHITDOWN") {
            sprite = scorpionBeingHitDown;
//            cout << "BEINGHITDOWN" << endl;
            sprite->Play(150, scorpion->getHitWidth());
    }
    else if (scorpion->getHitReception() == "FALLING") {
            sprite = scorpionFall;
            sprite->Play(200, scorpion->getWidth());
    }
    else if (scorpion->getMovement() == "NONE" && scorpion->getHit() == "NONE") {
        sprite = scorpionStance;
        RestartAllScorpionSprites();
        sprite->Play(100, scorpion->getWidth());
    }
    else if (scorpion->getMovement() == "RIGHT" && scorpion->getHit() == "NONE") {
    	sprite = scorpionWalk;
    	if(scorpion->getX() < raiden->getX()){
    		sprite->Play(100, scorpion->getWidth());
		}else{
			sprite->PlayBack(100);
		}
    }
    else if (scorpion->getMovement() == "LEFT" && scorpion->getHit() == "NONE") {
    	sprite = scorpionWalk;
    	if(scorpion->getX() > raiden->getX()){
			sprite->Play(100, scorpion->getWidth());
		}else{
			sprite->PlayBack(100);
		}
    }
    else if (scorpion->getMovement() == "DUCK") {
        sprite = scorpionDuck;
        sprite->Play(20, scorpion->getWidth());
    }
    else if (scorpion->getHit() == "KICK") {
		sprite = scorpionKick;
		sprite->Play(100, scorpion->getHitWidth());
	}
    else if (scorpion->getHit() == "KICKDOWN") {
    		sprite = scorpionKickDown;
    		sprite->Play(100, scorpion->getHitWidth());
    }
    else if (scorpion->getHit() == "PUNCH") {
    		sprite = scorpionPunch;
    		sprite->Play(100, scorpion->getHitWidth());
    }
    else if (scorpion->getHit() == "SHOOT") {
    		sprite = scorpionShootOne;

    		currentFrame = sprite->PlayShoot(90, scorpion->getHitWidth());
    		if (currentFrame >= 3 && currentFrame <=6)
    		{
    			shootChar1 = scorpionShootTwo;
    			shootChar1->PlayShoot2(150, shootWidthCalculatedDistance());
    		}
    		else
    			shootChar1 = NULL;
    }
    else if (scorpion->getHit() == "DEFENSE") {
            sprite = scorpionBlock;
            sprite->Play(100, scorpion->getHitWidth());
    } else if (scorpion->getHit() == "DEFENSEDOWN") {
            sprite = scorpionBlockDown;
            sprite->Play(100, scorpion->getWidth());
    }
    else if (scorpion->getHit() == "DIZZY") {
    		sprite = scorpionDizzy;
    		sprite->Play(150, scorpion->getWidth());
    }
    else if ((scorpion->getHit() == "PUNCHJUMPLEFT" || scorpion->getHit() == "PUNCHJUMPRIGHT")) {
    	if (scorpion->isJumping() )
    	{
			sprite = scorpionPunchJump;
			sprite->Play(400, scorpion->getHitWidth());
    	}
    	else
    	{
            sprite = scorpionStance;
            RestartAllScorpionSprites();
            sprite->Play(100, scorpion->getWidth());
    	}
	}
    else if (scorpion->getHit() == "WINNER") {
    		sprite = scorpionWinner;
    		sprite->Play(150, scorpion->getHitWidth());
    }
    else if (scorpion->getHit() == "PUNCHUP") {
        		sprite = scorpionPunchUp;
        		sprite->Play(100, scorpion->getHitWidth());
	};

    /****************************************************************************************************/

    CharacterSprite* sprite2;

    if (raiden->isJumping() && raiden->getJumpMovement() == "NONE" && raiden->getHit() == "NONE") {
        sprite2 = raidenJump;
        sprite2->Play(700, raiden->getWidth());
    }
    //HA: Aca hay q preguntar de q lado esta el oponente para ver si gira para un lado o el otro
    else if (raiden->isJumping() && raiden->getJumpMovement() == "RIGHT" && raiden->getHit() == "NONE") {
        sprite2 = raidenSideJump;
        sprite2->Play(50, raiden->getWidth());
    }
    else if (raiden->isJumping() && raiden->getJumpMovement() == "LEFT" && raiden->getHit() == "NONE") {
        sprite2 = raidenSideJump;
        sprite2->PlayBack(50);
    }
    else if (raiden->getHitReception() == "BEINGHIT") {
            sprite2 = raidenBeingHit;
            sprite2->Play(100, raiden->getWidth());
    } else if (raiden->getHitReception() == "BEINGHITDOWN") {
            sprite2 = raidenBeingHitDown;
            sprite2->Play(100, raiden->getHitWidth());
    }
    else if (raiden->getHitReception() == "FALLING") {
            sprite2 = raidenFall;
            sprite2->Play(50, raiden->getWidth());
    }
    else if (raiden->getMovement() == "NONE" && raiden->getHit() == "NONE") {
        sprite2 = raidenStance;
        RestartAllRaidenSprites();
        sprite2->Play(50, raiden->getWidth());
    }
    else if (raiden->getMovement() == "RIGHT" && raiden->getHit() == "NONE") {
		sprite2 = raidenWalk;
		if(scorpion->getX() > raiden->getX()){
			sprite2->Play(100, raiden->getWidth());
		}else{
			sprite2->PlayBack(100);
		}
    }
    else if (raiden->getMovement() == "LEFT" && raiden->getHit() == "NONE") {
		sprite2 = raidenWalk;
		if(scorpion->getX() < raiden->getX()){
			sprite2->Play(100, raiden->getWidth());
		}else{
			sprite2->PlayBack(100);
		}
    }
    else if (raiden->getMovement() == "DUCK") {
        sprite2 = raidenDuck;
        sprite2->Play(20, raiden->getWidth());
    }
    else if (raiden->getHit() == "KICK") {
		sprite2 = raidenKick;
		sprite2->Play(100, raiden->getHitWidth());
	}
    else if (raiden->getHit() == "KICKDOWN") {
    		sprite2 = raidenKickDown;
    		sprite2->Play(100, raiden->getHitWidth());
    }
    else if (raiden->getHit() == "PUNCH") {
    		sprite2 = raidenPunch;
    		sprite2->Play(100, raiden->getHitWidth());
    }
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
    else if (raiden->getHit() == "DEFENSE") {
    		sprite2 = raidenBlock;
    		sprite2->Play(100, raiden->getHitWidth());
    } else if (raiden->getHit() == "DEFENSEDOWN") {
    		sprite2 = raidenBlockDown;
    		sprite2->Play(100, raiden->getHitWidth());
    }
    else if (raiden->getHit() == "DIZZY") {
    		sprite2 = raidenDizzy;
    		sprite2->Play(150, raiden->getWidth());
    }
    else if ((raiden->getHit() == "PUNCHJUMPLEFT" || raiden->getHit() == "PUNCHJUMPRIGHT")) {
    	if (raiden->isJumping() )
    	{
			sprite2 = raidenPunchJump;
			sprite2->Play(400, raiden->getHitWidth());
    	}
    	else
    	{
            sprite2 = raidenStance;
            RestartAllRaidenSprites();
            sprite2->Play(100, raiden->getWidth());
    	}
	}
    else if (raiden->getHit() == "WINNER") {
    		sprite2 = raidenWinner;
    		sprite2->Play(150, raiden->getHitWidth());
    }
    else if (raiden->getHit() == "PUNCHUP") {
		sprite2 = raidenPunchUp;
		sprite2->Play(150, raiden->getHitWidth());
	};

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

    if (GameController::isVibrating())
        if(!sprite->vibrationFinished())
            sprite->vibrate();
        else
            GameController::setVibrating(false);
    else
        sprite->resetFinished();


    sprite2->setX(raiden->getX());
    sprite2->setY(raiden->getY());

    if (GameController::isVibrating())
        if(!sprite2->vibrationFinished())
           sprite2->vibrate();
        else
            GameController::setVibrating(false);
    else
        sprite2->resetFinished();

    if (raiden->getIsHiting()) {
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
