#ifndef MORTALKOMBAT_TALLER1C2015_LAYER_H
#define MORTALKOMBAT_TALLER1C2015_LAYER_H

#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

using namespace std;

class Layer {

public:
    Layer(int width, int z_index);
    ~Layer();
    void moveRight();
    void moveLeft();
    int getWidth();
    void setWidth(int width);
    float getSpeed();
    void setLeft_border(int left_border);
    int getLeft_border();
    void update();
    void setMovement(string move);

private:
    int width;
    float speed;
    int z_index;
    int left_border;
    int timeCheck;
    string movement;
};

#endif //MORTALKOMBAT_TALLER1C2015_LAYER_H
