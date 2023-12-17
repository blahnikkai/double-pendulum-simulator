#pragma once
#include <SFML/Graphics.hpp>
#include "clickable.h"

class Button : public Clickable {

    std::function<void()> on_click;
    sf::Sprite sprt;
    sf::RectangleShape bounds;

public:

    Button(float x, float y, int w, int h, const std::function<void()> & on_click, const sf::Texture & txtr, float img_scale=1.);
    ~Button() override = default;
    void query_click(int x, int y) override;
    bool query_hover(int x, int y, sf::RenderWindow & wndw) override;
    virtual void draw(sf::RenderWindow & wndw) const;
    sf::Sprite & get_sprt();
};
