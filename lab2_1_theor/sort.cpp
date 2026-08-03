#include "sort.h"
#include <cstdlib>//бібліотека для rand()
#include <iostream>

void Swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int Partition(int arr[], int p, int r) {
    int x = arr[r];//r - pivot
    int i = p - 1;

    for (int j = p; j < r; j++){
        if (arr[j] <= x){
            i++;
            Swap(arr[i], arr[j]);
        }
    }
    Swap(arr[i + 1], arr[r]);
    return i + 1; //повертаємо індекс півота
}

int RandomizedPartition(int arr[], int p, int r){
    int i = p + rand() % (r - p + 1);//формула вибору випадкового індексу від p до r
    Swap(arr[i], arr[r]);// Міняємо випадковий елемент з останнім
    return Partition(arr, p, r);
}

// 1. Звичайний QuickSort (завжди бере ОСТАННІЙ елемент як півот)
void QuickSort(int arr[], int p, int r) {
    if (p < r) {
        // Тут ми викликаємо базовий Partition!
        int q = Partition(arr, p, r); 
        QuickSort(arr, p, q - 1);
        QuickSort(arr, q + 1, r);
    }
}

// 2. Рандомізований QuickSort
void RandomizedQuickSort(int arr[], int p, int r) {
    if (p < r) {
        // викликаємо RandomizedPartition
        int q = RandomizedPartition(arr, p, r); 
        RandomizedQuickSort(arr, p, q - 1);
        RandomizedQuickSort(arr, q + 1, r);
    }
}