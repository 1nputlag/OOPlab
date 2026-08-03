#include "Car.h"
#include <iostream>

using namespace std;

// Конструктор за замовчуванням (маса 1000 кг, швидкість 10 м/с)
Car::Car() : mass(1000.0), velocity(10.0) 
{}

// Конструктор з параметрами
Car::Car(double initialMass, double initialVelocity)
{
    setMass(initialMass);
    setVelocity(initialVelocity);
}

void Car::setMass(double newMass)
{
    // Маса не може бути від'ємною або нульовою
    if (newMass > 0)
        mass = newMass;
    else 
        mass = 1000.0;
}

void Car::setVelocity(double newVelocity)
{
    // Швидкість не може бути від'ємною
    if (newVelocity >= 0)
        velocity = newVelocity;
    else 
        velocity = 0.0;
}

double Car::getMass() const { return mass; }
double Car::getVelocity() const { return velocity; }

double Car::getKineticEnergy() const
{
    // E = (m * v^2) / 2
    return (mass * velocity * velocity) / 2.0;
}

double Car::getBrakingDistance(double frictionCoefficient) const
{
    // Гальмівний шлях: S = v^2 / (2 * mu * g)
    // Якщо коефіцієнт тертя задано некоректно, беремо 0.7 (сухий асфальт)
    double mu = (frictionCoefficient > 0) ? frictionCoefficient : 0.7;
    const double g = 9.81; 
    
    return (velocity * velocity) / (2.0 * mu * g);
}

double Car::getTravelTime(double distance) const
{
    // t = S / v
    if (velocity == 0) return 0.0;
    return distance / velocity;
}

void Car::displayPhysicsStats() const
{
    cout << "\n --- Car Physics Stats ---"
         << "\n Mass = " << getMass() << " kg"
         << "\n Velocity = " << getVelocity() << " m/s"
         << "\n Kinetic Energy = " << getKineticEnergy() << " Joules"
         << "\n Braking Distance (mu=0.7) = " << getBrakingDistance(0.7) << " meters" << endl;
}