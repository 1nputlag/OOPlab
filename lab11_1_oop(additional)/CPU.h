#pragma once
#include "PCComponent.h"

class CPU : public PCComponent {
private:
    int cores;
    double clockSpeed;
public:
    CPU(std::string n, int c, double s);
    void showSpecs() const override;
};