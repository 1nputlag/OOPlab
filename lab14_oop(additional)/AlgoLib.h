#pragma once

// Кросплатформове налаштування макросу для експорту
#if defined(_WIN32)
    #ifdef ALGOLIB_EXPORTS
        #define ALGOLIB_API __declspec(dllexport)
    #else
        #define ALGOLIB_API __declspec(dllimport)
    #endif
#else
    #define ALGOLIB_API __attribute__((visibility("default")))
#endif

// Оголошуємо функцію QuickSort, яку зможуть викликати інші програми
extern "C" ALGOLIB_API void quickSort(int arr[], int low, int high);