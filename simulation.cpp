#include "simulation.h"

void Simulation::draw_all() {
    for(sf::RectangleShape & gl : guidelines)
        wndw.draw(gl);
    wndw.draw(pivot);
    for(Pendulum & p : pendulums)
        p.draw(wndw);
    for(DoublePendulum & dp : double_pendulums)
        dp.draw(wndw, CENTER_X, CENTER_Y);
    wndw.draw(toolbar);
    for(const Button * const btn : buttons)
        btn->draw(wndw);
    for(const TextField & tf : textfields)
        tf.draw(wndw);
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
        int x = event.mouseButton.x;
        int y = event.mouseButton.y;
        for(Button * button : buttons)
            button->query_click(x, y);
        for(TextField & tf : textfields)
            tf.query_click(x, y);
    }
}

void Simulation::handle_text_enter(sf::Event & event) {
    for(TextField & tf : textfields)
        tf.text_entered(event);
}

Simulation::Simulation() :
    paused(false),
    wndw(sf::VideoMode(WNDW_W, WNDW_H),"Pendulum Simulator", sf::Style::Close),
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
    add_pendulum_btn(6.5 * BUTTON_H, WNDW_H - ((float)(TOOLBAR_H + BUTTON_H) / 2),
                     BUTTON_H, BUTTON_H,
                     [&]() {
        try {
            float leng1 = std::stof(textfields.at(0).get_content());
            float theta1 = deg_to_rad(std::stof(textfields.at(1).get_content()));
            float mass1 = std::stof(textfields.at(2).get_content());
            float leng2 = std::stof(textfields.at(3).get_content());
            float theta2 = deg_to_rad(std::stof(textfields.at(4).get_content()));
            float mass2 = std::stof(textfields.at(5).get_content());
            double_pendulums.emplace_back(leng1, theta1, mass1, leng2, theta2, mass2);
        }
        catch(std::invalid_argument & ia) {
            try {
                float leng = std::stof(textfields.at(0).get_content());
                float theta = deg_to_rad(std::stof(textfields.at(1).get_content()));
                pendulums.emplace_back(leng, theta);
            }
            catch(std::invalid_argument & ia) {
                return;
            }
        }
    }, rm.get("add.png")),
    clear_btn(9 * BUTTON_H, WNDW_H - ((float)(TOOLBAR_H + BUTTON_H) / 2),
              BUTTON_H, BUTTON_H,
              [&]() {
                    pendulums.clear();
                    double_pendulums.clear();
                },
              rm.get("clear.png")),
    toolbar({WNDW_W, TOOLBAR_H}),
    buttons({&pause_btn, &clear_btn, &add_pendulum_btn})
{
    wndw.setFramerateLimit(FRAMERATE);
    toolbar.setPosition(0, WNDW_H - TOOLBAR_H);
    toolbar.setFillColor(TOOLBAR_CLR);
    for(int i = 0; i < 3; ++i)
        pendulums.emplace_back(i * 1.5 + .5, PI / 4);
    double_pendulums.emplace_back(1, PI, 1, PI / 2, 1, 1);
    for(int i = 0; i < 6; ++i)
        textfields.emplace_back((4 + 1.1 * (i / 3)) * BUTTON_H,
                                WNDW_H - ((float) (TOOLBAR_H + BUTTON_H) / 2) + 30 * (i % 3),
                                rm);
    create_guidelines();
}

void Simulation::start() {
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
        wndw.display();
        if(!paused) {
            for(Pendulum & p : pendulums)
                p.update();
            for(DoublePendulum & dp : double_pendulums)
                dp.update();
        }
    }
}