#include "button.h"

Button::Button(float x, float y,
               int w, int h,
               const std::function<void()> & on_click,
               const sf::Texture & txtr,
               float img_scale) :
    on_click(on_click)
{
    bounds.setPosition(x, y);
    bounds.setSize({(float)w, (float)h});
    bounds.setFillColor(sf::Color::White);
    bounds.setOutlineThickness(2);
    bounds.setOutlineColor(sf::Color::Black);

    sprt.setTexture(txtr);
    auto txtr_sz = txtr.getSize();
    sprt.setScale(img_scale * (float)w / (float)txtr_sz.x, img_scale * (float)h / (float)txtr_sz.y);
    sprt.setOrigin((float)txtr_sz.x / 2, (float)txtr_sz.y / 2);
    sprt.setPosition(x + (float)w / 2, y + (float)h / 2);
}

void Button::query_click(int x, int y) {
    if(bounds.getGlobalBounds().contains(x, y))
        on_click();
}

bool Button::query_hover(int x, int y, sf::RenderWindow & wndw) {
    if(bounds.getGlobalBounds().contains(x, y)) {
        sprt.setColor(sf::Color(100, 100, 100));
        bounds.setFillColor(sf::Color(100, 100, 100));
        return true;
    }
    else {
        sprt.setColor(sf::Color::White);
        bounds.setFillColor(sf::Color::White);
        return false;
    }
}

void Button::draw(sf::RenderWindow & wndw) const {
    wndw.draw(bounds);
    wndw.draw(sprt);
}

sf::Sprite & Button::get_sprt() {
    return sprt;
}
