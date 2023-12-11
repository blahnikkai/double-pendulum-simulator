#pragma once
#include <iostream>
#include "pendulum.h"
#include "util.h"

class DoublePendulum {
    Pendulum p1;
    Pendulum p2;
    float m1;
    float m2;

public:
    DoublePendulum(float theta1, float l1, float m1, float theta2, float l2, float m2);
    void update();
    void draw(sf::RenderWindow & wndw, int center_x, int center_y, bool paused);
};