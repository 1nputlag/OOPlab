#pragma once
#include <string>

class PCComponent {
protected:
    std::string name;
public:
    PCComponent(std::string n);
    virtual void showSpecs() const = 0;
    virtual ~PCComponent();
};