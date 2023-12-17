#pragma once
#include <SFML/Graphics.hpp>
#include "clickable.h"

class Button : public Clickable {

    std::function<void()> on_click;

protected:

    sf::RectangleShape bounds;

public:

    Button(float x, float y, int w, int h, const std::function<void()> & on_click);
    ~Button() override = default;
    void query_click(int x, int y) override;
    virtual void draw(sf::RenderWindow & wndw) const;
};
