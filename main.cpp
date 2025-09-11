#include <stdio.h>

#include <fstream>
#include <iostream>
#include <vector>

#include "src/Order.h"

using namespace std;

// Function to map month abbreviation to number (1-12)
int month_to_number(const std::string& month) {
    const std::string months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    // Tiny linear search 👀
    for (int i = 0; i < 12; i++) {
        if (month == months[i]) {
            return i + 1;
        }
    }
    return 0;  // invalid month
}

void print_orders(vector<Order> orders) {
    cout << "========== ORDERS ==========" << endl;

    for (Order& i : orders) {
        cout << "Month: " << to_string(i.get_month()) << "	";
        cout << "Day: " << to_string(i.get_day()) << "	";
        cout << "Restaurant: " << i.get_restaurant_name() << "	";
        cout << "Order: " << i.get_dish() << "	";
        cout << "Price: " << i.get_price() << endl;
    }

    cout << "============================" << endl;
}

int main() {
    fstream OrdersFile("orders.txt");

    vector<Order> orders = {};

    string text;
    int index, rest_index, order_index, price_index, price_index_end;

    if (OrdersFile.is_open()) {
        while (getline(OrdersFile, text)) {
            string line = text;
            index = text.find(" ");

            string month = line.substr(0, index);

            line = text.substr(index + 1);
            index = line.find(" ");
            string day = line.substr(0, index);

            rest_index = line.find("R:");
            order_index = text.find("O:");
            price_index = line.find("(");
            price_index_end = line.find(")");

            string restaurant_name =
                line.substr(rest_index + 2, order_index - rest_index - 7);
            string dish =
                line.substr(order_index - 2, price_index - order_index + 2);

            string price =
                line.substr(price_index + 1, price_index_end - price_index - 1);

            Order element =
                Order(month_to_number(month), stoi(day), restaurant_name, dish, stoi(price));

            orders.push_back(element);
        }
    }

    print_orders(orders);
}