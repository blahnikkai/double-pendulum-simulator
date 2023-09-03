#include "double_pendulum.h"

DoublePendulum::DoublePendulum(float l1, float theta1, float m1, float l2, float theta2, float m2) :
        p1(l1, theta1),
        p2(l2, theta2),
        m1(m1),
        m2(m2)
{
    sf::Color clr = random_clr();
    p1.set_clr(clr);
    p2.set_clr(clr);
}

void DoublePendulum::update() {
    p1.acc = (-g * (2 * m1 + m2) * sin(p1.theta)
                   - m2 * g * sin(p1.theta - 2 * p2.theta)
                   - 2 * sin(p1.theta - p2.theta) * m2 *
                    (p2.speed * p2.speed * p2.leng + p1.speed * p1.speed * p1.leng * cos(p1.theta - p2.theta)))
                    /
                    (p1.leng * (2 * m1 + m2 - m2 * cos(2 * p1.theta - 2 * p2.theta)));
    p2.acc = (2 * sin(p1.theta - p2.theta)
            * (p1.speed * p1.speed * p1.leng * (m1 + m2)
                + g * (m1 + m2) * cos(p1.theta) + p2.speed * p2.speed * p2.leng * m2 * cos(p1.theta - p2.theta)))
                        / (p2.leng * (2 * m1 + m2 - m2 * cos(2 * p1.theta - 2 * p2.theta)));

    p1.integrate();
    p2.integrate();
}

void DoublePendulum::draw(sf::RenderWindow & wndw, int center_x, int center_y) {
    p1.arm.setRotation(rad_to_deg(p1.theta));
    p1.weight.setRotation(rad_to_deg(p1.theta));
    p2.arm.setPosition(-PX_METER_RATIO * p1.leng * sin(p1.theta) + center_x,
                             PX_METER_RATIO * p1.leng * cos(p1.theta) + center_y);
    p2.weight.setPosition(p2.arm.getPosition());
    p2.arm.setRotation(rad_to_deg(p2.theta));
    p2.weight.setRotation(rad_to_deg(p2.theta));

    wndw.draw(p1.arm);
    wndw.draw(p2.arm);
    wndw.draw(p1.weight);
    wndw.draw(p2.weight);
}