// * Daniel Medina | A01286980
// * Monday September 22nd, 2025

#include <stdio.h>
#include <time.h>

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "src/colors.h"
#include "src/sorts.h"
#include "src/utils.h"

// * Project Description

// This project reads a list of food orders from a text file, sorts them using
// various sorting algorithms, and allows the user to search for orders within
// a specific date range. The sorted orders can also be saved to an output file.
// The project is designed to demonstrate the implementation of sorting
// algorithms and file handling in C++.

// The user can input a start and end date, and the program will filter and
// display all orders that fall within that range. The user also has the option
// to save the filtered results to a separate file.

// Throughout the file there are constants in uppercase, which are color code
// constantes defined in the src/colors.h file. They are used to color the text
// in the terminal and give the project a better appearance.

using namespace std;

// * Main function

// * Functions from the "utils.cpp" file:
// * – parse_order_line
// * – save_to_file
// * – parse_user_date
// * – filter_orders_by_date_range
// * – get_string
// * – display_filtered_orders
// * – ask_user_to_save

// * Functions from the "sorts.cpp" file:
// * – merge_sort

int main() {
    fstream OrdersFile("orders.txt");

    vector<Order> orders = {};

    string text;

    // Loop over every line and create a vector of Orders.

    if (OrdersFile.is_open()) {
        while (getline(OrdersFile, text)) {
            Order order = parse_order_line(text);
            orders.push_back(order);
        }
    }

    OrdersFile.close();

    // We now have access to the `orders` vector to perform the different sorts.

    // We've chosen MergeSort since when testing out the six different
    // algorithms, it was the fastest of them all, closely followed by
    // QuickSort :D

    cout << SECTION_HEADER << "===== Merge Sort =====    " << RESET << "\n"
         << endl;

    // Setup the chronometer to time the algorithm
    auto start = chrono::high_resolution_clock::now();
    vector<Order> merge_sorted = merge_sort(orders);  // * Sort call

    // End the timer
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> duration = end - start;

    cout << INFO_STYLE << "Merge Sort took " << SUCCESS_STYLE
         << duration.count() << " ms" << RESET << "\n";
    cout << "\n";

    // Display first 10 sorted orders
    cout << SECTION_HEADER << "===== First 10 Sorted Orders =====    " << RESET
         << "\n"
         << endl;

    int display_count = min(10, (int)merge_sorted.size());
    for (int i = 0; i < display_count; i++) {
        char time_str[20];
        // Pass the timestamp to localtime to convert to struct tm
        struct tm* timeinfo = localtime(&merge_sorted[i].timestamp);
        strftime(time_str, sizeof(time_str), "%b %d %H:%M:%S", timeinfo);

        // Print with colors
        cout << BOLD << (i + 1) << ". " << RESET << TIMESTAMP_STYLE << time_str
             << RESET << " | " << RESTAURANT_STYLE
             << "Restaurant: " << merge_sorted[i].restaurant << RESET << " | "
             << ITEM_STYLE << "Item: " << merge_sorted[i].item << RESET << " | "
             << PRICE_STYLE << "Price: $" << merge_sorted[i].price << RESET
             << endl;
    }
    cout << "\n";

    // Save all sorted orders to output.txt
    cout << SECTION_HEADER << "===== Saving to File =====    " << RESET << "\n"
         << endl;
    cout << INFO_STYLE << "Saving all sorted orders to: " << RESET << BOLD
         << "output.txt" << RESET << "\n"
         << endl;

    // Call the save to file function to save sorted elements.
    save_to_file("output.txt", merge_sorted);
    cout << SUCCESS_HEADER << " SUCCESS " << RESET << " " << SUCCESS_STYLE
         << "All " << merge_sorted.size()
         << " sorted orders saved to output.txt!" << RESET << "\n";
    cout << "\n";

    cout << SECTION_HEADER << "===== Date Range Search =====    " << RESET
         << "\n"
         << endl;

    // Get date range from user
    cout << WARNING_STYLE
         << "Enter dates in format 'Mon DD' (e.g., 'Feb 13', 'Dec 24')" << RESET
         << endl;

     // Receive user input for both dates
    string start_date_str = get_string("Enter start date: ");
    string end_date_str = get_string("Enter end date: ");

    // Parse dates to time_t
    time_t start_date = parse_user_date(start_date_str);
    time_t end_date = parse_user_date(end_date_str);

    // Validation
    if (start_date == -1 || end_date == -1) {
        cout << ERROR_HEADER << " ERROR " << RESET << " " << ERROR_STYLE
             << "Invalid date format. Please use 'Mon DD' format." << RESET
             << endl;
        return 1;
    }

    // Prevent errors where start date is after end date
    if (start_date > end_date) {
        cout << ERROR_HEADER << " ERROR " << RESET << " " << ERROR_STYLE
             << "Start date cannot be after end date." << RESET << endl;
        return 1;
    }

    // Filter orders by date range
    vector<Order> filtered_orders =
        filter_orders_by_date_range(merge_sorted, start_date, end_date);

    // Display results
    display_filtered_orders(filtered_orders);

    // Ask user if they want to save results
    if (!filtered_orders.empty() && ask_user_to_save()) {
        string filename =
            get_string("Enter filename (default: search_results.txt): ");
        if (filename.empty()) {
            filename = "search_results.txt";
        }

        save_to_file(filename, filtered_orders);
        cout << SUCCESS_HEADER << " SAVED " << RESET << " " << SUCCESS_STYLE
             << "Results saved to " << filename << "!" << RESET << endl;
    }

    return 0;
}