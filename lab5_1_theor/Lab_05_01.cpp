#include <iostream>
#include <vector>
#include "Heap.h"

using namespace std;

void printArray(const vector<int>& A) {
    for (int v : A) cout << v << " ";
    cout << "\n";
}

int main() {
    vector<int> data;
    int n, val;
    cout << "--- Проект Lab_05_01 (Побудова та Сортування) ---\n";
    cout << "Введіть кількість елементів: ";
    cin >> n;
    cout << "Введіть елементи масиву: ";
    for (int i = 0; i < n; i++) {
        cin >> val;
        data.push_back(val);
    }

    int choice;
    do {
        cout << "\nМеню:\n1. Побудувати Max-Heap\n2. Побудувати Min-Heap\n3. Сортувати за зростанням\n4. Сортувати за спаданням\n0. Вихід\nВаш вибір: ";
        cin >> choice;

        vector<int> temp = data; // Копія для роботи
        switch (choice) {
            case 1:
                BuildMaxHeap(temp);
                cout << "Max-Heap: "; printArray(temp); break;
            case 2:
                BuildMinHeap(temp);
                cout << "Min-Heap: "; printArray(temp); break;
            case 3:
                HeapSort(temp, true);
                cout << "Відсортовано за зростанням: "; printArray(temp); break;
            case 4:
                HeapSort(temp, false);
                cout << "Відсортовано за спаданням: "; printArray(temp); break;
        }
    } while (choice != 0);

    return 0;
}