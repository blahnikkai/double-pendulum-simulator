#include "double_pendulum.h"

DoublePendulum::DoublePendulum(float theta1, float l1, float m1, float theta2, float l2, float m2) :
        p1(theta1, l1),
        p2(theta2, l2),
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

void DoublePendulum::draw(sf::RenderWindow & wndw, int center_x, int center_y, bool paused, bool draw_trace) {
    p1.draw(wndw, center_x, center_y, paused, draw_trace);
    p2.draw(wndw,
            -PX_METER_RATIO * p1.leng * sin(p1.theta) + center_x,
            PX_METER_RATIO * p1.leng * cos(p1.theta) + center_y,
            paused, draw_trace);
    wndw.draw(p1.arm);
    wndw.draw(p2.arm);
    wndw.draw(p1.weight);
    wndw.draw(p2.weight);
}
