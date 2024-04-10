#include <iostream>
#include <algorithm> // For copy
#include <cassert>   // For assert

using namespace std;

class DynamicArray {
public:
    DynamicArray()
        : size_(0), capacity_(1), data_(new int[1]) {}

    ~DynamicArray() {
        delete[] data_;
    }

    void push_back(int value) {
        if (size_ == capacity_) {
            // Double the capacity
            int newCapacity = capacity_ * 2;
            int* newData = new int[newCapacity];

            // Copy old data to new data
            copy(data_, data_ + size_, newData);

            // Delete old data and use the new data
            delete[] data_;
            data_ = newData;
            capacity_ = newCapacity;
        }

        // Add the new element
        data_[size_] = value;
        ++size_;
        print_size(); // Print the current size after insertion
    }

    void pop_back() {
        if (size_ == 0) {
            cerr << "Array is empty. Cannot pop_back." << endl;
            return;
        }

        --size_;
        print_size(); // Print the current size after deletion
    }

    int& operator[](size_t index) {
        assert(index < size_ && "Index out of bounds");
        return data_[index];
    }

    size_t size() const {
        return size_;
    }

private:
    size_t size_;
    size_t capacity_;
    int* data_;

    // Prints the current size of the DynamicArray
    void print_size() const {
        cout << "Current size: " << size_ << endl;
    }
};

int main() {
    DynamicArray arr;

    cout << "Inserting elements:" << endl;
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);

    cout << "Array elements after insertions:" << endl;
    for (size_t i = 0; i < arr.size(); ++i) {
        cout << arr[i] << endl;
    }

    cout << "Removing last element:" << endl;
    arr.pop_back();

    cout << "Array elements after pop_back:" << endl;
    for (size_t i = 0; i < arr.size(); ++i) {
        cout << arr[i] << endl;
    }

    return 0;
}



// This code is written by Aaryan Mori
// References: https://www.geeksforgeeks.org/how-do-dynamic-arrays-work/