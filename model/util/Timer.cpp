#include <SDL2/SDL_timer.h>
#include "Timer.h"

Timer::Timer() {
    this->startTime = 0;
}

Timer::~Timer() {

}

void Timer::stop() {
    this->startTime = 0;
}

void Timer::run() {
    this->startTime = SDL_GetTicks();
}

int Timer::getCurrentTime() {
    if (!this->startTime == 0)
        return SDL_GetTicks() - this->startTime;
    return 0;
}
