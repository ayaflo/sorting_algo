#include "../utils/utils.h"

// heap sort
void heapRebuild(int *arr, int index, int heap_size, long long &cmps) {

    int left = 2 * index + 1;
    if(++cmps && left >= heap_size)
        return;
    int larger = left;
    int right = 2 * index + 2;
    if(++cmps && right < heap_size)
        if(++cmps && arr[right] > arr[larger])
            larger = right;

    if(++cmps && arr[index] < arr[larger])
    {
        HoanVi(arr[index], arr[larger]);
        heapRebuild(arr, larger, heap_size, cmps);
    }
}

Result heapSort(int *arr, int n) {
    Result r;
    auto start = chrono::high_resolution_clock::now();

    for(int i = (n - 1) / 2; ++r.cmps && i >= 0; i--)
        heapRebuild(arr, i, n, r.cmps);

    HoanVi(arr[0], arr[n - 1]);
    int heap_size = n - 1;
    while(++r.cmps && heap_size > 1)
    {
        heapRebuild(arr, 0, heap_size, r.cmps);
        heap_size--;
        HoanVi(arr[0], arr[heap_size]);
    }

    chrono::duration<double, std::milli> duration = chrono::high_resolution_clock::now() - start;
    r.time = duration.count();
    return r;
} 
