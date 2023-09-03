#pragma once
#include <vector>
#include <SFML/graphics.hpp>
#include "image_button.h"
#include "button.h"
#include "pendulum.h"
#include "double_pendulum.h"
#include "text_field.h"
#include "resource_manager.h"

// 100 px = 100 cm = 1 m
const sf::Color TOOLBAR_CLR = sf::Color(50, 50, 50);
const int FRAMERATE = 60;
const int WNDW_W = 800;
const int WNDW_H = 700;
const int GUIDELINE_W = 2;
const float PIVOT_RAD = 10;
const int TOOLBAR_H = 100;
const int BUTTON_H = 75;
const float CENTER_X = (float)WNDW_W / 2;
const float CENTER_Y = (float)(WNDW_H - TOOLBAR_H) / 2;

class Simulation {
    bool paused;
    ResourceManager rm;
    sf::RenderWindow wndw;
    std::vector<Pendulum> pendulums;
    std::vector<sf::RectangleShape> guidelines;
    sf::CircleShape pivot;
    sf::RectangleShape toolbar;
    ImageButton pause_btn;
    ImageButton add_pendulum_btn;
    ImageButton clear_btn;
    TextField angle1_tf;
    TextField leng1_tf;
    TextField mass1_tf;
    TextField angle2_tf;
    TextField leng2_tf;
    TextField mass2_tf;
    void draw_all();
    void create_guidelines();
    void handle_click(sf::Event & event);
    void handle_text_enter(sf::Event & event);

public:
    Simulation();
    void start();
};
