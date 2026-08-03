#include "RacingPhysics.h"
#include <iostream>

int main() {
    setlocale(LC_ALL, "Ukrainian");

    // Створення об'єкта базового класу
    CarPhysics sedan(1600, 3200);
    sedan.displayInfo();

    std::cout << "\n---------------------------\n\n";

    // Створення об'єкта класу-нащадка
    RacingPhysics bolid(1100, 5500, 0.28, 2500);
    bolid.displayInfo();

    // Демонстрація роботи нового методу нащадка
    double speed = 50.0; // 50 м/с (~180 км/год)
    std::cout << "\nОпір повітря на швидкості " << speed << " м/с: " 
              << bolid.getDragForce(speed) << " Н\n";

    return 0;
}