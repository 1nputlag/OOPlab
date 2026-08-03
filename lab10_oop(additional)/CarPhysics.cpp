#include "CarPhysics.h"
#include <iostream>

CarPhysics::CarPhysics(double m, double force) : mass(m), engineForce(force) {}

void CarPhysics::setMass(double m) { if (m > 0) mass = m; }
void CarPhysics::setForce(double force) { if (force >= 0) engineForce = force; }

double CarPhysics::getAcceleration() const {
    return engineForce / mass;
}

void CarPhysics::displayInfo() const {
    std::cout << "--- Базова фізика автомобіля ---\n"
              << "Маса: " << mass << " кг\n"
              << "Сила двигуна: " << engineForce << " Н\n"
              << "Прискорення: " << getAcceleration() << " м/с^2\n";
}