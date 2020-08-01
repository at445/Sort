#include <memory.h>
namespace MergeSortOrigion {
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
        if (start < end) {
            int middle = (start + end) / 2;
            MergeSort(p, start, middle);
            MergeSort(p, middle + 1, end);
            Merge(p, start, end);
        }
    }
}
