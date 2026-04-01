#include <iostream>
using namespace std;

struct Node {
    int v;
    Node *next;
} *first, *last;

int main() {
    Node *q;

    Node *n1 = new Node;
    cout << "Enter a number for the beginning: ";
    cin >> n1->v;
    n1->next = 0;
    first = n1;
    last = n1;

    Node *n2 = new Node;
    cout << "Enter a number for the end: ";
    cin >> n2->v;
    n2->next = 0;
    last->next = n2;
    last = n2;

    Node *n3 = new Node;
    cout << "Enter a number for the beginning again: ";
    cin >> n3->v;
    n3->next = first;
    first = n3;

    Node *n4 = new Node;
    cout << "Enter a number for the middle (after first): ";
    cin >> n4->v;
    n4->next = first->next;
    first->next = n4;

    q = first;
    float sum = 0;
    int count = 0;
    while (q != 0) {
        sum += q->v;
        count++;
        q = q->next;
    }
    cout << "Average: " << sum / count << '\n';

    q = first;
    Node *prev = 0;
    while (q != 0) {
        if (q->v % 2 == 0) {
            if (prev == 0) {
                first = q->next;
            } else {
                prev->next = q->next;
            }
            delete q;
            break;
        }
        prev = q;
        q = q->next;
    }

    cout << "List after removing first even element: ";
    q = first;
    while (q != 0) {
        cout << q->v << " ";
        q = q->next;
    }
    cout << '\n';

    while (first != 0) {
        q = first;
        first = first->next;
        delete q;
    }

    return 0;
}
