#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Book {
    string title;
    string genre;
    double price;
    int pop;
    string date;
};

int main() {
    vector<Book> v;
    v.push_back({"B1", "G1", 300.0, 10, "2023"});
    v.push_back({"B2", "G2", 500.0, 0, "2022"});
    v.push_back({"B3", "G1", 450.0, 5, "2024"});

    v.erase(remove_if(v.begin(), v.end(), [](const Book &b) {
        return b.pop == 0;
    }), v.end());

    sort(v.begin(), v.end(), [](const Book &a, const Book &b) {
        return a.price < b.price;
    });

    for (int i = 0; i < v.size(); i++) {
        if (v[i].price < 600.0) {
            cout << v[i].title << " " << v[i].price << " UAH" << endl;
        }
    }

    return 0;
}
