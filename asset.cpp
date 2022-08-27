#include <iostream>
//#include <SFML/Graphics>
#include <assert.h>

#include "include/asset.hpp"

AssetManager* AssetManager::sInstance = nullptr;

AssetManager::AssetManager()
{
    assert(sInstance==nullptr);
    sInstance=this;
    std::cout<<"constructed"<<std::endl;
}

sf::Texture& AssetManager::GetTexture(std::string const& filename)
{
    auto& texMap = sInstance->textures;

    auto pairFound = texMap.find(filename);

    if (pairFound != texMap.end())
    {
        return pairFound->second;
    }
    else
    {
        auto& texture = texMap[filename];
        texture.loadFromFile(filename);
        return texture;
    }
}

sf::Texture& AssetManager::GetTexture(std::string const& filename, sf::IntRect rect)
{
    auto& texMap = sInstance->textures;

    auto pairFound = texMap.find(filename);

    if (pairFound != texMap.end())
    {
        return pairFound->second;
    }
    else
    {
        auto& texture = texMap[filename];
        texture.loadFromFile(filename, rect);
        return texture;
    }
}
