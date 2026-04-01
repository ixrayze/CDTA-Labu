#include <iostream>
#include <string>
#include <cctype>

using namespace std;

struct Student {
    string name;
    int group;
    int exams[5];
};

double getAverage(Student s) {
    double sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += s.exams[i];
    }
    return sum / 5.0;
}

void printGoodStudents(Student arr[], int n) {
    cout << "\nStudents with average score > 4.0\n";
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (getAverage(arr[i]) > 4.0) {
            cout << "Name: " << arr[i].name << ", Group: " << arr[i].group << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No students with average score > 4.0 found." << endl;
    }
}

void printVowelSurnames(Student arr[], int n) {
    cout << "\nStudents whose names start with a vowel\n";
    string vowels = "aeiouy";

    for (int i = 0; i < n; i++) {
        if (arr[i].name.length() > 0) {
            char firstLetter = tolower(arr[i].name[0]);
            if (vowels.find(firstLetter) != string::npos) {
                cout << "Name: " << arr[i].name << ", Group: " << arr[i].group << ", Average score: " <<
                        getAverage(arr[i]) << endl;
            }
        }
    }
}

void sortStudents(Student arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (getAverage(arr[j]) > getAverage(arr[j + 1])) {
                Student temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void deleteAfterMin(Student arr[], int &n) {
    if (n < 2) return;

    int minIndex = 0;
    for (int i = 1; i < n; i++) {
        if (getAverage(arr[i]) < getAverage(arr[minIndex])) {
            minIndex = i;
        }
    }

    if (minIndex < n - 1) {
        for (int i = minIndex + 1; i < n - 1; i++) {
            arr[i] = arr[i + 1];
        }
        n--;
        cout << "\nElement after the student with min score deleted.\n";
    } else {
        cout << "\nStudent with min score is the last one, nothing to delete.\n";
    }
}

void printAll(Student arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i].name << " (Group " << arr[i].group << "), Average score: " << getAverage(arr[i]) << endl;
    }
}

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;

    Student students[100];

    for (int i = 0; i < n; i++) {
        cout << "\nStudent " << i + 1 << "\n";
        cout << "Name: ";
        cin >> students[i].name;
        cout << "Group: ";
        cin >> students[i].group;
        cout << "Grades (5 numbers separated by space): ";
        for (int j = 0; j < 5; j++) {
            cin >> students[i].exams[j];
        }
    }

    printGoodStudents(students, n);

    printVowelSurnames(students, n);

    cout << "\nArray BEFORE sorting\n";
    printAll(students, n);

    sortStudents(students, n);
    cout << "\nArray AFTER sorting (ascending)\n";
    printAll(students, n);

    deleteAfterMin(students, n);
    cout << "\nArray AFTER deletion\n";
    printAll(students, n);

    return 0;
}
