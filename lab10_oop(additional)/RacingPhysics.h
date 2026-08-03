#ifndef RACING_PHYSICS_H
#define RACING_PHYSICS_H

#include "CarPhysics.h"

class RacingPhysics : public CarPhysics {
private:
    double aeroCoefficient; // Коефіцієнт обтічності (0.2 - 0.5)
    double nitroBoost;      // Додаткова сила нітро

public:
    RacingPhysics(double m, double force, double aero, double nitro);

    // Перевизначення розрахунку прискорення з урахуванням нітро
    double getAcceleration() const override;
    
    // Новий метод для розрахунку сили опору повітря на певній швидкості
    double getDragForce(double velocity) const;

    void displayInfo() const override;
};

#endif