#pragma once
#include "Interfaces.h"
#include <vector>
#include <cmath>

class FourierTermFunction : public IFunction {
private:
    const IFunction& baseFunc;
    int n;
    bool isCosine;
public:
    FourierTermFunction(const IFunction& f, int n, bool isCos) : baseFunc(f), n(n), isCosine(isCos) {}
    double evaluate(double x) const override {
        return isCosine ? baseFunc.evaluate(x) * std::cos(n * x) : baseFunc.evaluate(x) * std::sin(n * x);
    }
    std::wstring getName() const override { return L"Терм"; }
};

class FourierSeries {
private:
    std::vector<double> a_coeffs;
    std::vector<double> b_coeffs;
    double a0;
    int harmonics;

public:
    void calculate(const IFunction& func, const IIntegrator& integrator, int h, int steps = 1300, double period = 2 * M_PI) {
        harmonics = h;
        a_coeffs.clear(); b_coeffs.clear();
        double L = period / 2.0;

        a0 = (1.0 / L) * integrator.integrate(func, -L, L, steps);
        for (int n = 1; n <= harmonics; ++n) {
            FourierTermFunction cosTerm(func, n, true);
            FourierTermFunction sinTerm(func, n, false);
            a_coeffs.push_back((1.0 / L) * integrator.integrate(cosTerm, -L, L, steps));
            b_coeffs.push_back((1.0 / L) * integrator.integrate(sinTerm, -L, L, steps));
        }
    }

    double evaluateApproximation(double x) const {
        double sum = a0 / 2.0;
        for (int n = 1; n <= harmonics; ++n) {
            sum += a_coeffs[n - 1] * std::cos(n * x) + b_coeffs[n - 1] * std::sin(n * x);
        }
        return sum;
    }

    double getAmplitude(int n) const {
        if (n == 0) return std::abs(a0 / 2.0);
        if (n > 0 && n <= harmonics) {
            return std::sqrt(a_coeffs[n-1]*a_coeffs[n-1] + b_coeffs[n-1]*b_coeffs[n-1]);
        }
        return 0.0;
    }
};