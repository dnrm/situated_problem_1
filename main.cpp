#include <stdio.h>
#include <time.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

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

    print_orders(orders);
    OrdersFile.close();

    // We now have access to the `orders` vector to perform the different sorts.


    
    return 0;
}