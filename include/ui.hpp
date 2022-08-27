#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Player;

class UIOption
{
private:
    sf::Texture buttonUnselected;
    sf::Texture buttonSelected;
    sf::Sprite button;
    sf::Font font;
    sf::Text text;

public:
    UIOption(std::string text);
    void draw(sf::RenderWindow& window, float x, float y);

    bool selected=false;
};

class UI
{
private:
    std::vector<UIOption> options;
    sf::RectangleShape rect1;

    Player* player;

public:
    UI(Player& player);
    void addOption(UIOption* option);
    void removeOption(int number);
    void draw(sf::RenderWindow& window);
    void selectNext();
    void selectPrevious();
    int getSize();

    UIOption* currentOption;
    int currentSelected=0;
    bool activated=false;
};
