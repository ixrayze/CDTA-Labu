#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Student {
    string surname;
    int marks[3];
    double average;
};

double calculateAverage(int marks[3]) {
    return (marks[0] + marks[1] + marks[2]) / 3.0;
}

void findMaxAverage(const vector<Student> &students) {
    double maxAvg = students[0].average;

    for (const auto &s: students) {
        if (s.average > maxAvg) {
            maxAvg = s.average;
        }
    }

    cout << "\nMax average score: " << maxAvg << endl;
    cout << "Students with max average:\n";

    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].average == maxAvg) {
            cout << "Index: " << i << ", Surname: " << students[i].surname << endl;
            return;
        }
    }
}

void binarySearch(vector<Student> &students, double target) {
    int left = 0, right = students.size() - 1;
    bool found = false;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (students[mid].average == target) {
            cout << "\nFound student(s) with average " << target << ":\n";

            int i = mid;
            while (i >= 0 && students[i].average == target) {
                cout << students[i].surname << endl;
                i--;
            }

            i = mid + 1;
            while (i < students.size() && students[i].average == target) {
                cout << students[i].surname << endl;
                i++;
            }

            found = true;
            break;
        }
        if (students[mid].average < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (!found) {
        cout << "\nNo student found with this average.\n";
    }
}

int main() {
    cout << "STARTING LAB16_TASK1" << endl;

    vector<Student> students = {
        {"f", {3, 4, 5}, 0},
        {"s", {5, 6, 7}, 0}
    };

    for (auto &s: students) {
        s.average = calculateAverage(s.marks);
    }

    cout << "===========" << endl;
    findMaxAverage(students);

    cout << "===========" << endl;
    sort(students.begin(), students.end(), [](Student a, Student b) {
        return a.average < b.average;
    });
    cout << "===========" << endl;

    double target = 6.0;

    binarySearch(students, target);

    return 0;
}