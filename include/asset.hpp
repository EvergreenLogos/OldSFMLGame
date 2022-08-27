#pragma once

#include <SFML/Graphics.hpp>

class AssetManager
{
public:
    AssetManager();

    static sf::Texture& GetTexture(std::string const& filename);
    static sf::Texture& GetTexture(std::string const& filename, sf::IntRect rect);


private:
    std::map<std::string, sf::Texture> textures;

    static AssetManager* sInstance;
};
