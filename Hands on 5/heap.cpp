#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <limits>
#define sout(n) cout << (n) << endl;
using namespace std;


template <typename T>  // Used for creating generic code as we will be using int and float

void heapify(vector<T>& a, size_t i, size_t n) {
    int smallest = i;
    int l = (i << 1) + 1;
    int r = (i << 1) + 2;
 
    if (l < n && a[l] < a[smallest])
        smallest = l;
 
    if (r < n && a[r] < a[smallest])
        smallest = r;
 
    if (smallest != i) {
        swap(a[i], a[smallest]);
        heapify(a, smallest, n);
    }
}


// Function to build a min heap from an unsorted array
template <typename T>
void build_minHeap(vector<T>& heap) {
    // Start heapifying from the last non-leaf node up to the root
    for (int i = (heap.size() >>1) - 1; i >= 0; --i) {
        heapify(heap, i, heap.size());
    }
}

// Function to insert a new element into the heap

template <typename T>
void insert(vector<T>& heap, const T& value) 
{
    // Add the new element to the end of the heap
    heap.push_back(value);
    // Get the index of the last element
    int itr = heap.size() - 1;
    // Compare the new element with its parent and swap if
    // necessary
    while (itr > 0
           && heap[(itr - 1) >> 1] > heap[itr]) {
        swap(heap[itr], heap[(itr - 1) >> 1]);
        // Move up the tree to the parent of the current
        // element
        itr = (itr - 1) >> 1;
    }
}

// Function to remove and return the root node (minimum) element from the heap

template <typename T>
T pop(vector<T>& heap) {
    if (heap.empty()) {
        throw out_of_range("Cannot pop from an empty heap");
    }

    // Store the minimum element for return
    T minElement = heap.front(); 

    // Replace root with the last element
    swap(heap.front(), heap.back()); 
    heap.pop_back(); // Remove the former root

    // Restore heap property (start from the new root)
    heapify(heap, 0,heap.size());

    return minElement;
}

// Function to print the elements of the heap
template <typename T>
void printHeap(const vector<T>& heap) {
    
    for (int j = 0; j < heap.size(); j++) {
        cout << heap[j] << " ";
    }
    sout("")
}

int main() {


    // Building the heap with integers
    vector<int> a = {10, 5, 11, 18, 19, 7, 8};

  // Perform heapify operation on min-heap
    for (int i = a.size()/2 - 1; i >= 0; i--)
        heapify(a, i, a.size());

    // Build min_heap and heapify
    build_minHeap(a);
    sout("Initial array(vector) after heapify and min_heap build")
    printHeap(a); 


    // Insertion of a node element 
    insert(a, 4);
    sout("Heap after inserting 4 :")
    printHeap(a); 

    // Removing (pop) the root node from he heap and also (re-heapify)
    int root = pop(a);
    cout << "Popped root: " << root << endl; 
    printHeap(a); 

    // Implementation using floats
    vector<float> f = {2.5, 3.2, 0.8, 7.9, 4.3, 5.1, 8.9};
    
    //Build min_heap and heapify (using floats)
    build_minHeap(f);
    sout("Heap build with floats")
    printHeap(f); 

    return 0;
}


// This code is written on C++11 Extension please use following command to run it 
// g++ -o heap heap.cpp -std=c++17 && ./heap

// OUTPUT

// Initial array(vector) after heapify and min_heap build
// 5 10 7 18 19 11 8 

// Heap after inserting 4
// 4 5 7 10 19 11 8 18 

// Popped root: 4
// 5 10 7 18 19 11 8 

// Heap build with floats
// 0.8 3.2 2.5 7.9 4.3 5.1 8.9 


// References - https://www.geeksforgeeks.org/implement-min-heap-using-stl/