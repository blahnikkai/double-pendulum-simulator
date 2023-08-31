#pragma once
#include <string>
#include <SFML/graphics.hpp>
#include "clickable.h"
#include "resource_manager.h"

class TextField : public Clickable {
    std::string content;
    sf::Text txt;
    sf::RectangleShape box;
    bool focus;
public:
    TextField(float x, float y, float h, const ResourceManager & rm);
    void query_click(float x, float y) override;
    void text_entered(sf::Event & event);
    void draw(sf::RenderWindow & wndw) const;
    std::string get_content() const;
};