#pragma once
#include "Shape.h"

class Triangle : public Shape {
private:
    double base;
    double height;
public:
    Triangle(double, double);
    double Calc_Area() const override;
};