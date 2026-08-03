#pragma once
#include "Shape.h"

class Circle : public Shape {
private:
    double R;
public:
    Circle(double);
    double Calc_Area() const override;
};