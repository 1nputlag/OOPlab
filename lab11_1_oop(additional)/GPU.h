#pragma once
#include "PCComponent.h"

class GPU : public PCComponent {
private:
    int vram;
public:
    GPU(std::string n, int v);
    void showSpecs() const override;
};