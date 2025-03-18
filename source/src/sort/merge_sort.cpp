#include "../utils/utils.h"
void merge(Result &r,int *arr,int left,int right){
	// Bên trai: left -> middle
	int middle=(left+right)/2;
	int len_left = middle - left + 1;

	// Bên phai: middle + 1 -> right
	int len_right = right - middle;

	// Tao mang tam thoi
	int arr_left[len_left], arr_right[len_right];

	for (int i = 0; ++r.cmps && i < len_left; i++) {
		arr_left[i] = arr[left + i];
	}

	for (int i = 0; ++r.cmps && i < len_right; i++) {
		arr_right[i] = arr[middle + 1 + i];
	}

	// Gop hai mang theo quy tac phan tu nho hon duoc dua vao mang gop truoc
	int i1 = 0; // Vi tri hien tai cua phan tu mang ben trai
	int i2 = 0; // Vi tri hien tai cua phan tu mang bên phai
	int k = left;
	while ((++r.cmps && i1 < len_left) && (++r.cmps && i2 < len_right)) {
		if (++r.cmps && arr_left[i1] <= arr_right[i2]) {
			arr[k] = arr_left[i1];
			i1++;
		} else {
			arr[k] = arr_right[i2];
			i2++;
		}
		k++;
	}

	// Copy nhung phan cua mang ben trai chua duoc dua vao
	while (++r.cmps && i1 < len_left) {
		arr[k] = arr_left[i1];
		i1++;
		k++;
	}

	// Copy nhung phan cua mang bên phai chua duoc dua vao
	while (++r.cmps && i2 < len_right) {
		arr[k] = arr_right[i2];
		i2++;
		k++;
	}
	
}
void mergeSort(Result &r,int* arr, int left, int right)
{
	if (++r.cmps && left < right)
	{
		// Tim vi tri o giua
		int middle = (left + right) / 2;

		// Goi de quy sort tung phan ben trai va ben phai
		mergeSort(r,arr, left, middle);
		mergeSort(r,arr, middle + 1, right);

		// Gop hai phan ben trai va ben phai voi nhau
		merge(r,arr, left, right);
	}
}
Result mergeSort(int *a, int n) {
	Result r;
	auto start = chrono::high_resolution_clock::now();

	mergeSort(r,a,0,n-1);

	chrono::duration<double, std::milli> duration = chrono::high_resolution_clock::now() - start;
	r.time = duration.count();
	return r;
}
