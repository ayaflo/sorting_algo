#include "../utils/utils.h"

int binarySearch(Result &r, int *arr, int item, int low, int high) {
    while (++r.cmps && low <= high) {
        int mid = (low + high) / 2;
        if (++r.cmps && arr[mid] == item)
            return mid + 1;
        else if (++r.cmps && arr[mid] < item)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return low;
}

Result binaryInsertionSort(int *arr, int n) {
    Result r;
    auto start = chrono::high_resolution_clock::now();
    for (int i = 1;++r.cmps && i < n; ++i) {
        int key = arr[i];
        int pos = binarySearch(r,arr, key, 0, i - 1);

        int j = i;
        while (++r.cmps &&j > pos) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[pos] = key;
    }
    chrono::duration<double, std::milli> duration = chrono::high_resolution_clock::now() - start;
    r.time = duration.count();
    return r;
} 
