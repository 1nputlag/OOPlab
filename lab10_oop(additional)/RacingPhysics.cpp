#include "RacingPhysics.h"
#include <iostream>

RacingPhysics::RacingPhysics(double m, double force, double aero, double nitro)
    : CarPhysics(m, force), aeroCoefficient(aero), nitroBoost(nitro) {}

double RacingPhysics::getAcceleration() const {
    // Прискорення з урахуванням нітро-прискорювача
    return (engineForce + nitroBoost) / mass;
}

double RacingPhysics::getDragForce(double velocity) const {
    // Спрощена формула: F_drag = 0.5 * rho * v^2 * Cd * A
    // Припустимо, що константа середовища та площа = 1.0 для прикладу
    return 0.5 * (velocity * velocity) * aeroCoefficient;
}

void RacingPhysics::displayInfo() const {
    std::cout << "--- Фізика спортивного авто ---\n";
    CarPhysics::displayInfo();
    std::cout << "Коефіцієнт аеродинаміки: " << aeroCoefficient << "\n"
              << "Сила Nitro: " << nitroBoost << " Н\n"
              << "Макс. прискорення (з Nitro): " << getAcceleration() << " м/с^2\n";
}