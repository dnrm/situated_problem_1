// * Daniel Medina | A01286980
// * Monday September 22nd, 2025

// ❗️ All of the sorts sort the data based on the `timestamp` field.

// Why size_t is used:
// https://www.geeksforgeeks.org/cpp/difference-between-int-and-size_t-in-cpp/

#include "sorts.h"

// * ========= BEGIN SORT IMPLEMENTATIONS =========

// 1. Insertion Sort

vector<Order> insertion_sort(vector<Order> orders_copy) {
    size_t n = orders_copy.size();
    for (size_t i = 1; i < n; i++) {
        Order key = orders_copy[i];
        int j = i - 1;  // Keep as int since we need to check j >= 0
        while (j >= 0 && orders_copy[j].timestamp > key.timestamp) {
            orders_copy[j + 1] = orders_copy[j];
            j = j - 1;
        }
        orders_copy[j + 1] = key;
    }
    return orders_copy;
}

// 2. Selection Sort

vector<Order> selection_sort(vector<Order> orders_copy) {
    size_t n = orders_copy.size();
    for (size_t i = 0; i < n - 1; i++) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < n; j++) {
            if (orders_copy[j].timestamp < orders_copy[min_idx].timestamp) {
                min_idx = j;
            }
        }
        swap(orders_copy[i], orders_copy[min_idx]);
    }
    return orders_copy;
}

// 3. Swap Sort

vector<Order> swap_sort(vector<Order> orders_copy) {
    size_t n = orders_copy.size();
    bool swapped;
    do {
        swapped = false;
        for (size_t i = 0; i < n - 1; i++) {
            if (orders_copy[i].timestamp > orders_copy[i + 1].timestamp) {
                swap(orders_copy[i], orders_copy[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
    return orders_copy;
}

// 4. Bubble Sort

vector<Order> bubble_sort(vector<Order> orders_copy) {
    size_t n = orders_copy.size();
    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < n - i - 1; j++) {
            if (orders_copy[j].timestamp > orders_copy[j + 1].timestamp) {
                swap(orders_copy[j], orders_copy[j + 1]);
            }
        }
    }
    return orders_copy;
}

// 5. Merge Sort (Recursive)

// This is the helper function to make it recursive
vector<Order> merge(const vector<Order>& left, const vector<Order>& right) {
    vector<Order> result;
    size_t i = 0, j = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i].timestamp <= right[j].timestamp) {
            result.push_back(left[i]);
            i++;
        } else {
            result.push_back(right[j]);
            j++;
        }
    }
    while (i < left.size()) {
        result.push_back(left[i]);
        i++;
    }
    while (j < right.size()) {
        result.push_back(right[j]);
        j++;
    }
    return result;
}

vector<Order> merge_sort(vector<Order> orders_copy) {
    if (orders_copy.size() <= 1) {
        return orders_copy;
    }
    size_t mid = orders_copy.size() / 2;
    vector<Order> left(orders_copy.begin(), orders_copy.begin() + mid);
    vector<Order> right(orders_copy.begin() + mid, orders_copy.end());
    return merge(merge_sort(left), merge_sort(right));
}

// 6. Quick Sort

vector<Order> quick_sort(vector<Order> orders_copy) {
    if (orders_copy.size() <= 1) {
        return orders_copy;
    }

    // Choosing the middle value as the first pivot :)
    Order pivot = orders_copy[orders_copy.size() / 2];
    vector<Order> less;
    vector<Order> equal;
    vector<Order> greater;
    for (const auto& order : orders_copy) {
        if (order.timestamp < pivot.timestamp) {
            less.push_back(order);
        } else if (order.timestamp == pivot.timestamp) {
            equal.push_back(order);
        } else {
            greater.push_back(order);
        }
    }
    vector<Order> sorted_less = quick_sort(less);
    vector<Order> sorted_greater = quick_sort(greater);
    sorted_less.insert(sorted_less.end(), equal.begin(), equal.end());
    sorted_less.insert(sorted_less.end(), sorted_greater.begin(),
                       sorted_greater.end());
    return sorted_less;
}