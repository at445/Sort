#include <memory.h>
#include <iostream>
#include "ThreadPooling.h"
namespace MergeSorInsertAndParallel {
    ThreadPoolPtr g_thread_pool = nullptr;
    const int ParticalSize = 524288;
    void InsertSort(int* p, int max)
    {
        int key = 0;
        int j = 0;
        for (int i = 1; i < max; i++) {
            key = p[i];
            for (j = i - 1; j >= 0; j--) {
                p[j + 1] = p[j];
                if (p[j] <= key) break;
            }
            p[j + 1] = key;
        }
    }
    void Merge(int* p, int start, int middle, int end)
    {
        if ((p == NULL) || (start >= end)) {
            return;
        }
        int tempLen = end - start + 1;
        int* Temp = new int[tempLen];
        int j = 0;
        int iSt = start - 1;
        int iMi = middle;
        for (int i = start - 1; i < end; i++)
        {
            if (p[iSt] > p[iMi]) {
                Temp[j++] = p[iMi++];
            }
            else {
                Temp[j++] = p[iSt++];
            }
            if ((iSt == middle) || (iMi == end)) break;
        }
        while (iSt < middle)
        {
            Temp[j++] = p[iSt++];
        }
        while (iMi < end)
        {
            Temp[j++] = p[iMi++];
        }
        memcpy(&p[start - 1], Temp, tempLen * sizeof(int));
        delete[] Temp;
    }
    void MergeSort(int* p, int start, int end)
    {
        if (start + 40 < end) {
            int middle = (start + end) / 2;
            MergeSort(p, start, middle);
            MergeSort(p, middle + 1, end);
            Merge(p, start, middle, end);
        }
        else if (start < end) {
            InsertSort(&p[start - 1], end - start + 1);
        }
    }
    int decideMiddle(int value)
    {
        if (value <= ParticalSize) return ParticalSize;
        int i = 0;
        do {
            value >>= 1;
            i++;
        } while (value != 1);
        int ret = 1;
        while (i-- != 0) {
            ret <<= 1;
        }
        return ret;
    }
    void MergeSort_Special(int* p, int start, int end)
    {
        if (start + ParticalSize < end) {

            int middle = start + decideMiddle(end-start) - 1;
            MergeSort_Special(p, start, middle);
            MergeSort_Special(p, middle + 1, end);
            Merge(p, start, middle, end);
        }
    }
    void Init()
    {
        int threads = std::thread::hardware_concurrency();

        g_thread_pool = std::make_shared<ThreadPool>(threads);

        std::cout << "init the thread pooling, threads number " << threads << std::endl;
    }
    void Process(int* p, int end)
    {
        int loop = end / ParticalSize;
        int i = 0;
        for (i = 0; i < loop; i++)
        {
            g_thread_pool->enqueue([p, i]() {
                MergeSort(&p[i * ParticalSize], 1, ParticalSize);
                });
        }
        g_thread_pool->enqueue([p, i, end]() {
            MergeSort(&p[i * ParticalSize], 1, end%ParticalSize);
            });
        g_thread_pool->waitTillFinish();
        MergeSort_Special(p, 1, end);
        
    }
}
