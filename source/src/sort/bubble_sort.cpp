#include "../utils/utils.h"

Result bubbleSort(int *arr, int n) {
    Result r;
    auto start = chrono::high_resolution_clock::now();

    for(int i = n - 1; ++r.cmps && i > 0; i--)
    {
        for(int j = 0; ++r.cmps && j < i; j++)
        {
            if(++r.cmps && arr[j] > arr[j + 1])
                HoanVi(arr[j], arr[j + 1]);
        }
    }

    chrono::duration<double, std::milli> duration = chrono::high_resolution_clock::now() - start;
    r.time = duration.count();
    return r;
} 