#ifndef MORTALKOMBAT_TALLER1C2015_LAYER_H
#define MORTALKOMBAT_TALLER1C2015_LAYER_H

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

private:
    int width;
    float speed;
    int z_index;
    int left_border;
};

#endif //MORTALKOMBAT_TALLER1C2015_LAYER_H
