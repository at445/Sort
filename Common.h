#pragma once
#include <Windows.h>
class PerformanceCounter
{
private:
    LARGE_INTEGER freq;

    LARGE_INTEGER start_t, stop_t;

    double exe_time;
public:
    PerformanceCounter();
    void start();
    void end();
};
int* dataGnerator(int len);
int* dataGneratorRandom(int len);
void verification(int* p, int maxSize);