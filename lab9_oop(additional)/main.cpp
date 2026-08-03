#include <iostream>
#include <iomanip>
#include "Car.h"

using namespace std;

int main() 
{
    cout << fixed << setprecision(2);

    cout << "===============================================" << endl;
    cout << "   ЛАБОРАТОРНА РОБОТА: ДОДАТКОВЕ ЗАВДАННЯ      " << endl;
    cout << "   Об'єктно-орієнтоване моделювання авто       " << endl;
    cout << "===============================================" << endl;

    // 1. Автомобіль зі стандартними параметрами
    Car defaultCar;
    cout << "\n>>> Тест 1: Автомобіль за замовчуванням (1000 кг, 10 м/с)";
    defaultCar.displayPhysicsStats();

    // 2. Власне авто (наприклад, 1500 кг, 25 м/с - це 90 км/год)
    Car myCar(1500.0, 25.0);
    cout << "\n>>> Тест 2: Користувацький автомобіль (1500 кг, 25 м/с)";
    myCar.displayPhysicsStats();

    // 3. Динамічна зміна швидкості
    cout << "\n>>> Тест 3: Екстрене гальмування (збільшуємо швидкість до 40 м/с)" << endl;
    myCar.setVelocity(40.0); // 144 км/год
    myCar.displayPhysicsStats();

    // Перевірка часу в дорозі для дистанції 10 км (10000 метрів)
    cout << "\nЧас на подолання 10 км при 40 м/с: " 
         << myCar.getTravelTime(10000.0) << " секунд" << endl;

    return 0;
}