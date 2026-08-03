

#include "Hash.h" // підключаємо наш заголовочний файл
#include <iomanip>          // std::setw — форматування виводу (ширина поля)

// =============================================================
// ХЕШ-ФУНКЦІЇ
// =============================================================

int hashDivision(int key, int m) {
    // Формула: h(k) = k mod m
    // Проблема: оператор % в C++ може давати від'ємний результат
    // для від'ємних ключів. Наприклад: -3 % 7 = -3 (не 4!)
    // Рішення: додаємо m і беремо mod ще раз — гарантуємо [0, m-1]
    return ((key % m) + m) % m;
    // Приклад: key=10, m=7 → (10%7+7)%7 = (3+7)%7 = 10%7 = 3
    // Приклад: key=-3, m=7 → (-3%7+7)%7 = (-3+7)%7 = 4%7 = 4
}

int hashMultiplication(int key, int m) {
    // Формула: h(k) = floor( m * frac(k * A) )
    // де A = (sqrt(5)-1)/2 ≈ 0.6180339887 — стала Кнута (золотий перетин)

    // Крок 1: обчислюємо сталу A
    const double A = (std::sqrt(5.0) - 1.0) / 2.0; // ≈ 0.6180339887

    // Крок 2: множимо ключ на A, беремо тільки дробову частину
    // frac(x) = x - floor(x)    наприклад: frac(25.957) = 0.957
    double frac = key * A - std::floor(key * A);

    // Крок 3: множимо на m і беремо цілу частину — це і є індекс
    return static_cast<int>(std::floor(m * frac));
    // Приклад: key=42, m=7
    //   A = 0.618, 42*0.618 = 25.957, frac = 0.957
    //   floor(7 * 0.957) = floor(6.7) = 6  → комірка [6]
}


// =============================================================
// ЧАСТИНА 1: МЕТОД ЛАНЦЮГІВ
// =============================================================

ChainTable ChainedHashCreate(int m) {
    // Створюємо вектор з m елементів типу std::list<int>
    // Кожен список спочатку порожній — це і є порожній ланцюг
    return ChainTable(m);
    // Результат: [[], [], [], ..., []]  — m порожніх списків
}

// Допоміжна внутрішня функція (static = видима тільки в цьому файлі)
// Повертає індекс комірки для ключа key залежно від типу хеш-функції
static int getIndex(int key, int m, int hashType) {
    if (hashType == 0)
        return hashDivision(key, m);      // метод ділення
    else
        return hashMultiplication(key, m); // метод множення
}

void ChainedHashInsert(ChainTable& table, int key, int hashType) {
    // Крок 1: обчислюємо в яку комірку вставляти
    // table.size() повертає кількість комірок (= m)
    int idx = getIndex(key, static_cast<int>(table.size()), hashType);

    // Крок 2: вставляємо на ПОЧАТОК списку у комірці idx
    // push_front — додає елемент на початок: O(1)
    // (push_back — додавав би в кінець, але нам потрібен початок)
    table[idx].push_front(key);

    // Після вставки ланцюг виглядає: новий_ключ -> старі_ключі -> NULL
}

bool ChainedHashSearch(const ChainTable& table, int key, int hashType) {
    // Крок 1: обчислюємо в якій комірці шукати
    int idx = getIndex(key, static_cast<int>(table.size()), hashType);

    // Крок 2: перебираємо всі елементи ланцюга в комірці idx
    // range-based for: v приймає значення кожного елемента списку
    for (int v : table[idx]) {
        if (v == key) return true;  // знайшли — повертаємо true
    }

    // Пройшли весь ланцюг, не знайшли
    return false;
}

bool ChainedHashDelete(ChainTable& table, int key, int hashType) {
    // Крок 1: знаходимо комірку
    int idx = getIndex(key, static_cast<int>(table.size()), hashType);

    // Посилання на ланцюг (список) у комірці idx
    // auto& — компілятор сам визначає тип (std::list<int>&)
    auto& chain = table[idx];

    // Крок 2: перебираємо список через ітератор
    // Ітератор — це "вказівник" на елемент списку
    for (auto it = chain.begin();  // it = початок списку
         it != chain.end();        // поки не досягли кінця
         ++it) {                   // переходимо до наступного
        if (*it == key) {          // *it — значення на яке вказує ітератор
            chain.erase(it);       // видаляємо елемент зі списку: O(1)
            return true;           // успішно видалено
        }
    }

    // Елемент не знайдено в ланцюгу
    return false;
}

void ChainedHashShow(const ChainTable& table) {
    std::cout << "\n===== ХЕШ-ТАБЛИЦЯ (ЛАНЦЮГИ) =====\n";

    // Перебираємо всі комірки таблиці від 0 до m-1
    for (int i = 0; i < (int)table.size(); ++i) {

        // setw(3) — виводимо індекс у полі шириною 3 символи (вирівнювання)
        std::cout << "[" << std::setw(3) << i << "] ";

        if (table[i].empty()) {
            // Список порожній — ланцюг не містить жодного елемента
            std::cout << "-> NULL";
        } else {
            // Виводимо кожен елемент ланцюга через стрілку
            for (int v : table[i]) {
                std::cout << "-> " << v << " ";
            }
            std::cout << "-> NULL"; // кінець ланцюга
        }
        std::cout << "\n"; // новий рядок для кожної комірки
    }
    std::cout << "===================================\n\n";
}


// =============================================================
// ЧАСТИНА 2: ВІДКРИТА АДРЕСАЦІЯ
// =============================================================

OpenTable HashCreate(int m) {
    // Створюємо вектор з m об'єктів Cell
    // Конструктор Cell() автоматично встановлює state = EMPTY
    return OpenTable(m);
}

int h1(int key, int m) {
    // Перша хеш-функція — метод ділення
    // Те саме що hashDivision, але використовується всередині probeIndex
    return ((key % m) + m) % m;
}

int h2(int key, int m) {
    // Друга хеш-функція для подвійного дослідження
    // Формула: h2(k) = 1 + (k mod (m-1))
    //
    // Чому +1? Щоб результат ніколи не був 0.
    // Якщо h2 = 0, то крок дослідження = 0 і ми вічно перевіряємо
    // ту саму комірку → нескінченний цикл!
    //
    // ((key%(m-1)) + (m-1)) % (m-1) — захист від від'ємних значень
    return 1 + (((key % (m - 1)) + (m - 1)) % (m - 1));
    // Приклад: key=10, m=7 → h2 = 1 + (10 mod 6) = 1 + 4 = 5
}

int probeIndex(int key, int i, int m, ProbeType type,
               double c1, double c2) {
    // Обчислюємо базовий індекс (при i=0 — це просто h1)
    int base = h1(key, m);

    switch (type) {
        case ProbeType::LINEAR:
            // Лінійне дослідження: крок завжди +1
            // При i=0: base, i=1: base+1, i=2: base+2 ...
            // mod m — щоб "обернутись" якщо вийшли за межі
            return (base + i) % m;

        case ProbeType::QUADRATIC:
            // Квадратичне дослідження: крок зростає квадратично
            // h(k,i) = (h1(k) + c1*i + c2*i^2) mod m
            // При c1=0.5, c2=0.5, i=0,1,2,3:
            //   кроки: 0, 1, 3, 6, 10 ... (трикутні числа)
            // (int)(c1*i) — перетворення double в int (беремо цілу частину)
            return (int)((base + (int)(c1 * i) + (int)(c2 * i * i)) % m + m) % m;

        case ProbeType::DOUBLE:
            // Подвійне дослідження: крок = h2(key)
            // h(k,i) = (h1(k) + i * h2(k)) mod m
            // Різні ключі мають різний крок → менше кластеризації
            return (base + i * h2(key, m)) % m;
    }
    return base; // на випадок якщо type не розпізнано
}

bool HashInsert(OpenTable& table, int key, ProbeType type,
                double c1, double c2) {
    // Отримуємо розмір таблиці m
    int m = static_cast<int>(table.size());

    // Пробуємо максимум m разів (більше немає сенсу — обійдемо всю таблицю)
    for (int i = 0; i < m; ++i) {
        // Обчислюємо індекс для i-ї спроби
        int idx = probeIndex(key, i, m, type, c1, c2);

        // Якщо комірка EMPTY або DELETED — можна вставити
        // DELETED теж підходить бо елемент вже видалено — місце вільне
        if (table[idx].state == CellState::EMPTY ||
            table[idx].state == CellState::DELETED) {
            table[idx].key   = key;                // записуємо ключ
            table[idx].state = CellState::OCCUPIED; // позначаємо як зайняту
            return true; // вставка успішна
        }
        // Якщо OCCUPIED — ця комірка зайнята, пробуємо наступну (i++)
    }

    // Пройшли всі m спроб — жодної вільної комірки немає
    std::cerr << "ПОМИЛКА: Таблиця переповнена!\n";
    return false;
}

int HashSearch(const OpenTable& table, int key, ProbeType type,
               double c1, double c2) {
    int m = static_cast<int>(table.size());

    for (int i = 0; i < m; ++i) {
        int idx = probeIndex(key, i, m, type, c1, c2);

        if (table[idx].state == CellState::EMPTY) {
            // EMPTY — тут ніколи нічого не було.
            // Якби наш ключ вставляли і він "проскочив" цю комірку —
            // він би зупинився тут або раніше. Далі шукати немає сенсу.
            return -1; // не знайдено
        }

        if (table[idx].state == CellState::OCCUPIED &&
            table[idx].key == key) {
            return idx; // знайдено! повертаємо індекс комірки
        }

        // Якщо DELETED — пропускаємо і йдемо далі (i++)
        // Елемент міг бути вставлений "через" цю комірку
    }

    // Обійшли всю таблицю — не знайдено
    return -1;
}

bool HashDelete(OpenTable& table, int key, ProbeType type,
                double c1, double c2) {
    // Спочатку знаходимо індекс комірки де лежить ключ
    int idx = HashSearch(table, key, type, c1, c2);

    if (idx == -1) return false; // ключа немає — нічого видаляти

    // КРИТИЧНО: позначаємо як DELETED, а НЕ EMPTY!
    // Якщо поставити EMPTY — пошук інших ключів може зламатись:
    // він зупиниться на цій "порожній" комірці і не знайде елементи
    // що були вставлені далі через колізію
    table[idx].state = CellState::DELETED;
    return true; // успішно видалено
}

void HashShow(const OpenTable& table) {
    std::cout << "\n===== ХЕШ-ТАБЛИЦЯ (ВІДКРИТА АДРЕСАЦІЯ) =====\n";
    for (int i = 0; i < (int)table.size(); ++i) {
        std::cout << "[" << std::setw(3) << i << "] ";

        // Виводимо стан комірки залежно від CellState
        switch (table[i].state) {
            case CellState::EMPTY:
                std::cout << "  [EMPTY]";    // порожня
                break;
            case CellState::DELETED:
                std::cout << "  [DELETED]";  // видалена (зайнята "привидом")
                break;
            case CellState::OCCUPIED:
                std::cout << "  " << table[i].key; // виводимо ключ
                break;
        }
        std::cout << "\n";
    }
    std::cout << "==============================================\n\n";
}