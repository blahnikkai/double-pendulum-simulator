#include "number_field.h"

NumberField::NumberField(float x, float y, const ResourceManager & rm) :
    focus(false)
{
    box.setPosition(x, y);
    box.setSize({NUMBER_FIELD_W, NUMBER_FIELD_H});
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(2);
    txt.setPosition(x, y);
    txt.setCharacterSize(TEXT_SIZE);
    txt.setFont(rm.get_font());
    txt.setFillColor(sf::Color::Black);
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
    txt.setString(content);
}

void NumberField::draw(sf::RenderWindow & wndw) const {
    wndw.draw(box);
    wndw.draw(txt);
}

std::string NumberField::get_content() const {
    return content;
}