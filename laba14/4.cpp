#include <iostream>
#include <set>
#include <unordered_set>
#include <string>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;

int main() {
    int n, k;
    cout << "Enter N (insert count) and K (search count): ";
    cin >> n >> k;

    vector<string> words(n);
    vector<string> queries(k);
    cout << "Enter " << n << " words for insert:\n";
    for (int i = 0; i < n; i++) cin >> words[i];

    cout << "Enter " << k << " words for search:\n";
    for (int i = 0; i < k; i++) cin >> queries[i];

    set<string> s1;
    unordered_set<string> s2;

    auto start_time = high_resolution_clock::now();
    for (string w: words) s1.insert(w);
    auto end_time = high_resolution_clock::now();
    cout << "set insert time: " << duration_cast<microseconds>(end_time - start_time).count() << " mks\n";

    start_time = high_resolution_clock::now();
    for (string w: words) s2.insert(w);
    end_time = high_resolution_clock::now();
    cout << "unordered_set insert time: " << duration_cast<microseconds>(end_time - start_time).count() << " mks\n";

    start_time = high_resolution_clock::now();
    for (string q: queries) s1.find(q);
    end_time = high_resolution_clock::now();
    cout << "set search time: " << duration_cast<microseconds>(end_time - start_time).count() << " mks\n";

    start_time = high_resolution_clock::now();
    for (string q: queries) s2.find(q);
    end_time = high_resolution_clock::now();
    cout << "unordered_set search time: " << duration_cast<microseconds>(end_time - start_time).count() << " mks\n";

    return 0;
}
