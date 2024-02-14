#include <iostream>
#include <vector>

#define sout(n) cout << (n) << endl;
using namespace std;

void removeDuplicates(vector<int>& nums) {
    int n = nums.size();
    if (n <= 1) return;

    int j = 0; 
    for (int i = 0; i < n - 1; i++) {
        if (nums[i] != nums[i + 1]) {
            nums[j++] = nums[i];
        }
    }
    nums[j++] = nums[n - 1]; 

    nums.resize(j);
}

int main() {
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;

    vector<int> array(size);
    cout << "Enter the sorted array elements: ";
    for (int i = 0; i < size; i++) {
        cin >> array[i];
    }

    removeDuplicates(array);

    sout("Output after removing duplicates:");
    for (int num : array) {
        cout << (num) << " ";
    }
    cout << endl;

    return 0;
}


// This code is written on C++11 Extension please use following command to run it 
// g++ -std=c++11 problem1.cpp -o problem1

// INPUT
// Enter the size of the array: 9
// Enter the sorted array elements: 1 2 2 3 4 4 4 5 5

// OUTPUT
// Output after removing duplicates:
// 1 2 3 4 5 
