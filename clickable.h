#pragma once

class Clickable {
public:
    virtual ~Clickable() = default;
    virtual void query_click(float x, float y) = 0;
};
