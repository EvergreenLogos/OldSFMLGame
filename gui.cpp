#include "include/gui.hpp"

#include "include/system.hpp"
#include "include/game.hpp"
//#include "include/inventory.hpp"
//#include "include/item.hpp"

//class Item;
//class Wand;
class Game;


GUI::GUI(System& system) : rect1(sf::Vector2f(410, 200)), rect2(sf::Vector2f(550, 100)), rect3(sf::Vector2f(32, 32)), slots(40, sf::Sprite(slotUnselected)), selectMenu(system.player)
{
    font.loadFromFile("asset/Dustismo_Roman.ttf");
    selectedName.setFont(font);
    selectedDesc.setFont(font);
    selectedName.setCharacterSize(24);
    selectedName.setColor(sf::Color::Black);
    selectedDesc.setCharacterSize(16);
    selectedDesc.setColor(sf::Color::Black);

    rect1.setOutlineColor(sf::Color::White);
    rect1.setOutlineThickness(5);
    rect1.setFillColor(sf::Color::Blue);
    rect2.setOutlineColor(sf::Color::White);
    rect2.setOutlineThickness(5);
    rect2.setFillColor(sf::Color::Blue);
    rect3.setOutlineColor(sf::Color::White);
    rect3.setOutlineThickness(5);
    rect3.setFillColor(sf::Color::Yellow);

    slotSelected.loadFromFile("asset/ui/box-selected.png");
    slotUnselected.loadFromFile("asset/ui/box-deselected.png");
    slot.setTexture(slotUnselected);

    for (int i=0; i!=40; i++)
    {
        slots.insert(slots.begin()+i, slot);
    }

    selectMenu.addOption(new UIOption("Select"));
    selectMenu.addOption(new UIOption("Cancel"));
}

void GUI::selectItem(System& system)
{
    int x=system.player.x-200;
    int y=system.player.y-100;

    rect1.setPosition(x-10, y-10);
    rect2.setPosition(system.player.x-240, system.player.y+100);
    system.game->mWindow.draw(rect1);
    system.game->mWindow.draw(rect2);
    if (system.inventory.selected->item!=NULL)
    {
        rect3.setPosition(system.inventory.selected->x, system.inventory.selected->y);
    }
    system.game->mWindow.draw(rect3);

    for (int i=0; i!=40; i++)
    {
        slots[i].setPosition(x, y);
        system.game->mWindow.draw(slots[i]);

        if (i==selected)
        {
            slots[i].setTexture(slotSelected);
        }
        else
        {
            slots[i].setTexture(slotUnselected);
        }

        if (i==9 || i==19 || i==29)
        {
            y+=50;
            x=system.player.x-200;
        }
        else
        {
            x+=40;
        }
    }

    x=system.player.x-200;
    y=system.player.y-100;

    for (int i=0; i!=40; i++)
    {
        if (!system.inventory.slots[i].empty)
        {
            system.inventory.slots[i].draw(system.game->mWindow, x, y);
        }

        if (i==9 || i==19 || i==29)
        {
            y+=50;
            x=system.player.x-200;
        }
        else
        {
            x+=40;
        }
    }

    selectMenu.draw(system.game->mWindow);

    if (selectMenu.activated)
    {
        selectMenu.activated=false;
        std::cout << "activated" << std::endl;
        if (selectMenu.currentSelected==0)
        {
            mode=0;
            transfer=true;
        }
        else if (selectMenu.currentSelected==1)
        {
            mode=0;
        }
    }
}

InventoryGUI::InventoryGUI(System& system) : GUI(system)
{
    label = "inventory";
}

void InventoryGUI::draw(System& system)
{
    //system.inventory.drawInventory(system);
}

/***WandGUI::WandGUI(System& system) : menu1(system.player), boxes(10, sf::Sprite(boxUnselected)), GUI(system)
{
    /***label = "wand";

    //game.currentUI=&menu1;
    menu1.addOption(new UIOption("Add Spell"));
    menu1.addOption(new UIOption("Bind Spell"));
    menu1.addOption(new UIOption("Exit"));

    boxSelected.loadFromFile("asset/ui/box-selected.png");
    boxUnselected.loadFromFile("asset/ui/box-deselected.png");
    box.setTexture(boxUnselected);

    //item::Wand* wand;

    wand = static_cast<item::Wand*>(system.inventory.selected->item);

    for (int i=0; i!=wand->maxSpells; i++)
    {
        boxes.insert(boxes.begin()+i, box);
    }
}

void WandGUI::draw(System& system)
{
    /***if (mode==0)
    {
        if (game.currentUI!=&menu1)
        {
            game.currentUI=&menu1;
        }
        menu1.draw(game.mWindow);

        if (menu1.activated)
        {
            menu1.activated=false;
            std::cout << "activated" << std::endl;
            if (menu1.currentSelected==0)
            {
                mode=1;
                game.currentUI=&selectMenu;
            }
            else if (menu1.currentSelected==1)
            {

            }
            else if (menu1.currentSelected==2)
            {
                GUI* toBeDeleted = this;
                game.currentGUI = NULL;
                delete toBeDeleted;
            }
        }

        for (int i=0; i!=wand->maxSpells; i++)
        {
            boxes[i].setPosition(game.player.x-230+(40*i), game.player.y-100);
            game.mWindow.draw(boxes[i]);
        }

        for (auto i=wand->spells.begin(); i!=wand->spells.end(); i++)
        {
            int it = std::distance(wand->spells.begin(), i);
            (*i)->icon.setPosition(game.player.x-230+(40*it), game.player.y-100);
            game.mWindow.draw((*i)->icon);
        }

        if (transfer)
        {
            transfer=false;
            //std::vector<Item*>* itemVector;
            //itemVector = reinterpret_cast<std::vector<Item*>*>(&wand->spells);
            game.inventory.transfer(*wand, selected);
        }
    }
    else if (mode==1)
    {
        selectItem(game);
    }
}***/

/***ShopGUI::ShopGUI(System& system) : menu1(system.player), boxes(10, sf::Sprite(boxUnselected)), GUI(system)
{
    mode = 0;

    menu1.addOption(new UIOption("Buy"));
    menu1.addOption(new UIOption("Sell"));
    menu1.addOption(new UIOption("Exit"));
}

void ShopGUI::draw(System& system)
{
    /***if (mode==0)
    {
        if (game.currentUI!=&menu1)
        {
            game.currentUI=&menu1;
        }
        menu1.draw(system.game->mWindow);

        if (menu1.activated)
        {
            menu1.activated=false;
            if (menu1.currentSelected==0)
            {
                mode=1;
            }
        }
    }
}
***/
