# Sorting Algorithm Analysis for Delivery Orders

For delivery companies, it’s essential to analyze the orders placed through the delivery app. This helps them understand more about the clients, such as which days have the most orders or which hours have the fewest orders.

For this, we got a list of a thousand orders made in a delivery app. The mission is to **sort all the orders by date with an efficient sorting algorithm**. To solve this problem, six different sorting algorithms were tested:

- Insertion Sort
- Selection Sort
- Swap Sort
- Bubble Sort
- Merge Sort
- Quick Sort

---

## Insertion Sort

- **Runtime:** 531.086 ms
- **Time Complexity:** O(n²)

Insertion sort compares each number for sorting. If a number must be changed in position, it is stored in an extra variable, all bigger numbers are shifted, and the number is inserted in the correct position.  
This requires going through the array twice: once to check positions, and once to actually move elements.

---

## Selection Sort

- **Time Complexity:** O(n²)

Selection sort finds the smallest element in the array, then swaps it into its correct position. This is repeated for all elements, requiring two passes through the array each time.

---

## Swap Sort

- **Time Complexity:** O(n²)

Swap sort is similar to selection sort, since it also searches for the smallest number and sorts from smallest to largest. The difference is that it uses a **do-while loop** to swap elements whenever needed.

---

## Bubble Sort

- **Runtime:** 175.104 ms
- **Time Complexity:** O(n²)

Bubble sort compares adjacent elements and swaps them if they are out of order.  
Each iteration “bubbles” the largest element to the end of the array. Because it requires nested loops, its complexity is quadratic.

---

## Merge Sort

- **Runtime:** 8.88508 ms
- **Time Complexity:** O(n log n)

Merge sort divides the array into halves recursively until each element is alone, then merges them back in sorted order.

- The **divide step** takes `log(n)` times (solved from the equation `n / 2^k = 1`).
- The **merge step** takes O(n), since all elements must be combined.

Thus, the overall complexity is O(n log n).

---

## Quick Sort

- **Runtime:** 7.90296 ms
- **Time Complexity:** O(n log n)

Quick sort selects a **pivot** (in this case, the middle element) and partitions elements into those greater or smaller than the pivot. This process repeats recursively until all elements are sorted.

- The **divide step** takes O(log n).
- The **sort/merge step** takes O(n).

This makes it one of the most efficient sorting algorithms.

---

## Conclusion

**Merge sort** was chosen as the final algorithm because it consistently showed fast runtimes across multiple tests.

Although **Quick sort** (7.90296 ms) and **Merge sort** (8.88508 ms) performed similarly, Merge sort proved to be slightly more reliable. This is expected, since both have **O(n log n)** complexity, unlike the quadratic algorithms (Insertion, Selection, Swap, Bubble).

👉 **Final Choice: Merge Sort** for its balance of efficiency and consistency.
