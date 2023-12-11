#include "resource_manager.h"

ResourceManager::ResourceManager() {
    std::vector<std::string> filename_lst = {"add.png", "clear.png", "pause.png", "play.png", "trace.png"};
    for(const std::string & filename : filename_lst) {
        sf::Texture txtr;
        if(!txtr.loadFromFile("resources/images/" + filename))
            throw std::runtime_error("Failed to load file: resources/images/" + filename);
        txtr.setSmooth(true);
        txtr_map.emplace(filename, txtr);
    }
    if(!font.loadFromFile("resources/DMSans-Regular.ttf"))
        throw std::runtime_error("Failed to load file: resources/DMSans-Regular.ttf");
}

const sf::Texture & ResourceManager::get(const std::string & filename) const {
    return txtr_map.at(filename);
}

const sf::Font & ResourceManager::get_font() const {
    return font;
}

