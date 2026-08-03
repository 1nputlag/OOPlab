#include "Triangle.h"

Triangle::Triangle(double b, double h) : base(b), height(h) {}

double Triangle::Calc_Area() const {
    return 0.5 * base * height;
}