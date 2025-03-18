#ifndef SORTING_GROUP_PROJECT_UTILS_H
#define SORTING_GROUP_PROJECT_UTILS_H
#include <cstring>
#include <vector>
#include <chrono>
#include "DataGenerator.cpp"
#include  "ctime"
using namespace std;

struct Result{
	double time{-1.0};
	long long cmps{0};
};
bool fileExist(const char *fileName) {
	ifstream file(fileName);
	if (!file.is_open()) {
		return false;
	}
	file.close();
	return true;
}

int* readFile(const char *fileName, int &n) {
	ifstream file(fileName);
	if (!file.is_open()) return nullptr;

	file >> n;
	int *a = new int[n];
	for (int i = 0; i < n; i++) {
		file >> a[i];
	}
	file.close();
	return a;
}

vector<int> readFile2Vector(const char *fileName, int &n) {
	ifstream file(fileName);
	if (!file.is_open()) {
		return {};
	}
	file >> n;
	vector<int> a;
	a.reserve(n);
	for (int i = 0; i < n; i++) {
		file >> a[i];
	}
	file.close();
	return a;
}

void writeFile(const char *fileName, int *a, int n) {
	ofstream file(fileName);
	if (!file.is_open()) {
		return;
	}
	file << n << '\n';
	for (int i = 0; i < n; i++) {
		file << a[i] << ' ';
	}
}

enum SortingAlgo{
	UNKNOWN_SORT = -1,
	BINARY_INSERTION_SORT = 0,
	BUBBLE_SORT = 1,
	COUNTING_SORT = 2,
	FLASH_SORT = 3,
	HEAP_SORT = 4,
	INSERTION_SORT = 5,
	MERGE_SORT = 6,
	QUICK_SORT = 7,
	RADIX_SORT = 8,
	SELECTION_SORT = 9,
	SHAKER_SORT = 10,
	SHELL_SORT = 11,
};

static vector<string> sortingAlgo = {
	"binary-insertion-sort",
	"bubble-sort",
	"counting-sort",
	"flash-sort",
	"heap-sort",
	"insertion-sort",
	"merge-sort",
	"quick-sort",
	"radix-sort",
	"selection-sort",
	"shaker-sort",
	"shell-sort",
};

static vector<string> algoName = {
	"Binary Insertion Sort",
	"Bubble Sort",
	"Counting Sort",
	"Flash Sort",
	"Heap Sort",
	"Insertion Sort",
	"Merge Sort",
	"Quick Sort",
	"Radix Sort",
	"Selection Sort",
	"Shaker Sort",
	"Shell Sort",
};

SortingAlgo getSortingAlgoFromText(char* s) {
	for (int i = 0; i < sortingAlgo.size(); i++) {
		if (strcmp(s, sortingAlgo[i].c_str()) == 0) {
			return (SortingAlgo) i;
		}
	}
	return SortingAlgo::UNKNOWN_SORT;
}

bool isValidInputNumber(char *s) {
	for (int i = 0; s[i]; s++)
		if (s[i] > '9' || s[i] < '0')
			return false;
	return true;
}

enum InputOrder{
	ORDER_UNKNOWN = -1,
	ORDER_RAND = 0,
	ORDER_SORTED = 1,
	ORDER_REV = 2,
	ORDER_NSORTED = 3,
};

InputOrder getInputOrder(char *s) {
	if (strcmp(s, "-rand") == 0) {
		return InputOrder::ORDER_RAND;
	}
	if (strcmp(s, "-sorted") == 0) {
		return InputOrder::ORDER_SORTED;
	}
	if (strcmp(s, "-rev") == 0) {
		return InputOrder::ORDER_REV;
	}
	if (strcmp(s, "-nsorted") == 0) {
		return InputOrder::ORDER_NSORTED;
	}
	return InputOrder::ORDER_UNKNOWN;
}

enum OutputMode{
	NONE = -1,
	TIME = 0,
	COMP = 1,
	BOTH = 2,
};

OutputMode getOutputMode(char* s) {
	if (strcmp(s, "-time") == 0) {
		return OutputMode::TIME;
	}
	if (strcmp(s, "-comp") == 0) {
		return OutputMode::COMP;
	}
	if (strcmp(s, "-both") == 0) {
		return OutputMode::BOTH;
	}
	return OutputMode::NONE;
}

#endif //SORTING_GROUP_PROJECT_UTILS_H
