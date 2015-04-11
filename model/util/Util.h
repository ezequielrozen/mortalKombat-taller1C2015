#ifndef MORTALKOMBAT_TALLER1C2015_UTIL_H
#define MORTALKOMBAT_TALLER1C2015_UTIL_H

class Util {

public:
    static Util* getInstance();
    int getWindowWidth();
    void setWindowWidth(int);
    int getWindowHeight();
    void setWindowHeight(int);
    float getLogicalWindowWidth();
    void setLogicalWindowWidth(float);
    float getLogicalStageWidth();
    void setLogicalStageWidth(float);
    float getLogicalWindowHeight();
    void setLogicalWindowHeight(float);
    float getScalingConstant();

private:
    static Util* instance;
    //ventana
    int windowWidth;
    int windowHeight;
    //ventana logica
    float logicalWindowWidth;
    float logicalWindowHeight;
    //escenario
    float logicalStageWidth;
};


#endif //MORTALKOMBAT_TALLER1C2015_UTIL_H
