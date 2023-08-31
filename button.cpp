#include "button.h"

Button::Button(float x, float y, int w, int h, const std::function<void()> & on_click) :
    on_click(on_click)
{
    bounds.setPosition(x, y);
    bounds.setSize({(float)w, (float)h});
    bounds.setFillColor(sf::Color::White);
}

void Button::query_click(float x, float y) {
    if(bounds.getGlobalBounds().contains(x, y))
        on_click();
}

const sf::RectangleShape & Button::get_bounds() {
    return bounds;
}