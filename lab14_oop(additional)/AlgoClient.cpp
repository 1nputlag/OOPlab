#include <iostream>
#include "AlgoLib.h"

// Допоміжна функція для виводу масиву
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int data[] = {87, 34, 12, 59, 98, 3, 45, 22, 104, 1};
    int n = sizeof(data) / sizeof(data[0]);

    std::cout << "=== Test Custom Dynamic Library (QuickSort) ===" << std::endl;
    std::cout << "Unsorted array:" << std::endl;
    printArray(data, n);

    // Виклик функції з нашої dylib/DLL
    quickSort(data, 0, n - 1);

    std::cout << "\nSorted array:" << std::endl;
    printArray(data, n);
    std::cout << "===============================================" << std::endl;

    return 0;
}