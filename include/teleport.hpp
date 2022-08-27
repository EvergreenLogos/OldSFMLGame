#pragma once

#include <SFML/Graphics.hpp>
#include <string>

//class Player;

#include "player.hpp"
#include "map.hpp"

class Teleport
{
private:
    sf::Texture texture;
    float x;
    float y;
    float destx;
    float desty;

    void checkIfBad(Map& map);

public:
    Teleport(float x, float y, int destID, int locID, float destx, float desty, std::string texture, sf::RenderWindow& window, Map* map);
    void draw(sf::RenderWindow& window);
    void use();
    void die(Map& map);
    sf::Sprite sprite;
    int destID;
    int locID;
};
