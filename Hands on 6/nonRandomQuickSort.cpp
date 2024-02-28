#include <iostream>
#include <vector>

using namespace std;
#define sout(n) cout << (n)<< " ";


int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than or equal to pivot
        if (arr[j] <= pivot) {
            i++; // increment index of smaller element
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        // pi is partitioning index, arr[pi] is now at right place
        int pi = partition(arr, low, high);

        // Separately sort elements before partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    vector<int> a = {18, 23, 2, 6, 12, 5};
    int n = a.size();
    quickSort(a, 0, n - 1);
    
    cout<<"Sorted Array\n";
    for(int i=0;i<n;i++)
    {
        sout(a[i]);
    }
    cout<<endl;
    return 0;
}



// This code is written by Aaryan Mori

// Reference : https://www.geeksforgeeks.org/quick-sort/
