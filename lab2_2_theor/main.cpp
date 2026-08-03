#include <iostream>
#include "sort.h"

int RandomizedSelect(int arr[], int p, int r, int i) {
    if (p == r) {
        return arr[p];
    }

    int q = RandomizedPartition(arr, p, r);//рандомний півот стає на середину
    int k = q - p + 1;//рахуємо індекс півота

    if (i == k) {
        return arr[q];
    } else if (i < k) {
        return RandomizedSelect(arr, p, q - 1, i);
    } else {
        return RandomizedSelect(arr, q + 1, r, i - k);//права частина відкидається, (i-k) передаємо нові порядкові номера 
    }
}

int main() {
    int n;
    std::cout << "Введіть розмір масиву: ";
    std::cin >> n;

    int* arr = new int[n];
    std::cout << "Введіть елементи масиву: " << std::endl;
    for (int j = 0; j < n; j++) {
        std::cin >> arr[j];
    }

    std::cout << "\n--- Порядкові статистики масиву ---" << std::endl;

    // 1. Мінімум (1-ша статистика)
    int min = RandomizedSelect(arr, 0, n - 1, 1);
    std::cout << "Мінімум (1-ша статистика): " << min << std::endl;

    // 2. Медіана
    if (n % 2 != 0) {
        // Якщо n непарне (остача від ділення на 2 не дорівнює нулю)
        int medianIndex = (n + 1) / 2;
        int median = RandomizedSelect(arr, 0, n - 1, medianIndex);
        std::cout << "Медіана (" << medianIndex << "-та статистика): " << median << std::endl;
    } else {
        // Якщо n парне, шукаємо дві медіани
        int lowerIndex = n / 2;
        int upperIndex = n / 2 + 1;
        
        int lowerMedian = RandomizedSelect(arr, 0, n - 1, lowerIndex);
        int upperMedian = RandomizedSelect(arr, 0, n - 1, upperIndex);
        
        std::cout << "Нижня медіана (" << lowerIndex << "-та статистика): " << lowerMedian << std::endl;
        std::cout << "Верхня медіана (" << upperIndex << "-та статистика): " << upperMedian << std::endl;
    }

    // 3. Максимум (n-на статистика)
    int max = RandomizedSelect(arr, 0, n - 1, n);
    std::cout << "Максимум (" << n << "-та статистика): " << max << std::endl;

    delete[] arr; 
    return 0;
}