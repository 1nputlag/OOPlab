#ifndef HEAP_H
#define HEAP_H

#include <vector>

// Навігація
int Parent(int i);
int Left(int i);
int Right(int i);

// Частина 1: Max-Heap
void MaxHeapify(std::vector<int>& A, int i, int heap_size);
void BuildMaxHeap(std::vector<int>& A);

// Частина 1: Min-Heap
void MinHeapify(std::vector<int>& A, int i, int heap_size);
void BuildMinHeap(std::vector<int>& A);

// Пірамідальне сортування
void HeapSort(std::vector<int>& A, bool ascending);

// Частина 2: Черга з пріоритетами (Max-Heap)
int HeapMax(const std::vector<int>& A);
int HeapExtractMax(std::vector<int>& A);
void HeapIncreaseKey(std::vector<int>& A, int i, int key);
void MaxHeapInsert(std::vector<int>& A, int key);

// Частина 2: Черга з пріоритетами (Min-Heap)
int HeapMin(const std::vector<int>& A);
int HeapExtractMin(std::vector<int>& A);
void HeapDecreaseKey(std::vector<int>& A, int i, int key);
void MinHeapInsert(std::vector<int>& A, int key);

#endif