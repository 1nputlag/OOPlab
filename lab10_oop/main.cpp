#include <iostream>
#include "Sphere.h"
#include "Ball.h"
#include "BilliardBall.h" // Обов'язково підключаємо наш новий клас

using namespace std;

int main()
{
    // --- Основне завдання ---
    cout << "--- Testing Sphere ---" << endl;
    Sphere unitSphere;
    unitSphere.displayStatistics();

    Sphere mySphere(5.1);
    cout << "d=" << mySphere.getDiameter() << endl;
    cout << "************" << endl;
    mySphere.displayStatistics();
    
    cout << "=============" << endl;
    mySphere.setRadius(4.2);
    cout << "d=" << mySphere.getDiameter() << endl;
    mySphere.displayStatistics();
    
    cout << "=============" << endl;
    cout << "--- Testing Ball ---" << endl;
    Ball myBall;
    myBall.resetBall(30.5, "My_Footbol");
    myBall.displayStatistics();
    
    // Демонстрація роботи вказівників (поліморфізм)
    cout << "111111111111111111" << endl;
    Sphere* spherePtr1 = &mySphere;
    spherePtr1->displayStatistics();
    
    cout << "222222222222" << endl;
    Sphere* spherePtr2 = &myBall;
    spherePtr2->displayStatistics();

    // --- Перше додаткове завдання (BilliardBall) ---
    cout << "\n--- Testing BilliardBall ---" << endl;
    
    // Створюємо більярдну кулю з радіусом 2.85, назвою "Black Ball" і номером 8
    BilliardBall myBilliard(2.85, "Black Ball", 8);
    myBilliard.displayStatistics();

    cout << "333333333333" << endl;
    // Перевіряємо, чи працює вказівник на базовий клас для нашого нового нащадка
    Sphere* spherePtr3 = &myBilliard;
    spherePtr3->displayStatistics();

    system("pause");
    return 0;
}