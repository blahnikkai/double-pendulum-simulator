#pragma once

class Clickable {
public:
    virtual ~Clickable() = default;
    virtual void query_click(int x, int y) = 0;
    virtual bool query_hover(int x, int y, sf::RenderWindow & wndw) = 0;
};
