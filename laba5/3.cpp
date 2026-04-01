#include <iostream>
#include <string>
using namespace std;

struct Car {
    string model;
    int year;
    int price;
    Car *next;
} *first, *last;

int main() {
    int n;
    cout << "Enter number of cars: ";
    cin >> n;
    Car *q;

    for (int i = 0; i < n; i++) {
        Car *c = new Car;
        cout << "Enter car model, year and price: ";
        cin >> c->model >> c->year >> c->price;
        c->next = 0;
        if (first == 0) {
            first = c;
            last = c;
        } else {
            last->next = c;
            last = c;
        }
    }

    cout << "Cars older than 10 years and cheaper than 5000:\n";
    q = first;
    while (q != 0) {
        if ((2026 - q->year > 10) && (q->price < 5000)) {
            cout << q->model << " " << q->year << " " << q->price << '\n';
        }
        q = q->next;
    }

    while (first != 0) {
        q = first;
        first = first->next;
        delete q;
    }

    return 0;
}
