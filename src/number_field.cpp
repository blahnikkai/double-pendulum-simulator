#include "number_field.h"

NumberField::NumberField(float x, float y, const ResourceManager & rm, const std::string & placeholder_txt) :
    focus(false),
    placeholder_txt(placeholder_txt)
{
    box.setPosition(x, y);
    box.setSize({NUMBER_FIELD_W, NUMBER_FIELD_H});
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(2);
    txt.setPosition(x + 5, y);
    txt.setCharacterSize(TEXT_SIZE);
    txt.setFont(rm.get_font());
    txt.setFillColor(sf::Color(0, 0, 0, 128));
    txt.setString(placeholder_txt);
}

void NumberField::query_click(int x, int y) {
    if(box.getGlobalBounds().contains(x, y)) {
        focus = true;
        box.setOutlineColor(sf::Color::Blue);
    }
    else {
        focus = false;
        box.setOutlineColor(sf::Color::Black);
    }
}

void NumberField::text_entered(sf::Event & event) {
    if(!focus)
        return;
    char let = (char)event.text.unicode;
    if(let == '\b')
        content.pop_back();
    else if(std::isdigit(let) || let == '.' || let == '-')
        content += let;
    if(content.empty()) {
        txt.setString(placeholder_txt);
        txt.setFillColor(sf::Color(0, 0, 0, 128));
    }
    else {
        txt.setString(content);
        txt.setFillColor(sf::Color(0, 0, 0, 255));
    }
}

void NumberField::draw(sf::RenderWindow & wndw) const {
    wndw.draw(box);
    wndw.draw(txt);
}

std::string NumberField::get_content() const {
    return content;
}