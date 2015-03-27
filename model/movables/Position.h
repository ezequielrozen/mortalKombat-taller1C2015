#ifndef MORTALKOMBAT_TALLER1C2015_POSITION_H
#define MORTALKOMBAT_TALLER1C2015_POSITION_H


class Position {

public:
    Position(float, float);
    ~Position();
    void setCoordinateX(float);
    void setCoordinateY(float);
    float getCoordinateX();
    float getCoordinateY();
    void move();

private:
    float coordinateX, coordinateY;
};


#endif //MORTALKOMBAT_TALLER1C2015_POSITION_H
