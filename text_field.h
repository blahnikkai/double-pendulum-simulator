#pragma once
#include <string>
#include <SFML/graphics.hpp>
#include "clickable.h"
#include "resource_manager.h"

const int TEXTFIELD_W = 100;
const int TEXT_SIZE = 20;

class TextField : public Clickable {
    std::string content;
    sf::Text txt;
    sf::RectangleShape box;
    bool focus;
public:
    TextField(float x, float y, float h, const ResourceManager & rm);
    void query_click(int x, int y) override;
    void text_entered(sf::Event & event);
    void draw(sf::RenderWindow & wndw) const;
    std::string get_content() const;
};
