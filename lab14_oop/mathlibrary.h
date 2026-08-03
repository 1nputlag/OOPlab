// MathLibrary.h - Оголошення функцій
#pragma once

// Кросплатформове налаштування експорту
#if defined(_WIN32)
    #ifdef MATHLIBRARY_EXPORTS
        #define MATHLIBRARY_API __declspec(dllexport)
    #else
        #define MATHLIBRARY_API __declspec(dllimport)
    #endif
#else
    #define MATHLIBRARY_API __attribute__((visibility("default")))
#endif

extern "C" MATHLIBRARY_API void fibonacci_init(const unsigned long long a, const unsigned long long b);
extern "C" MATHLIBRARY_API bool fibonacci_next();
extern "C" MATHLIBRARY_API unsigned long long fibonacci_current();
extern "C" MATHLIBRARY_API unsigned fibonacci_index();