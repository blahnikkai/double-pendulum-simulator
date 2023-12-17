#include "image_button.h"

ImageButton::ImageButton(float x, float y, int w, int h, const std::function<void()> & on_click, const sf::Texture & txtr, float img_scale) :
    Button(x, y, w, h, on_click)
{
    sprt.setTexture(txtr);
    auto txtr_sz = txtr.getSize();
    sprt.setScale(img_scale * (float)w / (float)txtr_sz.x, img_scale * (float)h / (float)txtr_sz.y);
    sprt.setOrigin((float)txtr_sz.x / 2, (float)txtr_sz.y / 2);
    sprt.setPosition(x + (float)w / 2, y + (float)h / 2);
}

sf::Sprite & ImageButton::get_sprt() {
    return sprt;
}

bool ImageButton::query_hover(int x, int y, sf::RenderWindow & wndw) {
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

void ImageButton::draw(sf::RenderWindow & wndw) const {
    Button::draw(wndw);
    wndw.draw(sprt);
}