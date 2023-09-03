#pragma once
#include <iostream>
#include "pendulum.h"

class DoublePendulum {
    Pendulum p1;
    Pendulum p2;
    float m1;
    float m2;

public:
    DoublePendulum(float l1, float theta1, float m1, float l2, float theta2, float m2);
    void update();
    void draw(sf::RenderWindow & wndw, int center_x, int center_y);
};