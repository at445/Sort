// Sort.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include "Common.h"
#include "MergeSortOrigin.h"

int main(void)
{
    PerformanceCounter counter;
    const int MAX = 10000000;
    int * p = dataGnerator(MAX);
    counter.start();
    MergeSortOrigion::MergeSort(p, 0, MAX - 1);
    counter.end();
    return 0;

}