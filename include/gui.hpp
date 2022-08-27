#pragma once

#include <SFML/Graphics.hpp>

class System;

//class Wand;
#include "ui.hpp"

class GUI
{
private:
    sf::Font font;
    sf::Text selectedName;
    sf::Text selectedDesc;
    sf::RectangleShape rect1;
    sf::RectangleShape rect2;
    sf::RectangleShape rect3;

protected:
    sf::Texture slotSelected;
    sf::Texture slotUnselected;
    sf::Sprite slot;

    std::vector<sf::Sprite> slots;

    bool transfer=false;
    UI selectMenu;

public:
    GUI(System& system);
    virtual void draw(System& system) = 0;
    void selectItem(System& system);
    std::string label;

    int selected=0;
    int mode=0;
};

class InventoryGUI : public GUI
{
public:
    InventoryGUI(System& system);
    void draw(System& system);
};

/***class WandGUI : public GUI
{
private:
    UI menu1;

    std::vector<sf::Sprite> boxes;

    item::Wand* wand;
    sf::Texture boxSelected;
    sf::Texture boxUnselected;
    sf::Sprite box;

public:
    WandGUI(System& system);
    void draw(System& system);
};***/

/***class ShopGUI : public GUI
{
private:
    UI menu1;

    std::vector<sf::Sprite> boxes;

    entity::Shop* shop;
    sf::Texture boxSelected;
    sf::Texture boxUnselected;
    sf::Sprite box;


public:
    ShopGUI(System& system);
    void draw(System& System);
};***/
