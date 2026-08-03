#pragma once

const double PI = 3.14159; // Глобальна константа

class Sphere
{
public:
    Sphere();                                 // Конструктор за замовчуванням
    Sphere(double initialRadius);             // Конструктор з параметром
    
    void setRadius(double newRadius);         // Змінити радіус
    
    // Константні методи (не змінюють стан об'єкта)
    double getRadius() const;
    double getDiameter() const;
    double getCircumference() const;
    double getArea() const;
    double getVolume() const;
    void displayStatistics() const;

private:
    double theRadius;                         // Приховане поле класу
};