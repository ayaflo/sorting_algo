#include "../utils/utils.h"

Result shakerSort(int *arr, int n) {
	Result r;
	auto start = chrono::high_resolution_clock::now();
	int left = 0, right = n - 1, k = 0;

	while (left < right) {
		for (int i = left; ++r.cmps && i < right; ++i) {
			if (++r.cmps && arr[i] > arr[i + 1]) {
				HoanVi(arr[i], arr[i + 1]);
				k = i;
			}
		}

		right = k;
		for (int i = right; ++r.cmps && i > left; --i) {
			if (++r.cmps && arr[i] < arr[i - 1]) {
				HoanVi(arr[i], arr[i - 1]);
				k = i;
			}
		}
		left = k;
	}
	chrono::duration<double, std::milli> duration = chrono::high_resolution_clock::now() - start;
	r.time = duration.count();
	return r;
}
