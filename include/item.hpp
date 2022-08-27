#pragma once

#include <SFML/Graphics.hpp>
#include <string>

//class Player;

#include "player.hpp"
#include "map.hpp"
#include "system.hpp"

class Spell;

class Item
{
protected:
    std::string name;
    std::string description;
    sf::Texture texture;
    float price;

public:
    Item();
    virtual void use(System& system) = 0;
    sf::Sprite icon;
    void setPrice(float price);
    std::string getName();
    std::string getDesc();
    bool destroyOnUse=false;
    float id;
};

namespace item
{

class Weapon : public Item
{
protected:
    float damage;

public:
    Weapon();
    virtual void use(System& system) = 0;

    float cooldown;
};

class DirectionGun : public Weapon
{
public:
    DirectionGun();
    virtual void use(System& system);
};

class LaserGun : public Weapon
{
public:
    LaserGun();
    void use(System& system);
};

class RPG : public Weapon
{
public:
    RPG();
    void use(System& system);
};

class AR15 : public Weapon
{
public:
    AR15();
    void use(System& system);
};

class Consumable : public Item
{
public:
    Consumable();
    virtual void use(System& system) = 0;
};

class PotionI : public Consumable
{
public:
    PotionI();
    void use(System& system);
};

class PotionII : public Consumable
{
public:
    PotionII();
    void use(System& system);
};

class Wand : public Item
{
public:
    Wand();
    void use(System& system);
    void insert(Spell& spell, int pos);
    Spell& remove(int pos);
    int maxSpells;
    std::vector<Spell*> spells;
    std::vector<bool> empty;

private:
    std::vector<Spell*>::iterator it;
};

}

class Spell : public Item
{
public:
    Spell();
    virtual void use(System& system) = 0;
};

namespace spell
{

class testSpell : public Spell
{
public:
    testSpell();
    void use(System& system);
};

}
