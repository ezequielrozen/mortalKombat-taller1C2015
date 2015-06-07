#ifndef MORTALKOMBAT_TALLER1C2015_ROUNDTIMER_H
#define MORTALKOMBAT_TALLER1C2015_ROUNDTIMER_H


class RoundTimer {

public:
    RoundTimer();
    ~RoundTimer();
    void stop();
    void run();
    int getCurrentTime();

private:
    int startTime;
};


#endif //MORTALKOMBAT_TALLER1C2015_ROUNDTIMER_H
