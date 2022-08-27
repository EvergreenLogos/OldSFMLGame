#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <vector>

#include "ui.hpp"

class System;
class Item;
class Map;

class Slot
{
public:
    Item* item;
    Slot();
    void insert(Item& item);
    void draw(sf::RenderWindow& window, float x, float y);

    bool empty=true;
    float x;
    float y;
};

class Inventory
{
private:
    Player* player;
    Map* map;

    sf::Font font;
    sf::Text selectedName;
    sf::Text selectedDesc;
    sf::RectangleShape rect1;
    sf::RectangleShape rect2;
    sf::RectangleShape rect3;

    sf::Texture slotSelected;
    sf::Texture slotUnselected;
    sf::Sprite slot;
    std::vector<sf::Sprite> slotSprites;

public:
    std::array<Slot, 40> slots;

    Inventory(Player& player, Map& map);
    void insert(Item* item);
    void drop(int slot);
    void drawInventory(System& system);
    //void transfer(item::Wand& destination, int slot);
    bool visible=false;

    Slot* selected = &slots[0];
    UI ui;
    UI ui2;
    UI* currentUI = &ui;
    int currentSelected = 0;
};
