#ifndef SORT_H
#define SORT_H

// Допоміжна функція для обміну значень
void Swap(int& a, int& b);

// Базове розбиття масиву (Partition)
int Partition(int arr[], int p, int r);

// Рандомізоване розбиття масиву (RandomizedPartition)
int RandomizedPartition(int arr[], int p, int r);

// Головна функція швидкого сортування (QuickSort)
void QuickSort(int arr[], int p, int r);
 
void RandomizedQuickSort(int arr[], int p, int r);

#endif