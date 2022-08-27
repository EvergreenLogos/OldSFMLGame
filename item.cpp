#include "include/item.hpp"
#include "include/entity.hpp"

#include <iostream>

Item::Item()
{

}

void Item::setPrice(float price)
{
    this->price=price;
}

std::string Item::getName()
{
    return name;
}

std::string Item::getDesc()
{
    return description;
}

item::Weapon::Weapon()
{

}

item::DirectionGun::DirectionGun()
{
    texture.loadFromFile("asset/texture/gun1.png");
    icon.setTexture(texture);
    name="Direction Gun";
    description="This kind of gun shoots different shots depending on the direction it is facing.";
}

void item::DirectionGun::use(System& system)
{
    if (system.player.dir==0)
    {
        std::cout << "shot the direction gun left" << std::endl;
        new entity::PlayerProjectile(system, system.player.x+32, system.player.y+32, 10.f, 180, 12, 0);
        new entity::PlayerProjectile(system, system.player.x+32, system.player.y+32, 10.f, 175, 12, 0);
        new entity::PlayerProjectile(system, system.player.x+32, system.player.y+32, 10.f, 185, 12, 0);
    }
    if (system.player.dir==1)
    {
        std::cout << "shot the direction gun right" << std::endl;
        new entity::PlayerProjectile(system, system.player.x+32, system.player.y+32, 7.5, 0, 20, 1);
    }
}

item::LaserGun::LaserGun()
{
    texture.loadFromFile("asset/texture/gun2.png");
    icon.setTexture(texture);
    name="Laser Gun";
    description="This kind of gun shoots lasers.";
}

void item::LaserGun::use(System& system)
{
    if (system.player.dir==0)
    {
        std::cout << "shot the laser gun left" << std::endl;
        new entity::PlayerProjectile(system, system.player.x+32, system.player.y+32, -10.f, 0.f, 20, 2);
    }
    if (system.player.dir==1)
    {
        std::cout << "shot the laser gun right" << std::endl;
        new entity::PlayerProjectile(system, system.player.x+32, system.player.y+32, 7.5, 0.f, 20, 2);
    }
}

item::RPG::RPG()
{
    texture.loadFromFile("asset/texture/rpg.png");
    icon.setTexture(texture);
    name="RPG";
    description="Rocket Propelled Grenade. Shoots a projectile that expodes after a few seconds";
}

void item::RPG::use(System& system)
{
    if (system.player.dir==0)
    {
        std::cout << "shot the RPG left" << std::endl;
        new entity::PlayerProjectile(system, system.player.x+32, system.player.y+8, -10.f, 0.f, 15, 3);
    }
    if (system.player.dir==1)
    {
        std::cout << "shot the RPG right" << std::endl;
        new entity::PlayerProjectile(system, system.player.x+32, system.player.y+8, 7.5, 0.f, 15, 3);
    }
}

item::AR15::AR15()
{
    texture.loadFromFile("asset/texture/gun3.png");
    icon.setTexture(texture);
    name="AR-15";
    description="Semi-automatic assault rifle.";
}

void item::AR15::use(System& system)
{
    if (system.player.dir==0)
    {
        std::cout << "shot the AR-15 left" << std::endl;
        new entity::PlayerProjectile(system, system.player.x+32, system.player.y+24, -13.f, 0.f, 15, 4);
    }
    if (system.player.dir==1)
    {
        std::cout << "shot the AR-15 right" << std::endl;
        new entity::PlayerProjectile(system, system.player.x+32, system.player.y+24, 13, 0.f, 15, 4);
    }
}

item::Consumable::Consumable()
{

}

item::PotionI::PotionI()
{
    texture.loadFromFile("asset/texture/items1.png", sf::IntRect(192, 256, 32, 32));
    icon.setTexture(texture);
    name="Potion I";
    description="Restores 50 HP.";
    destroyOnUse=true;
}

void item::PotionI::use(System& system)
{
    system.player.hp+=50;
    if (system.player.hp>system.player.hpmax)
    {
        system.player.hp=system.player.hpmax;
    }
}

item::PotionII::PotionII()
{
    texture.loadFromFile("asset/texture/items1.png", sf::IntRect(192, 256, 32, 32));
    icon.setTexture(texture);
    name="Potion II";
    description="Restores 250 HP.";
    destroyOnUse=true;
}

item::Wand::Wand()
{
    texture.loadFromFile("asset/texture/items1.png", sf::IntRect(192, 160, 32, 32));
    icon.setTexture(texture);
    name="Wand";
    description="Test wand";
    id=10.0;
    maxSpells=10;
}

void item::Wand::use(System& system)
{

}

void item::Wand::insert(Spell& spell, int pos)
{
    for (it = spells.begin(); it != spells.end(); it++)
    {
        if ((*it)!=NULL)
        {
            spells.insert(it, &spell);
        }
    }
}

Spell& item::Wand::remove(int pos)
{

}

void item::PotionII::use(System& system)
{
    system.player.hp+=250;
    if (system.player.hp>system.player.hpmax)
    {
        system.player.hp=system.player.hpmax;
    }
}

Spell::Spell()
{

}

spell::testSpell::testSpell()
{
    texture.loadFromFile("asset/texture/items1.png", sf::IntRect(64, 352, 32, 32));
    icon.setTexture(texture);
    name="Spell";
    description="Test spell";
}

void spell::testSpell::use(System& system)
{

}
