#pragma once
#include <map>
#include <string>
#include <SFML/Graphics.hpp>

class ResourceManager {

    std::map<std::string, sf::Texture> txtr_map;
    sf::Font font;

public:

    ResourceManager();
    const sf::Texture & get_texture(const std::string & filename) const;
    const sf::Font & get_font() const;
};
