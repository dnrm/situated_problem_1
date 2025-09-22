// * Daniel Medina | A01286980
// * Monday September 22nd, 2025

#include <stdio.h>
#include <time.h>

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "src/sorts.h"
#include "src/utils.h"

using namespace std;

// * Main function

// * Functions from the "utils.cpp" file:
// * – parse_order_line
// * – print_orders

int main() {
    fstream OrdersFile("orders.txt");

    vector<Order> orders = {};

    string text;

    if (OrdersFile.is_open()) {
        while (getline(OrdersFile, text)) {
            Order order = parse_order_line(text);
            orders.push_back(order);
        }
    }

    OrdersFile.close();

    // We now have access to the `orders` vector to perform the different sorts.

    // 1. Insertion Sort

    auto start = chrono::high_resolution_clock::now();

    cout << "===== \x1b[1;34mInsertion Sort:\033[0m\n" << endl;
    vector<Order> insertion_sorted = insertion_sort(orders);
    print_orders(insertion_sorted);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> duration = end - start;
    cout << "Insertion Sort took \x1b[1;32m" << duration.count() << "\033[0m ms\n";
    cout << "\n";

    // 2. Selection Sort

    start = chrono::high_resolution_clock::now();

    cout << "===== \x1b[1;34mSelection Sort:\033[0m\n" << endl;
    vector<Order> selection_sorted = selection_sort(orders);
    print_orders(selection_sorted);

    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Selection Sort took \x1b[1;32m" << duration.count() << "\033[0m ms\n";
    cout << "\n";

    // 3. Swap Sort

    start = chrono::high_resolution_clock::now();

    cout << "===== \x1b[1;34mSwap Sort:\033[0m\n" << endl;
    vector<Order> swap_sorted = swap_sort(orders);
    print_orders(swap_sorted);

    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Swap Sort took \x1b[1;32m" << duration.count() << "\033[0m ms\n";
    cout << "\n";

    // 4. Bubble Sort

    start = chrono::high_resolution_clock::now();

    cout << "===== \x1b[1;34mBubble Sort:\033[0m\n" << endl;
    vector<Order> bubble_sorted = bubble_sort(orders);
    print_orders(bubble_sorted);

    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Bubble Sort took \x1b[1;32m" << duration.count() << "\033[0m ms\n";
    cout << "\n";

    // 5. Merge Sort

    start = chrono::high_resolution_clock::now();

    cout << "===== \x1b[1;34mMerge Sort:\033[0m\n" << endl;
    vector<Order> merge_sorted = merge_sort(orders);
    print_orders(merge_sorted);

    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Merge Sort took \x1b[1;32m" << duration.count() << "\033[0m ms\n";
    cout << "\n";

    // 6. QuickSort

    start = chrono::high_resolution_clock::now();

    cout << "===== \x1b[1;34mQuick Sort:\033[0m\n" << endl;
    vector<Order> quick_sorted = quick_sort(orders);
    print_orders(quick_sorted);

    end = chrono::high_resolution_clock::now();
    duration = end - start;
    cout << "Quick Sort took \x1b[1;32m" << duration.count() << "\033[0m ms\n";
    cout << "\n";

    cout << "=====\n" << endl;
    cout << "End program :)\n" << endl;

    return 0;
}