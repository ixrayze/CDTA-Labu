#include <iostream>
#include <string>

using namespace std;

enum Faculty {
    IT,
    Economics,
    Law,
    Management
};

struct Student {
    string surname;
    int year;
    double averageGrade;
    Faculty faculty;
};

int main() {
    const int N = 3;
    Student group[N];
    double totalSum = 0;

    cout << "--- Entering student data ---" << endl;

    for (int i = 0; i < N; i++) {
        cout << "\nStudent #" << i + 1 << ":" << endl;

        cout << "Surname: ";
        cin >> group[i].surname;

        cout << "Year: ";
        cin >> group[i].year;

        cout << "Average grade: ";
        cin >> group[i].averageGrade;

        cout << "Faculty (0 - IT, 1 - Economics, 2 - Law, 3 - Management): ";
        int facChoice;
        cin >> facChoice;

        group[i].faculty = (Faculty)facChoice;

        totalSum = totalSum + group[i].averageGrade;
    }

    double groupAverage = totalSum / N;
    cout << "\n=====================================" << endl;
    cout << "Group average grade: " << groupAverage << endl;

    cout << "\n=====================================" << endl;
    cout << "Enter faculty number to search (0, 1, 2 or 3): ";
    int searchFac;
    cin >> searchFac;

    Faculty targetFaculty = (Faculty)searchFac;

    cout << "\nList of found students:" << endl;
    bool found = false;

    for (int i = 0; i < N; i++) {
        if (group[i].faculty == targetFaculty) {
            cout << "- " << group[i].surname << " (Year: " << group[i].year
                 << ", Grade: " << group[i].averageGrade << ")" << endl;
            found = true;
        }
    }

    if (found == false) {
        cout << "No students found in this faculty." << endl;
    }

    return 0;
}