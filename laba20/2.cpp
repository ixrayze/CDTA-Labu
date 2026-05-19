#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Структура для зберігання даних про заняття
struct Activity {
    int id;
    int start;
    int end;
};

// Правило сортування: жадібний алгоритм вимагає сортування за часом закінчення
bool compareActivities(Activity a, Activity b) {
    return a.end < b.end;
}

int getValidChoice() {
    int choice;
    while (!(cin >> choice)) {
        cin.clear();
        while (cin.get() != '\n') continue;
        cout << "Invalid input. Please enter a valid number: ";
    }
    return choice;
}

void scheduleActivities() {
    cout << "Enter the total number of activities: ";
    int n = getValidChoice();
    
    if (n <= 0) {
        cout << "Number of activities must be greater than 0.\n";
        return;
    }

    vector<Activity> activities(n);
    
    for (int i = 0; i < n; i++) {
        activities[i].id = i + 1;
        cout << "Activity " << i + 1 << " start time: ";
        activities[i].start = getValidChoice();
        cout << "Activity " << i + 1 << " end time: ";
        activities[i].end = getValidChoice();
        
        // Захист від дурня: закінчення не може бути раніше початку
        if (activities[i].end <= activities[i].start) {
            cout << "End time must be after start time. Try again.\n";
            i--; 
        }
    }

    // Крок 1: Сортуємо заняття за часом закінчення
    sort(activities.begin(), activities.end(), compareActivities);

    vector<Activity> selectedActivities;
    
    // Крок 2: Завжди беремо перше заняття (воно закінчується найраніше)
    selectedActivities.push_back(activities[0]);
    int lastEndTime = activities[0].end;

    // Крок 3: Жадібно вибираємо наступні заняття
    for (int i = 1; i < n; i++) {
        if (activities[i].start >= lastEndTime) {
            selectedActivities.push_back(activities[i]);
            lastEndTime = activities[i].end;
        }
    }

    // Виведення результату
    cout << "\n=== Optimal Schedule ===\n";
    cout << "Maximum non-overlapping activities: " << selectedActivities.size() << "\n";
    cout << "Selected activities:\n";
    for (size_t i = 0; i < selectedActivities.size(); i++) {
        cout << "-> Activity " << selectedActivities[i].id 
             << " [Start: " << selectedActivities[i].start 
             << " | End: " << selectedActivities[i].end << "]\n";
    }
}

int main() {
    bool isRunning = true;
    
    while (isRunning) {
        cout << "\n=== Menu ===\n";
        cout << "1. Enter activities and calculate schedule\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        
        int choice = getValidChoice();
        cin.ignore();

        switch (choice) {
            case 1:
                scheduleActivities();
                break;
            case 0:
                cout << "Exiting program...\n";
                isRunning = false;
                break;
            default:
                cout << "Incorrect choice.\n";
                break;
        }
    }
    return 0;
}