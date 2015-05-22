#ifndef MORTALKOMBAT_TALLER1C2015_PAINTER_H
#define MORTALKOMBAT_TALLER1C2015_PAINTER_H

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb;

typedef struct {
    double h;
    double s;
    double v;
} hsv;

class Painter {

public:
    Painter(double initH, double finalH, int offset);
    ~Painter();
    void paint(SDL_Surface* surface);

private:
    double initialH;
    double finalH;
    int offset;
    Uint32 getpixel(SDL_Surface *surface, int x, int y);
    void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

    hsv convertToHSV(rgb pRgb);

    rgb convertToRGB(hsv hsv_param);
};


#endif //MORTALKOMBAT_TALLER1C2015_PAINTER_H
