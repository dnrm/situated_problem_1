# Function Documentation

This document provides detailed documentation for all functions in the situated_problem_1 project.

## Data Structures

### Order Struct
```cpp
struct Order {
    time_t timestamp;
    std::string restaurant;
    std::string item;
    int price;
};
```

## Sorting Functions (sorts.h/sorts.cpp)

### insertion_sort
```cpp
vector<Order> insertion_sort(vector<Order> orders_copy);
```
**Input:** `vector<Order>` - a vector of elements of type Order containing unsorted order data  
**Output:** `vector<Order>` - a vector of elements of type Order sorted by timestamp in ascending order using insertion sort algorithm

### selection_sort
```cpp
vector<Order> selection_sort(vector<Order> orders_copy);
```
**Input:** `vector<Order>` - a vector of elements of type Order containing unsorted order data  
**Output:** `vector<Order>` - a vector of elements of type Order sorted by timestamp in ascending order using selection sort algorithm

### swap_sort
```cpp
vector<Order> swap_sort(vector<Order> orders_copy);
```
**Input:** `vector<Order>` - a vector of elements of type Order containing unsorted order data  
**Output:** `vector<Order>` - a vector of elements of type Order sorted by timestamp in ascending order using swap sort algorithm (a variant of bubble sort)

### bubble_sort
```cpp
vector<Order> bubble_sort(vector<Order> orders_copy);
```
**Input:** `vector<Order>` - a vector of elements of type Order containing unsorted order data  
**Output:** `vector<Order>` - a vector of elements of type Order sorted by timestamp in ascending order using bubble sort algorithm

### merge_sort
```cpp
vector<Order> merge_sort(vector<Order> orders_copy);
```
**Input:** `vector<Order>` - a vector of elements of type Order containing unsorted order data  
**Output:** `vector<Order>` - a vector of elements of type Order sorted by timestamp in ascending order using merge sort algorithm (recursive implementation)

### quick_sort
```cpp
vector<Order> quick_sort(vector<Order> orders_copy);
```
**Input:** `vector<Order>` - a vector of elements of type Order containing unsorted order data  
**Output:** `vector<Order>` - a vector of elements of type Order sorted by timestamp in ascending order using quick sort algorithm (recursive implementation)

### merge (Helper Function)
```cpp
vector<Order> merge(const vector<Order>& left, const vector<Order>& right);
```
**Input:** 
- `const vector<Order>&` - a constant reference to a vector of elements of type Order representing the left sorted half
- `const vector<Order>&` - a constant reference to a vector of elements of type Order representing the right sorted half  

**Output:** `vector<Order>` - a vector of elements of type Order containing the merged and sorted elements from both input vectors

## Utility Functions (utils.h/utils.cpp)

### month_to_number
```cpp
int month_to_number(const std::string& month);
```
**Input:** `const std::string&` - a constant reference to a string containing a month abbreviation (e.g., "Feb", "Mar")  
**Output:** `int` - an integer representing the month number (0-11, where 0 is January)

### convert_time_to_unix
```cpp
time_t convert_time_to_unix(const std::string& date_str);
```
**Input:** `const std::string&` - a constant reference to a string containing a date in format "Feb 13 12:24:25"  
**Output:** `time_t` - a time_t value representing the Unix timestamp, or -1 if parsing fails

### parse_details
```cpp
void parse_details(const std::string& details_str, Order& order);
```
**Input:** 
- `const std::string&` - a constant reference to a string containing order details in format "R:restaurant O:item (price)"
- `Order&` - a reference to an Order object to be populated with parsed data  

**Output:** `void` - no return value (modifies the Order object passed by reference)

### parse_order_line
```cpp
Order parse_order_line(std::string line);
```
**Input:** `std::string` - a string containing a complete order line with date, restaurant, item, and price information  
**Output:** `Order` - an Order object containing the parsed timestamp, restaurant, item, and price data

### print_orders
```cpp
void print_orders(const std::vector<Order>& orders);
```
**Input:** `const std::vector<Order>&` - a constant reference to a vector of elements of type Order to be printed  
**Output:** `void` - no return value (prints the first and last orders in the vector to standard output)

## Notes

- All sorting functions receive their input by value (creating a copy) to avoid modifying the original data
- All sorting functions sort orders by their `timestamp` field in ascending order
- The `merge` function is a helper function used internally by `merge_sort`
- Error handling is implemented in parsing functions (returns -1 for invalid timestamps, "ERROR" for invalid parsing)
- The `print_orders` function only displays the first and last elements of the sorted vector for performance reasons