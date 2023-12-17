#include "util.h"

float deg_to_rad(float deg) {
    return deg * PI / 180;
}
float rad_to_deg(float rad) {
    return rad * 180 / PI;
}
sf::Color random_clr() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(50, 255);
    int r = distribution(gen);
    int g = distribution(gen);
    int b = distribution(gen);
    return sf::Color(r, g, b);
};
