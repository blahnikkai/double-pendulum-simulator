#pragma once
#include <map>
#include <string>
#include <SFML/graphics.hpp>

class ResourceManager {
    std::map<std::string, sf::Texture> txtr_map;
    sf::Font font;
public:
    ResourceManager();
    const sf::Texture & get(const std::string & filename) const;
    const sf::Font & get_font() const;
};
