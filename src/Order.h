#include <stdio.h>

#include <iostream>

using namespace std;

class Order {
   public:
    int get_month();
    int get_day();
    string get_restaurant_name();
    string get_dish();
    int get_price();

    Order(int month, int day, string restaurant_name, string dish, int price);

   private:
    int month;
    int day;
    string restaurant_name;
    string dish;
    int price;
};