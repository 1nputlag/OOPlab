// Lab_07_02.cpp — Частина 2: Відкрита адресація
#include <iostream>  // cout, cin
#include <limits>    // numeric_limits
#include "Hash.h"

// Очищення буфера cin після помилки вводу
static void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Безпечне зчитування цілого числа (повторює запит при помилці)
static int readInt(const std::string& prompt) {
    int v;
    while (true) {
        std::cout << prompt;
        if (std::cin >> v) return v;
        std::cout << "Некоректне введення, спробуйте ще раз.\n";
        clearInput();
    }
}

// Безпечне зчитування числа з плаваючою точкою (для c1, c2)
static double readDouble(const std::string& prompt) {
    double v;
    while (true) {
        std::cout << prompt;
        if (std::cin >> v) return v;
        std::cout << "Некоректне введення.\n";
        clearInput();
    }
}

// -------------------------------------------------------------
// Підменю для одного конкретного виду дослідження
// Параметри:
//   table  — посилання на хеш-таблицю (змінюємо її)
//   type   — тип дослідження (LINEAR / QUADRATIC / DOUBLE)
//   c1, c2 — константи для квадратичного дослідження
// -------------------------------------------------------------
static void probeMenu(OpenTable& table, ProbeType type,
                      double c1, double c2) {

    // Визначаємо назву типу дослідження для виведення в заголовку
    std::string typeName;
    if      (type == ProbeType::LINEAR)    typeName = "ЛІНІЙНЕ";
    else if (type == ProbeType::QUADRATIC) typeName = "КВАДРАТИЧНЕ";
    else                                    typeName = "ПОДВІЙНЕ";

    int choice;
    do {
        // Підменю з назвою поточного методу дослідження
        std::cout << "\n  -- Підменю [" << typeName << " дослідження] --\n";
        std::cout << "    1. Вставити елемент\n";
        std::cout << "    2. Знайти елемент\n";
        std::cout << "    3. Видалити елемент\n";
        std::cout << "    4. Показати таблицю\n";
        std::cout << "    0. Назад\n";
        choice = readInt("  Ваш вибір: ");

        switch (choice) {

            case 1: { // ВСТАВКА
                int key = readInt("  Введіть ключ для вставки: ");

                // HashInsert шукає вільну комірку методом дослідження type
                // c1, c2 використовуються тільки для QUADRATIC
                if (HashInsert(table, key, type, c1, c2))
                    std::cout << "  Ключ " << key << " вставлено.\n";
                // Якщо false — таблиця переповнена (HashInsert виведе помилку)
                break;
            }

            case 2: { // ПОШУК
                int key = readInt("  Введіть ключ для пошуку: ");

                // HashSearch повертає індекс комірки або -1
                int idx = HashSearch(table, key, type, c1, c2);
                if (idx != -1)
                    std::cout << "  Ключ " << key
                              << " ЗНАЙДЕНО у комірці [" << idx << "].\n";
                else
                    std::cout << "  Ключ " << key << " НЕ ЗНАЙДЕНО.\n";
                break;
            }

            case 3: { // ВИДАЛЕННЯ
                int key = readInt("  Введіть ключ для видалення: ");

                // HashDelete ставить DELETED замість EMPTY — це важливо!
                if (HashDelete(table, key, type, c1, c2))
                    std::cout << "  Ключ " << key << " ВИДАЛЕНО "
                              << "(комірка позначена як DELETED).\n";
                else
                    std::cout << "  Ключ " << key << " не знайдено.\n";
                break;
            }

            case 4: // ПОКАЗАТИ ТАБЛИЦЮ
                HashShow(table); // виводить EMPTY/DELETED/значення
                break;

            case 0: // НАЗАД до головного меню
                break;

            default:
                std::cout << "  Невідома команда.\n";
        }

    } while (choice != 0); // повторюємо підменю поки не натиснуть 0
}


// -------------------------------------------------------------
// Головна функція програми
// -------------------------------------------------------------
int main() {
    std::cout << "=== Лабораторна робота №7, Частина 2 ===\n";
    std::cout << "    Хешування відкритою адресацією\n\n";

    // Зчитуємо розмір таблиці (m > 1, бо h2 використовує m-1)
    int m = readInt("Введіть розмір хеш-таблиці (m): ");
    while (m <= 1) {
        std::cout << "Розмір повинен бути > 1.\n";
        m = readInt("Введіть розмір хеш-таблиці (m): ");
    }

    // Створюємо таблицю: вектор з m комірок, всі EMPTY
    OpenTable table = HashCreate(m);

    // Зчитуємо константи для квадратичного дослідження
    // c1, c2 = 0.5 — рекомендовані значення при m = степінь двійки (8,16,32...)
    double c1 = 0.5, c2 = 0.5;
    std::cout << "\nПараметри квадратичного дослідження:\n";
    std::cout << "  h(k,i) = (h1(k) + c1*i + c2*i^2) mod m\n";
    std::cout << "  Рекомендовані значення для повного заповнення:\n";
    std::cout << "  c1=0.5, c2=0.5 (при m=2^p, наприклад m=8,16,32)\n";
    c1 = readDouble("  Введіть c1 (напр. 0.5): ");
    c2 = readDouble("  Введіть c2 (напр. 0.5): ");

    // Головний цикл меню
    int choice;
    do {
        // Виводимо формули для кожного методу — для наочності
        std::cout << "\n=== ГОЛОВНЕ МЕНЮ ===\n";
        std::cout << "  Оберіть вид дослідження:\n";
        std::cout << "  1. Лінійне дослідження\n";
        std::cout << "     h(k,i) = (h1(k) + i) mod m\n";
        std::cout << "  2. Квадратичне дослідження";
        std::cout << " (c1=" << c1 << ", c2=" << c2 << ")\n";
        std::cout << "     h(k,i) = (h1(k) + c1*i + c2*i^2) mod m\n";
        std::cout << "  3. Подвійне дослідження\n";
        std::cout << "     h(k,i) = (h1(k) + i*h2(k)) mod m\n";
        std::cout << "  4. Показати поточну таблицю\n";
        std::cout << "  5. Очистити таблицю\n";
        std::cout << "  6. Змінити c1, c2\n";
        std::cout << "  0. Вихід\n";
        choice = readInt("Ваш вибір: ");

        switch (choice) {

            // Відкриваємо підменю з відповідним типом дослідження
            case 1:
                probeMenu(table, ProbeType::LINEAR,    c1, c2);
                break;
            case 2:
                probeMenu(table, ProbeType::QUADRATIC, c1, c2);
                break;
            case 3:
                probeMenu(table, ProbeType::DOUBLE,    c1, c2);
                break;

            case 4: // Показати таблицю без входу в підменю
                HashShow(table);
                break;

            case 5: // Очистити таблицю — створюємо нову порожню
                table = HashCreate(m); // старий вектор замінюється новим
                std::cout << "Таблицю очищено.\n";
                break;

            case 6: // Змінити константи квадратичного дослідження
                c1 = readDouble("Введіть c1: ");
                c2 = readDouble("Введіть c2: ");
                break;

            case 0:
                std::cout << "До побачення!\n";
                break;

            default:
                std::cout << "Невідома команда.\n";
        }

    } while (choice != 0);

    return 0;
}