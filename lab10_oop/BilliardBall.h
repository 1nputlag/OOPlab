#pragma once
#include "Ball.h"

class BilliardBall : public Ball
{
public:
    BilliardBall();
    BilliardBall(double initialRadius, const std::string initialName, int ballNumber);

    int getNumber() const;
    void setNumber(int newNumber);
    void displayStatistics() const;

private:
    int number;
};