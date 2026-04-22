#include <iostream>
#include <array>
#include <algorithm>
#include <ctime>

using namespace std;

int main() {
    srand(time(NULL));
    array<int, 10> assessment;
    double sum = 0;
    cout << "Enter assessment: ";
    for (int i = 0; i < 10; i++) {
        assessment[i] = 2 + rand() % 4;
        sum += assessment[i];
    }
    double avg = sum / 10.0;
    cout << "Avg of assessment: " << avg;
    auto min_it = min_element(assessment.begin(), assessment.end());
    auto max_it = max_element(assessment.begin(), assessment.end());
    int count = count_if(assessment.begin(), assessment.end(), [avg](int x) {
        return x > avg;
    });
    cout << "\nMax assessment: " << *max_it;
    cout << "\nMin assessment: " << *min_it;;

    sort(assessment.begin(), assessment.end());
    cout << "\nSorted assessment: ";
    for (int x: assessment) cout << x << " ";

    sort(assessment.begin(), assessment.end(), greater<int>());
    cout << "\nSorted assessment: ";
    for (int x: assessment)
        cout << x << " ";
    cout << '\n';

    return 0;
}
