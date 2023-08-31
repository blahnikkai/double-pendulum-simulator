#include "simulation.h"

void Simulation::draw_all() {
    for(sf::RectangleShape & gl : guidelines)
        wndw.draw(gl);
    for(Pendulum & p: pendulums)
        p.draw(wndw);
    wndw.draw(pivot);
    wndw.draw(toolbar);
    wndw.draw(pause_btn.get_sprt());
    wndw.draw(add_pendulum_btn.get_bounds());
    wndw.draw(add_pendulum_btn.get_sprt());
    wndw.draw(clear_btn.get_bounds());
    wndw.draw(clear_btn.get_sprt());
    angle_tf.draw(wndw);
    leng_tf.draw(wndw);
}

void Simulation::create_guidelines() {
    for(int i = 0; i <= 11; ++i) {
        sf::RectangleShape guideline({GUIDELINE_W, 1000});
        guideline.setFillColor(sf::Color(100, 100, 100));
        guideline.setOrigin((float)GUIDELINE_W / 2, 0);
        guideline.setRotation(30 * (float)i);
        guideline.setPosition((float)WNDW_W / 2, (float)(WNDW_H - TOOLBAR_H) / 2);
        guidelines.push_back(guideline);
    }
    pivot.setFillColor(sf::Color(50, 50, 50));
    pivot.setOrigin(PIVOT_RAD, PIVOT_RAD);
    pivot.setPosition((float)WNDW_W / 2, (float)(WNDW_H - TOOLBAR_H) / 2);
}

void Simulation::handle_click(sf::Event & event) {
    if(event.mouseButton.button == sf::Mouse::Left) {
        float x = event.mouseButton.x;
        float y = event.mouseButton.y;
        pause_btn.query_click(x, y);
        add_pendulum_btn.query_click(x, y);
        clear_btn.query_click(x, y);
        angle_tf.query_click(x, y);
        leng_tf.query_click(x, y);
    }
}

void Simulation::handle_text_enter(sf::Event & event) {
    angle_tf.text_entered(event);
    leng_tf.text_entered(event);
}

Simulation::Simulation() :
    paused(false),
    wndw(sf::VideoMode(WNDW_W, WNDW_H),
"Pendulum Simulator", sf::Style::Close),
    pivot(PIVOT_RAD),
    pause_btn(BUTTON_H, WNDW_H - ((float)(TOOLBAR_H + BUTTON_H) / 2),
              BUTTON_H, BUTTON_H,
              [&]() {
        if (paused)
            pause_btn.get_sprt().setTexture(rm.get("pause.png"));
        else
            pause_btn.get_sprt().setTexture(rm.get("play.png"));
        paused = !paused;
    }, rm.get("pause.png")),
    add_pendulum_btn(7 * BUTTON_H, WNDW_H - ((float)(TOOLBAR_H + BUTTON_H) / 2),
                     BUTTON_H, BUTTON_H,
                     [&]() {
        float leng;
        try {
            leng = std::stof(leng_tf.get_content());
        }
        catch(std::invalid_argument & ia) {
            return;
        }
        float theta;
        try {
            theta = deg_to_rad(std::stof(angle_tf.get_content()));
        }
        catch(std::invalid_argument & ia) {
            return;
        }
        pendulums.emplace_back(leng, theta);
    }, rm.get("add.png")),
    clear_btn(9 * BUTTON_H, WNDW_H - ((float)(TOOLBAR_H + BUTTON_H) / 2),
              BUTTON_H, BUTTON_H,
              [&]() {pendulums.clear();},
              rm.get("clear.png")),
    angle_tf(3 * BUTTON_H, WNDW_H - ((float)(TOOLBAR_H + BUTTON_H) / 2), 25, rm),
    leng_tf(3 * BUTTON_H, WNDW_H - ((float)(TOOLBAR_H + BUTTON_H) / 2) + 50, 25, rm),
    toolbar({WNDW_W, TOOLBAR_H})
{
    wndw.setFramerateLimit(FRAMERATE);
    toolbar.setPosition(0, WNDW_H - TOOLBAR_H);
    toolbar.setFillColor(TOOLBAR_CLR);
    for(int i = 0; i <= 2; ++i)
        pendulums.emplace_back(i * 1.5 + .5, PI / 4);
    create_guidelines();
}

void Simulation::start() {
    DoublePendulum dp(1, PI, 1, PI / 2);
    while(wndw.isOpen()) {
        sf::Event event;
        while(wndw.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                wndw.close();
            if(event.type == sf::Event::MouseButtonPressed)
                handle_click(event);
            if(event.type == sf::Event::TextEntered)
                handle_text_enter(event);
        }
        wndw.clear(sf::Color::Black);
        draw_all();
        dp.draw(wndw);
        wndw.display();
        if(!paused) {
            for(Pendulum & p: pendulums)
                p.update();
            dp.update();
        }
    }
}