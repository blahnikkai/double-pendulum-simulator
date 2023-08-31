#include "image_button.h"

ImageButton::ImageButton(float x, float y, int w, int h, const std::function<void()> & on_click, const sf::Texture & txtr) :
    Button(x, y, w, h, on_click)
{
    sprt.setTexture(txtr);
    auto txtr_sz = txtr.getSize();
    sprt.setScale((float)w / txtr_sz.x, (float)h / txtr_sz.y);
    sprt.setPosition(x, y);
}

sf::Sprite & ImageButton::get_sprt() {
    return sprt;
}

const sf::Sprite & ImageButton::get_sprt() const {
    return sprt;
};