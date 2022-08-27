#include "include/player.hpp"
#include <iostream>

#include "include/item.hpp"
#include "include/entity.hpp"
#include "include/teleport.hpp"

Player::Player()
{
    texture.loadFromFile("asset/texture/pc/pc.png", sf::IntRect(0, 0, 64, 64));
    sprite.setTexture(texture);
    x=256;
    y=192;
    respawnx=256;
    respawny=192;
    prevx=x;
    prevy=y;
    collision=false;
    fallSpeed=1;
    dir=0;
    hp=120;
    hpmax=120;
    mon=50;
    //weapon1 = new LaserGun();
    weapon1 = new item::RPG();
    weapon2 = new item::DirectionGun();

    iframes=false;
    iframesCount=0;

    keys[0] = false;
    keys[1] = false;
    keys[2] = false;
    keys[3] = false;
    keys[4] = false;
    keys[5] = false;

    hitbox.width=32.f;
    hitbox.height=64.f;
}

void Player::update(Map& map)
{
    if (!iframes)
    {
        for (std::list<Entity*>::iterator i = map.allEntities.begin(); i != map.allEntities.end(); i++)
        {
            /***if (!dynamic_cast<Hostile*>((*i)) == NULL)
            {
                Hostile* hostile = static_cast<Hostile*>((*i));
                if (hitbox.intersects(hostile->sprite.getGlobalBounds()))
                {
                    hp-=hostile->contactDamage;
                    iframes=true;
                }
            }***/
        }
    }

    if (iframes)
    {
        iframesCount++;
        if (iframesCount<10)
        {
            stun=true;
            if (dir==0)
            {
                velocity.x+=1.2;
            }
            else if (dir==1)
            {
                velocity.x-=1.2;
            }
        }
        else if (iframesCount==20)
        {
            stun=false;
        }
        if (iframesCount>40)
        {
            iframes=false;
            iframesCount=0;
        }
    }

    prevx=x;
    prevy=y;

    if (jumping)
    {
        if (jumpCounter<4)
        {
            velocity.y-=1.5+jumpCounter;
            jumpCounter+=1;
        }
        else
        {
            std::cout << "jump" << std::endl;
            jumping=false;
            jumpCounter=0;
        }
    }



    //std::cout<<"y after movement: "<<y<<std::endl;

    if (!collisionBottom)
    {
        velocity.y+=0.5;

        velocity.x*=0.925;
    }

    if (velocity.y>=12)
    {
        velocity.y=12;
    }


    int xStart = nearbyint(x/32)-2;
    int xEnd = nearbyint(x/32)+4;
    int yStart = nearbyint(y/32)-3;
    int yEnd = nearbyint(y/32)+4;

    if (xStart<0)
    {
        xStart=0;
    }
    else if (xEnd>map.getMap().GetWidth())
    {
        xEnd=map.getMap().GetWidth();
    }
    if (yStart<0)
    {
        yStart=0;
    }
    else if (yEnd>map.getMap().GetHeight())
    {
        yEnd=map.getMap().GetHeight();
        std::cout<<yEnd<<std::endl;
    }


    y+=velocity.y;
    hitbox.top=y;

    for (int i=xStart; i<xEnd; ++i)
    {
        for (int ii=yStart; ii<yEnd; ++ii)
        {
            sf::FloatRect tile = map.getSolid().GetTile(i,ii).GetGlobalBounds();
            if (tile.intersects(hitbox))
            {
                std::cout<<"Collision y axis"<<std::endl;
                velocity.y=0;
                if (prevy<y) // direction: down
                {
                    //y=(ii*32)-64;
                    //std::cout<<"collision down"<<std::endl;
                    while(true)
                    {
                        //std::cout<<"relocate"<<std::endl;
                        y-=1;
                        //std::cout<<y<<std::endl;
                        hitbox.top-=1;
                        if(!tile.intersects(hitbox))
                        {
                            break;
                        }
                    }
                    collisionBottom=true;
                    y=ceil(y);
                    std::cout<<"bottom, adjusted y: "<<y<<std::endl;
                }
                else if (prevy>y) // direction: up
                {
                    std::cout<<"collision top"<<std::endl;
                    //jumping=false;
                    //y=(ii*32)-64;
                    //std::cout<<"collision down"<<std::endl;
                    while(true)
                    {
                        //std::cout<<"relocate"<<std::endl;
                        y+=1;
                        //std::cout<<y<<std::endl;
                        hitbox.top+=1;
                        if(!tile.intersects(hitbox))
                        {
                            break;
                        }
                    }
                    y=std::floor(y);
                    std::cout<<"top, adjusted y: "<<y<<std::endl;
                }
            }
        }
    }



    x+=velocity.x;
    hitbox.left=x+16;

    for (int i=xStart; i<xEnd; ++i)
    {
        for (int ii=yStart; ii<yEnd; ++ii)
        {
            sf::FloatRect tile = map.getSolid().GetTile(i,ii).GetGlobalBounds();
            if (tile.intersects(hitbox))
            {
                std::cout<<"Collision x axis"<<std::endl;
                velocity.x=0;
                if (prevx<x) // direction: right
                {
                    std::cout<<"a"<<std::endl;
                    //y=(ii*32)-64;
                    //std::cout<<"collision down"<<std::endl;
                    while(true)
                    {
                        //std::cout<<"relocate"<<std::endl;
                        x-=1;
                        //std::cout<<y<<std::endl;
                        hitbox.left-=1;
                        if(!tile.intersects(hitbox))
                        {
                            break;
                        }
                    }
                    //collisionBottom=true;
                    x=ceil(x);
                    std::cout<<"right, adjusted x: "<<x<<std::endl;
                }
                else if (prevx>x) // direction: left
                {
                    std::cout<<"a"<<std::endl;
                    //y=(ii*32)-64;
                    //std::cout<<"collision down"<<std::endl;
                    while(true)
                    {
                        //std::cout<<"relocate"<<std::endl;
                        x+=1;
                        //std::cout<<y<<std::endl;
                        hitbox.left+=1;
                        if (!tile.intersects(hitbox))
                        {
                            break;
                        }
                    }
                    x=std::floor(x);
                    std::cout<<"left, adjusted x: "<<x<<std::endl;
                }
            }
        }
    }

    if (collisionBottom)
    {
        if (!checkFloor(map))
        {
            collisionBottom=false;
        }

        velocity.x*=.78;
    }

    sprite.setPosition(x, y);
}

bool Player::checkFloor(Map& map)
{
    hitbox.top+=5;
    for (int i=0; i<map.getSolid().GetWidth(); ++i)
    {
        for (int ii=((y/32)-3); ii<((y/32)+3); ++ii)
        {
            if (map.getSolid().GetTile(i, ii).GetGlobalBounds().intersects(hitbox))
            {
                hitbox.top-=5;
                return true;
            }
        }
    }
    hitbox.top-=5;
    return false;
}

void Player::move(float dx, float dy)
{
    prevx=x;
    prevy=y;

    velocity.x = dx;
    velocity.y = dy;
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(sprite);

    if (dir==0)
    {
        sprite.setOrigin({ sprite.getLocalBounds().width, 0 });
        sprite.setScale({ -1, 1 });
    }
    else if (dir==1)
    {
        sprite.setOrigin({ 0, 0 });
        sprite.setScale({ 1, 1 });
    }

    if (collisionBottom)
    {
        if (moving)
        {
            if (animCount<5)
            {
                texture.loadFromFile("asset/texture/pc/pc.png", sf::IntRect(64, 0, 64, 64));
            }
            else if (animCount==5)
            {
                texture.loadFromFile("asset/texture/pc/pc.png", sf::IntRect(128, 0, 64, 64));
            }
            else if (animCount==10)
            {
                texture.loadFromFile("asset/texture/pc/pc.png", sf::IntRect(192, 0, 64, 64));
            }
            else if (animCount==15)
            {
                texture.loadFromFile("asset/texture/pc/pc.png", sf::IntRect(128, 0, 64, 64));
            }
            else if (animCount==20)
            {
                animCount=0;
            }
            animCount++;
        }
        else
        {
            texture.loadFromFile("asset/texture/pc/pc.png", sf::IntRect(0, 0, 64, 64));
        }
    }
    else if (!collisionBottom)
    {
        texture.loadFromFile("asset/texture/pc/pc.png", sf::IntRect(64, 0, 64, 64));
    }
}

void Player::interact(Map& map)
{
    for (auto& o : map.teleports)
    {
        Teleport* teleport = static_cast<Teleport*>(o);
        if (hitbox.intersects(teleport->sprite.getGlobalBounds()))
        {
            //std::cout << "used teleport" << std::endl;
            //teleport->use(*this, map);
            //map.initRoom();
        }
    }

    for (std::list<Entity*>::iterator i = map.allEntities.begin(); i != map.allEntities.end(); i++)
    {
        /***if (!dynamic_cast<entity::Sign*>((*i)) == NULL)
        {
            entity::Sign* sign = static_cast<entity::Sign*>((*i));
            if (hitbox.intersects(sign->sprite.getGlobalBounds()))
            {
                //sign->read(*this, map);
            }
        }
        else if (!dynamic_cast<entity::Chest*>((*i)) == NULL)
        {
            entity::Chest* chest = static_cast<entity::Chest*>((*i));
            if (hitbox.intersects(chest->sprite.getGlobalBounds()))
            {
                //chest->open(*this, map);
            }
        }***/
    }

    /***for (auto& o : map.allEntities)
    {
        if (!dynamic_cast<Sign*>(o) == NULL)
        {
            Sign* sign = static_cast<Sign*>(o);
            sign->read(*this, map);
        }
        //Shop* shop = static_cast<Shop>(o);
        Shop* shop = &o;
        if (hitbox.intersects(shop->sprite.getGlobalBounds()))
        {
            shop->use(*this, map);
        }
    }***/
}
