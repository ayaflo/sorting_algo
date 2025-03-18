#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <thread>
#include "utils/utils.h"

#include "sort.h"

using namespace std;

void printHelp() {
	cout << "SGP is a tool for measuring time and comparisons of sorting algorithms\n\n"
		 << "Usage: sgp [arguments]\n"
		 << "       sgp -a [algorithm] [input filename] [output param]\n"
		 << "       sgp -a [algorithm] [input size] [input order] [output param]\n"
		 << "       sgp -a [algorithm] [input size] [output param]\n\n"
		 << "       sgp -c [algorithm1] [algorithm2] [input filename]\n"
		 << "       sgp -c [algorithm1] [algorithm2] [input size] [input order]\n\n"
		 << "       sgp -l >> List all supported sorting algorithms\n";
}

int* cloneArray(const int* a, int n) {
	int *clone_a{new int[n]};
	for (int i = 0; i < n; i++) {
		clone_a[i] = a[i];
	}
	return clone_a;
}

Result sort(SortingAlgo algo, int *a, int n, const char *outputFile = nullptr) {
	if (algo == UNKNOWN_SORT) {
		return {-1, 0};
	}
	int *clone_a = cloneArray(a, n);
	Result r;
	switch (algo) {
		case SortingAlgo::BINARY_INSERTION_SORT:
			r = binaryInsertionSort(clone_a, n);
			break;
		case SortingAlgo::BUBBLE_SORT:
			r = bubbleSort(clone_a, n);
			break;
		case SortingAlgo::COUNTING_SORT:
			r = countingSort(clone_a, n);
			break;
		case SortingAlgo::FLASH_SORT:
			r = flashSort(clone_a, n);
			break;
		case SortingAlgo::HEAP_SORT:
			r = heapSort(clone_a, n);
			break;
		case SortingAlgo::INSERTION_SORT:
			r = insertionSort(clone_a, n);
			break;
		case SortingAlgo::MERGE_SORT:
			r = mergeSort(clone_a, n);
			break;
		case SortingAlgo::QUICK_SORT:
			r = quickSort(clone_a, n);
			break;
		case SortingAlgo::RADIX_SORT:
			r = radixSort(clone_a, n);
			break;
		case SortingAlgo::SELECTION_SORT:
			r = selectionSort(clone_a, n);
			break;
		case SortingAlgo::SHAKER_SORT:
			r = shakerSort(clone_a, n);
			break;
		case SortingAlgo::SHELL_SORT:
			r = shellSort(clone_a, n);
			break;
		default:
			break;
	}
	if (outputFile != nullptr && *outputFile != '\0') {
		writeFile(outputFile, clone_a, n);
	}
	delete[] clone_a;
	return r;
}

void refSort(SortingAlgo algo, int *a, int n, Result *r, const char *outputFile = nullptr) {
	*r = sort(algo, a, n, outputFile);
}

void printAlgoList() {
	cout << "Here is the list of all algorithms: \n";
	cout << "No)    Name                    Tag\n";
	for (int i = 0; i < algoName.size(); i++) {
		printf("%2d)  %-21s - %s\n", i + 1, algoName[i].c_str(), sortingAlgo[i].c_str());
	}
}

void logGenerateDataInfo(InputOrder order) {
	cout << "Input order: ";
	switch (order) {
		case InputOrder::ORDER_RAND:
			cout << "Random\n";
			break;
		case InputOrder::ORDER_SORTED:
			cout << "Sorted\n";
			break;
		case InputOrder::ORDER_REV:
			cout << "Reverse sorted\n";
			break;
		case InputOrder::ORDER_NSORTED:
			cout << "Near sorted\n";
			break;
		default:
			break;
	}
}

void generateDataInfo(int *a, int n, InputOrder order, const char *outputFile = nullptr) {
	switch (order) {
		case InputOrder::ORDER_RAND:
			GenerateData(a, n, 0);
			break;
		case InputOrder::ORDER_SORTED:
			GenerateData(a, n, 1);
			break;
		case InputOrder::ORDER_REV:
			GenerateData(a, n, 2);
			break;
		case InputOrder::ORDER_NSORTED:
			GenerateData(a, n, 3);
			break;
		default:
			break;
	}
	if (outputFile != nullptr && *outputFile != '\0') {
		writeFile(outputFile, a, n);
	}
}

void logOutputInfo(Result r, OutputMode oMode) {
	cout << "--------------------------\n";
	cout << "Running time (if required): ";
	if (oMode == BOTH || oMode == TIME) {
		printf("%.3f (ms)", r.time);
	}
	cout << '\n';
	cout << "Comparisons (if required): ";
	if (oMode == BOTH || oMode == COMP) {
		cout << r.cmps << " (times)";
	}
	cout << '\n';
}

int main(int argc, char **argv) {
	if (argc < 2) {
		printHelp();
		return 0;
	}
	int *a1 = nullptr;
	int n = 0;

	if (strcmp(argv[1], "-a") == 0) {
		OutputMode oMode;
		if (argc < 5) {
			printf("Command required at least 5 parameters, %d given!\n", argc);
			printHelp();
			return 0;
		}
		SortingAlgo algo = getSortingAlgoFromText(argv[2]);
		if (algo == SortingAlgo::UNKNOWN_SORT) {
			printf("Unknown algorithm (%s)\n", argv[2]);
			printAlgoList();
			return 0;
		}
		cout << "ALGORITHM MODE\n";
		Result r;
		cout << "Algorithm: " << algoName[algo] << '\n';
		if (isValidInputNumber(argv[3])) { // command 2 or command 3
			cout << "Input size: " << argv[3] << '\n';
			n = stoi(argv[3]);
			a1 = new int[n];
			if (argc == 5) { // command 3
				oMode = getOutputMode(argv[4]);
				cout << '\n';
				int *c_a1 = new int[n];
				int *c_a2 = new int[n];
				int *c_a3 = new int[n];
				int *c_a4 = new int[n];
				Result r1;
				Result r2;
				Result r3;
				Result r4;
				generateDataInfo(c_a1, n, ORDER_RAND, "input_1.txt");
				thread t1(refSort, algo, c_a1, n, &r1, nullptr);
				generateDataInfo(c_a2, n, ORDER_SORTED, "input_2.txt");
				thread t2(refSort, algo, c_a2, n, &r2, nullptr);
				generateDataInfo(c_a3, n, ORDER_REV, "input_3.txt");
				thread t3(refSort, algo, c_a3, n, &r3, nullptr);
				generateDataInfo(c_a4, n, ORDER_NSORTED, "input_4.txt");
				thread t4(refSort, algo, c_a4, n, &r4, nullptr);
				logGenerateDataInfo(ORDER_RAND);
				t1.join();
				logOutputInfo(r1, oMode);
				cout << '\n';
				delete[] c_a1;
				logGenerateDataInfo(ORDER_SORTED);
				t2.join();
				delete[] c_a2;
				logOutputInfo(r2, oMode);
				cout << '\n';
				logGenerateDataInfo(ORDER_REV);
				t3.join();
				delete[] c_a3;
				logOutputInfo(r3, oMode);
				cout << '\n';
				logGenerateDataInfo(ORDER_NSORTED);
				t4.join();
				delete[] c_a4;
				logOutputInfo(r4, oMode);
				delete[] a1;
				return 0;
			}
			// command 2
			InputOrder iOrder = getInputOrder(argv[4]);

			if (iOrder == InputOrder::ORDER_UNKNOWN) {
				printHelp();
				return 0;
			}
			logGenerateDataInfo(iOrder);
			generateDataInfo(a1, n, iOrder, "input.txt");
			oMode = getOutputMode(argv[5]);
		} else if (fileExist(argv[3])) { // command 1
			a1 = readFile(argv[3], n);
			cout << "Input file: " << argv[3] << "\n";
			cout << "Input size: " << n << "\n";
			oMode = getOutputMode(argv[4]);
		} else {
			cout << "Cannot find file with the name: " << argv[3] << "\n";
			return 0;
		}
		r = sort(algo, a1, n, "output.txt");
		if (oMode == OutputMode::NONE) { // send help
			printHelp();
			return 0;
		}
		logOutputInfo(r, oMode);
	} else if (strcmp(argv[1], "-c") == 0) { // command 4, 5
		SortingAlgo algo1 = getSortingAlgoFromText(argv[2]);
		SortingAlgo algo2 = getSortingAlgoFromText(argv[3]);
		Result r1;
		Result r2;
		if (algo1 == UNKNOWN_SORT || algo2 == UNKNOWN_SORT || argc < 5) {
			printHelp();
			delete[] a1;
			return 0;
		}
		cout << "COMPARE MODE\n";
		printf("Algorithm: %21s | %-21s\n", algoName[algo1].c_str(), algoName[algo2].c_str());
		if (isValidInputNumber(argv[4])) { // command 5
			cout << "Input size: " << argv[4] << '\n';
			n = stoi(argv[4]);
			a1 = new int[n];
			InputOrder iOrder = getInputOrder(argv[5]);
			if (iOrder == InputOrder::ORDER_UNKNOWN) {
				printHelp();
				return 0;
			}
			GenerateData(a1, n, iOrder);
			writeFile("input.txt", a1, n);
		} else if (fileExist(argv[4])) { // command 4
			a1 = readFile(argv[4], n);
			cout << "Input file: " << argv[4] << "\n";
			cout << "Input size: " << n << "\n";
			a1 = readFile(argv[4], n);
		} else {
			cout << "Cannot find file with the name: " << argv[4] << "\n";
			delete[] a1;
			return 0;
		}

		thread t1(refSort, algo1, a1, n, &r1, nullptr);
		thread t2(refSort, algo2, a1, n, &r2, nullptr);
		t1.join();
		t2.join();

		cout << "--------------------------------------------------------------\n";
		printf("Running time: %18f | %-18f  (ms)\n", r1.time, r2.time);
		printf("Comparisons:  %18lld | %-18lld  (times)\n", r1.cmps, r2.cmps);
	} else if (strcmp(argv[1], "-l") == 0) { // extra command for display all algorithms
		printAlgoList();
	} else {
		printHelp();
	}

	delete[] a1;
	return 0;
}
