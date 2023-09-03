#pragma once

class Clickable {
public:
    virtual ~Clickable() = default;
    virtual void query_click(int x, int y) = 0;
};
