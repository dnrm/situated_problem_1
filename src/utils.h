#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <ctime>

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

#endif // UTILS_H