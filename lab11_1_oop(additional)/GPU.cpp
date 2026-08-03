#include <iostream>
#include "GPU.h"

GPU::GPU(std::string n, int v) : PCComponent(n), vram(v) {}

void GPU::showSpecs() const {
    std::cout << "GPU: " << name << " | VRAM: " << vram << " GB" << std::endl;
}