#pragma once

#include <SFML/Graphics.hpp>
#include <STP/TMXLoader.hpp>
#include <string.h>
#include <math.h>

class Weapon;
class Map;
class Item;

class Player
{
public:
    Player();
    void update(Map& map);
    void move(float dx, float dy);
    void draw(sf::RenderWindow& window);
    void interact(Map& map);

    std::vector<sf::Vector2i> tiles;

    float bottom, left, right, top;

    sf::Sprite sprite;
    sf::Rect<float> hitbox;
    //sf::Rect<float> floor;
    sf::Vector2f velocity;

    sf::FloatRect hitboxTop;
    sf::FloatRect hitboxBottom;
    sf::FloatRect hitboxLeft;
    sf::FloatRect hitboxRight;

    float x=10.f;
    float y=200.f;
    float prevx;
    float prevy;
    float respawnx;
    float respawny;

    int dir;

    bool collision = false;
    bool floor = false;
    bool jumping = false;
    bool moving = false;

    bool stun=false;
    bool sprint=false;

    bool collisionTop=false;
    bool collisionBottom=false;
    bool collisionLeft=false;
    bool collisionRight=false;

    int hp;
    int hpmax;
    int ch;
    int mon;

    Item* weapon1;
    Item* weapon2;

    std::array<bool, 5> keys;

    bool iframes = false;

private:
    sf::Texture texture;

    bool checkFloor(Map& map);

    int jumpCounter=0;
    int fallSpeed;
    int iframesCount;
    int animCount=0;
};
