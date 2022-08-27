#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include "system.hpp"

//class Player;

class Dialog
{
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Font font;
    sf::Text currentMessage;

    std::list<std::string> strings;
    std::list<std::string>::reverse_iterator i = strings.rbegin();
    int current=0;

public:
    Dialog(System& system);
    void addMessage(std::string string);
    void next();
    void draw(sf::RenderWindow& window);

    bool end=false;
};
