#pragma once
#include <vector>
#include <SFML/graphics.hpp>
#include "image_button.h"
#include "button.h"
#include "pendulum.h"
#include "double_pendulum.h"
#include "number_field.h"
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

const std::vector<std::string> number_field_placeholders = {"Angle 1 (deg)", "Length 1 (m)", "Mass 1 (kg)", "Angle 2 (deg)", "Length 2 (m)", "Mass 2 (kg)"};

class Simulation {
    bool paused;
    ResourceManager rm;
    sf::RenderWindow wndw;
    std::vector<Pendulum> pendulums;
    std::vector<DoublePendulum> double_pendulums;
    std::vector<sf::RectangleShape> guidelines;
    sf::CircleShape pivot;
    sf::RectangleShape toolbar;
    ImageButton pause_btn;
    ImageButton add_pendulum_btn;
    ImageButton clear_btn;
    std::vector<NumberField> number_fields;
    std::vector<Button *> buttons;
    void draw_all();
    void create_guidelines();
    void handle_click(sf::Event & event);
    void handle_text_enter(sf::Event & event);

public:
    Simulation();
    void start();
};
