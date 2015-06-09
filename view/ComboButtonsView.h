//
// Created by mauri on 08/06/15.
//

#ifndef MORTALKOMBAT_TALLER1C2015_COMBOBUTTONSVIEW_H
#define MORTALKOMBAT_TALLER1C2015_COMBOBUTTONSVIEW_H
#include "stage/ImageSprite.h"
#include "ComboButtonsView.h"
#include "Position.h"

typedef std::map<std::string, ImageSprite*> ButtonSpriteMap;

class ComboButtonsView {
public:
    ~ComboButtonsView();
    void draw();
    void addButton(Events button);
    static ComboButtonsView* getInstance();
    void init(SDL_Renderer* renderer);
    void activate();

private:
    ComboButtonsView();
    static ComboButtonsView* instance;
    ButtonSpriteMap buttonSprites;
    std::vector<ImageSprite*> buffer;
    std::vector<Position> positions;
    bool activated;

    void shiftPositions();
};


#endif //MORTALKOMBAT_TALLER1C2015_COMBOBUTTONSVIEW_H
