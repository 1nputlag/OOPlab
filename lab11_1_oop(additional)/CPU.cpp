#include <iostream>
#include "CPU.h"

CPU::CPU(std::string n, int c, double s) : PCComponent(n), cores(c), clockSpeed(s) {}

void CPU::showSpecs() const {
    std::cout << "CPU: " << name << " | Cores: " << cores << " | Base Clock: " << clockSpeed << " GHz" << std::endl;
}