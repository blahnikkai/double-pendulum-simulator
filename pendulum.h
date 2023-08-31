#pragma once
#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>

#include "util.h"

const sf::Color ARM_CLR = sf::Color(50, 50, 50);
const sf::Color WEIGHT_CLR = sf::Color::Blue;
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

    void integrate();

public:
    Pendulum(float leng, float theta);
    void update();
    void draw(sf::RenderWindow & wndw);

    friend class DoublePendulum;
};
