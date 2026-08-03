#include "Ball.h"
#include <iostream>

using namespace std;

Ball::Ball() : Sphere()
{
    setName("FootBall");
}

Ball::Ball(double initialRadius, const string initialName) : Sphere(initialRadius)
{
    setName(initialName);
}

string Ball::getName() const
{
    return theName;
}

void Ball::setName(const string newName)
{
    theName = newName;
}

void Ball::resetBall(double newRadius, const string newName)
{
    setRadius(newRadius);
    setName(newName);
}

void Ball::displayStatistics() const
{
    cout << "Object Name = " << theName << ":";
    Sphere::displayStatistics();
}