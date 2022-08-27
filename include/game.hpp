#pragma once

#include <SFML/Graphics.hpp>
#include <STP/TMXLoader.hpp>
#include <set>
#include <iostream>
#include <string>

#include "system.hpp"
#include "asset.hpp"

class Game;

class Screen
{
public:
    Screen(Game& game);

    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void handlePlayerInput(sf::Keyboard::Key key, bool isPressed) = 0;

    Game* game;
};

class Screen0 : public Screen
{
public:
    Screen0(Game& game);

    void update();
    void draw(sf::RenderWindow& window);
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    float getFPS(const sf::Time& time)
    {
        return (1000000.0f / time.asMicroseconds());
    }

    sf::FloatRect screen;

private:

    System system;

    sf::Texture mTexture;
    sf::Sprite mPlayer;
    sf::View camera;
    sf::Font font;

    sf::Texture bgTexture;
    //sf::Sprite background;

    sf::Text health;
    sf::Text charge;
    sf::Text coordinates;
    sf::Text framerate;

    sf::Texture keyTexture0;
    sf::Texture keyTexture1;
    sf::Texture keyTexture2;
    sf::Texture keyTexture3;
    sf::Texture keyTexture4;
    sf::Texture keyTexture5;
    sf::Sprite key0;
    sf::Sprite key1;
    sf::Sprite key2;
    sf::Sprite key3;
    sf::Sprite key4;
    sf::Sprite key5;

    sf::Clock FPSClock;

    bool pause = false;
    int pauseCooldown = 0;
    int fpsCooldown = 0;
    int keyCooldown = 0;


    sf::RectangleShape* background;
};

class Game
{
private:
    AssetManager manager;
    std::vector<Screen*> screens;

    Screen0 mainScreen;

public:
    Game();
    void run();
    sf::RenderWindow mWindow;
    /***Player player;

    bool teleported=false;
    Entity* onlyUpdate;
    bool dialog = false;
    Dialog* currentDialog;
    UI* currentUI=NULL;
    GUI* currentGUI=NULL;
    Inventory inventory;

    sf::FloatRect screen;
    sf::RectangleShape background;

    //sf::RenderWindow unmoving;***/

    sf::FloatRect* screen;

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void drawAllEntities();
    void render();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    float getFPS(const sf::Time& time)
    {
        return (1000000.0f / time.asMicroseconds());
    }

private:

    /***sf::Texture mTexture;
    sf::Sprite mPlayer;
    sf::View camera;
    sf::Font font;

    sf::Texture bgTexture;
    //sf::Sprite background;

    sf::Text health;
    sf::Text charge;
    sf::Text coordinates;
    sf::Text framerate;

    sf::Texture keyTexture0;
    sf::Texture keyTexture1;
    sf::Texture keyTexture2;
    sf::Texture keyTexture3;
    sf::Texture keyTexture4;
    sf::Texture keyTexture5;
    sf::Sprite key0;
    sf::Sprite key1;
    sf::Sprite key2;
    sf::Sprite key3;
    sf::Sprite key4;
    sf::Sprite key5;***/

    /***sf::Clock FPSClock;

    Map map;

    bool mIsMovingUp = false;
    bool mIsMovingDown = false;
    bool mIsMovingLeft = false;
    bool mIsMovingRight = false;

    bool pause = false;
    int pauseCooldown = 0;
    int fpsCooldown = 0;
    int keyCooldown = 0;

    bool generateParticles = false;
    sf::Texture particleTexture;
    std::vector<sf::CircleShape> particles;***/


};
