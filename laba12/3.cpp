#include <iostream>
#include <deque>
#include <string>
#include <algorithm>

using namespace std;

struct Order {
    int id;
    string client;
    double price;
    bool urgent;
    string status;
};

int main() {
    deque<Order> d;

    d.push_back({1, "Ivanov", 500.0, false, "Active"});
    d.push_front({2, "Petrov", 1500.0, true, "Active"});
    d.push_back({3, "Sydorov", 200.0, false, "Canceled"});

    d.erase(remove_if(d.begin(), d.end(), [](const Order &o) {
        return o.status == "Canceled";
    }), d.end());

    sort(d.begin(), d.end(), [](const Order &a, const Order &b) {
        return a.price < b.price;
    });

    for (auto o: d) {
        cout << o.id << " " << o.client << " " << o.price << endl;
    }

    return 0;
}
