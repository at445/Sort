// Sort.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include "Common.h"
#include "MergeSortOrigin.h"
#include "MergeSortInsertOptimized.h"
#include "MergeSorInsertAndParallel.h"

int main(void)
{
    PerformanceCounter counter;
    const int MAX = 100000000;
    int* p = nullptr;
    p = dataGnerator(MAX);
    counter.start();
    MergeSortOrigion::MergeSort(p, 1, MAX);
    counter.end();
    verification(p, MAX);
    delete[] p;

    p = dataGnerator(MAX);
    counter.start();
    MergeSortInsertOptimized::MergeSort(p, 1, MAX);
    counter.end();
    verification(p, MAX);
    delete[] p;


    p = dataGnerator(MAX);
    MergeSorInsertAndParallel::Init();
    counter.start();
    MergeSorInsertAndParallel::Process(p, MAX);
    counter.end();
    verification(p, MAX);
    delete[] p;
    system("pause");
    return 0;
}