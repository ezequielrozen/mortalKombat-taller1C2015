#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_endian.h>
#include <SDL2/SDL_surface.h>
#include <iostream>
#include "Painter.h"
#include "../../model/util/Util.h"

Painter::Painter(double initH, double finalHparam, double offsetParam) {
    this->initialH = initH;
    this->finalH = finalHparam;
    this->offset = offsetParam;
}

Painter::~Painter() {

}

Uint32 Painter::getpixel(SDL_Surface *surface, int x, int y) {
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
        case 1:
            return *p;

        case 2:
            return *(Uint16 *)p;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;

        case 4:
            return *(Uint32 *)p;

        default:
            return 0;       /* shouldn't happen, but avoids warnings */
    }
}

void Painter::putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
        case 1:
            *p = pixel;
            break;

        case 2:
            *(Uint16 *)p = pixel;
            break;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            } else {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4:
            *(Uint32 *)p = pixel;
            break;
        default:
            break;       /* shouldn't happen, but avoids warnings */
    }
}

hsv Painter::convertToHSV(rgb rgb_param) {
    hsv newHSV;
    uint8_t min, max, delta;

    min = rgb_param.r < rgb_param.g ? rgb_param.r : rgb_param.g;
    min = min  < rgb_param.b ? min  : rgb_param.b;

    max = rgb_param.r > rgb_param.g ? rgb_param.r : rgb_param.g;
    max = max  > rgb_param.b ? max  : rgb_param.b;

    newHSV.v = max;                                // v
    delta = max - min;
    if( max > 0.0 ) { // NOTE: if Max is == 0, this divide would cause a crash
        newHSV.s = (delta*1.0 / max);                  // s
    } else {
        // if max is 0, then r = g = b = 0
        // s = 0, v is undefined
        newHSV.s = 0;
        newHSV.h = NAN;                            // its now undefined
        return newHSV;
    }
    if (delta > 0) {
        if( rgb_param.r >= max )                           // > is bogus, just keeps compilor happy
            newHSV.h = ( rgb_param.g - rgb_param.b ) / delta*1.0;        // between yellow & magenta
        else if( rgb_param.g >= max )
                newHSV.h = 2.0 + ( rgb_param.b - rgb_param.r ) / delta*1.0;  // between cyan & yellow
        else
            newHSV.h = 4.0 + ( rgb_param.r - rgb_param.g ) / delta*1.0;  // between magenta & cyan
    }

    newHSV.h *= 60.0;                              // degrees

    if( newHSV.h < 0.0 )
        newHSV.h += 360.0;

    return newHSV;

}

rgb Painter::convertToRGB(hsv hsv_param) {
    rgb newRGB;
    double hh, p, q, t, ff;
    long i;

    if(hsv_param.s <= 0.0) {       // < is bogus, just shuts up warnings
        newRGB.r = hsv_param.v;
        newRGB.g = hsv_param.v;
        newRGB.b = hsv_param.v;
        return newRGB;
    }
    hh = hsv_param.h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = hsv_param.v * (1.0 - hsv_param.s);
    q = hsv_param.v * (1.0 - (hsv_param.s * ff));
    t = hsv_param.v * (1.0 - (hsv_param.s * (1.0 - ff)));

    switch(i) {
        case 0:
            newRGB.r = hsv_param.v;
            newRGB.g = t;
            newRGB.b = p;
            break;
        case 1:
            newRGB.r = q;
            newRGB.g = hsv_param.v;
            newRGB.b = p;
            break;
        case 2:
            newRGB.r = p;
            newRGB.g = hsv_param.v;
            newRGB.b = t;
            break;

        case 3:
            newRGB.r = p;
            newRGB.g = q;
            newRGB.b = hsv_param.v;
            break;
        case 4:
            newRGB.r = t;
            newRGB.g = p;
            newRGB.b = hsv_param.v;
            break;
        default:
            newRGB.r = hsv_param.v;
            newRGB.g = p;
            newRGB.b = q;
            break;
    }
    return newRGB;
}

void Painter::paint(SDL_Surface *surface) {
    for (int x = 0; x < surface->w; x++) {
        for (int y = 0; y < surface->h; y++) {
            Uint8 alpha;
            Uint32 px = this->getpixel(surface, x, y);
            rgb aRGB;
            SDL_GetRGBA(px, surface->format,&aRGB.r,&aRGB.g,&aRGB.b,&alpha);
            if (alpha == 0) {
                continue;
            }
            hsv hsvConverted = this->convertToHSV(aRGB);
            if (Util::getInstance()->getInitialH() <= hsvConverted.h && hsvConverted.h <= Util::getInstance()->getFinalH()) {
                hsvConverted.h += Util::getInstance()->getOffset();
            }
            aRGB = this->convertToRGB(hsvConverted);
            this->putpixel(surface,x,y,SDL_MapRGB(surface->format,aRGB.r,aRGB.g,aRGB.b));
        }
    }
}
