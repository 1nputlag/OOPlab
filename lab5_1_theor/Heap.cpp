#include "Heap.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>

using namespace std;

// --- Навігація ---
int Parent(int i) { return (i - 1) / 2; }
int Left(int i) { return 2 * i + 1; }
int Right(int i) { return 2 * i + 2; }

// ================= ЧАСТИНА 1 =================

// --- Підтримка властивості Max-Heap ---
void MaxHeapify(vector<int>& A, int i, int heap_size) {
    int l = Left(i);
    int r = Right(i);
    int largest = i;

    if (l < heap_size && A[l] > A[largest]) largest = l;
    if (r < heap_size && A[r] > A[largest]) largest = r;

    if (largest != i) {
        swap(A[i], A[largest]);
        MaxHeapify(A, largest, heap_size);
    }
}

void BuildMaxHeap(vector<int>& A) {
    int heap_size = A.size();
    for (int i = heap_size / 2 - 1; i >= 0; i--) {
        MaxHeapify(A, i, heap_size);
    }
}

// --- Підтримка властивості Min-Heap ---
void MinHeapify(vector<int>& A, int i, int heap_size) {
    int l = Left(i);
    int r = Right(i);
    int smallest = i;

    if (l < heap_size && A[l] < A[smallest]) smallest = l;
    if (r < heap_size && A[r] < A[smallest]) smallest = r;

    if (smallest != i) {
        swap(A[i], A[smallest]);
        MinHeapify(A, smallest, heap_size);
    }
}

void BuildMinHeap(vector<int>& A) {
    int heap_size = A.size();
    for (int i = heap_size / 2 - 1; i >= 0; i--) {
        MinHeapify(A, i, heap_size);
    }
}

// --- Пірамідальне сортування ---
void HeapSort(vector<int>& A, bool ascending) {
    int heap_size = A.size();
    if (ascending) {
        BuildMaxHeap(A);
        for (int i = A.size() - 1; i > 0; i--) {
            swap(A[0], A[i]);
            heap_size--;
            MaxHeapify(A, 0, heap_size);
        }
    } else {
        BuildMinHeap(A);
        for (int i = A.size() - 1; i > 0; i--) {
            swap(A[0], A[i]);
            heap_size--;
            MinHeapify(A, 0, heap_size);
        }
    }
}

// ================= ЧАСТИНА 2 =================

// --- Черга з пріоритетами (Max-Heap) ---
int HeapMax(const vector<int>& A) {
    if (A.empty()) throw runtime_error("Черга порожня");
    return A[0];
}

int HeapExtractMax(vector<int>& A) {
    if (A.empty()) throw runtime_error("Черга порожня");
    int max_val = A[0];
    A[0] = A.back();
    A.pop_back();
    MaxHeapify(A, 0, A.size());
    return max_val;
}

void HeapIncreaseKey(vector<int>& A, int i, int key) {
    if (key < A[i]) {
        cerr << "Помилка: новий ключ менший за поточний!\n";
        return;
    }
    A[i] = key;
    while (i > 0 && A[Parent(i)] < A[i]) {
        swap(A[i], A[Parent(i)]);
        i = Parent(i);
    }
}

void MaxHeapInsert(vector<int>& A, int key) {
    A.push_back(-2147483648); // Мінімально можливе значення (int)
    HeapIncreaseKey(A, A.size() - 1, key);
}

// --- Черга з пріоритетами (Min-Heap) ---
int HeapMin(const vector<int>& A) {
    if (A.empty()) throw runtime_error("Черга порожня");
    return A[0];
}

int HeapExtractMin(vector<int>& A) {
    if (A.empty()) throw runtime_error("Черга порожня");
    int min_val = A[0];
    A[0] = A.back();
    A.pop_back();
    MinHeapify(A, 0, A.size());
    return min_val;
}

void HeapDecreaseKey(vector<int>& A, int i, int key) {
    if (key > A[i]) {
        cerr << "Помилка: новий ключ більший за поточний!\n";
        return;
    }
    A[i] = key;
    while (i > 0 && A[Parent(i)] > A[i]) {
        swap(A[i], A[Parent(i)]);
        i = Parent(i);
    }
}

void MinHeapInsert(vector<int>& A, int key) {
    A.push_back(2147483647); // Максимально можливе значення (int)
    HeapDecreaseKey(A, A.size() - 1, key);
}