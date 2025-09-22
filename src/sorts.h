// * Daniel Medina | A01286980
// * Monday September 22nd, 2025

// This file contains the declarations for all of the different sorts in the
// homework assignment. Each sort function takes a vector of `Order` objects
// by value (to create a copy) and returns a sorted vector of `Order` objects

#ifndef SORTS_H
#define SORTS_H


#include <time.h>

#include <ctime>
#include <string>
#include <vector>

#include "utils.h"

using namespace std;

// 1. Insertion Sort

vector<Order> insertion_sort(
    vector<Order> orders_copy);  // Pass by value = automatic copy

// 2. Selection Sort

vector<Order> selection_sort(
    vector<Order> orders_copy);  // Pass by value = automatic copy

// 3. Swap Sort

vector<Order> swap_sort(
    vector<Order> orders_copy);  // Pass by value = automatic copy

// 4. Bubble Sort

vector<Order> bubble_sort(
    vector<Order> orders_copy);  // Pass by value = automatic copy

// 5. Merge Sort

vector<Order> merge_sort(
    vector<Order> orders_copy);  // Pass by value = automatic copy

// 6. Quick Sort

vector<Order> quick_sort(
    vector<Order> orders_copy);  // Pass by value = automatic copy

#endif  // SORTS_H