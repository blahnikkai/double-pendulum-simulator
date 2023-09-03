#include "pendulum.h"
#include "simulation.h"

void Pendulum::integrate() {
    speed += acc / (float)FRAMERATE;
    theta += speed / (float)FRAMERATE;
}

// leng is physics unit meters
Pendulum::Pendulum(float leng, float theta) :
    leng(leng),
    theta(theta),
    arm({ARM_W, leng * PX_METER_RATIO}),
    weight(WEIGHT_RAD),
    speed(0),
    acc(0)
{
    arm.setOrigin(ARM_W / 2, 0);
    weight.setOrigin(WEIGHT_RAD, WEIGHT_RAD - leng * PX_METER_RATIO);
    arm.setPosition(CENTER_X, CENTER_Y);
    weight.setPosition(CENTER_X, CENTER_Y);
    arm.setFillColor(ARM_CLR);
    weight.setFillColor(random_clr());
    weight.setOutlineThickness(2);
    weight.setOutlineColor(sf::Color::Black);
}

void Pendulum::update() {
    acc = -g * sin(theta) / leng;
    integrate();
}

void Pendulum::draw(sf::RenderWindow & wndw) {
    arm.setRotation(rad_to_deg(theta));
    weight.setRotation(rad_to_deg(theta));
    wndw.draw(arm);
    wndw.draw(weight);
}

void Pendulum::set_clr(sf::Color new_clr) {
    weight.setFillColor(new_clr);
}
