#include "../utils/utils.h"

Result insertionSort(int *arr, int n) {
	Result r;
	auto start = chrono::high_resolution_clock::now();

	for(int i = 1; ++r.cmps && i < n; i++)
	{
		int j = i - 1;
		int key = arr[i];
		while((++r.cmps && j >= 0) && (++r.cmps && key < arr[j]))
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
	chrono::duration<double, std::milli> duration = chrono::high_resolution_clock::now() - start;
	r.time = duration.count();
	return r;
}
