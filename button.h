#pragma once
#include <SFML/Graphics.hpp>
#include "clickable.h"

class Button : public Clickable {
    sf::RectangleShape bounds;
    std::function<void()> on_click;
public:
    Button(float x, float y, int w, int h, const std::function<void()> & on_click);
    ~Button() override = default;
    void query_click(int x, int y) override;
    const sf::RectangleShape & get_bounds();
    virtual void draw(sf::RenderWindow & wndw) const;
};
