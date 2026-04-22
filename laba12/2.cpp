#include <iostream>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

struct Car {
    string name;
    int year;
    int km;
};

int main() {
    list<Car> l;
    int choice;

    do {
        cout <<
                "1. Vvod\n2. Vstavka pochatok\n3. Vstavka kinec\n4. Poshuk\n5. Vydalennya\n6. Pereglyad\n7. Vyhid\nVybir: ";
        cin >> choice;

        if (choice == 1 || choice == 2) {
            l.push_front({"BMW", 2015, 120000});
        } else if (choice == 3) {
            l.push_back({"Audi", 2020, 50000});
        } else if (choice == 4) {
            string target;
            cin >> target;
            auto it = find_if(l.begin(), l.end(), [&](const Car &c) { return c.name == target; });
            if (it != l.end()) cout << "Avto " << target << " ye v spysku\n";
            else cout << "Avto " << target << " nema v spysku\n";
        } else if (choice == 5) {
            int y;
            cin >> y;
            l.remove_if([&](const Car &c) { return c.year < y; });
        } else if (choice == 6) {
            for (auto c: l) cout << c.name << " " << c.year << endl;
        }
    } while (choice != 7);

    return 0;
}
