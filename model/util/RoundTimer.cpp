#include <SDL2/SDL_timer.h>
#include "RoundTimer.h"

RoundTimer::RoundTimer() {
    this->startTime = 0;
}

RoundTimer::~RoundTimer() {

}

void RoundTimer::stop() {
    this->startTime = 0;
}

void RoundTimer::run() {
    this->startTime = SDL_GetTicks();
}

int RoundTimer::getCurrentTime() {
    if (!this->startTime == 0)
        return SDL_GetTicks() - this->startTime;
    return 0;
}
