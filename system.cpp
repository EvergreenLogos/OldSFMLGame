#include <assert.h>
#include <iostream>

#include "include/system.hpp"
#include "include/game.hpp"
#include "include/entity.hpp"

TextIndicator::TextIndicator(sf::Font& font, std::string string, float x, float y, float angle, int scale)
: x(x), y(y), angle(angle), scale(scale)
{
    text.setString(string);
    text.setPosition(sf::Vector2f(x,y));
    text.setFont(font);
    text.setCharacterSize(24);
    text.setColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);
    text.setScale(sf::Vector2f(scale, scale));
}

TextIndicator::~TextIndicator()
{

}

System* System::sInstance = nullptr;

System::System(Game& game) : map(*this), inventory(player, map), game(&game)
{
    assert(sInstance==nullptr);
    sInstance=this;

    generateParticles=true;
    teleported=false;
    mIsMovingDown=false;
    mIsMovingLeft=false;
    mIsMovingRight=false;
    mIsMovingUp=false;

    background.setTexture(&AssetManager::GetTexture("asset/texture/background/space.jpg"));
    background.setSize(sf::Vector2f(820,570));

    font.loadFromFile("asset/Dustismo_Roman.ttf");

    std::cout<<"system initialized"<<std::endl;
}

void System::update()
{
    if (generateParticles)
    {
        if (rand() % 100 > 30)
        {
            sf::CircleShape particle;
            particle.setFillColor(sf::Color::White);
            particle.setPosition(game->screen->left-200+rand() % 1120, game->screen->top);
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

            if ((*i).getPosition().y>game->screen->top+570)
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
        else if (!dynamic_cast<HostileA*>((*i)) == NULL)
        {
            HostileA* hostile = static_cast<HostileA*>((*i));
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
            if (player.sprint)
            {
                player.velocity.x-=3;
            }
            player.moving=true;
        }
    }

    if (mIsMovingRight)
    {
        if (!player.stun)
        {
            player.velocity.x=5.f;
            if (player.sprint)
            {
                player.velocity.x+=3;
            }
            player.moving=true;
        }
    }

    player.update(map);

    for (auto& o : map.allEntities)
    {
        o->update();
    }

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
            break;
        }
    }
}

void System::draw(sf::RenderWindow& window)
{
    background.setPosition(sf::Vector2f(game->screen->left, game->screen->top));
    window.draw(background);

    map.draw(window);

    player.draw(window);

    for (auto& o : map.allEntities)
    {
        o->draw(window);
    }

    if (generateParticles)
    {
        for (std::vector<sf::CircleShape>::iterator i = particles.begin(); i != particles.end(); i++)
        {
            window.draw((*i));
        }
    }

    for (std::vector<TextIndicator*>::iterator i = textIndicators.begin(); i != textIndicators.end(); i++)
    {
        double angleInRadians = (*i)->angle * 3.14159265 / 180;
        float dx = 2 * cos(angleInRadians);
        float dy = 2 * sin(angleInRadians);
        float x=(*i)->text.getPosition().x;
        float y=(*i)->text.getPosition().y;
        (*i)->text.setPosition(sf::Vector2f(x+(dx*.9), y+(dy*.9)));
        (*i)->count++;
        window.draw((*i)->text);
        if ((*i)->count>20)
        {
            i = textIndicators.erase(i);
            break;
        }
    }
}

void System::dealDamage(int amount, int type)
{
    if (!player.iframes)
    {
        player.hp-=amount;
        player.iframes=true;
        if (player.hp<0)
        {
            player.hp=0;
        }
    }
}

void System::dealDamage(AnimateA& target, int amount, int type)
{
    target.hp-=amount;
    if (target.hp<0)
    {
        target.dead=true;
    }
}

void System::generateText(std::string text, float x, float y, int scale)
{
    //TextIndicator* indicator = new TextIndicator(font, text, x, y, rand() & 360+1, scale);
    textIndicators.push_back(new TextIndicator(font, text, x, y, rand() & 360+1, scale));
}
