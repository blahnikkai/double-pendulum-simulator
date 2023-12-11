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

const sf::Sprite & ImageButton::get_sprt() const {
    return sprt;
}

void ImageButton::draw(sf::RenderWindow & wndw) const {
    Button::draw(wndw);
    wndw.draw(sprt);
};