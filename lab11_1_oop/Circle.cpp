#include "Circle.h"

const double PI = 3.14159265;

Circle::Circle(double r) : R(r) {}

double Circle::Calc_Area() const {
    return PI * R * R;
}