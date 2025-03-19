#include <iostream>
#include <vector>
#include <thread>
#include <cstring>
#include <string>
#include "utils/utils.h"
#include "sort.h"

using namespace std;

void displayHelp() {
    cout << "SGP - Sorting Algorithm Performance Tester\n\n"
         << "Usage: sgp [arguments]\n"
         << "       sgp -a [algorithm] [input filename] [output param]\n"
         << "       sgp -a [algorithm] [input size] [input order] [output param]\n"
         << "       sgp -a [algorithm] [input size] [output param]\n\n"
         << "       sgp -c [algorithm1] [algorithm2] [input filename]\n"
         << "       sgp -c [algorithm1] [algorithm2] [input size] [input order]\n\n"
         << "       sgp -l  (List all supported sorting algorithms)\n";
}

int* duplicateArray(const int* arr, int size) {
    int* newArr = new int[size];
    memcpy(newArr, arr, size * sizeof(int));
    return newArr;
}

Result executeSort(SortingAlgo algo, int* arr, int size, const char* outputFile = nullptr) {
    if (algo == UNKNOWN_SORT) return {-1, 0};
    
    int* tempArr = duplicateArray(arr, size);
    Result result;

    switch (algo) {
        case BINARY_INSERTION_SORT: result = binaryInsertionSort(tempArr, size); break;
        case BUBBLE_SORT: result = bubbleSort(tempArr, size); break;
        case COUNTING_SORT: result = countingSort(tempArr, size); break;
        case FLASH_SORT: result = flashSort(tempArr, size); break;
        case HEAP_SORT: result = heapSort(tempArr, size); break;
        case INSERTION_SORT: result = insertionSort(tempArr, size); break;
        case MERGE_SORT: result = mergeSort(tempArr, size); break;
        case QUICK_SORT: result = quickSort(tempArr, size); break;
        case RADIX_SORT: result = radixSort(tempArr, size); break;
        case SELECTION_SORT: result = selectionSort(tempArr, size); break;
        case SHAKER_SORT: result = shakerSort(tempArr, size); break;
        case SHELL_SORT: result = shellSort(tempArr, size); break;
        default: break;
    }

    if (outputFile && *outputFile) {
        writeFile(outputFile, tempArr, size);
    }
    delete[] tempArr;
    return result;
}
void printAlgoList() {
    cout << "Here is the list of all algorithms: \n";
    cout << "No)    Name                    Tag\n";
    for (int i = 0; i < algoName.size(); i++) {
        printf("%2d)  %-21s - %s\n", i + 1, algoName[i].c_str(), sortingAlgo[i].c_str());
    }
}
void logInputOrder(InputOrder order) {
    cout << "Input order: ";
    switch (order) {
        case ORDER_RAND: cout << "Random"; break;
        case ORDER_SORTED: cout << "Sorted"; break;
        case ORDER_REV: cout << "Reverse sorted"; break;
        case ORDER_NSORTED: cout << "Near sorted"; break;
        default: return;
    }
    cout << "\n";
}

void generateInputData(int* arr, int size, InputOrder order, const char* outputFile = nullptr) {
    GenerateData(arr, size, static_cast<int>(order));
    if (outputFile && *outputFile) {
        writeFile(outputFile, arr, size);
    }
}

void displaySortResult(Result res, OutputMode mode) {
    cout << "--------------------------\n";
    if (mode == BOTH || mode == TIME) {
        cout << "Execution Time: " << res.time << " ms\n";
    }
    if (mode == BOTH || mode == COMP) {
        cout << "Comparisons: " << res.cmps << " times\n";
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        displayHelp();
        return 0;
    }

    int* arr = nullptr;
    int size = 0;

    if (strcmp(argv[1], "-a") == 0) {
        if (argc < 5) {
            cout << "Insufficient parameters!\n";
            displayHelp();
            return 0;
        }

        SortingAlgo algo = getSortingAlgoFromText(argv[2]);
        if (algo == UNKNOWN_SORT) {
            cout << "Invalid sorting algorithm: " << argv[2] << "\n";
            return 0;
        }

        OutputMode mode;
        if (isValidInputNumber(argv[3])) {
            size = stoi(argv[3]);
            arr = new int[size];
            
            if (argc == 5) {
                mode = getOutputMode(argv[4]);
                Result res = executeSort(algo, arr, size, "output.txt");
                displaySortResult(res, mode);
            } else {
                InputOrder order = getInputOrder(argv[4]);
                logInputOrder(order);
                generateInputData(arr, size, order, "input.txt");
                mode = getOutputMode(argv[5]);
                Result res = executeSort(algo, arr, size, "output.txt");
                displaySortResult(res, mode);
            }
        } else if (fileExist(argv[3])) {
            arr = readFile(argv[3], size);
            mode = getOutputMode(argv[4]);
            Result res = executeSort(algo, arr, size, "output.txt");
            displaySortResult(res, mode);
        } else {
            cout << "File not found: " << argv[3] << "\n";
        }
    } else if (strcmp(argv[1], "-c") == 0) {
        if (argc < 5) {
            displayHelp();
            return 0;
        }

        SortingAlgo algo1 = getSortingAlgoFromText(argv[2]);
        SortingAlgo algo2 = getSortingAlgoFromText(argv[3]);
        if (algo1 == UNKNOWN_SORT || algo2 == UNKNOWN_SORT) {
            displayHelp();
            return 0;
        }

        if (isValidInputNumber(argv[4])) {
            size = stoi(argv[4]);
            arr = new int[size];
            generateInputData(arr, size, getInputOrder(argv[5]), "input.txt");
        } else if (fileExist(argv[4])) {
            arr = readFile(argv[4], size);
        } else {
            cout << "File not found: " << argv[4] << "\n";
            return 0;
        }

        Result res1, res2;
        thread t1([&] { res1 = executeSort(algo1, arr, size, nullptr); });
        thread t2([&] { res2 = executeSort(algo2, arr, size, nullptr); });
        t1.join();
        t2.join();

        cout << "--------------------------------------------------------------\n";
        printf("Execution Time: %18f | %-18f (ms)\n", res1.time, res2.time);
        printf("Comparisons: %18lld | %-18lld (times)\n", res1.cmps, res2.cmps);
    } else if (strcmp(argv[1], "-l") == 0) {
        printAlgoList();
    } else {
        displayHelp();
    }

    delete[] arr;
    return 0;
}
