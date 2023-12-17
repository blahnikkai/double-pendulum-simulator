#pragma once
#include <utility>
#include "button.h"

class ImageButton : public Button {
    sf::Sprite sprt;
    std::function<void()> on_click;

public:
    ImageButton(float x, float y, int w, int h, const std::function<void()> & on_click, const sf::Texture & txtr, float img_scale=1.);
    sf::Sprite & get_sprt();
    bool query_hover(int x, int y, sf::RenderWindow & wndw) override;
    void draw(sf::RenderWindow & wndw) const override;
};
