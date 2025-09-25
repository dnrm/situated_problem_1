// * Daniel Medina | A01286980
// * Monday September 22nd, 2025

// This file contains the declarations for the utility functions used in the
// project, including time conversion and order parsing.

#ifndef UTILS_H
#define UTILS_H

#include <ctime>
#include <string>
#include <vector>

struct Order {
    time_t timestamp;
    std::string restaurant;
    std::string item;
    int price;
};

// Function declarations
int month_to_number(const std::string& month);
time_t convert_time_to_unix(const std::string& date_str);
void parse_details(const std::string& details_str, Order& order);
Order parse_order_line(std::string line);
void print_orders(const std::vector<Order>& orders);
void save_to_file(const std::string& filename,
                  const std::vector<Order>& orders);

#endif  // UTILS_H