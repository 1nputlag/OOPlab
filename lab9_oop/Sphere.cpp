#include "Sphere.h"
#include <iostream>

using namespace std;

// Реалізація конструктора за замовчуванням
Sphere::Sphere() : theRadius(1.0) 
{}

// Реалізація конструктора з параметром
Sphere::Sphere(double initialRadius)
{
    if (initialRadius > 0)
        theRadius = initialRadius;
    else 
        theRadius = 1.0;
}

// Зміна радіусу з перевіркою
void Sphere::setRadius(double newRadius)
{
    if (newRadius > 0)
        theRadius = newRadius;
    else 
        theRadius = 1.0;
}

double Sphere::getRadius() const
{
    return theRadius;
}

double Sphere::getDiameter() const
{
    return 2.0 * theRadius;
}

double Sphere::getCircumference() const
{
    return PI * getDiameter();
}

double Sphere::getArea() const
{
    return 4.0 * PI * theRadius * theRadius;
}

double Sphere::getVolume() const
{
    double radiusCubed = theRadius * theRadius * theRadius;
    return (4.0 * PI * radiusCubed) / 3.0;
}

void Sphere::displayStatistics() const
{
    cout << "\n Radius = " << getRadius()
         << "\n Diameter = " << getDiameter()
         << "\n Circumference = " << getCircumference()
         << "\n Area = " << getArea()
         << "\n Volume = " << getVolume() << endl;
}