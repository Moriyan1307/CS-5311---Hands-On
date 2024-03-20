#include <iostream>
using namespace std;
#define sout(n) cout << (n)<< " ";

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++; // increment index of smaller element
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

int quickSelect(int arr[], int low, int high, int i) {
    if (low == high)
        return arr[low];

    int pivotIndex = partition(arr, low, high);

    // Number of elements in low..pivotIndex
    int k = pivotIndex - low + 1;

    if (i == k) // Pivot value is the answer
        return arr[pivotIndex];
    else if (i < k)
        return quickSelect(arr, low, pivotIndex - 1, i);
    else
        return quickSelect(arr, pivotIndex + 1, high, i - k);
}

int main() {
    int arr[] = {12, 3, 5, 7, 4, 19, 26};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i = 3; // Find the 3rd smallest element
    cout << "The " << i << "rd smallest element is " << quickSelect(arr, 0, n-1, i) << endl;
    return 0;
}


// OUTPUT 
// The 3rd smallest element is 5

// This code is written by Aaryan Mori
// Reference : https://www.geeksforgeeks.org/quick-sort/