#ifndef MORTALKOMBAT_TALLER1C2015_LAYER_H
#define MORTALKOMBAT_TALLER1C2015_LAYER_H

#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

using namespace std;

class Layer {

public:
    Layer(float width);
    ~Layer();
    void moveRight();
    void moveLeft();
    float getWidth();
    void setWidth(float width);
    float getSpeed();
    void setLeft_border(float left_border);
    float getLeft_border();
    void update();
    void setMovement(string move);

private:
    float width;
    float speed;
    float left_border;
    uint timeCheck;
    string movement;
};

#endif //MORTALKOMBAT_TALLER1C2015_LAYER_H
