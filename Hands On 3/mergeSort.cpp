#include <iostream>

void merge(int arr[], int left, int mid, int right) {
    int sizeLeft = mid - left + 1;
    int sizeRight = right - mid;

    int* leftArr = new int[sizeLeft];
    int* rightArr = new int[sizeRight];

    for (int i = 0; i < sizeLeft; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < sizeRight; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int mergedIndex = left;

    while (i < sizeLeft && j < sizeRight) {
        if (leftArr[i] <= rightArr[j]) {
            arr[mergedIndex] = leftArr[i];
            i++;
        } else {
            arr[mergedIndex] = rightArr[j];
            j++;
        }
        mergedIndex++;
    }

    while (i < sizeLeft) {
        arr[mergedIndex] = leftArr[i];
        i++;
        mergedIndex++;
    }

    while (j < sizeRight) {
        arr[mergedIndex] = rightArr[j];
        j++;
        mergedIndex++;
    }

    delete[] leftArr;
    delete[] rightArr;
}

void mergeSort(int arr[], int begin, int end) {
    if (begin >= end)
        return;

    int mid = begin + (end - begin) / 2;
    mergeSort(arr, begin, mid);
    mergeSort(arr, mid + 1, end);
    merge(arr, begin, mid, end);
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}

int main() {
    int arr[] = {5, 2, 4, 7, 1, 3, 2, 6};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Original array:\n";
    printArray(arr, arrSize);

    mergeSort(arr, 0, arrSize - 1);

    std::cout << "\nSorted array:\n";
    printArray(arr, arrSize);

    return 0;
}
