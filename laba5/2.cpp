#include <iostream>
#include <string>
using namespace std;

struct City {
    string name;
    int dist;
    City *next;
} *first, *last;

int main() {
    int n;
    cout << "Enter number of cities: ";
    cin >> n;
    City *q;

    for (int i = 0; i < n; i++) {
        City *c = new City;
        cout << "Enter city name and distance to Kyiv: ";
        cin >> c->name >> c->dist;
        c->next = 0;
        if (first == 0) {
            first = c;
            last = c;
        } else {
            last->next = c;
            last = c;
        }
    }

    int max1 = -1, max2 = -1;
    string c1 = "", c2 = "";

    q = first;
    while (q != 0) {
        if (q->dist > max1) {
            max2 = max1;
            c2 = c1;
            max1 = q->dist;
            c1 = q->name;
        } else if (q->dist > max2) {
            max2 = q->dist;
            c2 = q->name;
        }
        q = q->next;
    }

    cout << "Most distant cities: " << c1 << " " << c2 << '\n';

    City *foreign = new City;
    cout << "Enter foreign city name and distance: ";
    cin >> foreign->name >> foreign->dist;
    foreign->next = first;
    first = foreign;

    while (first != 0) {
        q = first;
        first = first->next;
        delete q;
    }

    return 0;
}
