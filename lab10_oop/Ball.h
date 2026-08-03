#pragma once
#include "Sphere.h"
#include <string>

using std::string;

class Ball : public Sphere
{
public:
    Ball();
    Ball(double initialRadius, const string initialName);
    
    string getName() const;
    void setName(const string newName);
    void resetBall(double newRadius, const string newName);
    void displayStatistics() const;

private:
    string theName;
};