#include <iostream>
#include <string>
using namespace std;

struct Student {
    string name;
    int group;
    double SES[5];

    void input() {
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter group: ";
        cin >> group;
        cout << "Enter SES: ";
        for (int i = 0; i < 5; i++) {
            cin >> SES[i];
        }
    }

    void show() {
        cout << "Student name: " << name << "\n";
        cout << "Student group: " << group << "\n";
        for (int i = 0; i < 5; i++) {
            cout << "SES: " << SES[i] << " ";
        }
    }
};

void seredniyBal(Student s) {
    int suma = 0;
    for (int i = 0; i < 5; i++) {
        suma += s.SES[i];
    }

    if (suma / 5 > 4) {
        cout << s.name << " " << s.group << '\n';
    }

    int main()
    {
        int n;
        cout << "Enter number of students: ";
        cin >> n;
        Student student[n];
        for (int i = 0; i < n; i++) {
            student[i].input();
        }
        for (int i = 0; i < n; i++) {
            student[i].show();
        }

        return 0;
    }
