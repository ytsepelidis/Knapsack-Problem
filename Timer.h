#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <chrono>

class Timer
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
public:
    Timer();
    ~Timer();

    void Stop();
};

#endif // TIMER_H