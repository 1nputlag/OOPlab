#pragma once
#include "Interfaces.h"

class SimpsonRule : public IIntegrator {
public:
    double integrate(const IFunction& func, double a, double b, int steps) const override {
        if (steps % 2 != 0) steps++;
        double h = (b - a) / steps;
        double sum = func.evaluate(a) + func.evaluate(b);
        for (int i = 1; i < steps; i += 2) sum += 4 * func.evaluate(a + i * h);
        for (int i = 2; i < steps - 1; i += 2) sum += 2 * func.evaluate(a + i * h);
        return sum * h / 3.0;
    }
    std::wstring getName() const override { return L"Метод Сімпсона"; }
};

class RectangleRule : public IIntegrator {
public:
    double integrate(const IFunction& func, double a, double b, int steps) const override {
        double width = (b - a) / steps;
        double sum = 0.0;
        for (int i = 0; i < steps; ++i) sum += func.evaluate(a + i * width + width / 2.0) * width;
        return sum;
    }
    std::wstring getName() const override { return L"Прямокутники"; }
};

class TrapezoidalRule : public IIntegrator {
public:
    double integrate(const IFunction& func, double a, double b, int steps) const override {
        double width = (b - a) / steps;
        double sum = 0.5 * (func.evaluate(a) + func.evaluate(b));
        for (int i = 1; i < steps; ++i) sum += func.evaluate(a + i * width);
        return sum * width;
    }
    std::wstring getName() const override { return L"Трапеції"; }
};