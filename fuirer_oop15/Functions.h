#pragma once
#include "Interfaces.h"
#include <cmath>

class SawtoothWave : public IFunction {
public:
    double evaluate(double x) const override {
        double normalized_x = fmod(x, 2 * M_PI);
        if (normalized_x < 0) normalized_x += 2 * M_PI;
        return (normalized_x / M_PI) - 1.0;
    }
    std::wstring getName() const override { return L"Пилка"; } // L - означає Wide String
};

class SquareWave : public IFunction {
public:
    double evaluate(double x) const override {
        double normalized_x = fmod(x, 2 * M_PI);
        if (normalized_x < 0) normalized_x += 2 * M_PI;
        return (normalized_x < M_PI) ? 1.0 : -1.0;
    }
    std::wstring getName() const override { return L"Меандр"; }
};