#include "text_field.h"

TextField::TextField(float x, float y, float h, const ResourceManager & rm) :
    focus(false)
{
    box.setPosition(x, y);
    box.setSize({200, h});
    box.setOutlineColor(sf::Color::Black);
    txt.setPosition(x, y);
    txt.setCharacterSize(24);
    txt.setFont(rm.get_font());
    txt.setFillColor(sf::Color::Black);
}

void TextField::query_click(float x, float y) {
    if(box.getGlobalBounds().contains(x, y)) {
        focus = true;
        box.setOutlineThickness(5);
    }
    else {
        focus = false;
        box.setOutlineThickness(0);
    }
}

void TextField::text_entered(sf::Event & event) {
    if(!focus)
        return;
    char let = (char)event.text.unicode;
    if(let == '\b')
        content.pop_back();
    else
        content += let;
    txt.setString(content);
}

void TextField::draw(sf::RenderWindow & wndw) const {
    wndw.draw(box);
    wndw.draw(txt);
}

std::string TextField::get_content() const {
    return content;
}