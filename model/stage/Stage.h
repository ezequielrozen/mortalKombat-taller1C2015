#ifndef MORTALKOMBAT_TALLER1C2015_STAGE_H
#define MORTALKOMBAT_TALLER1C2015_STAGE_H

#include "Layer.h"
#include <list>

class Stage {

public:
    Stage(std::list<Layer*>* layers, int width, int heigh, int floor);
    ~Stage();
    std::list<Layer*>* getLayers();
    void setLayers(std::list<Layer*>* layers);

private:
    int width;
    int height;
    int floor;
    std::list<Layer*>* layers;
};


#endif //MORTALKOMBAT_TALLER1C2015_STAGE_H
