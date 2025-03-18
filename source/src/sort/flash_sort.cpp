#include "../utils/utils.h"

int getBucketID(int m, int minn, int maxx, int val) {
    return 1LL * (m - 1) * (val - minn) / (maxx - minn);
}
Result flashSort(int *a, int n) {
    Result r;
    auto start = chrono::high_resolution_clock::now();
    if (++r.cmps && n <= 1) {
        auto endt = chrono::high_resolution_clock::now();
        chrono::duration<double, std::milli> duration = endt - start;
        r.time = duration.count();
        return r;
    }
    // number of buckets
    int m = 0.45 * n;
    if (m <= 2) m = 2;

    // find maximum and minimum value
    int maxx = a[0], minn = a[0];
    for (int i = 1; ++r.cmps && i < n; ++i) {
        if (++r.cmps && maxx < a[i]) maxx = a[i];
        if (++r.cmps && minn > a[i]) minn = a[i];
    }

    // Step 1: precalculate counter array
    // counter[i] saves number of elements in bucket i-th
    int* counter = new int[m];
    for (int i = 0; ++r.cmps && i < m; ++i) counter[i] = 0;

    for (int i = 0; ++r.cmps && i < n; ++i) 
        ++counter[getBucketID(m, minn, maxx, a[i])];
    
    // turns counter array into cummulative sum so that it points out correct last
    // index of each bucket
    for (int i = 1; ++r.cmps && i < m; ++i) counter[i] += counter[i - 1];

    // Step 2: rearrange elements into its correct bucket 
    int numSwap = 0;
    int i = 0;

    while (++r.cmps && numSwap < n) {
        int id = getBucketID(m, minn, maxx, a[i]);
        // moving to next bucket when current bucket is already arranged
        while (++r.cmps && i >= counter[id]) id = getBucketID(m, minn, maxx, a[++i]);

        // arranging bucket id-th
        int tmp = a[i];
        while (++r.cmps && i != counter[id]) {
            id = getBucketID(m, minn, maxx, tmp); // find the correct bucket for current a[i]
            int tmp2 = a[counter[id] - 1];
            a[--counter[id]] = tmp;  // swap it with the last element of its correct bucket
            tmp = tmp2;
            ++numSwap;
        }
    }

    // Step 3: insertion sort on each bucket
    for (int k = 1; ++r.cmps && k < m; ++k) {
        for (int i = counter[k] - 2; ++r.cmps && i >= counter[k - 1]; --i) {
            int tmp = a[i], j = i;
            while (++r.cmps && tmp > a[j + 1]) {
                a[j] = a[j + 1];
                ++j;
            }
            a[j] = tmp;
        }
    }

    delete[] counter;

    auto endt = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> duration = endt - start;
    r.time = duration.count();
    return r;
}