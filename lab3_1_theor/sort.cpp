#include "sort.h"
#include <cmath>

// Реалізація Counting Sort
void CountingSort(int A[], int B[], int n, int k) {
    // Створюємо масив C для підрахунку розміром k + 1, заповнений нулями
    int* C = new int[k + 1](); 

    // 1. Рахуємо кількість входжень кожного числа
    for (int j = 0; j < n; j++) {
        C[A[j]]++;
    }

    // 2. Рахуємо кількість елементів, менших або рівних i
    for (int i = 1; i <= k; i++) {
        C[i] += C[i - 1];
    }

    // 3. Формуємо відсортований масив (йдемо з кінця для збереження СТІЙКОСТІ)
    for (int j = n - 1; j >= 0; j--) {
        B[C[A[j]] - 1] = A[j]; // -1, бо індекси починаються з 0
        C[A[j]]--;
    }

    delete[] C; // Очищення пам'яті
}

// Допоміжна функція для RadixSort: модифікований підрахунок за певним розрядом
void CountingSortForRadix(int A[], int n, int exp) {
    int* B = new int[n];
    int C[10] = {0}; // Цифри від 0 до 9

    // Рахуємо кількості для конкретного розряду
    for (int j = 0; j < n; j++) {
        int digit = (A[j] / exp) % 10;
        C[digit]++;
    }

    for (int i = 1; i < 10; i++) {
        C[i] += C[i - 1];
    }

    // Збираємо масив
    for (int j = n - 1; j >= 0; j--) {
        int digit = (A[j] / exp) % 10;
        B[C[digit] - 1] = A[j];
        C[digit]--;
    }

    // Копіюємо результат назад у вихідний масив A
    for (int i = 0; i < n; i++) {
        A[i] = B[i];
    }

    delete[] B;
}

// Реалізація Radix Sort
void RadixSort(int A[], int n, int d) {
    int exp = 1; // 10^(i-1) - множник розряду: 1, 10, 100...

    // Проходимося по кожному з d розрядів (від молодшого до старшого)
    for (int i = 1; i <= d; i++) {
        CountingSortForRadix(A, n, exp);
        exp *= 10; // Перехід до наступного розряду
    }
}