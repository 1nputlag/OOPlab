#include <iostream>
#include "sort.h" 

int main() {
    int n;
    std::cout << "Введіть розмір масиву: ";
    std::cin >> n;

    int* arr = new int[n];

    std::cout << "Введіть елементи масиву: " << std::endl;
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    // Вибір методу сортування ---
    int choice;
    std::cout << "\nВиберіть метод вибору півота:" << std::endl;
    std::cout << "1 - Останній елемент (Звичайний QuickSort)" << std::endl;
    std::cout << "2 - Випадковий елемент (Randomized QuickSort)" << std::endl;
    std::cout << "Ваш вибір (1 або 2): ";
    std::cin >> choice;

    if (choice == 1) {
        QuickSort(arr, 0, n - 1);
        std::cout << "\nМасив відсортовано класичним методом!" << std::endl;
    } else if (choice == 2) {
        RandomizedQuickSort(arr, 0, n - 1);
        std::cout << "\nМасив відсортовано рандомізованим методом!" << std::endl;
    } else {
        std::cout << "\nПомилка: Неправильний вибір. Масив не відсортовано." << std::endl;
    }
    // --------------------------------------------

    std::cout << "Масив після сортування: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    delete[] arr;
    return 0;
}