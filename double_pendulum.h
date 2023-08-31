#pragma once
#include <iostream>
#include "pendulum.h"
#include "simulation.h"

class DoublePendulum {
    Pendulum p1;
    Pendulum p2;

public:
    DoublePendulum(float l1, float theta1, float l2, float theta2);
    void update();
    void draw(sf::RenderWindow & wndw);
};