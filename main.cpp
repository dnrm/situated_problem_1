#include <stdio.h>
#include <time.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "src/utils.cpp"

using namespace std;

// struct Order {
//     time_t timestamp;
//     string restaurant;
//     string item;
//     int price;
// };

// Main function

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

    print_orders(orders);
    OrdersFile.close();
    return 0;
}