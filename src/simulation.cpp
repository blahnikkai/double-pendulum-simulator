#include "simulation.h"

void Simulation::draw_all() {
    for(sf::RectangleShape & gl : guidelines)
        wndw.draw(gl);
    wndw.draw(pivot);
    for(Pendulum & p: pendulums)
        p.draw(wndw, CENTER_X, CENTER_Y, paused, draw_trace);
    for(DoublePendulum & dp: double_pendulums)
        dp.draw(wndw, CENTER_X, CENTER_Y, paused, draw_trace);
    wndw.draw(toolbar);
    for(const Button * const btn : buttons)
        btn->draw(wndw);
    for(const NumberField & nf : number_fields)
        nf.draw(wndw);
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
        for(NumberField & nf : number_fields)
            nf.query_click(x, y);
    }
}

void Simulation::handle_mouse_move(sf::Event & event) {
    int x = event.mouseMove.x;
    int y = event.mouseMove.y;
    bool hover_button = handle_mouse_move_buttons(x, y);
    bool hover_nfs = handle_mouse_move_nfs(x, y);
    if(hover_button)
        wndw.setMouseCursor(hand);
    else if(hover_nfs)
        wndw.setMouseCursor(text);
    else
        wndw.setMouseCursor(arrow);
}

bool Simulation::handle_mouse_move_buttons(int x, int y) {
    for(Button * button : buttons) {
        if(button->query_hover(x, y, wndw))
            return true;
    }
    return false;
}

bool Simulation::handle_mouse_move_nfs(int x, int y) {
    for(NumberField & nf : number_fields) {
        if(nf.query_hover(x, y, wndw))
            return true;
    }
    return false;
}

void Simulation::handle_text_enter(sf::Event & event) {
    for(NumberField & nf : number_fields)
        nf.text_entered(event);
}

Simulation::Simulation() :
    paused(false),
    draw_trace(true),
    wndw(sf::VideoMode(WNDW_W, WNDW_H),"Pendulum Simulator", sf::Style::Close),
    pivot(PIVOT_RAD),
    trace_btn(.5 * BUTTON_H, WNDW_H - ((float)(TOOLBAR_H + BUTTON_H) / 2), BUTTON_H, BUTTON_H,
        [&]() {
            draw_trace = !draw_trace;
        }
    , rm.get_texture("trace.png")),
    pause_btn(1.7 * BUTTON_H, WNDW_H - ((float)(TOOLBAR_H + BUTTON_H) / 2),
              BUTTON_H, BUTTON_H,
              [&]() {
        if(paused)
            pause_btn.get_sprt().setTexture(rm.get_texture("pause.png"));
        else
            pause_btn.get_sprt().setTexture(rm.get_texture("play.png"));
        paused = !paused;
    }, rm.get_texture("pause.png")),
    add_pendulum_btn(WNDW_W - 2.7 * BUTTON_H, WNDW_H - ((float)(TOOLBAR_H + BUTTON_H) / 2),
                     BUTTON_H, BUTTON_H,
                     [&]() {
        try {
            float theta1 = deg_to_rad(std::stof(number_fields.at(0).get_content()));
            float leng1 = std::stof(number_fields.at(1).get_content());
            float mass1 = std::stof(number_fields.at(2).get_content());
            float theta2 = deg_to_rad(std::stof(number_fields.at(3).get_content()));
            float leng2 = std::stof(number_fields.at(4).get_content());
            float mass2 = std::stof(number_fields.at(5).get_content());
            double_pendulums.emplace_back(theta1, leng1, mass1, theta2, leng2, mass2);
        }
        catch(std::invalid_argument & ia) {
            try {
                float theta = deg_to_rad(std::stof(number_fields.at(0).get_content()));
                float leng = std::stof(number_fields.at(1).get_content());
                pendulums.emplace_back(theta, leng);
            }
            catch(std::invalid_argument & ia) {
                return;
            }
        }
    }, rm.get_texture("add.png"), .75),
    clear_btn(WNDW_W - 1.5 * BUTTON_H, WNDW_H - ((float)(TOOLBAR_H + BUTTON_H) / 2),
              BUTTON_H, BUTTON_H,
              [&]() {
                    pendulums.clear();
                    double_pendulums.clear();
                },
              rm.get_texture("clear.png")),
    toolbar({WNDW_W, TOOLBAR_H}),
    buttons({&trace_btn, &pause_btn, &clear_btn, &add_pendulum_btn})
{
    wndw.setFramerateLimit(FRAMERATE);
    toolbar.setPosition(0, WNDW_H - TOOLBAR_H);
    toolbar.setFillColor(TOOLBAR_CLR);
    for(int i = 0; i < 3; ++i)
        pendulums.emplace_back(PI / 4, i * 1.5 + .5);
    double_pendulums.emplace_back(PI, 1, 1, PI / 2, 1, 1);
    for(int i = 0; i < 6; ++i)
        number_fields.emplace_back(WNDW_W - 5.9 * BUTTON_H + (i >= 3) * (NUMBER_FIELD_W + .1 * BUTTON_H),
                                WNDW_H - ((float) (TOOLBAR_H + BUTTON_H) / 2) + 30 * (i % 3) - 5,
                                   rm, number_field_placeholders.at(i));
    create_guidelines();
    text.loadFromSystem(sf::Cursor::Text);
    hand.loadFromSystem(sf::Cursor::Hand);
}

void Simulation::start() {
    while(wndw.isOpen()) {
        sf::Event event;
        while(wndw.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                wndw.close();
            if(event.type == sf::Event::MouseButtonPressed)
                handle_click(event);
            if(event.type == sf::Event::MouseMoved)
                handle_mouse_move(event);
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
