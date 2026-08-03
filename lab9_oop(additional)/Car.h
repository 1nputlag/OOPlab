#pragma once

class Car
{
public:
    // Конструктори
    Car();
    Car(double initialMass, double initialVelocity);

    // Сетери (зміна параметрів)
    void setMass(double newMass);
    void setVelocity(double newVelocity);

    // Гетери (отримання значень)
    double getMass() const;
    double getVelocity() const;

    // Фізичні розрахунки
    double getKineticEnergy() const;
    double getBrakingDistance(double frictionCoefficient) const;
    double getTravelTime(double distance) const;

    // Вивід статистики
    void displayPhysicsStats() const;

private:
    double mass;       // Маса автомобіля (у кілограмах)
    double velocity;   // Швидкість (у метрах за секунду)
};