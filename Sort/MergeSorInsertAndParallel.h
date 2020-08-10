#pragma once
namespace MergeSorInsertAndParallel {
	void Merge(int* p, int start, int end);
	void MergeSort(int* p, int start, int end);
	void InsertSort(int* p, int max);
	void Init(void);
	void Process(int* p, int end);
	void End(void);
	int decideMiddle(int end);
}
