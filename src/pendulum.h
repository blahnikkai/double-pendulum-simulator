#pragma once
#include <cmath>
#include <vector>
#include <deque>
#include <SFML/Graphics.hpp>
#include "util.h"

const sf::Color ARM_CLR = sf::Color(50, 50, 50);
const float g = 9.81;
const float ARM_W = 5;
const float WEIGHT_RAD = 15;
const int PX_METER_RATIO = 100;

class Pendulum {
    float leng;
    float theta;
    float acc;
    float speed;
    sf::RectangleShape arm;
    sf::CircleShape weight;
    std::deque<sf::CircleShape> trace;

    void integrate();

public:
    Pendulum(float theta, float leng);
    void update();
    void draw(sf::RenderWindow & wndw, int center_x, int center_y, bool paused, bool draw_trace);
    void set_clr(sf::Color clr);
    friend class DoublePendulum;
};
