#include <iostream>
#include "Sphere.h"

using namespace std;

int main()
{
    Sphere unitSphere;               // Створюється сфера з радіусом 1.0
    Sphere mySphere(5.1);            // Створюється сфера з радіусом 5.1

    unitSphere.displayStatistics();  // Вивід статистики для першої сфери

    mySphere.setRadius(4.2);         // Змінюємо радіус другої сфери
    cout << "\nd = " << mySphere.getDiameter() << endl; // Перевіряємо новий діаметр

    return 0;
}