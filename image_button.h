#pragma once
#include <utility>
#include "button.h"

class ImageButton : public Button {
    sf::Sprite sprt;
    std::function<void()> on_click;

public:
    ImageButton(float x, float y, int w, int h, const std::function<void()> & on_click, const sf::Texture & txtr);
    sf::Sprite & get_sprt();
    const sf::Sprite & get_sprt() const;
};
