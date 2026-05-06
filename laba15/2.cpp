#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Time {
    int hours;
    int minutes;

    int toMinutes() const {
        return hours * 60 + minutes;
    }

    void print() const {
        cout << hours << ":" << (minutes < 10 ? "0" : "") << minutes;
    }
};

struct Train {
    int number;
    string destination;
    int distance;
    Time departure;
    Time arrival;
    int travelTime;

    void calculateTravelTime() {
        travelTime = arrival.toMinutes() - departure.toMinutes();
        if (travelTime < 0) {
            travelTime += 24 * 60;
        }
    }

    void print() const {
        cout << "Train #" << number << " -> " << destination;
        cout << " | Departure: ";
        departure.print();
        cout << " | Arrival: ";
        arrival.print();
        cout << " | Travel time: " << travelTime << " min" << endl;
    }
};

int findMaxTravelTimeIndex(const vector<Train> &trains) {
    int maxIndex = 0;
    for (size_t i = 1; i < trains.size(); i++) {
        if (trains[i].travelTime > trains[maxIndex].travelTime) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

void selectionSortByTravelTime(vector<Train> &trains) {
    int n = trains.size();

    for (int i = 0; i < n - 1; i++) {
        int maxIdx = i;

        for (int j = i + 1; j < n; j++) {
            if (trains[j].travelTime > trains[maxIdx].travelTime) {
                maxIdx = j;
            }
        }

        if (maxIdx != i) {
            swap(trains[i], trains[maxIdx]);
        }
    }
}

int main() {
    vector<Train> trains = {
        {101, "Kyiv", 450, {8, 0}, {14, 30}, 0},
        {205, "Lviv", 320, {9, 45}, {15, 15}, 0},
        {312, "Odesa", 280, {10, 30}, {16, 45}, 0},
        {157, "Kharkiv", 520, {7, 15}, {15, 45}, 0},
        {423, "Dnipro", 210, {12, 0}, {16, 30}, 0},
        {389, "Zaporizhzhia", 380, {13, 20}, {21, 10}, 0},
        {256, "Vinnytsia", 150, {15, 0}, {18, 45}, 0},
    };

    for (auto &train: trains) {
        train.calculateTravelTime();
    }

    cout << "================================================================" << endl;
    cout << "                     TRAIN SCHEDULE" << endl;
    cout << "================================================================" << endl;
    for (const auto &train: trains) {
        train.print();
    }

    cout << "\n================================================================" << endl;
    cout << "PART A: Finding train with longest travel time" << endl;
    cout << "================================================================" << endl;

    int maxIndex = findMaxTravelTimeIndex(trains);
    cout << "Train with longest travel time:" << endl;
    cout << "   Train number: " << trains[maxIndex].number << endl;
    cout << "   Destination: " << trains[maxIndex].destination << endl;
    cout << "   Travel time: " << trains[maxIndex].travelTime << " minutes" << endl;

    cout << "\n================================================================" << endl;
    cout << "PART B: Sorting by travel time using SELECTION SORT" << endl;
    cout << "================================================================" << endl;

    vector<Train> sortedTrains = trains;
    selectionSortByTravelTime(sortedTrains);

    cout << "\nAfter Selection Sort (descending order):" << endl;
    cout << "------------------------------------------------" << endl;
    cout << "Train with MAXIMUM travel time:" << endl;
    cout << "   Train number: " << sortedTrains[0].number << endl;
    cout << "   Destination: " << sortedTrains[0].destination << endl;
    cout << "   Travel time: " << sortedTrains[0].travelTime << " minutes" << endl;

    cout << "\nAll trains sorted by travel time (descending):" << endl;
    cout << "------------------------------------------------" << endl;
    for (const auto &train: sortedTrains) {
        cout << "   Train #" << train.number << " -> " << train.destination;
        cout << " | Travel time: " << train.travelTime << " min" << endl;
    }

    cout << "\n================================================================" << endl;
    cout << "VERIFICATION: Both methods give the same result?" << endl;
    cout << "================================================================" << endl;

    if (trains[maxIndex].number == sortedTrains[0].number &&
        trains[maxIndex].destination == sortedTrains[0].destination) {
        cout << "YES! Both methods identified the same train." << endl;
    } else {
        cout << "ERROR: Methods gave different results!" << endl;
    }

    return 0;
}