#include <iostream>
#include <vector>
#include <stdexcept>
#include "Heap.h"

using namespace std;

// Допоміжна функція для виводу черги
void printQueue(const vector<int>& A, const string& name) {
    cout << name << " (поточний стан): ";
    for (int v : A) cout << v << " ";
    cout << "\n";
}

// ================= РОБОТА З MAX-HEAP =================
void runMaxHeapQueue() {
    vector<int> q;
    int n, val, choice, idx;
    
    cout << "\n--- Черга на базі MAX-HEAP ---\n";
    cout << "Скільки елементів додати для початкової побудови черги? : ";
    cin >> n;
    
    if (n > 0) {
        cout << "Введіть " << n << " елементів: ";
        for (int i = 0; i < n; i++) {
            cin >> val;
            q.push_back(val);
        }
        BuildMaxHeap(q); // Будуємо незростаючу піраміду з введеного масиву
        printQueue(q, "Max-Heap");
    }

    do {
        cout << "\n[Max-Heap] Меню:\n"
             << "1. Додати елемент (MaxHeapInsert)\n"
             << "2. Переглянути максимум (HeapMax)\n"
             << "3. Видалити максимум (HeapExtractMax)\n"
             << "4. Збільшити ключ елемента (HeapIncreaseKey)\n"
             << "0. Повернутися до головного меню\nОберіть дію: ";
        cin >> choice;

        try {
            switch (choice) {
                case 1:
                    cout << "Введіть значення: "; cin >> val;
                    MaxHeapInsert(q, val);
                    printQueue(q, "Max-Heap");
                    break;
                case 2:
                    cout << "Максимальний елемент: " << HeapMax(q) << "\n";
                    break;
                case 3:
                    cout << "Видалено: " << HeapExtractMax(q) << "\n";
                    printQueue(q, "Max-Heap");
                    break;
                case 4:
                    cout << "Введіть індекс (починаючи з 0) та нове значення: "; 
                    cin >> idx >> val;
                    if (idx < 0 || idx >= q.size()) {
                        cout << "Невірний індекс!\n";
                    } else {
                        HeapIncreaseKey(q, idx, val);
                        printQueue(q, "Max-Heap");
                    }
                    break;
            }
        } catch (const exception& e) {
            cerr << "Помилка: " << e.what() << "\n";
        }
    } while (choice != 0);
}

// ================= РОБОТА З MIN-HEAP =================
void runMinHeapQueue() {
    vector<int> q;
    int n, val, choice, idx;
    
    cout << "\n--- Черга на базі MIN-HEAP ---\n";
    cout << "Скільки елементів додати для початкової побудови черги? (0 - почати з порожньої): ";
    cin >> n;
    
    if (n > 0) {
        cout << "Введіть " << n << " елементів: ";
        for (int i = 0; i < n; i++) {
            cin >> val;
            q.push_back(val);
        }
        BuildMinHeap(q); // Будуємо неростаючу піраміду з введеного масиву
        printQueue(q, "Min-Heap");
    }

    do {
        cout << "\n[Min-Heap] Меню:\n"
             << "1. Додати елемент (MinHeapInsert)\n"
             << "2. Переглянути мінімум (HeapMin)\n"
             << "3. Видалити мінімум (HeapExtractMin)\n"
             << "4. Зменшити ключ елемента (HeapDecreaseKey)\n"
             << "0. Повернутися до головного меню\nОберіть дію: ";
        cin >> choice;

        try {
            switch (choice) {
                case 1:
                    cout << "Введіть значення: "; cin >> val;
                    MinHeapInsert(q, val);
                    printQueue(q, "Min-Heap");
                    break;
                case 2:
                    cout << "Мінімальний елемент: " << HeapMin(q) << "\n";
                    break;
                case 3:
                    cout << "Видалено: " << HeapExtractMin(q) << "\n";
                    printQueue(q, "Min-Heap");
                    break;
                case 4:
                    cout << "Введіть індекс (починаючи з 0) та нове значення: "; 
                    cin >> idx >> val;
                    if (idx < 0 || idx >= q.size()) {
                        cout << "Невірний індекс!\n";
                    } else {
                        HeapDecreaseKey(q, idx, val);
                        printQueue(q, "Min-Heap");
                    }
                    break;
            }
        } catch (const exception& e) {
            cerr << "Помилка: " << e.what() << "\n";
        }
    } while (choice != 0);
}

// ================= ГОЛОВНЕ МЕНЮ =================
int main() {
    int mainChoice;
    
    do {
        cout << "1. Працювати з Max-Priority Queue (Max-Heap)\n";
        cout << "2. Працювати з Min-Priority Queue (Min-Heap)\n";
        cout << "0. Вихід з програми\n";
        cout << "Оберіть тип черги: ";
        cin >> mainChoice;

        if (mainChoice == 1) {
            runMaxHeapQueue();
        } else if (mainChoice == 2) {
            runMinHeapQueue();
        }

    } while (mainChoice != 0);

    return 0;
}