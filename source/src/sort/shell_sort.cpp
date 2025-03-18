#include "../utils/utils.h"

Result shellSort(int *arr, int n) {
	Result r;
	auto start = chrono::high_resolution_clock::now();
	for (int gap = n / 2; ++r.cmps && gap > 0; gap /= 2) {
		for (int i = gap; ++r.cmps && i < n; i++) {
			int temp = arr[i];
			int j;
			for (j = i; (++r.cmps && j >= gap) && (++r.cmps && arr[j - gap] > temp); j -= gap) {
				arr[j] = arr[j - gap];
			}
			arr[j] = temp;
		}
	}
	chrono::duration<double, std::milli> duration = chrono::high_resolution_clock::now() - start;
	r.time = duration.count();
	return r;
}
