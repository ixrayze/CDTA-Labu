#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    multimap<string, string> phoneBook;
    int choice;

    do {
        cout <<
                "\n1. Add record\n2. View numbers by name\n3. Delete specific number\n4. Delete all numbers by name\n5. View all directory\n6. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            string name, number;
            cout << "Enter name and number: ";
            cin >> name >> number;
            phoneBook.insert({name, number});
        } else if (choice == 2) {
            string name;
            cout << "Enter name: ";
            cin >> name;
            auto range = phoneBook.equal_range(name);
            for (auto it = range.first; it != range.second; ++it) {
                cout << it->second << endl;
            }
        } else if (choice == 3) {
            string name, number;
            cout << "Enter name and number to delete: ";
            cin >> name >> number;
            auto range = phoneBook.equal_range(name);
            for (auto it = range.first; it != range.second; ++it) {
                if (it->second == number) {
                    phoneBook.erase(it);
                    break;
                }
            }
        } else if (choice == 4) {
            string name;
            cout << "Enter name: ";
            cin >> name;
            phoneBook.erase(name);
        } else if (choice == 5) {
            cout << "Directory:\n";
            for (auto p: phoneBook) {
                cout << p.first << " - " << p.second << endl;
            }
        }
    } while (choice != 6);

    return 0;
}
