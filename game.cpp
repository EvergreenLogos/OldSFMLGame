#include <SFML/Graphics.hpp>
#include <STP/TMXLoader.hpp>
#include <set>
#include <iostream>
#include <string>

#include "include/map.hpp"
#include "include/player.hpp"
#include "include/game.hpp"
#include "include/teleport.hpp"
#include "include/item.hpp"

Screen::Screen(Game& game)
{
    this->game=&game;
}

Screen0::Screen0(Game& game) : Screen(game), system(game)
{
    game.screen = &screen;

    mTexture.loadFromFile("asset/texture/Eagle.png");
    mPlayer.setTexture(mTexture);
    font.loadFromFile("asset/Dustismo_Roman.ttf");

    health.setFont(font);
    health.setCharacterSize(24);
    health.setColor(sf::Color::White);
    health.setStyle(sf::Text::Bold);

    coordinates.setFont(font);
    coordinates.setCharacterSize(14);
    coordinates.setColor(sf::Color::White);
    coordinates.setStyle(sf::Text::Bold);

    framerate.setFont(font);
    framerate.setCharacterSize(14);
    framerate.setColor(sf::Color::White);
    framerate.setStyle(sf::Text::Bold);

    std::cout<<"main screen initialized"<<std::endl;
}

void Screen0::update()
{
    system.update();

    int cameraX = system.player.x+32;
    int cameraY = system.player.y+32;

    sf::FloatRect cameraRect = camera.getViewport();

    if ((cameraY-285)<0)
    {
        cameraY=(abs(cameraRect.top-0))+285;
    }
    else if ((cameraY+285)>(system.map.getMap().GetHeight()*32))
    {
        cameraY=(abs(cameraRect.top-(system.map.getMap().GetHeight()*32)))-285;
    }
    if ((cameraX-410)<0)
    {
        cameraX=(abs(cameraRect.left-0))+410;
    }
    else if ((cameraX+410)>(system.map.getMap().GetWidth()*32))
    {
        cameraX=(abs(cameraRect.left-(system.map.getMap().GetWidth()*32)))-410;
    }
    screen.top = cameraY-285;
    screen.left = cameraX-410;
    camera.setCenter(sf::Vector2f(cameraX, cameraY));
    //camera.setSize(sf::Vector2f(640, 480));
    //camera.setSize(sf::Vector2f(710, 533));
    camera.setSize(sf::Vector2f(820, 570));


}

void Screen0::draw(sf::RenderWindow& window)
{
    window.setView(camera);

    system.draw(window);



    //for (auto& o : map.teleports)
    //    static_cast<Teleport*>(o)->draw(mWindow);

    //mWindow.draw(mPlayer);

    //player.draw(mWindow);
    health.setString("Health: " + std::to_string(system.player.hp) + "/" + std::to_string(system.player.hpmax) + " Money: " + std::to_string(system.player.mon));
    health.setPosition(screen.left+50, screen.top+30);
    window.draw(health);
    coordinates.setString("Room: " + std::to_string(system.map.currentID) + "\nX: " + std::to_string(system.player.x) + " Y: " + std::to_string(system.player.y));
    coordinates.setPosition(screen.left+50, screen.top+520);
    window.draw(coordinates);
    key0.setPosition(system.player.x-100, system.player.y+230);
    key1.setPosition(system.player.x-70, system.player.y+230);
    key2.setPosition(system.player.x-40, system.player.y+230);
    key3.setPosition(system.player.x-10, system.player.y+230);
    key4.setPosition(system.player.x+20, system.player.y+230);
    key5.setPosition(system.player.x+50, system.player.y+230);
    for (int i=0; i!=6; i++)
    {
        if (system.player.keys[i])
        {
            switch (i)
            {
            case 0:
                window.draw(key0);
                break;
            case 1:
                window.draw(key1);
                break;
            case 2:
                window.draw(key2);
                break;
            case 3:
                window.draw(key3);
                break;
            case 4:
                window.draw(key4);
                break;
            case 5:
                window.draw(key5);
                break;
            }
        }
    }
    if (fpsCooldown==10)
    {
        float fps = getFPS(FPSClock.restart());
        framerate.setString(std::to_string(fps*10));
        fpsCooldown=0;
    }
    else
    {
        fpsCooldown++;
    }
    framerate.setPosition(screen.left+740, screen.top+30);
    window.draw(framerate);
    system.player.weapon1->icon.setPosition(screen.left+700, screen.top+510);
    window.draw(system.player.weapon1->icon);
    system.player.weapon2->icon.setPosition(screen.left+740, screen.top+510);
    window.draw(system.player.weapon2->icon);
    //mWindow.draw(testEntity.sprite);
    //testEntity.sprite.draw(mWindow);
    /***for (auto& o : map.allEntities)
    {
        o->draw(mWindow);
    }

    if (generateParticles)
    {
        for (std::vector<sf::CircleShape>::iterator i = particles.begin(); i != particles.end(); i++)
        {
            mWindow.draw((*i));
        }
    }***/

    /***if (dialog)
    {
        currentDialog->draw(mWindow);
    }***/

    /***if (inventory.visible)
    {
        inventory.drawInventory(mWindow);
    }

    if (currentGUI!=NULL)
    {
        currentGUI->draw(*this);
    }***/

    //mWindow.display();
}

void Screen0::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if (!pause)
    {
        /***if (key == sf::Keyboard::A)
        {
            if (keyCooldown>10)
            {
                //inventory.visible=true;
                std::cout << "keys" << std::endl;
                currentGUI = new InventoryGUI(*this);
                pause=true;
                inventory.currentUI=&inventory.ui;
                keyCooldown=0;
            }
        }***/

        if (key == sf::Keyboard::Left)
        {
            system.mIsMovingLeft = isPressed;
        }
        else if (key == sf::Keyboard::Right)
        {
            system.mIsMovingRight = isPressed;
        }
        else if (key == sf::Keyboard::Up)
        {
            system.player.interact(system.map);
        }
        else if (key == sf::Keyboard::Z)
        {
            if (system.player.collisionBottom)
            {
                system.player.jumping=isPressed;
            }
        }
        if (key == sf::Keyboard::X)
        {
            system.player.weapon1->use(system);
        }
        else if (key == sf::Keyboard::C)
        {
            system.player.weapon2->use(system);
        }

        if (key == sf::Keyboard::LControl)
        {
            system.player.sprint=isPressed;
        }
        /***else if (key == sf::Keyboard::C)
        {
            if (player.dir==0)
            {
                new Spider(map, player.x-70, player.y, 20, 20);
            }
            else if (player.dir==1)
            {
                new Spider(map, player.x+70, player.y, 20, 20);
            }
        }***/
        /***else if (key == sf::Keyboard::P)
        {
            if (keyCooldown>20)
            {
                currentDialog = new Dialog(player);
                currentDialog->addMessage("first");
                currentDialog->addMessage("second");
                currentDialog->addMessage("third");
                currentDialog->addMessage("fourth");
                currentDialog->addMessage("fifth");
                currentDialog->next();
                dialog=true;
                keyCooldown=0;
            }
        }***/

        /***if (dialog)
        {
            if (key == sf::Keyboard::Z)
            {
                if (keyCooldown>20)
                {
                    currentDialog->next();
                    keyCooldown=0;
                }
            }
        }***/
    }
    else
    {
        //std::cout << "pause keys" << std::endl;
        /***if (keyCooldown>10)
        {
            if (currentGUI!=NULL)
            {
                if (currentGUI->label=="inventory")
                {
                    currentUI=inventory.currentUI;
                    if (key == sf::Keyboard::A)
                    {
                        //inventory.visible=false;
                        std::cout << "close inventory" << std::endl;
                        GUI* toBeDeleted = currentGUI;
                        currentGUI = NULL;
                        delete toBeDeleted;
                        pause=false;
                        inventory.currentUI=&inventory.ui;
                        keyCooldown=0;
                    }

                    if (key == sf::Keyboard::Right)
                    {
                        if (inventory.currentSelected!=39)
                        {
                            inventory.selected = &inventory.slots[inventory.currentSelected+=1];
                            if (!inventory.selected->empty)
                            {
                                if (inventory.selected->item->id==10)
                                {
                                    inventory.ui.addOption(new UIOption("Wand"));
                                }
                                else
                                {
                                    if (inventory.ui.getSize()==5)
                                    {
                                        inventory.ui.removeOption(4);
                                    }
                                }
                            }
                        }
                    }
                    else if (key == sf::Keyboard::Left)
                    {
                        if (inventory.currentSelected!=0)
                        {
                            inventory.selected = &inventory.slots[inventory.currentSelected-=1];
                            if (!inventory.selected->empty)
                            {
                                if (inventory.selected->item->id==10)
                                {
                                    inventory.ui.addOption(new UIOption("Wand"));
                                }
                                else
                                {
                                    if (inventory.ui.getSize()==5)
                                    {
                                        inventory.ui.removeOption(4);
                                    }
                                }

                            }
                        }
                    }
                }
                else if (currentGUI->label=="wand")
                {
                    WandGUI* wandGUI;
                    wandGUI = static_cast<WandGUI*>(currentGUI);

                    if (wandGUI->mode==1)
                    {
                        if (key == sf::Keyboard::Right)
                        {
                            if (wandGUI->selected!=39)
                            {
                                wandGUI->selected+=1;
                            }
                        }
                        else if (key == sf::Keyboard::Left)
                        {
                            if (wandGUI->selected!=0)
                            {
                                wandGUI->selected-=1;
                            }
                        }
                    }
                }
            }

            if (key == sf::Keyboard::Up)
            {
                currentUI->selectPrevious();
            }
            else if (key == sf::Keyboard::Down)
            {
                currentUI->selectNext();
            }
            else if (key==sf::Keyboard::Z)
            {
                currentUI->activated=true;
            }
            keyCooldown=0;
        }
        ***/
    }
}

class Textbox
{
private:
    sf::Texture boxTexture;
    sf::Sprite box;
    sf::Text message;

public:
    Textbox(std::string text, sf::Font font, sf::RenderWindow& window, Player& player);
};

Textbox::Textbox(std::string text, sf::Font font, sf::RenderWindow& window, Player& player)
{
    message.setString(text);
    message.setPosition(player.x-260, player.y+120);
    message.setFont(font);
    message.setCharacterSize(24);
    message.setColor(sf::Color::Black);
    message.setStyle(sf::Text::Bold);
    boxTexture.loadFromFile("asset/texture/textbox.png");
    box.setTexture(boxTexture);
    box.setPosition(player.x-282, player.y+110);
    window.draw(box);
    window.draw(message);
    //std::cout << "drawn textbox" << std::endl;
}

Game::Game()
//: mWindow(sf::VideoMode(640, 480), "SFML Application")
//: mWindow(sf::VideoMode(700, 525), "SFML Application")
: mWindow(sf::VideoMode(820, 570), "SFML Application")
//, map(*this, player)
//, inventory(player, map)
, mainScreen(*this)
//, enemy(testMap, 1000, 300, 100, 100)
//, camera(sf::Vector2f(350, 300), sf::Vector2f(300, 200))
//, mTexture()
//, mPlayer()
{
    mWindow.setMouseCursorVisible(false);
    /***mTexture.loadFromFile("asset/texture/Eagle.png");
    mPlayer.setTexture(mTexture);
    font.loadFromFile("asset/Dustismo_Roman.ttf");

    health.setFont(font);
    health.setCharacterSize(24);
    health.setColor(sf::Color::White);
    health.setStyle(sf::Text::Bold);

    coordinates.setFont(font);
    coordinates.setCharacterSize(14);
    coordinates.setColor(sf::Color::White);
    coordinates.setStyle(sf::Text::Bold);

    framerate.setFont(font);
    framerate.setCharacterSize(14);
    framerate.setColor(sf::Color::White);
    framerate.setStyle(sf::Text::Bold);

    inventory.insert(new item::DirectionGun);
    inventory.insert(new item::RPG);
    inventory.insert(new item::LaserGun);
    inventory.insert(new item::PotionI);
    inventory.insert(new item::Wand);
    inventory.insert(new spell::testSpell);
    //inventory.drop(4);
    //inventory.visible=true;

    keyTexture0.loadFromFile("asset/texture/key0.png");
    keyTexture1.loadFromFile("asset/texture/key1.png");
    keyTexture2.loadFromFile("asset/texture/key2.png");
    keyTexture3.loadFromFile("asset/texture/key3.png");
    keyTexture4.loadFromFile("asset/texture/key4.png");
    keyTexture5.loadFromFile("asset/texture/key5.png");
    key0.setTexture(keyTexture0);
    key1.setTexture(keyTexture1);
    key2.setTexture(keyTexture2);
    key3.setTexture(keyTexture3);
    key4.setTexture(keyTexture4);
    key5.setTexture(keyTexture5);

    bgTexture.loadFromFile("asset/texture/background/space.jpg");
    bgTexture.setRepeated(true);
    bgTexture.setSmooth(true);
    background.setTexture(&AssetManager::GetTexture("asset/texture/background/space.jpg"));
    background.setSize(sf::Vector2f(820,570));

    generateParticles=true;***/

    screens.push_back(&mainScreen);
}

float getFPS(const sf::Time& time) {
     return (1000000.0f / time.asMicroseconds());
}

void Game::run()
{
    sf::Clock clock;
    mWindow.setFramerateLimit(60);
    //new Spider(testMap, 500, 220, 100, 100);
    //camera.setCenter(sf::Vector2f(player.x+32, player.y+32));
    //camera.setSize(sf::Vector2f(640, 480));
    //mWindow.setView(camera);
    while (mWindow.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        processEvents();
        update(deltaTime);
        render();

        /***keyCooldown++;
        if (!pause)
        {
            if (!dialog)
            {
                sf::Time deltaTime = clock.restart();
                processEvents();
                update(deltaTime);
                render();
            }
            else
            {
                processEvents();
                render();
                if (currentDialog->end)
                {
                    std::cout << "dialog off" << std::endl;
                    delete currentDialog;
                    currentDialog=NULL;
                    dialog=false;
                }
            }
        }
        else
        {
            processEvents();
            render();
            if (currentGUI == NULL)
            {
                pause=false;
            }
        }
    }***/
    }
}

void Game::processEvents()
{
    sf::Event event;

    /***sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
            break;
        case sf::Event::Closed:
            mWindow.close();
            break;
        }
    }***/

    for (auto& o : screens)
    {
        while (mWindow.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyPressed:
                o->handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                o->handlePlayerInput(event.key.code, false);
                break;
            case sf::Event::Closed:
                mWindow.close();
                break;
            }
        }
    }
}

void Game::update(sf::Time deltaTime)
{
    for (auto& o : screens)
    {
        o->update();
    }


    //background.scale(nearbyint(screen.height/background.getGlobalBounds().height));
    //background.setScale(map.getMap().GetWidth()/background.getGlobalBounds().width, map.getMap().GetHeight()/background.getGlobalBounds().height);

    /***if (generateParticles)
    {
        if (rand() % 100 > 30)
        {
            sf::CircleShape particle;
            particle.setFillColor(sf::Color::White);
            particle.setPosition(screen.left-200+rand() % 1120, screen.top);
            particle.setRadius(1);
            particles.push_back(particle);
        }

        for (std::vector<sf::CircleShape>::iterator i = particles.begin(); i != particles.end(); i++)
        {
            float dx, dy;

            if (rand() % 2 + 0 == 0)
            {
                dx = rand() % 4 + 0;
            }
            else
            {
                dx = -1 * (rand() % 4 + 0);
            }

            dy = rand() % 1 + 2;

            (*i).move(dx, dy);

            if ((*i).getPosition().y>screen.top+570)
            {
                particles.erase(i);
            }
        }
    }

    for (std::list<Entity*>::iterator i = map.allEntities.begin(); i != map.allEntities.end(); i++)
    {
        if (!dynamic_cast<entity::Projectile*>((*i)) == NULL)
        {
            if ((*i)->lifespan!=-1)
            {
                entity::Projectile* projectile = static_cast<entity::Projectile*>((*i));
                if (projectile->count>projectile->lifespan)
                {
                    delete *i;
                    i = map.allEntities.erase(i);
                }
            }
        }
        else if (!dynamic_cast<entity::EnemyProjectile*>((*i)) == NULL)
        {
            if ((*i)->lifespan!=-1)
            {
                entity::EnemyProjectile* enemyProjectile = static_cast<entity::EnemyProjectile*>((*i));
                if (enemyProjectile->count>enemyProjectile->lifespan)
                {
                    delete *i;
                    i = map.allEntities.erase(i);
                }
            }
        }
        else if (!dynamic_cast<entity::Explosion*>((*i)) == NULL)
        {
            entity::Explosion* explosion = static_cast<entity::Explosion*>((*i));
            if (explosion->count>32)
            {
                delete *i;
                i = map.allEntities.erase(i);
            }
        }
        else if (!dynamic_cast<Hostile*>((*i)) == NULL)
        {
            Hostile* hostile = static_cast<Hostile*>((*i));
            if (hostile->hp<0)
            {
                std::cout << "dead" << std::endl;
                delete *i;
                i = map.allEntities.erase(i);
            }
        }
    }

    if (player.y>(map.getMap().GetHeight()*32)-100)
    {
        std::cout << "player died" << std::endl;
        player.x=player.respawnx;
        player.y=player.respawny;
    }




    //sf::Vector2f movement(0.f, 0.f);

    //for (int i=0; i<testMap.solid.GetWidth(); ++i)
    //{
    //   for (int ii=0; ii<testMap.solid.GetHeight(); ++ii)
    //   {
    //       if (testMap.solid.GetTile(i, ii).GetGlobalBounds().intersects(player.hitbox))
    //       {
    //           player.collision=true;
    //       }
    //       }
    //   }
    //}
    if (player.dir==0)
    {
        if (mIsMovingRight)
        {
            player.dir=1;
        }
    }
    if (player.dir==1)
    {
        if (mIsMovingLeft)
        {
            player.dir=0;
        }
    }

    if (!mIsMovingLeft || !mIsMovingRight)
    {
        //player.velocity.x=0;
        //player.velocity.y=0;
        player.moving=false;
    }

    if (mIsMovingLeft)
    {
        if (!player.stun)
        {
            player.velocity.x=-5.f;
            player.moving=true;
        }
    }

    if (mIsMovingRight)
    {
        if (!player.stun)
        {
            player.velocity.x=5.f;
            player.moving=true;
        }
    }




    //mPlayer.move(movement * deltaTime.asSeconds());

    //for (int i=0; i<testMap.solid.height_; ++i)
    //{
    //    for (int ii=0; i<testMap.solid.width_; ++ii)
    //    {

    //    }
    //}

    //sf::Rect.intersects

    background.setPosition(screen.left,screen.top);

    player.update(map);

    for (auto& o : map.allEntities)
    {
        if (o->inProximity)
        {
            o->update(map);
        }
    }


    //camera.reset(sf::Rect<float>(player.y-300, player.x+300, 600, 600));
    int cameraX = player.x+32;
    int cameraY = player.y+32;

    sf::FloatRect cameraRect = camera.getViewport();

    if ((cameraY-285)<0)
    {
        cameraY=(abs(cameraRect.top-0))+285;
    }
    else if ((cameraY+285)>(map.getMap().GetHeight()*32))
    {
        cameraY=(abs(cameraRect.top-(map.getMap().GetHeight()*32)))-285;
    }
    if ((cameraX-410)<0)
    {
        cameraX=(abs(cameraRect.left-0))+410;
    }
    else if ((cameraX+410)>(map.getMap().GetWidth()*32))
    {
        cameraX=(abs(cameraRect.left-(map.getMap().GetWidth()*32)))-410;
    }
    screen.top = cameraY-285;
    screen.left = cameraX-410;
    camera.setCenter(sf::Vector2f(cameraX, cameraY));
    //camera.setSize(sf::Vector2f(640, 480));
    //camera.setSize(sf::Vector2f(710, 533));
    camera.setSize(sf::Vector2f(820, 570));
    mWindow.setView(camera);

    for (std::list<Entity*>::iterator i = map.allEntities.begin(); i != map.allEntities.end(); i++)
    {
        if (((*i)->x-player.x)<500 && ((*i)->y-player.y)<500)
        {
            (*i)->inProximity=true;
        }
        else if (((*i)->x-player.x)>500 && ((*i)->y-player.y)>500)
        {
            (*i)->inProximity=false;
        }

        if ((*i)->testCloseProximity)
        {
            if (((*i)->x-player.x)<50 && ((*i)->y-player.y)<50)
            {
                (*i)->inCloseProximity=true;
            }
            else if (((*i)->x-player.x)>50 && ((*i)->y-player.y)>50)
            {
                (*i)->inCloseProximity=false;
            }
        }

        if ((*i)->dead)
        {
            Entity* toBeDeleted = *i;
            i = map.allEntities.erase(i);
            delete toBeDeleted;
        }
    }***/
}

void Game::render()
{
    mWindow.clear(sf::Color(12, 9, 56, 255));


    for (auto& o : screens)
    {
        o->draw(mWindow);
    }

    /***
    mWindow.draw(background);

    map.draw(mWindow);

     for (auto& o : map.teleports)
        static_cast<Teleport*>(o)->draw(mWindow);

    //mWindow.draw(mPlayer);

    player.draw(mWindow);
    health.setString("Health: " + std::to_string(player.hp) + "/" + std::to_string(player.hpmax) + " Money: " + std::to_string(player.mon));
    health.setPosition(screen.left+50, screen.top+30);
    mWindow.draw(health);
    coordinates.setString("Room: " + std::to_string(map.currentID) + "\nX: " + std::to_string(player.x) + " Y: " + std::to_string(player.y));
    coordinates.setPosition(screen.left+50, screen.top+520);
    mWindow.draw(coordinates);
    key0.setPosition(player.x-100, player.y+230);
    key1.setPosition(player.x-70, player.y+230);
    key2.setPosition(player.x-40, player.y+230);
    key3.setPosition(player.x-10, player.y+230);
    key4.setPosition(player.x+20, player.y+230);
    key5.setPosition(player.x+50, player.y+230);
    for (int i=0; i!=6; i++)
    {
        if (player.keys[i])
        {
            switch (i)
            {
            case 0:
                mWindow.draw(key0);
                break;
            case 1:
                mWindow.draw(key1);
                break;
            case 2:
                mWindow.draw(key2);
                break;
            case 3:
                mWindow.draw(key3);
                break;
            case 4:
                mWindow.draw(key4);
                break;
            case 5:
                mWindow.draw(key5);
                break;
            }
        }
    }
    if (fpsCooldown==10)
    {
        float fps = getFPS(FPSClock.restart());
        framerate.setString(std::to_string(fps*10));
        fpsCooldown=0;
    }
    else
    {
        fpsCooldown++;
    }
    framerate.setPosition(screen.left+740, screen.top+30);
    mWindow.draw(framerate);
    player.weapon1->icon.setPosition(screen.left+700, screen.top+510);
    mWindow.draw(player.weapon1->icon);
    player.weapon2->icon.setPosition(screen.left+740, screen.top+510);
    mWindow.draw(player.weapon2->icon);
    //mWindow.draw(testEntity.sprite);
    //testEntity.sprite.draw(mWindow);
    for (auto& o : map.allEntities)
    {
        o->draw(mWindow);
    }

    if (generateParticles)
    {
        for (std::vector<sf::CircleShape>::iterator i = particles.begin(); i != particles.end(); i++)
        {
            mWindow.draw((*i));
        }
    }

    if (dialog)
    {
        currentDialog->draw(mWindow);
    }

    /***if (inventory.visible)
    {
        inventory.drawInventory(mWindow);
    }

    if (currentGUI!=NULL)
    {
        currentGUI->draw(*this);
    }***/

    mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    /***if (!pause)
    {
        if (key == sf::Keyboard::A)
        {
            if (keyCooldown>10)
            {
                //inventory.visible=true;
                std::cout << "keys" << std::endl;
                currentGUI = new InventoryGUI(*this);
                pause=true;
                inventory.currentUI=&inventory.ui;
                keyCooldown=0;
            }
        }

        if (key == sf::Keyboard::Left)
        {
            mIsMovingLeft = isPressed;
        }
        else if (key == sf::Keyboard::Right)
        {
            mIsMovingRight = isPressed;
        }
        else if (key == sf::Keyboard::Up)
        {
            player.interact(map);
        }
        else if (key == sf::Keyboard::Z)
        {
            if (player.collisionBottom)
            {
                player.jumping=true;
            }
        }
        if (key == sf::Keyboard::X)
        {
            player.weapon1->use(player, map);
        }
        else if (key == sf::Keyboard::C)
        {
            player.weapon2->use(player, map);
        }
        /***else if (key == sf::Keyboard::C)
        {
            if (player.dir==0)
            {
                new Spider(map, player.x-70, player.y, 20, 20);
            }
            else if (player.dir==1)
            {
                new Spider(map, player.x+70, player.y, 20, 20);
            }
        }***/
        /***else if (key == sf::Keyboard::P)
        {
            if (keyCooldown>20)
            {
                currentDialog = new Dialog(player);
                currentDialog->addMessage("first");
                currentDialog->addMessage("second");
                currentDialog->addMessage("third");
                currentDialog->addMessage("fourth");
                currentDialog->addMessage("fifth");
                currentDialog->next();
                dialog=true;
                keyCooldown=0;
            }
        }

        if (dialog)
        {
            if (key == sf::Keyboard::Z)
            {
                if (keyCooldown>20)
                {
                    currentDialog->next();
                    keyCooldown=0;
                }
            }
        }
    }
    else
    {
        //std::cout << "pause keys" << std::endl;
        if (keyCooldown>10)
        {
            if (currentGUI!=NULL)
            {
                if (currentGUI->label=="inventory")
                {
                    currentUI=inventory.currentUI;
                    if (key == sf::Keyboard::A)
                    {
                        //inventory.visible=false;
                        std::cout << "close inventory" << std::endl;
                        GUI* toBeDeleted = currentGUI;
                        currentGUI = NULL;
                        delete toBeDeleted;
                        pause=false;
                        inventory.currentUI=&inventory.ui;
                        keyCooldown=0;
                    }

                    if (key == sf::Keyboard::Right)
                    {
                        if (inventory.currentSelected!=39)
                        {
                            inventory.selected = &inventory.slots[inventory.currentSelected+=1];
                            if (!inventory.selected->empty)
                            {
                                if (inventory.selected->item->id==10)
                                {
                                    inventory.ui.addOption(new UIOption("Wand"));
                                }
                                else
                                {
                                    if (inventory.ui.getSize()==5)
                                    {
                                        inventory.ui.removeOption(4);
                                    }
                                }
                            }
                        }
                    }
                    else if (key == sf::Keyboard::Left)
                    {
                        if (inventory.currentSelected!=0)
                        {
                            inventory.selected = &inventory.slots[inventory.currentSelected-=1];
                            if (!inventory.selected->empty)
                            {
                                if (inventory.selected->item->id==10)
                                {
                                    inventory.ui.addOption(new UIOption("Wand"));
                                }
                                else
                                {
                                    if (inventory.ui.getSize()==5)
                                    {
                                        inventory.ui.removeOption(4);
                                    }
                                }

                            }
                        }
                    }
                }
                else if (currentGUI->label=="wand")
                {
                    WandGUI* wandGUI;
                    wandGUI = static_cast<WandGUI*>(currentGUI);

                    if (wandGUI->mode==1)
                    {
                        if (key == sf::Keyboard::Right)
                        {
                            if (wandGUI->selected!=39)
                            {
                                wandGUI->selected+=1;
                            }
                        }
                        else if (key == sf::Keyboard::Left)
                        {
                            if (wandGUI->selected!=0)
                            {
                                wandGUI->selected-=1;
                            }
                        }
                    }
                }
            }

            if (key == sf::Keyboard::Up)
            {
                currentUI->selectPrevious();
            }
            else if (key == sf::Keyboard::Down)
            {
                currentUI->selectNext();
            }
            else if (key==sf::Keyboard::Z)
            {
                currentUI->activated=true;
            }
            keyCooldown=0;
        }
    }***/
}
