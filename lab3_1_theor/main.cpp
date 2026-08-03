#include <iostream>
#include "sort.h"

int main() {
    int n, k;
    std::cout << "--- Сортування підрахунком (Counting Sort) ---" << std::endl;
    std::cout << "Введіть кількість елементів масиву (n): ";
    std::cin >> n;

    std::cout << "Введіть максимальне можливе число в масиві (k): ";
    std::cin >> k;

    int* A = new int[n];
    int* B = new int[n];

    std::cout << "Введіть " << n << " цілих чисел (від 0 до " << k << "):" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cin >> A[i];
    }

    CountingSort(A, B, n, k);

    std::cout << "\nВідсортований масив: ";
    for (int i = 0; i < n; i++) {
        std::cout << B[i] << " ";
    }
    std::cout << std::endl;

    delete[] A;
    delete[] B;
    return 0;
}