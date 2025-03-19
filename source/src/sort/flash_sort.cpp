#include "../utils/utils.h"

Result flashSort(int *arr, int n) {
    Result r;
    auto start = chrono::high_resolution_clock::now();
    // Bước 1: Tìm giá trị lớn nhất trong mảng
    int max_val = arr[0];
    for (int i = 1; ++r.cmps && i < n; i++) {
        if (++r.cmps && arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    // Bước 2: Xác định số chữ số của max_val
    int digits = 0;
    int div = max_val;
    while (++r.cmps && div > 0) {
        digits++;
        div /= 10;
    }

    // Bước 3: Cấp phát mảng tạm
    int* temp_arr[10];
    for (int i = 0; ++r.cmps && i < 10; i++) {
        temp_arr[i] = new int[n];
    }

    int temp_count[10];

    // Bước 4: Thực hiện Radix Sort theo từng chữ số
    int exp = 1; // Lũy thừa của 10
    for (int i = 0; ++r.cmps && i < digits; i++) {
        // Khởi tạo lại bộ đếm của từng bucket
        for (int j = 0; ++r.cmps && j < 10; j++) {
            temp_count[j] = 0;
        }

        // Phân phối phần tử vào các bucket
        for (int j = 0; ++r.cmps && j < n; j++) {
            int idx = (arr[j] / exp) % 10;
            temp_arr[idx][temp_count[idx]++] = arr[j];
        }

        // Gom các phần tử từ bucket trở lại mảng chính
        int idx = 0;
        for (int j = 0; ++r.cmps && j < 10; j++) {
            for (int k = 0; ++r.cmps && k < temp_count[j]; k++) {
                arr[idx++] = temp_arr[j][k];
            }
        }

        // Nhân exp lên 10 để tiếp tục với hàng tiếp theo
        exp *= 10;
    }

    // Bước 5: Giải phóng bộ nhớ cấp phát động
    for (int i = 0; ++r.cmps && i < 10; i++) {
        delete[] temp_arr[i];
    }

    auto endt = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> duration = endt - start;
    r.time = duration.count();
    return r;
}
