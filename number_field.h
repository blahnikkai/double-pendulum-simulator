#pragma once
#include <string>
#include <SFML/graphics.hpp>
#include "clickable.h"
#include "resource_manager.h"

const int NUMBER_FIELD_W = 110;
const int NUMBER_FIELD_H = 22;
const int TEXT_SIZE = 16;

class NumberField : public Clickable {
    std::string content;
    std::string placeholder_txt;
    sf::Text txt;
    sf::RectangleShape box;
    bool focus;
public:
    NumberField(float x, float y, const ResourceManager & rm, const std::string & placeholder_txt);
    void query_click(int x, int y) override;
    void text_entered(sf::Event & event);
    void draw(sf::RenderWindow & wndw) const;
    std::string get_content() const;
};
