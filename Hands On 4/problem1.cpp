#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <limits>

#define sout(n) cout << (n) << endl;
using namespace std;

vector<int> mergeSortedArrays(vector<vector<int> >& arrays) {
    vector<int> result;
    
    while (!arrays.empty()) {
        int min_val = numeric_limits<int>::max();
        int min_index = -1;

        for (int i = 0; i < arrays.size(); ++i) {
            if (!arrays[i].empty() && arrays[i][0] < min_val) {
                min_val = arrays[i][0];
                min_index = i;
            }
        }

        if (min_index != -1) {
            result.push_back(min_val);
            arrays[min_index].erase(arrays[min_index].begin());
            if (arrays[min_index].empty()) {
                arrays.erase(arrays.begin() + min_index);
            }
        }
    }

    return result;
}



int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int k, n;
    sout("Enter K : ");
    cin >> k;
    sout("Enter N : ");
    cin >> n;

    vector<vector<int> > arrays;
    for (int i = 0; i < k; ++i) {
        cout << "Enter sorted array " << i + 1 << " (space separated): ";
        vector<int> array_input(n);
        for (int j = 0; j < n; ++j) {
            cin >> array_input[j];
        }
        arrays.push_back(array_input);
    }

    vector<int> merged_result = mergeSortedArrays(arrays);
    sout("Merged Result: ")
    for (int num : merged_result) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}


// This code is written on C++11 Extension please use following command to run it 
// g++ -std=c++11 problem1.cpp -o problem1

// INPUT
// Enter K : 
// 3
// Enter N : 
// 4
// Enter sorted array 1 (space separated): 1 3 5 7
// Enter sorted array 2 (space separated): 2 4 6 8
// Enter sorted array 3 (space separated): 0 9 10 11

// OUTPUT
// Merged Result: 
// 0 1 2 3 4 5 6 7 8 9 10 11

