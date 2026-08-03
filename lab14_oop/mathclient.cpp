#include <iostream>
#include "mathlibrary.h"

int main() {
    // Ініціалізуємо послідовність
    fibonacci_init(1, 1);
    
    // Виводимо значення, поки не досягнемо ліміту (переповнення)
    do {
        std::cout << fibonacci_index() << ": " << fibonacci_current() << std::endl;
    } while (fibonacci_next());
    
    std::cout << fibonacci_index() + 1 << " Fibonacci sequence values fit in an unsigned 64-bit integer." << std::endl;
    
    return 0;
}