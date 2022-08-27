#include "include/ui.hpp"

#include <iostream>

UIOption::UIOption(std::string text)
{
    //rect1.setOutlineColor(sf::Color::White);
    //rect1.setOutlineThickness(5);
    //rect1.setFillColor(sf::Color::Blue);
    buttonUnselected.loadFromFile("asset/ui/button-deselected.png");
    buttonSelected.loadFromFile("asset/ui/button-selected.png");

    font.loadFromFile("asset/Dustismo_Roman.ttf");

    this->text.setFont(font);
    this->text.setCharacterSize(18);
    this->text.setColor(sf::Color::Black);
    this->text.setString(text);
}

void UIOption::draw(sf::RenderWindow& window, float x, float y)
{
    if (selected)
    {
        button.setTexture(buttonSelected);
    }
    else
    {
        button.setTexture(buttonUnselected);
    }

    button.setPosition(x, y);
    window.draw(button);
    this->text.setPosition(x+12, y+8);
    window.draw(this->text);
}

UI::UI(Player& player)
{
    this->player=&player;
}

void UI::addOption(UIOption* option)
{
    options.push_back(*option);
    currentOption=&options[0];
    for (std::vector<UIOption>::iterator i=options.begin(); i!=options.end(); i++)
    {
        (*i).selected=false;
    }
    currentOption->selected=true;
}

void UI::removeOption(int number)
{
    //UIOption* toBeDeleted = &options[number];
    options.erase(options.begin()+number);
    //delete toBeDeleted;
}

void UI::selectNext()
{
    if (currentSelected!=getSize()-1)
    {
        currentSelected+=1;
        std::cout << "current selected " << currentSelected << std::endl;
        currentOption=&options[currentSelected];
    }
    for (std::vector<UIOption>::iterator i=options.begin(); i!=options.end(); i++)
    {
        (*i).selected=false;
    }
    currentOption->selected=true;
}

void UI::selectPrevious()
{
    if (currentSelected!=0)
    {
        currentSelected-=1;
        std::cout << "current selected " << currentSelected << std::endl;
        currentOption=&options[currentSelected];
    }
    for (std::vector<UIOption>::iterator i=options.begin(); i!=options.end(); i++)
    {
        (*i).selected=false;
    }
    currentOption->selected=true;
}

void UI::draw(sf::RenderWindow& window)
{
    /***int x=player->x+200;
    int y=player->y-100;

    for (std::vector<UIOption>::iterator i=options.begin(); i!=options.end(); i++)
    {
        (*i).draw(window, x, y);
        y+=40;
    }***/
}

int UI::getSize()
{
    return options.size();
}
