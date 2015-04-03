#ifndef MORTALKOMBAT_TALLER1C2015_STAGE_H
#define MORTALKOMBAT_TALLER1C2015_STAGE_H

#include "Layer.h"
#include <list>

class Stage {

public:
    Stage(std::list<Layer*>* layers, float width, float heigh, float floor);
    ~Stage();
    std::list<Layer*>* getLayers();
    void setLayers(std::list<Layer*>* layers);
    float getWidth();
    float getHeight();
    float getFloor();

private:
    float width;
    float height;
    float floor;
    std::list<Layer*>* layers;
};


#endif //MORTALKOMBAT_TALLER1C2015_STAGE_H
