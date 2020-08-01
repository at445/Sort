#include <memory.h>
namespace MergeSortInsertOptimized {
    void InsertSort(int* p, int max)
    {
        int key = 0;
        int j = 0;
        for (int i = 1; i < max; i++) {
            key = p[i];
            for (j = i-1; j >= 0; j--) {
                p[j + 1] = p[j];
                if (p[j] <= key) break;
            }
            p[j+1] = key;
        }
    }
    void Merge(int* p, int start, int end)
    {
        int tempLen = end - start + 1;
        int* Temp = new int[tempLen];
        int j = 0;
        int middle = (start + end) / 2;
        int iSt = start;
        int iMi = middle + 1;
        for (int i = start; i <= end; i++)
        {
            if (p[iSt] > p[iMi]) {
                Temp[j++] = p[iMi++];
            }
            else {
                Temp[j++] = p[iSt++];
            }
            if ((iSt == middle + 1) || (iMi == end + 1)) break;
        }
        while (iSt <= middle)
        {
            Temp[j++] = p[iSt++];
        }
        while (iMi <= end)
        {
            Temp[j++] = p[iMi++];
        }
        memcpy(&p[start], Temp, tempLen * sizeof(int));
        delete[] Temp;
    }
    void MergeSort(int* p, int start, int end)
    {
        if (start + 10 < end) {
            int middle = (start + end) / 2;
            MergeSort(p, start, middle);
            MergeSort(p, middle + 1, end);
            Merge(p, start, end);
        }
        else if (start < end) {
            InsertSort(&p[start], end - start + 1);
        }
    }
}
