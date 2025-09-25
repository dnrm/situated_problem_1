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

    // Setup the chronometer to time the algorithm

    // We've chosen MergeSort since when testing out the six different
    // algorithms, it was the fastest of them all, closely followed by
    // QuickSort :D

    cout << "===== \x1b[1;34mMerge Sort:\033[0m\n" << endl;

    auto start = chrono::high_resolution_clock::now();
    vector<Order> merge_sorted = merge_sort(orders);  // * Sort call
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> duration = end - start;

    print_orders(merge_sorted);

    cout << "Merge Sort took \x1b[1;32m" << duration.count() << "\033[0m ms\n";
    cout << "\n";

    cout << "===== \x1b[1;34mSaving first 10 lines to file:\033[0m output.txt\n"
         << endl;

    // Save first 10 lines to output.txt
    vector<Order> first_10(merge_sorted.begin(),
                           merge_sorted.begin() + 10);  // First 10 elements

    save_to_file("output.txt", first_10);

    cout << "\x1b[1;32mDone!\033[0m\n";

    return 0;
}