#include <iostream>
#include "Shape.h"
#include "Circle.h"
#include "Triangle.h"

using namespace std;

int main() {
    Shape *s;
    Circle c(5);
    Triangle t(3, 8);

    s = &c;
    cout << endl;
    cout << "s->Calc_Area() = " << s->Calc_Area() << endl;

    s = &t;
    cout << "s->Calc_Area() = " << s->Calc_Area() << endl;

    system("pause");
    return 0;
}