#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace chrono;

void bubbleSort(vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void insertionSort(vector<int> &arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            swap(arr[i], arr[minIdx]);
        }
    }
}

void gnomeSort(vector<int> &arr) {
    int i = 0;
    int n = arr.size();
    while (i < n) {
        if (i == 0 || arr[i] >= arr[i - 1]) {
            i++;
        } else {
            swap(arr[i], arr[i - 1]);
            i--;
        }
    }
}

long long measureTime(void (*sortFunc)(vector<int> &), vector<int> data) {
    auto start = high_resolution_clock::now();
    sortFunc(data);
    auto end = high_resolution_clock::now();
    return duration_cast<milliseconds>(end - start).count();
}

int main() {
    srand(time(nullptr));

    vector<int> sizes = {1000, 10000, 100000};

    // 2D array to store results: 4 algorithms x 3 array sizes
    vector<vector<long long>> results(4, vector<long long>(3));

    // Calculate times for each size
    for (size_t s = 0; s < sizes.size(); s++) {
        int n = sizes[s];
        vector<int> original(n);
        for (int i = 0; i < n; i++) {
            original[i] = rand() % 100000;
        }

        results[0][s] = measureTime(bubbleSort, original);
        results[1][s] = measureTime(insertionSort, original);
        results[2][s] = measureTime(selectionSort, original);
        results[3][s] = measureTime(gnomeSort, original);
    }

    // Print table header
    cout << "\n";
    cout << "================================================================================\n";
    cout << "             COMPARATIVE ANALYSIS OF SORTING TIME (in ms)\n";
    cout << "================================================================================\n";
    cout << left << setw(5) << "ID"
         << setw(25) << "Algorithm"
         << right << setw(15) << "n = 1000"
         << setw(15) << "n = 10000"
         << setw(15) << "n = 100000" << "\n";
    cout << "--------------------------------------------------------------------------------\n";

    // Print results rows
    cout << left << setw(5) << "1" << setw(25) << "Bubble Sort"
         << right << setw(15) << results[0][0] << setw(15) << results[0][1] << setw(15) << results[0][2] << "\n";

    cout << left << setw(5) << "2" << setw(25) << "Insertion Sort"
         << right << setw(15) << results[1][0] << setw(15) << results[1][1] << setw(15) << results[1][2] << "\n";

    cout << left << setw(5) << "3" << setw(25) << "Selection Sort"
         << right << setw(15) << results[2][0] << setw(15) << results[2][1] << setw(15) << results[2][2] << "\n";

    cout << left << setw(5) << "4" << setw(25) << "Gnome Sort"
         << right << setw(15) << results[3][0] << setw(15) << results[3][1] << setw(15) << results[3][2] << "\n";

    cout << "--------------------------------------------------------------------------------\n";

    return 0;
}