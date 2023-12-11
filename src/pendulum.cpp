#include "pendulum.h"
#include "simulation.h"

void Pendulum::integrate() {
    speed += acc / (float)FRAMERATE;
    theta += speed / (float)FRAMERATE;
}

// leng is physics unit meters
Pendulum::Pendulum(float theta, float leng) :
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

void Pendulum::draw(sf::RenderWindow & wndw, int center_x, int center_y, bool paused, bool draw_trace) {
    arm.setPosition(center_x, center_y);
    weight.setPosition(center_x, center_y);
    arm.setRotation(rad_to_deg(theta));
    weight.setRotation(rad_to_deg(theta));
    wndw.draw(arm);
    wndw.draw(weight);

    if(!paused) {
        sf::CircleShape weight_copy = weight;
        weight_copy.setOutlineThickness(0);
        trace.push_front(weight_copy);
        if(trace.size() > 50)
            trace.pop_back();
    }
    if(!draw_trace)
        return;
    double opacity = 100;
    for(sf::CircleShape & i : trace) {
        sf::Color color = i.getFillColor();
        // set opacity
        color.a = (unsigned char)opacity;
        opacity *= .9;
        i.setFillColor(color);
        wndw.draw(i);
    }
}

void Pendulum::set_clr(sf::Color new_clr) {
    weight.setFillColor(new_clr);
}
