#include "../utils/utils.h"

// radix sort
void sortByDigit(int *a, int n, int exp10, long long &cmps) {
    int *tmp = new int[n];
    int counter[10] = {0};

    for (int i = 0; ++cmps && i < n; ++i) {
        int digit = (a[i] / exp10) % 10;
        ++counter[digit];
    }

    for (int i = 1; ++cmps && i < 10; ++i) counter[i] += counter[i - 1];

    for (int i = n - 1; ++cmps && i >= 0; --i) {
        int digit = (a[i] / exp10) % 10;
        tmp[--counter[digit]] = a[i];
    }

    for (int i = 0; ++cmps && i < n; ++i) a[i] = tmp[i];

    delete[] tmp;
}

Result radixSort(int *a, int n) {
    Result r;
    auto start = chrono::high_resolution_clock::now();

    int mx = a[0];
    for (int i = 1; ++r.cmps && i < n; ++i) 
        if (++r.cmps && mx < a[i]) 
            mx = a[i];

    for (int exp10 = 1; ++r.cmps && mx / exp10 > 0; exp10 *= 10) {
        sortByDigit(a, n, exp10, r.cmps);
    }
    chrono::duration<double, std::milli> duration = chrono::high_resolution_clock::now() - start;
    r.time = duration.count();
    return r;
}