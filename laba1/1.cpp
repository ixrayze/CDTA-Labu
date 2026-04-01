#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cmath>

using namespace std;

bool isMultipleOf4(int n) {
    return n % 4 == 0;
}

void fillArray(double *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = -1.50 + (rand() % 601) / 100.0;
    }
}

void printArray(double *arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void createMatrix(double *arr, double **mat, int n) {
    int rows = n / 4;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 4; j++) {
            mat[i][j] = arr[i * 4 + j];
        }
    }
}

void bubbleSort(double *arr, int size, bool ascending) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (ascending) {
                if (arr[j] > arr[j + 1]) {
                    double temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            } else {
                if (arr[j] < arr[j + 1]) {
                    double temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
}

double findMax(double *arr, int size) {
    double maxVal = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

void runTest(int n, int testId, ofstream &outFile) {
    if (!isMultipleOf4(n)) return;

    clock_t start = clock();

    double *A = new double[n];
    fillArray(A, n);

    int rows = n / 4;
    double **B = new double *[rows];
    for (int i = 0; i < rows; i++) {
        B[i] = new double[4];
    }

    createMatrix(A, B, n);

    for (int i = 0; i < rows; i++) {
        bubbleSort(B[i], 4, i % 2 == 0);
    }

    double *colArray = new double[rows];
    double maxVals[4];

    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < rows; i++) {
            colArray[i] = B[i][j];
        }
        maxVals[j] = findMax(colArray, rows);
    }

    clock_t end = clock();
    double timeSec = double(end - start) / CLOCKS_PER_SEC;

    size_t spaceBytes = (sizeof(double) * n) + (sizeof(double *) * rows) + (sizeof(double) * n) + (
                            sizeof(double) * rows) + sizeof(maxVals) + sizeof(A) + sizeof(B) + sizeof(colArray);

    outFile << testId << "\t|\t" << n << "\t|\t" << fixed << setprecision(3) << timeSec << "\t\t|\t" << spaceBytes <<
            "\n";

    delete[] colArray;
    for (int i = 0; i < rows; i++) {
        delete[] B[i];
    }
    delete[] B;
    delete[] A;
}

int main() {
    srand(static_cast<unsigned>(time(NULL)));

    ofstream outFile("output.txt");
    outFile << "No.\t|\tn\t|\tTime, sec.\t|\tSpace, byte\n";

    runTest(20, 1, outFile);
    runTest(100, 2, outFile);
    runTest(1000, 3, outFile);

    outFile.close();
    cout << "Tests completed. Check output.txt file." << endl;

    return 0;
}
