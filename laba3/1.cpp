#include <iostream>
#include <string>
using namespace std;

struct Worker {
    string surname;
    string posada;
    int startedWork; //refactor field name
    int salary;

    int experience(int r) {
        if (r < startedWork) {
            cout << "Enter correct year!!!";
            return 0;
        } else {
            return r - startedWork;
        }
    }

    int finalSalary(int n) {
        return salary - (salary * (n / 100.0));
    }

    void input() {
        cout << "Enter the name of the surname: ";
        cin >> surname;
        cout << "Enter the name of the posada: ";
        cin >> posada;
        cout << "Enter the year of the surname: ";
        cin >> startedWork;
        cout << "Enter the salary of the surname: ";
        cin >> salary;
    }

    void show(int r, int n) {
        cout << "Experience " << experience(r) << '\n' << "Salary " << finalSalary(n) << '\n';
    }
};

int main() {
    int count, year, procent;

    Worker w;
    cout << "Enter year now: ";
    cin >> year;
    cout << "Enter procent: ";
    cin >> procent;

    w.input();
    w.show(year, procent);

    cout << '\n' << "Enter count workers: ";
    cin >> count;
    Worker *w1 = new Worker[count];

    for (int i = 0; i < count; i++) {
        w1[i].input();
    }
    for (int i = 0; i < count; i++) {
        w1[i].show(year, procent);
    }
    delete[] w1;

    return 0;
}
