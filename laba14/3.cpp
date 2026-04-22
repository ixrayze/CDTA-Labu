#include <iostream>
#include <deque>
#include <string>

using namespace std;

int main() {
    deque<string> requests;
    int choice;

    do {
        cout <<
                "\n1. Add normal request\n2. Add urgent request\n3. Process request\n4. View queue\n5. Queue size\n6. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            string req;
            cout << "Enter request: ";
            cin >> req;
            requests.push_back(req);
        } else if (choice == 2) {
            string req;
            cout << "Enter urgent request: ";
            cin >> req;
            requests.push_front(req);
        } else if (choice == 3) {
            if (!requests.empty()) {
                cout << "Processing: " << requests.front() << endl;
                requests.pop_front();
            } else {
                cout << "Queue is empty." << endl;
            }
        } else if (choice == 4) {
            cout << "Current queue:\n";
            for (string req: requests) {
                cout << req << endl;
            }
        } else if (choice == 5) {
            cout << "Total requests: " << requests.size() << endl;
        }
    } while (choice != 6);

    return 0;
}
