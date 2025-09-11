#include "Order.h"

#include <stdio.h>

#include <iostream>

int Order::get_month() { return this->month; }

int Order::get_day() { return this->day; }

string Order::get_dish() { return this->dish; }

string Order::get_restaurant_name() { return this->restaurant_name; }

int Order::get_price() { return this->price; }

Order::Order(int month, int day, string restaurant_name, string dish, int price) {
    this->month = month;
    this->day = day;
    this->restaurant_name = restaurant_name;
    this->dish = dish;
    this->price = price;
}