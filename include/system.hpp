#pragma once

#include <SFML/Graphics.hpp>

#include "inventory.hpp"
#include "map.hpp"
#include "player.hpp"

class AnimateA;

class TextIndicator
{
public:
    TextIndicator(sf::Font& font, std::string string, float x, float y, float angle, int scale);
    ~TextIndicator();

    float x, y, angle;
    int scale;
    int count=0;
    sf::Text text;
};

class System
{
public:
    System(Game& game);

    Player player;

    bool teleported;
    Entity* onlyUpdate;
    Inventory inventory;

    void update();
    void draw(sf::RenderWindow& window);

    void dealDamage(int amount, int type);
    void dealDamage(AnimateA& target, int amount, int type);

    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingLeft;
    bool mIsMovingRight;

    Game* game;

    Map map;

    sf::RectangleShape background;

    sf::Font font;

    void generateText(std::string text, float x, float y, int scale);

private:
    static System* sInstance;

    bool generateParticles = false;
    sf::Texture particleTexture;
    std::vector<sf::CircleShape> particles;


    std::vector<TextIndicator*> textIndicators;
};

