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
        cout << ERROR_STYLE << "No orders found." << RESET << endl;
        return;
    }

    // Convert timestamp to readable format
    char time_str[20];
    struct tm* timeinfo = localtime(&orders[0].timestamp);
    strftime(time_str, sizeof(time_str), "%b %d %H:%M:%S", timeinfo);

    cout << HEADER_STYLE << "First element: " << RESET << endl;
    cout << TIMESTAMP_STYLE << "Date: " << time_str << RESET << " | "
         << RESTAURANT_STYLE << "Restaurant: " << orders[0].restaurant << RESET
         << " | " << ITEM_STYLE << "Item: " << orders[0].item << RESET << " | "
         << PRICE_STYLE << "Price: $" << orders[0].price << RESET << endl;

    // Parse last element time
    timeinfo = localtime(&orders[orders.size() - 1].timestamp);
    strftime(time_str, sizeof(time_str), "%b %d %H:%M:%S", timeinfo);

    cout << HEADER_STYLE << "Last element: " << RESET << endl;
    cout << TIMESTAMP_STYLE << "Date: " << time_str << RESET << " | "
         << RESTAURANT_STYLE
         << "Restaurant: " << orders[orders.size() - 1].restaurant << RESET
         << " | " << ITEM_STYLE << "Item: " << orders[orders.size() - 1].item
         << RESET << " | " << PRICE_STYLE << "Price: $"
         << orders[orders.size() - 1].price << RESET << endl;
}

void save_to_file(const std::string& filename,
                  const std::vector<Order>& orders) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << ERROR_STYLE
                  << "Error opening file for writing: " << filename << RESET
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

// New functions for date range search
time_t parse_user_date(const std::string& date_str) {
    // Parse user input in format "Mon DD" (e.g., "Feb 13", "Dec 24")
    char month_buffer[4];
    int day;

    if (sscanf(date_str.c_str(), "%3s %d", month_buffer, &day) != 2) {
        return -1;  // Invalid format
    }

    // Get current year
    time_t now = time(nullptr);
    struct tm* local_tm_now = localtime(&now);
    int current_year = 1900 + local_tm_now->tm_year;

    struct tm time_info = {};
    time_info.tm_year = current_year - 1900;
    time_info.tm_mon = month_to_number(month_buffer);
    time_info.tm_mday = day;
    time_info.tm_hour = 0;  // Start of day
    time_info.tm_min = 0;
    time_info.tm_sec = 0;
    time_info.tm_isdst = -1;

    return mktime(&time_info);
}

std::vector<Order> filter_orders_by_date_range(const std::vector<Order>& orders,
                                               time_t start_date,
                                               time_t end_date) {
    std::vector<Order> filtered_orders;

    // Adjust end_date to end of day (23:59:59)
    struct tm* end_tm = localtime(&end_date);
    end_tm->tm_hour = 23;
    end_tm->tm_min = 59;
    end_tm->tm_sec = 59;
    time_t adjusted_end_date = mktime(end_tm);

    for (const auto& order : orders) {
        if (order.timestamp >= start_date &&
            order.timestamp <= adjusted_end_date) {
            filtered_orders.push_back(order);
        }
    }

    return filtered_orders;
}

std::string get_string(const std::string& prompt) {
    std::string input;
    std::cout << INFO_STYLE << prompt << RESET;
    std::getline(std::cin, input);
    return input;
}

void display_filtered_orders(const std::vector<Order>& orders) {
    if (orders.empty()) {
        std::cout << WARNING_STYLE
                  << "No orders found in the specified date range." << RESET
                  << std::endl;
        return;
    }

    std::cout << "\n"
              << SECTION_HEADER << "===== Search Results =====" << RESET
              << std::endl;
    std::cout << INFO_STYLE << "Found " << orders.size()
              << " order(s):" << RESET << std::endl;
    std::cout << DIM << "-------------------------" << RESET << std::endl;

    for (size_t i = 0; i < orders.size(); i++) {
        char time_str[20];
        struct tm* timeinfo = localtime(&orders[i].timestamp);
        strftime(time_str, sizeof(time_str), "%b %d %H:%M:%S", timeinfo);

        std::cout << BOLD << (i + 1) << ". " << RESET << TIMESTAMP_STYLE
                  << time_str << RESET << " | " << RESTAURANT_STYLE
                  << "Restaurant: " << orders[i].restaurant << RESET << " | "
                  << ITEM_STYLE << "Item: " << orders[i].item << RESET << " | "
                  << PRICE_STYLE << "Price: $" << orders[i].price << RESET
                  << std::endl;
    }
    std::cout << DIM << "-------------------------" << RESET << std::endl;
}

bool ask_user_to_save() {
    std::string response;
    std::cout << "\n"
              << INFO_STYLE
              << "Would you like to save these results to a file? (y/n): "
              << RESET;
    std::getline(std::cin, response);

    return (response == "y" || response == "Y" || response == "yes" ||
            response == "Yes");
}