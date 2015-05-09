#ifndef MORTALKOMBAT_TALLER1C2015_PAINTER_H
#define MORTALKOMBAT_TALLER1C2015_PAINTER_H


class Painter {

public:
    Painter();
    ~Painter();
    void paint(SDL_Surface* surface, int x, int y, Uint32 pixel);

private:
    Uint32 getpixel(SDL_Surface *surface, int x, int y);
    void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
};


#endif //MORTALKOMBAT_TALLER1C2015_PAINTER_H
