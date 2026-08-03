#pragma once
#include <string>

class IFunction {
public:
    virtual double evaluate(double x) const = 0;
    virtual std::wstring getName() const = 0; // Тепер використовуємо широкі рядки
    virtual ~IFunction() = default;
};

class IIntegrator {
public:
    virtual double integrate(const IFunction& func, double a, double b, int steps) const = 0;
    virtual std::wstring getName() const = 0;
    virtual ~IIntegrator() = default;
};