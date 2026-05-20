#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

int getValidChoice() {
    int choice;
    while (!(cin >> choice)) {
        cin.clear();
        while (cin.get() != '\n') continue;
        cout << "Invalid input. Please enter a valid number: ";
    }
    return choice;
}

struct Employee {
    string title;
    int count;
    double A;
    double B;

    double getK() const {
        return A / B;
    }
};

void calculateSalaries() {
    vector<Employee> staff = {
        {"Sanitarka", 7, 1, 1},
        {"Medsesra", 10, 6, 5},
        {"Likar", 10, 8, 5},
        {"Zav. aptekoyu", 1, 9, 5},
        {"Zav. viddilennyam", 3, 2, 1},
        {"Golovniy likar", 1, 12, 5},
        {"Zav. gosp.", 1, 13, 5},
        {"Zav. likarneyu", 1, 3, 1}
    };

    double totalFund = 380000.0;
    double totalCoefficientUnits = 0.0;

    // сумуємо всі коефіцієнти працівників
    for (size_t i = 0; i < staff.size(); i++) {
        totalCoefficientUnits += staff[i].count * staff[i].getK();
    }

    // знаходимо ставку санітарки
    int baseSalary = totalFund / totalCoefficientUnits;

    int actualSpent = 0;
    int tableWidth = 68;

    cout << "\n" << string(17, '=') << " Salary Distribution " << string(17, '=') << "\n";
    cout << left << setw(20) << "Position"
         << setw(10) << "Count"
         << setw(10) << "Coef(K)"
         << setw(15) << "Salary(1)"
         << "Total Salary\n";

    cout << string(tableWidth, '-') << "\n";

    for (size_t i = 0; i < staff.size(); i++) {
        int individualSalary = baseSalary * staff[i].getK();
        int groupSalary = individualSalary * staff[i].count;
        actualSpent += groupSalary;

        cout << left << setw(20) << staff[i].title
             << setw(10) << staff[i].count
             << setw(10) << fixed << setprecision(1) << staff[i].getK()
             << setw(15) << individualSalary
             << groupSalary << " UAH\n";
    }

    cout << string(tableWidth, '-') << "\n";
    cout << "Total Allocated Fund: " << actualSpent << " UAH\n";
    cout << "Remaining Budget:     " << (int)totalFund - actualSpent << " UAH\n";
    cout << string(tableWidth, '=') << "\n";
}

int main() {
    bool isRunning = true;

    while (isRunning) {
        cout << "\n" << string(3, '=') << " Hospital Salary Menu " << string(3, '=') << "\n";
        cout << "1. Calculate Optimal Salaries\n";
        cout << "0. Exit\n";
        cout << "Choice: ";

        int choice = getValidChoice();
        cin.ignore();

        switch (choice) {
            case 1:
                calculateSalaries();
                break;
            case 0:
                cout << "Exiting program...\n";
                isRunning = false;
                break;
            default:
                cout << "Incorrect choice. Try again.\n";
                break;
        }
    }
    return 0;
}