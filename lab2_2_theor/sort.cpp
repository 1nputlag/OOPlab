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

void QuickSort(int arr[], int p, int r){
    if (p < r){
        int q = RandomizedPartition(arr, p, r);// Отримуємо індекс розбиття
        QuickSort(arr, p , q - 1);// Сортуємо ліву частину
        QuickSort(arr, q + 1, r);// Сортуємо праву частину
    }
}