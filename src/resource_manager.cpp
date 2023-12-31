#include "resource_manager.h"
#include <unordered_map>

const std::vector<std::string> filename_lst = {"add.png", "clear.png", "pause.png", "play.png", "trace.png"};

ResourceManager::ResourceManager() {
    for(const std::string & filename : filename_lst) {
        sf::Texture txtr;
        if(!txtr.loadFromFile("src/resources/images/" + filename))
            throw std::runtime_error("Failed to load file: resources/images/" + filename);
        txtr.setSmooth(true);
        txtr_map.emplace(filename, txtr);
    }
    if(!font.loadFromFile("src/resources/DMSans-Regular.ttf"))
        throw std::runtime_error("Failed to load file: resources/DMSans-Regular.ttf");
}

const sf::Texture & ResourceManager::get_texture(const std::string & filename) const {
    return txtr_map.at(filename);
}

const sf::Font & ResourceManager::get_font() const {
    return font;
}
