#pragma once

#include <SFML/Graphics.hpp>
#include <STP/TMXLoader.hpp>
#include <set>
#include <iostream>
#include <string>
#include <list>

class Map;
class Player;
class Item;
class System;
class Game;


class Entity
{
public:
    Entity(System& system, float x, float y);
    ~Entity();
    virtual void update();
    void draw(sf::RenderWindow& window);
    virtual void die();
    bool checkPlayerProximity(float distance);
    sf::Sprite sprite;
    sf::Vector2f velocity;

    float x;
    float y;

    int lifespan;
    int count;

    bool dead = false;
    bool solid = false;

    bool canDamage = false;
    bool canReceiveDamage = false;

    bool inProximity = false;
    bool inCloseProximity = false;
    bool testCloseProximity = false;

    sf::Rect<float> hitbox;

protected:
    sf::Texture texture;

    System* system;
};

class AnimateA : public Entity
{
public:
    AnimateA(System& system, float x, float y, int hp, int hpmax, int lvl);
    ~AnimateA();
    void update();
    void die(System& system);

    int hp;
    int hpmax;
    int lvl;
};

class AnimateB : public AnimateA
{
public:
    AnimateB(System& system, float x, float y, int hp, int hpmax, int lvl);
    ~AnimateB();
    void update();
    bool checkFloor();

    bool flying;

private:
    int prevx, prevy;
    bool floor;
};

class HostileA : public AnimateA
{
public:
    HostileA(System& system, float x, float y, int hp, int hpmax, int lvl);
    ~HostileA();
    void update();

protected:
    int contactDamage;
    int damageType; // 0: Contact, 1: Blade, 2: Projectile, 3: Explosion, 4: Magic, 5: Critical
    std::array<float, 5> resist;
};

class HostileB : public AnimateB
{
public:
    HostileB(System& system, float x, float y, int hp, int hpmax, int lvl);
    ~HostileB();
    void update();

protected:
    int contactDamage;
    int damageType; // 0: Contact, 1: Blade, 2: Projectile, 3: Explosion, 4: Magic, 5: Critical
    std::array<float, 5> resist;
};

namespace entity
{

class Projectile : public Entity
{
public:
    Projectile(System& system, float x, float y, double speed, double angle, int damage, int shotType);
    ~Projectile();
    void update();

    sf::Rect<float> hitbox;

    int lifespan;
    int count;

protected:
    float dx, dy;
    int shotType;
    int damage;
    int damageType;

};

class PlayerProjectile : public Projectile
{
public:
    PlayerProjectile(System&, float x, float y, double speed, double angle, int damage, int shotType);
    ~PlayerProjectile();
    void update();
};

class EnemyProjectile : public Projectile
{
public:
    EnemyProjectile(System& system, float x, float y, double speed, double angle, int damage, int shotType);
    ~EnemyProjectile();
    void update();
};

class Fairy : public HostileB
{
public:
    Fairy(System& system, float x, float y, int hp, int hpmax, int lvl, int type);
    ~Fairy();
    void update();

protected:
    int type;
};

class Penguin : public AnimateA
{
public:
    Penguin(System& system, float x, float y, int hp, int hpmax, int lvl);
    ~Penguin();
    void update();
};

class Shop : public Entity
{
private:
    std::set<Item*> items;
    sf::Texture texture1;
    sf::Sprite box1;

public:
    Shop(System& system, float x, float y);
    void addItem(Item* item, float price);
    void use();
};

/***class HSpikeBall : public HostileB
{
private:
    //bool checkCollision(Map& map, std::string direction);
    sf::Vector2f velocity;
    bool collision = false;
public:
    HSpikeBall(Map& map, float x, float y, int hp, int hpmax);
    virtual void update(Map& map);

    int dir=0;
};

class VSpikeBall : public HostileB
{
private:
    sf::Vector2f velocity;
    bool collision = false;
public:
    VSpikeBall(Map& map, float x, float y, int hp, int hpmax);
    virtual void update(Map& map);

    int dir=0;
};***/

class Explosion : public HostileA
{
public:
    Explosion(System& system, float x, float y, int size);
    ~Explosion();
    void update();
};

class Cannon : public HostileA
{
public:
    Cannon(System& system, float x, float y, int type);
    ~Cannon();
    double getAngle(float x, float y);
    void update();

    int dir=0;
    int type;
};

/***class Sign : public Entity
{
private:
    std::list<std::string> strings;
    Game* game;
    //std::list<std::string>::reverse_iterator i = strings.rbegin();

public:
    Sign(Map& map, float x, float y, std::string path, Game& game);
    void addString(std::string);
    void read();
};

class Chest : public Entity
{
private:
    bool money=false;
    bool empty=false;
    Item* item=nullptr;
    int amount=0;

public:
    Chest(Map& map, float x, float y, bool money, int amount, Item* item, int type);
    void update(Map& map);
    void open();
};***/

class Key : public Entity
{
private:
    int color;

public:
    Key(System& system, float x, float y, int color);
    void update();
};

class SolidLock : public Entity
{
private:
    sf::RectangleShape rectangle;
    std::array<bool, 5> color;

public:
    SolidLock(System& system, float x, float y, float width, float height, int color);
    void update();
};

class FallingPlatform : public Entity
{
private:
    sf::FloatRect top;
    int count=0;
    bool falling=false;
    int type;
    float respawnX;
    float respawnY;
    bool counting=false;

public:
    FallingPlatform(System& system, float x, float y, int type);
    void update();
};

}
