#include <iostream>
#include <stdlib.h>
using namespace std;

class array1 {
    // Закриті поля класу array1
    int* Arr_Ptr; 
    int size;

public:
    // Звичайний конструктор ініціалізації
    array1(int sz) {
        Arr_Ptr = new int[sz];
        if (!Arr_Ptr) exit(1);
        size = sz;
        cout << "Ordinary constructor" << endl;
    }

    // Конструктор копіювання
    array1(const array1& a) {
        Arr_Ptr = new int[a.size]; // виділення пам'яті для копії масиву
        if (!Arr_Ptr) exit(1);
        size = a.size;
        for (int i = 0; i < a.size; i++) {
            Arr_Ptr[i] = a.Arr_Ptr[i]; // копіювання вмісту
        }
        cout << "Copy constructor" << endl;
    }

    // Деструктор
    ~array1() {
        delete[] Arr_Ptr;
    }

    void put(int i, int j) {
        if (i >= 0 && i < size) {
            Arr_Ptr[i] = j;
            cout << "i= " << i << " Work put" << endl;
        }
    }

    int get(int i) {
        return Arr_Ptr[i];
    }
};

int main() {
    array1 arr(10); // виклик конструктора ініціалізації
    
    for (int i = 0; i < 10; i++) {
        arr.put(i, i);
    }
    
    for (int i = 0; i < 10; i++) {
        cout << arr.get(i);
    }
    cout << endl;

    arr.~array1();
    array1 new_arr = arr; // виклик конструктора копіювання
            // штучне знищення об'єкту arr
    
    for (int i = 0; i < 10; i++) {
        cout << new_arr.get(i);
    }
    cout << endl;

    system("pause");
    return 0;
}