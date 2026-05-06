#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

struct Product {
    string name;
    double price;
    double protein, fats, carbohydrates;

    double getCalories() const {
        return 4 * protein + 9 * fats + 4 * carbohydrates;
    }
};

void printProducts(const vector<Product>& products) {
    cout << left << setw(15) << "Name"
         << setw(10) << "Price"
         << setw(20) << "P/F/C"
         << "Calories\n";
    cout << string(53, '-') << "\n";

    for (const auto& p : products) {
        ostringstream pfc;
        pfc << p.protein << "/" << p.fats << "/" << p.carbohydrates;

        cout << left << setw(15) << p.name
             << setw(10) << p.price
             << setw(20) << pfc.str()
             << p.getCalories() << "\n";
    }
    cout << "\n";
}

vector<Product> selectionSortByCalories(vector<Product> arr) {
    size_t n = arr.size();
    for (size_t i = 0; i < n - 1; i++) {
        size_t max_idx = i;
        for (size_t j = i + 1; j < n; j++) {
            if (arr[j].getCalories() > arr[max_idx].getCalories()) {
                max_idx = j;
            }
        }
        swap(arr[max_idx], arr[i]);
    }
    return arr;
}

vector<Product> gnomeSortByPrice(vector<Product> arr) {
    size_t n = arr.size();
    size_t index = 0;
    while (index < n) {
        if (index == 0) {
            index++;
        }
        if (arr[index].price >= arr[index - 1].price) {
            index++;
        } else {
            swap(arr[index], arr[index - 1]);
            index--;
        }
    }
    return arr;
}

vector<Product> searchByPrice(const vector<Product>& arr, double targetPrice) {
    vector<Product> foundProducts;
    for (const auto& p : arr) {
        if (p.price == targetPrice) {
            foundProducts.push_back(p);
        }
    }
    return foundProducts;
}

int main() {

    vector<Product> products = {
        {"Apple", 25.50, 0.3, 0.4, 13.8},
        {"Chicken", 150.00, 23.2, 1.6, 0.0},
        {"Bread", 25.50, 8.5, 3.3, 49.3},
        {"Avocado", 60.00, 2.0, 14.7, 8.5},
        {"Cheese", 250.00, 25.0, 27.5, 2.0},
        {"Banana", 45.00, 1.1, 0.3, 22.8},
        {"Salmon", 400.00, 20.0, 13.0, 0.0}
    };

    cout << "Initial array of products:\n";
    printProducts(products);

    vector<Product> sortedByCalories = selectionSortByCalories(products);
    cout << "Sorted by selection (descending calories):\n";
    printProducts(sortedByCalories);

    vector<Product> sortedByPrice = gnomeSortByPrice(products);
    cout << "Sorted by gnome (ascending price):\n";
    printProducts(sortedByPrice);

    double targetPrice = 60;
    cout << "--- Search results for price: " << targetPrice << " ---\n";

    vector<Product> found = searchByPrice(products, targetPrice);

    if (found.empty()) {
        cout << "No products found with this price.\n";
    } else {
        for (const auto& p : found) {
            cout << "Found: " << p.name << " (Calories: " << p.getCalories() << ")\n";
        }
    }
    cout << "\n";

    return 0;
}