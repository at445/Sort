#include <Windows.h>
#include <iostream>
#include <random>
#include "Common.h"
PerformanceCounter::PerformanceCounter()
{
    QueryPerformanceFrequency(&freq);
}
void PerformanceCounter::start()
{
    QueryPerformanceCounter(&start_t);
}
void PerformanceCounter::end()
{
    QueryPerformanceCounter(&stop_t);

    exe_time = 1e3 * (stop_t.QuadPart - start_t.QuadPart) / freq.QuadPart;

    std::cout << "Your program executed time is:" << exe_time/1000.0 << "s" << std::endl;
}

using std::default_random_engine;
int* dataGnerator(int len)
{
    int* p = new int[len];
    for (int i = 0; i < len; i++) {
        *(p + i) = len - i - 1;
    }
    return p;
}
void verification(int* p, int maxSize)
{
    default_random_engine e;
    e.seed(10);
    int temp = 0;
    for (size_t i = 0; i < 10; ++i) {
        temp = e() % maxSize;
        std::cout << "array[" << temp << "] = " << p[temp] << std::endl;
    }

}