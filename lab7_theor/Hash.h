// #pragma once — захист від подвійного підключення файлу.
// Якщо цей файл підключили двічі — компілятор ігнорує другий раз.
#pragma once

// Підключаємо стандартні бібліотеки:
#include <list>      // std::list — двозв'язний список (для ланцюгів)
#include <vector>    // std::vector — динамічний масив (основа таблиці)
#include <iostream>  // std::cout, std::cin — виведення/введення
#include <cmath>     // std::sqrt, std::floor — математичні функції


// =============================================================
// ХЕШ-ФУНКЦІЇ
// Оголошення (прототипи) — реалізація в Hash.cpp
// =============================================================

// Метод ділення: h(k) = k mod m
// key — ключ який хешуємо, m — розмір таблиці
// Повертає індекс комірки від 0 до m-1
int hashDivision(int key, int m);

// Метод множення Кнута: h(k) = floor(m * frac(k * A))
// A = (sqrt(5)-1)/2 ≈ 0.618 — "золотий перетин"
// Повертає індекс комірки від 0 до m-1
int hashMultiplication(int key, int m);


// =============================================================
// ЧАСТИНА 1: ХЕШ-ТАБЛИЦЯ МЕТОДОМ ЛАНЦЮГІВ
// =============================================================

// Псевдонім типу: ChainTable = вектор двозв'язних списків цілих чисел
// Кожен елемент вектора — це один ланцюг (список) для однієї комірки
// Наприклад: ChainTable t(7) — таблиця з 7 ланцюгів
using ChainTable = std::vector<std::list<int>>;

// Створити порожню хеш-таблицю розміром m
// Повертає вектор з m порожніх списків
ChainTable ChainedHashCreate(int m);

// Вставити ключ key у таблицю
// hashType: 0 = метод ділення, 1 = метод множення
void ChainedHashInsert(ChainTable& table, int key, int hashType = 0);

// Знайти ключ key у таблиці
// Повертає true якщо знайдено, false якщо ні
bool ChainedHashSearch(const ChainTable& table, int key, int hashType = 0);

// Видалити ключ key з таблиці
// Повертає true якщо видалено, false якщо не знайдено
bool ChainedHashDelete(ChainTable& table, int key, int hashType = 0);

// Вивести таблицю на екран у вигляді:
// [0] -> 10 -> 3 -> NULL
// [1] -> NULL
// ...
void ChainedHashShow(const ChainTable& table);


// =============================================================
// ЧАСТИНА 2: ХЕШ-ТАБЛИЦЯ З ВІДКРИТОЮ АДРЕСАЦІЄЮ
// =============================================================

// Перерахування: три можливі стани кожної комірки таблиці
// enum class — безпечне перерахування (не змішується з int)
enum class CellState {
    EMPTY,     // комірка порожня, ніколи не використовувалась
    OCCUPIED,  // комірка зайнята — є елемент
    DELETED    // елемент був, але його видалили (важливо для пошуку!)
};

// Структура однієї комірки таблиці з відкритою адресацією
struct Cell {
    int key;          // значення ключа що зберігається
    CellState state;  // поточний стан комірки

    // Конструктор: при створенні комірка порожня, ключ = 0
    Cell() : key(0), state(CellState::EMPTY) {}
};

// Псевдонім: OpenTable = вектор комірок
using OpenTable = std::vector<Cell>;

// Перерахування типів дослідження (probing) при колізії
enum class ProbeType {
    LINEAR,     // лінійне:     h(k,i) = (h1(k) + i) mod m
    QUADRATIC,  // квадратичне: h(k,i) = (h1(k) + c1*i + c2*i^2) mod m
    DOUBLE      // подвійне:    h(k,i) = (h1(k) + i*h2(k)) mod m
};

// Створити порожню таблицю з відкритою адресацією розміром m
OpenTable HashCreate(int m);

// Перша допоміжна хеш-функція: h1(k) = k mod m
int h1(int key, int m);

// Друга допоміжна хеш-функція: h2(k) = 1 + (k mod (m-1))
// Результат завжди >= 1, щоб крок дослідження не був нулем
int h2(int key, int m);

// Обчислити індекс при i-тій спробі дослідження
// key — ключ, i — номер спроби (0,1,2,...), m — розмір таблиці
// type — тип дослідження, c1/c2 — константи для квадратичного
int probeIndex(int key, int i, int m, ProbeType type,
               double c1 = 0.5, double c2 = 0.5);

// Вставити ключ у таблицю з відкритою адресацією
// Повертає true якщо вставлено, false якщо таблиця переповнена
bool HashInsert(OpenTable& table, int key, ProbeType type,
                double c1 = 0.5, double c2 = 0.5);

// Знайти ключ у таблиці
// Повертає індекс комірки де знайдено, або -1 якщо не знайдено
int HashSearch(const OpenTable& table, int key, ProbeType type,
               double c1 = 0.5, double c2 = 0.5);

// Видалити ключ (позначає комірку як DELETED, не EMPTY!)
// Повертає true якщо видалено, false якщо не знайдено
bool HashDelete(OpenTable& table, int key, ProbeType type,
                double c1 = 0.5, double c2 = 0.5);

// Вивести таблицю на екран
void HashShow(const OpenTable& table);