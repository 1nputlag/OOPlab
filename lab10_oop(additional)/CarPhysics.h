#ifndef CAR_PHYSICS_H
#define CAR_PHYSICS_H

class CarPhysics {
protected:
    double mass;          // Маса в кг
    double engineForce;   // Сила тяги двигуна в Ньютонах

public:
    CarPhysics(double m = 1500.0, double force = 3000.0);
    
    void setMass(double m);
    void setForce(double force);
    
    virtual double getAcceleration() const; // Віртуальний метод для перевизначення
    virtual void displayInfo() const;
};

#endif