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
    float min, max, chroma;
    float r,g,b;
    r = (rgb_param.r)/255.0;
    g = (rgb_param.g)/255.0;
    b = (rgb_param.b)/255.0;

    min = r < g ? r : g;
    min = min  < b ? min : b;

    max = r > g ? r : g;
    max = max  > b ? max : b;

    chroma = max - min;

    newHSV.v = max;
    if (max == 0) {
        newHSV.s = 0;
    } else {
        newHSV.s = chroma / max;
    }
    if(chroma != 0) {
        if(r == max) {
            newHSV.h = fmod(((g - b) / chroma),60);
            if(newHSV.h < 0.0) {
                newHSV.h += 6.0;
            }
        } else if(g == max) {
            newHSV.h = ((b - r) / chroma) + 2.0;
        } else {
            newHSV.h = ((r - g) / chroma) + 4.0;
        }
        newHSV.h *= 60;
    } else {
        newHSV.h = 0;
    }

    return newHSV;

}

rgb Painter::convertToRGB(hsv hsv_param) {
    rgb newRGB;
    double chroma, Hdash, min, x;
    chroma = (hsv_param.s) * (hsv_param.v);
    Hdash = hsv_param.h / 60.0;
    x = chroma * (1.0 - fabs(fmod(Hdash,2.0) - 1));
    if (Hdash < 1.0) {
        newRGB.r = chroma*255;
        newRGB.g = x*255;
        newRGB.b = 0;
    } else if (Hdash < 2.0) {
        newRGB.r = x*255;
        newRGB.g = chroma*255;
        newRGB.b = 0;
    } else if (Hdash < 3.0) {
        newRGB.r = 0;
        newRGB.g = chroma*255;
        newRGB.b = x*255;
    } else if (Hdash < 4.0) {
        newRGB.r = 0;
        newRGB.g = x*255;
        newRGB.b = chroma*255;
    } else if(Hdash < 5.0) {
        newRGB.r = x*255;
        newRGB.g = 0;
        newRGB.b = chroma*255;
    } else if (Hdash <= 6.0) {
        newRGB.r = chroma*255;
        newRGB.g = 0;
        newRGB.b = x*255;
    }
    min = (hsv_param.v - chroma)*255;
    newRGB.r += min;
    newRGB.g += min;
    newRGB.b += min;
    return newRGB;
}

void Painter::paint(SDL_Surface *surface) {
    for (int x = 0; x < surface->w; x++) {
        for (int y = 0; y < surface->h; y++) {
            Uint8 alpha;
            Uint32 px = this->getpixel(surface, x, y);
            rgb aRGB;
            SDL_GetRGBA(px, surface->format, &aRGB.r, &aRGB.g, &aRGB.b, &alpha);
            if (alpha == 0) {
                continue;
            }
            hsv hsvConverted = this->convertToHSV(aRGB);
            if (this->initialH <= hsvConverted.h && hsvConverted.h <= this->finalH) {
                int i = 1;
                double aux = this->offset;
                if (this->offset >= 360.0) {
                    aux = this->offset-360.0;
                    while (aux > 360) {
                        i++;
                        aux = this->offset-(i*360.0);
                    }
                }
                hsvConverted.h += aux;
            }
            aRGB = this->convertToRGB(hsvConverted);
            this->putpixel(surface, x, y, SDL_MapRGB(surface->format, aRGB.r, aRGB.g, aRGB.b));
        }
    }
}
