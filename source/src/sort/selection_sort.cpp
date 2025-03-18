#include "../utils/utils.h"

Result selectionSort(int *arr, int n) {
	Result r;
	auto start = chrono::high_resolution_clock::now();

	for(int i = 0; ++r.cmps && i < n - 1; i++)
	{
		int min = i;
		for(int j = i + 1; ++r.cmps && j < n; j++)
			if(++r.cmps && arr[j] < arr[min])
				min = j;
		if (++r.cmps && min!=i)
			HoanVi(arr[i], arr[min]);
	}
	chrono::duration<double, std::milli> duration = chrono::high_resolution_clock::now() - start;
	r.time = duration.count();
	return r;
}
