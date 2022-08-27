#include <iostream>

#include "include/inventory.hpp"
#include "include/item.hpp"
#include "include/game.hpp"

Slot::Slot()
{

}

void Slot::insert(Item& item)
{
    this->item=&item;
    empty=false;
}

void Slot::draw(sf::RenderWindow& window, float x, float y)
{
    if (!empty)
    {
        item->icon.setPosition(x, y);
        window.draw(item->icon);
    }
    this->x=x;
    this->y=y;
}

Inventory::Inventory(Player& player, Map& map) : rect1(sf::Vector2f(410, 200)), rect2(sf::Vector2f(550, 100)), rect3(sf::Vector2f(32, 32)), ui(player), ui2(player), slotSprites(40, sf::Sprite(slotUnselected))
{
    this->player = &player;
    this->map = &map;

    font.loadFromFile("asset/Dustismo_Roman.ttf");
    selectedName.setFont(font);
    selectedDesc.setFont(font);
    selectedName.setCharacterSize(24);
    selectedName.setColor(sf::Color::Black);
    selectedDesc.setCharacterSize(16);
    selectedDesc.setColor(sf::Color::Black);

    slotSelected.loadFromFile("asset/ui/box-selected.png");
    slotUnselected.loadFromFile("asset/ui/box-deselected.png");
    slot.setTexture(slotUnselected);

    for (int i=0; i!=40; i++)
    {
        slotSprites.insert(slotSprites.begin()+i, slot);
    }

    rect1.setOutlineColor(sf::Color::White);
    rect1.setOutlineThickness(5);
    rect1.setFillColor(sf::Color::Blue);
    rect2.setOutlineColor(sf::Color::White);
    rect2.setOutlineThickness(5);
    rect2.setFillColor(sf::Color::Blue);
    rect3.setOutlineColor(sf::Color::White);
    rect3.setOutlineThickness(5);
    rect3.setFillColor(sf::Color::Yellow);

    ui.addOption(new UIOption("Exit"));
    ui.addOption(new UIOption("Use"));
    ui.addOption(new UIOption("Drop"));
    ui.addOption(new UIOption("Equip"));

    ui2.addOption(new UIOption("Slot 1 (X)"));
    ui2.addOption(new UIOption("Slot 2 (C)"));
}

void Inventory::insert(Item* item)
{
    for (int i=0; i!=40; i++)
    {
        if (slots[i].empty)
        {
            slots[i].insert(*item);
            std::cout << "inserted " << slots[i].item->getName() << " to slot " << i << std::endl;
            break;
        }
    }
}

void Inventory::drop(int slot)
{
    if (!slots[slot].empty)
    {
        std::cout << "removed " << slots[slot].item->getName() << " from slot " << slot << std::endl;
        slots[slot].item=NULL;
        delete slots[slot].item;
        slots[slot].empty=true;
    }
}

void Inventory::drawInventory(System& system)
{
    int x=player->x-200;
    int y=player->y-100;

    //rect1.setPosition(x-10, y-10);
    rect2.setPosition(player->x-240, player->y+100);
    //game.mWindow.draw(rect1);
    system.game->mWindow.draw(rect2);
    /***if (selected->item!=NULL)
    {
        rect3.setPosition(selected->x, selected->y);
    }
    game.mWindow.draw(rect3);***/

    for (int i=0; i!=40; i++)
    {
        if (slots[i].item==NULL)
        {
            slots[i].empty=true;
        }

        if (i==currentSelected)
        {
            slotSprites[i].setTexture(slotSelected);
        }
        else
        {
            slotSprites[i].setTexture(slotUnselected);
        }

        slotSprites[i].setPosition(x, y);
        system.game->mWindow.draw(slotSprites[i]);

        if (!slots[i].empty)
        {
            slots[i].draw(system.game->mWindow, x, y);
        }

        if (i==9 || i==19 || i==29)
        {
            y+=40;
            x=player->x-200;
        }
        else
        {
            x+=40;
        }
    }

    currentUI->draw(system.game->mWindow);

    if (!selected->empty)
    {
        selectedName.setString(selected->item->getName() + " (slot: " + std::to_string(currentSelected) + ")");
        selectedDesc.setString(selected->item->getDesc());
    }
    else
    {
        selectedName.setString("Empty (slot: " + std::to_string(currentSelected) + ")");
        selectedDesc.setString("");
    }

    selectedName.setPosition(player->x-200, player->y+100);
    selectedDesc.setPosition(player->x-230, player->y+150);
    system.game->mWindow.draw(selectedName);
    system.game->mWindow.draw(selectedDesc);

    if (currentUI->activated)
    {
        currentUI->activated=false;
        std::cout << "activated" << std::endl;
        if (currentUI==&ui)
        {
            if (ui.currentSelected==0)
            {
                visible=false;
            }
            else if (ui.currentSelected==1)
            {
                selected->item->use(system);
                if (selected->item->destroyOnUse)
                {
                    selected->empty=true;
                    drop(currentSelected);
                }
            }
            else if (ui.currentSelected==2)
            {
                drop(currentSelected);
                selected->empty=true;
            }
            else if (ui.currentSelected==3)
            {
                currentUI=&ui2;
            }
            else if (ui.currentSelected==4)
            {
                if (system.inventory.selected->item->id==10)
                {
                    /***GUI* toBeDeleted = game.currentGUI;
                    game.currentGUI = NULL;
                    delete toBeDeleted;
                    game.inventory.currentUI=&game.inventory.ui;
                    game.currentGUI = new WandGUI(game);
                    game.currentGUI->draw(game);***/
                }
            }
        }
        else if (currentUI==&ui2)
        {
            if (ui2.currentSelected==0)
            {
                Item* item1=selected->item;
                Item* item2=player->weapon1;
                selected->item=NULL;
                player->weapon1=NULL;
                selected->item=item2;
                player->weapon1=item1;
            }
            else if (ui2.currentSelected==1)
            {
                Item* item1=selected->item;
                Item* item2=player->weapon2;
                selected->item=NULL;
                player->weapon2=NULL;
                selected->item=item2;
                player->weapon2=item1;
            }
        }
    }
}

/***void Inventory::transfer(item::Wand& destination, int slot)
{
    Item* toTransfer;
    toTransfer = slots[slot].item;
    Spell* spell;
    spell = static_cast<Spell*>(toTransfer);
    slots[slot].item=NULL;

    //destination.spells.insert(destination.spells.begin(), wand);
    destination.spells.push_back(spell);
    std::cout << destination.spells.size() << std::endl;
}***/
