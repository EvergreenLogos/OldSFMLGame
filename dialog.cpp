#include "include/dialog.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Player;

Dialog::Dialog(System& system)
{
    texture.loadFromFile("asset/texture/textbox.png");
    sprite.setTexture(texture);
    sprite.setPosition(system.player.x-282, system.player.y+110);
    font.loadFromFile("asset/Dustismo_Roman.ttf");
    currentMessage.setPosition(system.player.x-260, system.player.y+120);
}

void Dialog::addMessage(std::string string)
{
    strings.push_front(string);
    std::cout << "added message: " << string << std::endl;
}

void Dialog::next()
{
    std::cout << "dialog next" << std::endl;
    if (current==strings.size())
    {
        std::cout << "end dialog" << std::endl;
        end=true;
    }
    else
    {
        currentMessage.setString(*i);
        i++;
        current++;
        currentMessage.setFont(font);
        currentMessage.setCharacterSize(24);
        currentMessage.setColor(sf::Color::Black);
        currentMessage.setStyle(sf::Text::Bold);
    }
}

void Dialog::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
    window.draw(currentMessage);
}
