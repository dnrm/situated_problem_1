// * Daniel Medina | A01286980
// * Monday September 22nd, 2025

// This file contains the definitions for the utility functions used in the
// project. These include functions for converting time strings to Unix
// timestamps, parsing order details from strings, and printing orders.

#include "utils.h"

#include <stdio.h>
#include <time.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// Function to map month abbreviation to number (1-12)
int month_to_number(const std::string& month) {
    const std::string months[] = {"ene", "Feb", "Mar", "Abr", "May", "Jun",
                                  "Jul", "Ago", "Sep", "Oct", "Nov", "Dic"};

    // Tiny linear search 👀
    for (int i = 0; i < 12; i++) {
        if (month == months[i]) {
            return i;
        }
    }
    return 0;  // invalid month
}

time_t convert_time_to_unix(const std::string& date_str) {
    // Example date "Feb 13 12:24:25"

    time_t now = time(nullptr);
    struct tm* local_tm_now = localtime(&now);
    int current_year = 1900 + local_tm_now->tm_year;

    char month_buffer[4];
    int day, hour, min, sec;

    if (sscanf(date_str.c_str(), "%3s %d %d:%d:%d", month_buffer, &day, &hour,
               &min, &sec) != 5) {
        return -1;
    }

    struct tm time_info = {};

    time_info.tm_year = current_year - 1900;
    time_info.tm_mon = month_to_number(month_buffer);
    time_info.tm_mday = day;
    time_info.tm_hour = hour;
    time_info.tm_min = min;
    time_info.tm_sec = sec;

    time_info.tm_isdst = -1;

    time_t timestamp = mktime(&time_info);

    return timestamp;
}

void parse_details(const string& details_str, Order& order) {
    size_t restaurant_start = details_str.find("R:") + 2;
    size_t item_start = details_str.find(" O:") + 3;
    size_t price_start = details_str.find("(") + 1;

    // Verify that the markers are there
    if (restaurant_start == string::npos || item_start == string::npos) {
        order.restaurant = "ERROR";
        order.item = "ERROR";
        order.price = -1;
        return;
    }

    order.restaurant =
        details_str.substr(restaurant_start, item_start - restaurant_start - 3);
    order.item = details_str.substr(item_start, price_start - item_start - 1);
    order.price = stoi(details_str.substr(price_start, details_str.rfind(")")));
}

Order parse_order_line(string line) {
    Order result;
    istringstream iss(line);

    std::string date_section, details_section;

    iss >> std::ws;  // This is to trim whitespace apparently lol

    getline(iss, date_section, ' ');  // Gets the month
    date_section += " ";

    string temp;
    iss >> temp;  // Day
    date_section += temp + " ";
    iss >> temp;  // Time
    date_section += temp;

    getline(iss, details_section);

    getline(iss, details_section);
    // Trim the leading space from the details
    if (!details_section.empty() && details_section[0] == ' ') {
        details_section = details_section.substr(1);
    }

    result.timestamp = convert_time_to_unix(date_section);
    parse_details(details_section, result);

    return result;
}

void print_orders(const vector<Order>& orders) {
    if (orders.empty()) {
        cout << "No orders found." << endl;
        return;
    }

    // Convert timestamp to readable format
    char time_str[20];
    struct tm* timeinfo = localtime(&orders[0].timestamp);
    strftime(time_str, sizeof(time_str), "%b %d %H:%M:%S", timeinfo);

    cout << "First element: " << endl;
    cout << "Date: " << time_str << " | Restaurant: " << orders[0].restaurant
         << " | Item: " << orders[0].item << " | Price: $" << orders[0].price
         << endl;

    // Parse last element time
    timeinfo = localtime(&orders[orders.size() - 1].timestamp);
    strftime(time_str, sizeof(time_str), "%b %d %H:%M:%S", timeinfo);

    cout << "Last element: " << endl;
    cout << "Date: " << time_str
         << " | Restaurant: " << orders[orders.size() - 1].restaurant
         << " | Item: " << orders[orders.size() - 1].item << " | Price: $"
         << orders[orders.size() - 1].price << endl;
}

void save_to_file(const std::string& filename,
                  const std::vector<Order>& orders) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error opening file for writing: " << filename
                  << std::endl;
        return;
    }

    for (const auto& order : orders) {
        // Convert timestamp back to readable format
        char time_str[20];
        struct tm* timeinfo = localtime(&order.timestamp);
        strftime(time_str, sizeof(time_str), "%b %d %H:%M:%S", timeinfo);

        outfile << time_str << " R:" << order.restaurant << " O:" << order.item
                << " ($" << order.price << ")" << std::endl;
    }

    outfile.close();
}