#pragma once
#include <string>
#include <SFML/graphics.hpp>
#include "clickable.h"
#include "resource_manager.h"

const int NUMBER_FIELD_W = 75;
const int NUMBER_FIELD_H = 22;
const int TEXT_SIZE = 18;

class NumberField : public Clickable {
    std::string content;
    sf::Text txt;
    sf::RectangleShape box;
    bool focus;
public:
    NumberField(float x, float y, const ResourceManager & rm);
    void query_click(int x, int y) override;
    void text_entered(sf::Event & event);
    void draw(sf::RenderWindow & wndw) const;
    std::string get_content() const;
};
