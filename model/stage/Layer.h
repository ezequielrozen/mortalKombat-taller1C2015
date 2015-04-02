#ifndef MORTALKOMBAT_TALLER1C2015_LAYER_H
#define MORTALKOMBAT_TALLER1C2015_LAYER_H

class Layer {

public:
    Layer(float width, int z_index);
    ~Layer();
    void move();
    float getWidth();
    void setWidth(float width);
    float getSpeed();

private:
    float width;
    float speed;
    int z_index;
};

#endif //MORTALKOMBAT_TALLER1C2015_LAYER_H
