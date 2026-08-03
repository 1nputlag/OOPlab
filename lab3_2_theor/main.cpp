#include <iostream>
#include "sort.h"

int main() {
    int choice;

    std::cout << "============= ГОЛОВНЕ МЕНЮ =============" << std::endl;
    std::cout << "1 - Сортування підрахунком (Counting Sort)" << std::endl;
    std::cout << "2 - Сортування за розрядами (Radix Sort)" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Ваш вибір (1 або 2): ";
    std::cin >> choice;

    if (choice == 1) {
        // --- БЛОК 1: COUNTING SORT ---
        int n, k;
        std::cout << "\n--- Сортування підрахунком ---" << std::endl;
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

    } else if (choice == 2) {
        // --- БЛОК 2: RADIX SORT ---
        int n, d;
        std::cout << "\n--- Сортування за розрядами ---" << std::endl;
        std::cout << "Введіть кількість елементів масиву (n): ";
        std::cin >> n;
        std::cout << "Введіть розрядність чисел (d) (наприклад, 3 для тризначних): ";
        std::cin >> d;

        int* A = new int[n];

        std::cout << "Введіть " << n << " чисел (кожне з розрядністю до " << d << "):" << std::endl;
        for (int i = 0; i < n; i++) {
            std::cin >> A[i];
        }

        RadixSort(A, n, d);

        std::cout << "\nВідсортований масив: ";
        for (int i = 0; i < n; i++) {
            std::cout << A[i] << " ";
        }
        std::cout << std::endl;

        delete[] A;

    } else {
        std::cout << "\nПомилка: Неправильний вибір. Перезапустіть програму." << std::endl;
    }

    return 0;
}