#include <memory.h>
namespace MergeSortOrigion {
    void Merge(int* p, int start, int end)
    {
        if ((p == NULL) || (start >= end)) {
            return;
        }
        int tempLen = end - start + 1;
        int* Temp = new int[tempLen];
        int j = 0;
        int middle = (start + end) / 2;
        int iSt = start-1;
        int iMi = middle;
        for (int i = start-1; i < end; i++)
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
        memcpy(&p[start-1], Temp, tempLen * sizeof(int));
        delete[] Temp;
    }
    void MergeSort(int* p, int start, int end)
    {
        if (start < end) {
            int middle = (start + end) / 2;
            MergeSort(p, start, middle);
            MergeSort(p, middle + 1, end);
            Merge(p, start, end);
        }
    }
}
