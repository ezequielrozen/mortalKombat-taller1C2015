#include "CharacterSelectionView.h"

struct character {
  string name;
  int frames;
};

CharacterSelectionView::CharacterSelectionView(SDL_Renderer* aRenderer, Button** buttons1, Button** buttons2) {
	this->renderer = aRenderer;

	int scWidth = Util::getInstance()->getWindowWidth();
    int scHeight = Util::getInstance()->getWindowHeight();

	this->background = new LayerSprite(this->renderer, "data/background.png", scWidth, scHeight, Util::getInstance()->getLogicalWindowWidth());

	this->title = new ImageSprite(this->renderer, "data/CharacterSelection/chooseYourFighter.png", 0.175*scWidth, 0.02*scHeight, 0.65*scWidth, 0.11*scHeight);

	this->characters = new ImageSprite(this->renderer, "data/CharacterSelection/characters.png", 0.175*scWidth, 0.14*scHeight, 0.65*scWidth, 0.65*scHeight);

	float displaceX = 0.1588;
	float displaceY = 0.212;
	int i = 0;
	int j = 0;
    
	while (i < 3) {
		while (j < 4) {
			buttonSprites1[(4*i)+j] = new ButtonSprite(this->renderer, buttons1[(4*i)+j], (0.189+(displaceX*j))*scWidth, (0.148+(displaceY*i))*scHeight, 0.1488*scWidth, 0.202*scHeight);
			buttonSprites2[(4*i)+j] = new ButtonSprite(this->renderer, buttons2[(4*i)+j], (0.189+(displaceX*j))*scWidth, (0.148+(displaceY*i))*scHeight, 0.1488*scWidth, 0.202*scHeight);
			j++;
		}
		i++;
		j = 0;
	}

	float scaledScWidth = scWidth/Util::getInstance()->getScalingConstant();
	float scaledScHeight = scHeight/Util::getInstance()->getScalingYConstant();

	character ch[12] = {{"liukang",8}, {"kunglao",8}, {"cage",7}, {"reptile",7}, {"subzero",9}, {"shangtsung",6}, {"kitana",7}, {"jax",7}, {"mileena",7}, {"baraka",9}, {"scorpion",7}, {"raiden",10}};
	string name;

	for(int k = 0; k < 12; k++) {
		name = "data/CharacterSelection/"+ch[k].name+"Stance.png";
		characterSprites1[k] = new CharacterSprite(this->renderer, (char*)name.c_str(), 0.025*scaledScWidth,0.615*scaledScHeight, 0.17*scaledScWidth,0.345*scaledScHeight, ch[k].frames, "RIGHT", false, false, NULL);
    	characterSprites2[k] = new CharacterSprite(this->renderer, (char*)name.c_str(), 0.825*scaledScWidth,0.615*scaledScHeight, 0.17*scaledScWidth,0.345*scaledScHeight, ch[k].frames, "LEFT", false, false, NULL);	
    }
    
}

CharacterSelectionView::~CharacterSelectionView() {
    
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
    

    SDL_RenderPresent(renderer);
}