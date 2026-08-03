#include "BilliardBall.h"
#include <iostream>

using namespace std;

BilliardBall::BilliardBall() : Ball(2.85, "BilliardBall"), number(8)
{
}

BilliardBall::BilliardBall(double initialRadius, const string initialName, int ballNumber)
    : Ball(initialRadius, initialName), number(ballNumber)
{
}

int BilliardBall::getNumber() const
{
    return number;
}

void BilliardBall::setNumber(int newNumber)
{
    number = newNumber;
}

void BilliardBall::displayStatistics() const
{
    cout << "Billiard Ball Number: " << number << endl;
    Ball::displayStatistics();
}