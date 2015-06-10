#ifndef MORTALKOMBAT_TALLER1C2015_TIMER_H
#define MORTALKOMBAT_TALLER1C2015_TIMER_H


class Timer {

public:
    Timer();
    ~Timer();
    void stop();
    void run();
    int getCurrentTime();

private:
    int startTime;
};


#endif //MORTALKOMBAT_TALLER1C2015_TIMER_H
