#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>

using namespace std;

int getValidChoice() {
    int choice;
    while (!(cin >> choice)) {
        cin.clear();
        while (cin.get() != '\n') continue;
        cout << "Invalid input. Please enter a valid number: ";
    }
    return choice;
}

void printResult(const vector<vector<int>>& allocation, int totalCost, string methodName,
                 int numWarehouses, int numStores, bool addedDummyWarehouse, bool addedDummyStore) {

    cout << "\n" << string(3, '=') << " " << methodName << " " << string(3, '=') << "\n";
    cout << "Optimal delivery plan:\n";

    cout << "|    |";
    for (int j = 0; j < numStores; j++) {
        if (addedDummyStore && j == numStores - 1) {
            cout << " Dummy|";
        } else {
            cout << "  M" << j + 1 << "  |";
        }
    }

    cout << "\n|" << string(4, '-') << "|";
    for (int j = 0; j < numStores; j++) {
        cout << string(6, '-') << "|";
    }
    cout << "\n";

    for (int i = 0; i < numWarehouses; i++) {
        if (addedDummyWarehouse && i == numWarehouses - 1) {
            cout << "|Dum |";
        } else {
            cout << "| S" << i + 1 << " |";
        }
        for (int j = 0; j < numStores; j++) {
            cout << setw(5) << allocation[i][j] << " |";
        }
        cout << "\n";
    }
    cout << "\nMinimum total delivery cost: " << totalCost << " currency units.\n";
}

void solveDynamicTransportProblem(bool useHardcoded) {
    int numWarehouses, numStores;
    vector<int> supply;
    vector<int> demand;
    vector<vector<int>> costs;

    if (useHardcoded) {
        numWarehouses = 3;
        numStores = 3;

        supply = {1500, 1900, 1600};
        demand = {1800, 1200, 2000};

        costs = {
            {7, 8, 2},
            {1, 4, 3},
            {1, 5, 6}
        };
        cout << "\n[INFO] Loaded hardcoded data from Lab 21 assignment.\n";
    }
    else {
        cout << "Enter the number of real warehouses (S): ";
        numWarehouses = getValidChoice();
        cout << "Enter the number of real stores (M): ";
        numStores = getValidChoice();

        if (numWarehouses <= 0 || numStores <= 0) {
            cout << "Dimensions must be greater than 0.\n";
            return;
        }

        supply.resize(numWarehouses);
        for (int i = 0; i < numWarehouses; i++) {
            cout << "Enter supply for Warehouse S" << i + 1 << ": ";
            supply[i] = getValidChoice();
        }

        demand.resize(numStores);
        for (int j = 0; j < numStores; j++) {
            cout << "Enter demand for Store M" << j + 1 << ": ";
            demand[j] = getValidChoice();
        }

        costs.resize(numWarehouses, vector<int>(numStores));
        cout << "\nEnter the cost matrix (transportation tariffs):\n";
        for (int i = 0; i < numWarehouses; i++) {
            for (int j = 0; j < numStores; j++) {
                cout << "Cost from S" << i + 1 << " to M" << j + 1 << ": ";
                costs[i][j] = getValidChoice();
            }
        }
    }

    // Підрахунок сум для балансування
    int totalSupply = 0;
    for (int i = 0; i < numWarehouses; i++) totalSupply += supply[i];

    int totalDemand = 0;
    for (int j = 0; j < numStores; j++) totalDemand += demand[j];

    bool addedDummyWarehouse = false;
    bool addedDummyStore = false;

    vector<int> balancedSupply = supply;
    vector<int> balancedDemand = demand;
    vector<vector<int>> balancedCosts = costs;

    // перевірка на баланс і додавання фіктивних точок
    if (totalSupply > totalDemand) {
        int difference = totalSupply - totalDemand;
        cout << "\n[INFO] Supply > Demand. Creating Dummy Store (cost = 0).\n";

        addedDummyStore = true;
        balancedDemand.push_back(difference);
        numStores++;

        for (int i = 0; i < numWarehouses; i++) {
            balancedCosts[i].push_back(0);
        }
    } else if (totalDemand > totalSupply) {
        int difference = totalDemand - totalSupply;
        cout << "\n[INFO] Demand > Supply. Creating Dummy Warehouse (cost = 0).\n";

        addedDummyWarehouse = true;
        balancedSupply.push_back(difference);
        numWarehouses++;

        balancedCosts.push_back(vector<int>(numStores, 0));
    }

    // північно-західний кут
    vector<int> nwSupply = balancedSupply;
    vector<int> nwDemand = balancedDemand;
    vector<vector<int>> nwAllocation(numWarehouses, vector<int>(numStores, 0));
    int nwTotalCost = 0;

    int r = 0, c = 0;
    while (r < numWarehouses && c < numStores) {
        int amount = min(nwSupply[r], nwDemand[c]);
        nwAllocation[r][c] = amount;
        nwTotalCost += amount * balancedCosts[r][c];

        nwSupply[r] -= amount;
        nwDemand[c] -= amount;

        if (nwSupply[r] == 0) r++;
        else if (nwDemand[c] == 0) c++;
    }
    printResult(nwAllocation, nwTotalCost, "North-West Corner Method",
                numWarehouses, numStores, addedDummyWarehouse, addedDummyStore);

    // алгоритм мінімальної вартості
    vector<int> mcSupply = balancedSupply;
    vector<int> mcDemand = balancedDemand;
    vector<vector<int>> mcAllocation(numWarehouses, vector<int>(numStores, 0));
    int mcTotalCost = 0;

    while (true) {
        int minCost = 999999;
        int min_r = -1, min_c = -1;

        // шукаємо найдешевшу клітинку
        for (int i = 0; i < numWarehouses; i++) {
            for (int j = 0; j < numStores; j++) {
                if (mcSupply[i] > 0 && mcDemand[j] > 0 && balancedCosts[i][j] < minCost) {
                    minCost = balancedCosts[i][j];
                    min_r = i;
                    min_c = j;
                }
            }
        }

        if (min_r == -1) break;

        int amount = min(mcSupply[min_r], mcDemand[min_c]);
        mcAllocation[min_r][min_c] = amount;
        mcTotalCost += amount * balancedCosts[min_r][min_c];

        mcSupply[min_r] -= amount;
        mcDemand[min_c] -= amount;
    }
    printResult(mcAllocation, mcTotalCost, "Minimum Cost Method",
                numWarehouses, numStores, addedDummyWarehouse, addedDummyStore);
}

int main() {
    bool isRunning = true;

    while (isRunning) {
        cout << "\n" << string(3, '=') << " Advanced Logistics Optimization Menu " << string(3, '=') << "\n";
        cout << "1. Enter Data Manually & Solve\n";
        cout << "2. Use Hardcoded Lab Data & Solve\n";
        cout << "0. Exit\n";
        cout << "Choice: ";

        int choice = getValidChoice();
        cin.ignore();

        switch (choice) {
            case 1:
                solveDynamicTransportProblem(false); 
                break;
            case 2:
                solveDynamicTransportProblem(true);  
                break;
            case 0:
                cout << "Exiting program. Good luck!\n";
                isRunning = false;
                break;
            default:
                cout << "Incorrect choice.\n";
                break;
        }
    }
    return 0;
}
