#include "CharacterSelectionView.h"

struct character {
  string name;
  int frames;
};

CharacterSelectionView::CharacterSelectionView(SDL_Renderer* aRenderer, Button** buttons1, Button** buttons2, Button** nameButtons) {
	this->renderer = aRenderer;

	int scWidth = Util::getInstance()->getWindowWidth();
    int scHeight = Util::getInstance()->getWindowHeight();

	this->background = new LayerSprite(this->renderer, "data/background.png", scWidth, scHeight, Util::getInstance()->getLogicalWindowWidth());

	this->title = new ImageSprite(this->renderer, "data/CharacterSelection/chooseYourFighter.png", 0.175*scWidth, 0.02*scHeight, 0.65*scWidth, 0.11*scHeight);

	this->characters = new ImageSprite(this->renderer, "data/CharacterSelection/characters.png", 0.175*scWidth, 0.14*scHeight, 0.65*scWidth, 0.65*scHeight);

	for (int i = 0; i < 12; i++) {
		buttonSprites1[i] = new ButtonSprite(this->renderer, buttons1[i]);
		buttonSprites2[i] = new ButtonSprite(this->renderer, buttons2[i]);
	}

	float scaledScWidth = scWidth/Util::getInstance()->getScalingConstant();
	float scaledScHeight = scHeight/Util::getInstance()->getScalingYConstant();

	character ch[12] = {{"liukang",8}, {"kunglao",8}, {"cage",7}, {"reptile",7}, {"subzero",9}, {"shangtsung",6}, {"kitana",7}, {"jax",7}, {"mileena",7}, {"baraka",9}, {"scorpion",7}, {"raiden",10}};
	string name;

	for(int k = 0; k < 12; k++) {
		name = "data/CharacterSelection/"+ch[k].name+"Stance.png";
		characterSprites1[k] = new CharacterSprite(this->renderer, (char*)name.c_str(), 0.005*scaledScWidth,0.615*scaledScHeight, 0.17*scaledScWidth,0.345*scaledScHeight, ch[k].frames, "RIGHT", false, false, NULL);
    	characterSprites2[k] = new CharacterSprite(this->renderer, (char*)name.c_str(), 0.825*scaledScWidth,0.615*scaledScHeight, 0.17*scaledScWidth,0.345*scaledScHeight, ch[k].frames, "LEFT", false, false, NULL);
    }
    
    this->nameButtonSprites[0] = new ButtonSprite(this->renderer, nameButtons[0]);
    this->nameButtonSprites[1] = new ButtonSprite(this->renderer, nameButtons[1]);

    this->characterNames[0] = new Text("SCORPION  ", this->renderer, "center",{255, 222, 39});
    this->characterNames[0]->setPosition(0.175*scWidth, 0.89*scHeight);
    this->characterNames[0]->setDimensions(0.3*scWidth, 0.1*scHeight);
    this->characterNames[1] = new Text("RAIDEN    ", this->renderer, "center",{255, 222, 39});
    this->characterNames[1]->setPosition(0.525*scWidth, 0.89*scHeight);
    this->characterNames[1]->setDimensions(0.3*scWidth, 0.1*scHeight);
}

CharacterSelectionView::~CharacterSelectionView() {
    delete this->characterNames[0];
    delete this->characterNames[1];
    delete nameButtonSprites[0];
    delete nameButtonSprites[1];

    for (int i = 0; i < 12; i++) {
        delete buttonSprites1[i];
        delete buttonSprites2[i];
        delete characterSprites1[i];
        delete characterSprites2[i];
    }

	delete characters;
	delete title;
	delete background;
}

void CharacterSelectionView::updateCharacterNames(string name1, string name2) {

    delete this->characterNames[0];
    delete this->characterNames[1];

    int scWidth = Util::getInstance()->getWindowWidth();
    int scHeight = Util::getInstance()->getWindowHeight();

    this->characterNames[0] = new Text(name1.c_str(), this->renderer, "center",{255, 222, 39});
    this->characterNames[0]->setPosition(0.175*scWidth, 0.89*scHeight);
    this->characterNames[0]->setDimensions(0.3*scWidth, 0.1*scHeight);
    this->characterNames[1] = new Text(name2.c_str(), this->renderer, "center",{255, 222, 39});
    this->characterNames[1]->setPosition(0.525*scWidth, 0.89*scHeight);
    this->characterNames[1]->setDimensions(0.3*scWidth, 0.1*scHeight);
}

void CharacterSelectionView::render() {
	float scaledScWidth = Util::getInstance()->getWindowWidth()/Util::getInstance()->getScalingConstant();

	SDL_RenderClear(renderer);
    this->background->Draw();
    this->title->Draw();
    this->characters->Draw();
    
    int i = 0;
    while (i < 12) {
    	this->buttonSprites1[i]->Draw();
    	this->buttonSprites2[i]->Draw();
   
    	if (this->buttonSprites1[i]->isSelected()) {
    		this->characterSprites1[i]->Draw();
    		this->characterSprites1[i]->Play(6.66*GAMEDELAY, 0.17*scaledScWidth);
    	}
    	if (this->buttonSprites2[i]->isSelected()) {
    		this->characterSprites2[i]->Draw();
    		this->characterSprites2[i]->Play(6.66*GAMEDELAY, 0.17*scaledScWidth);
    	}
    	i++;
    }
    
    this->characterNames[0]->Draw();
    this->nameButtonSprites[0]->Draw();
    this->characterNames[1]->Draw();
    this->nameButtonSprites[1]->Draw();

    SDL_RenderPresent(renderer);
}