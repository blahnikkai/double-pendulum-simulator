#include "text_field.h"

TextField::TextField(float x, float y, float h, const ResourceManager & rm) :
    focus(false)
{
    box.setPosition(x, y);
    box.setSize({TEXTFIELD_W, h});
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(2);
    txt.setPosition(x, y);
    txt.setCharacterSize(TEXT_SIZE);
    txt.setFont(rm.get_font());
    txt.setFillColor(sf::Color::Black);
}

void TextField::query_click(int x, int y) {
    if(box.getGlobalBounds().contains(x, y)) {
        focus = true;
        box.setOutlineColor(sf::Color::Blue);
    }
    else {
        focus = false;
        box.setOutlineColor(sf::Color::Black);
    }
}

void TextField::text_entered(sf::Event & event) {
    if(!focus)
        return;
    char let = (char)event.text.unicode;
    if(let == '\b')
        content.pop_back();
    else if(std::isdigit(let))
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