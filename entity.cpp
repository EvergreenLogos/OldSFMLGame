#include <SFML/Graphics.hpp>
#include <STP/TMXLoader.hpp>
#include <set>
#include <iostream>
#include <string>
#include <cmath>

#include "include/entity.hpp"
#include "include/map.hpp"
#include "include/system.hpp"
#include "include/item.hpp"

class Game;

Entity::Entity(System& system, float x, float y) :  system(&system), x(x), y(y)
{
    hitbox.top=y;
    hitbox.left=x;
    system.map.allEntities.push_front(this);
}

Entity::~Entity()
{
    std::cout << "destructor called" << std::endl;
}

void Entity::update()
{
    sprite.setPosition(x, y);
    x+=velocity.x;
    y+=velocity.y;
    hitbox.left=x;
    hitbox.top=y;
    //game.mWindow.draw(sprite);
    //window.draw(sprite);
    //sprite.draw();
}


void Entity::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void Entity::die()
{
    //map.allEntities.remove(this);
    system->map.allEntities.pop_front();
    delete this;
}

bool Entity::checkPlayerProximity(float distance)
{
    if (system->player.x<=distance && system->player.y<=distance)
    {
        return true;
    }
}

AnimateA::AnimateA(System& system, float x, float y, int hp, int hpmax, int lvl) : Entity(system, x, y), hp(hp), hpmax(hpmax), lvl(lvl)
{

}

AnimateA::~AnimateA()
{

}

void AnimateA::update()
{
    Entity::update();

    if (velocity.x>0)
    {
        sprite.setOrigin({ sprite.getLocalBounds().width, 0 });
        sprite.setScale({ -1, 1 });
    }
    else if (velocity.x<0)
    {
        sprite.setOrigin({ 0, 0 });
        sprite.setScale({ 1, 1 });
    }
}

AnimateB::AnimateB(System& system, float x, float y, int hp, int hpmax, int lvl) : AnimateA(system, x, y, hp, hpmax, lvl)
{
    prevx=x;
    prevy=y;

    texture.loadFromFile("asset/texture/door0.png");
    sprite.setTexture(texture);
    hitbox.height=sprite.getGlobalBounds().height;
    hitbox.width=sprite.getGlobalBounds().width;
}

AnimateB::~AnimateB()
{

}

void AnimateB::update()
{
    AnimateA::update();

    prevx=x;
    prevy=y;

    if (!floor && !flying)
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
    else if (xEnd>system->map.getMap().GetWidth())
    {
        xEnd=system->map.getMap().GetWidth();
    }
    if (yStart<0)
    {
        yStart=0;
    }
    else if (yEnd>system->map.getMap().GetHeight())
    {
        yEnd=system->map.getMap().GetHeight();
        std::cout<<yEnd<<std::endl;
    }

    y+=velocity.y;
    hitbox.top=y;



    for (int i=xStart; i<xEnd; ++i)
    {
        for (int ii=yStart; ii<yEnd; ++ii)
        {
            sf::FloatRect tile = system->map.getSolid().GetTile(i,ii).GetGlobalBounds();
            if (tile.intersects(hitbox))
            {
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
                    floor=true;
                    y=ceil(y);
                }
                else if (prevy>y) // direction: up
                {
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
            sf::FloatRect tile = system->map.getSolid().GetTile(i,ii).GetGlobalBounds();
            if (tile.intersects(hitbox))
            {
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
                }
                else if (prevx>x) // direction: left
                {
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
                }
            }
        }
    }

    if (floor)
    {
        if (!checkFloor())
        {
            floor=false;
        }

        velocity.x*=.78;
    }

    AnimateA::update();
}

bool AnimateB::checkFloor()
{
    hitbox.top+=5;
    for (int i=0; i<system->map.getSolid().GetWidth(); ++i)
    {
        for (int ii=((y/32)-3); ii<((y/32)+3); ++ii)
        {
            if (system->map.getSolid().GetTile(i, ii).GetGlobalBounds().intersects(hitbox))
            {
                hitbox.top-=5;
                return true;
            }
        }
    }
    hitbox.top-=5;
    return false;
}

HostileA::HostileA(System& system, float x, float y, int hp, int hpmax, int lvl) : AnimateA(system, x, y, hp, hpmax, lvl)
{
    texture.loadFromFile("asset/texture/door0.png");
    sprite.setTexture(texture);
    hitbox.height=sprite.getGlobalBounds().height;
    hitbox.width=sprite.getGlobalBounds().width;
    canReceiveDamage=true;
    canDamage=true;

    contactDamage=10;
}

HostileA::~HostileA()
{
    std::cout << "destructor called" << std::endl;
}

void HostileA::update()
{
    AnimateA::update();

    if (canDamage)
    {
        if (hitbox.intersects(system->player.hitbox))
        {
            system->dealDamage(contactDamage, 0);
        }
    }
}

HostileB::HostileB(System& system, float x, float y, int hp, int hpmax, int lvl) : AnimateB(system, x, y, hp, hpmax, lvl)
{
    canReceiveDamage=true;
    canDamage=true;
}

HostileB::~HostileB()
{

}

void HostileB::update()
{
    AnimateB::update();

    if (canDamage)
    {
        if (hitbox.intersects(system->player.hitbox))
        {
            system->dealDamage(contactDamage, 0);
        }
    }
}

entity::Projectile::Projectile(System& system, float x, float y, double speed, double angle, int damage, int shotType) : Entity(system, x, y), damage(damage)
{
    double angleInRadians = angle * 3.14159265 / 180;
    dx = speed * cos(angleInRadians);
    dy = speed * sin(angleInRadians);

    damageType=2;
    damage=10;
    lifespan=200;
    hitbox.top=y;
    hitbox.left=x;
    hitbox.width=5.f;
    hitbox.height=5.f;
    count=0;
}

entity::Projectile::~Projectile()
{
    std::cout << "destructor called" << std::endl;
}

void entity::Projectile::update()
{
    Entity::update();
    x+=dx;
    y+=dy;
    sprite.setPosition(x, y);
    hitbox.top=y;
    hitbox.left=x;
    count++;

    if (count==lifespan)
    {
        if (shotType==3)
        {
            new Explosion(*system, x+10, y-32, 1);
        }
    }
}

entity::PlayerProjectile::PlayerProjectile(System& system, float x, float y, double speed, double angle, int damage, int shotType)
: Projectile(system, x, y, speed, angle, damage, shotType)
{
    switch(shotType)
    {
    case 0:
        texture.loadFromFile("asset/texture/projectile.png", sf::IntRect(9, 22, 16, 16));
        shotType=0;
        break;
    case 1:
        texture.loadFromFile("asset/texture/projectile.png", sf::IntRect(288, 37, 52, 16));
        shotType=1;
        break;
    case 2:
        texture.loadFromFile("asset/texture/projectile.png", sf::IntRect(392, 18, 42, 8));
        shotType=2;
        break;
    case 3:
        texture.loadFromFile("asset/texture/rpg2.png");
        shotType=3;
        lifespan=30;
        break;
    case 4:
        texture.loadFromFile("asset/texture/bullet.png");
        shotType=4;
        break;
    }

    sprite.setTexture(texture);
    sprite.setRotation(angle);
    sprite.setTexture(texture);
    hitbox.height=sprite.getGlobalBounds().height;
    hitbox.width=sprite.getGlobalBounds().width;
}

void entity::PlayerProjectile::update()
{
    Projectile::update();
    for (auto* o : system->map.allEntities)
    {
        if (o->canReceiveDamage)
        {
            if (hitbox.intersects(o->hitbox))
            {
                std::cout<<"can"<<std::endl;
                AnimateA* a = static_cast<AnimateA*>(o);
                system->dealDamage(*a, 10, 0);
                system->generateText("10", x+sprite.getGlobalBounds().width, y+(sprite.getGlobalBounds().height/2), 1);
                dead=true;
            }
        }
    }
}

entity::EnemyProjectile::EnemyProjectile(System& system, float x, float y, double speed, double angle, int damage, int shotType)
: Projectile(system, x, y, speed, angle, damage, shotType)
{
    switch(shotType)
    {
    case 0:
        texture.loadFromFile("asset/texture/projectile.png", sf::IntRect(9, 22, 16, 16));
        shotType=0;
        break;
    case 1:
        texture.loadFromFile("asset/texture/projectile.png", sf::IntRect(288, 37, 52, 16));
        shotType=1;
        break;
    case 2:
        texture.loadFromFile("asset/texture/projectile.png", sf::IntRect(392, 18, 42, 8));
        shotType=2;
        break;
    case 3:
        texture.loadFromFile("asset/texture/rpg2.png");
        shotType=3;
        lifespan=30;
        break;
    }

    sprite.setTexture(texture);
    sprite.setRotation(angle);
    sprite.setTexture(texture);
    hitbox.height=sprite.getGlobalBounds().height;
    hitbox.width=sprite.getGlobalBounds().width;
}

void entity::EnemyProjectile::update()
{
    Projectile::update();
    if (hitbox.intersects(system->player.hitbox))
    {
        system->dealDamage(damage, damageType);
    }
}

entity::Fairy::Fairy(System& system, float x, float y, int hp, int hpmax, int lvl, int type)
: HostileB(system, x, y, hp, hpmax, lvl), type(type)
{
    texture.loadFromFile("asset/texture/spritesheet1.png", sf::IntRect(10, 0, 48, 48));
    sprite.setTexture(texture);
    hitbox.height=48;
    hitbox.width=48;

    contactDamage=10;
    flying=true;
}

entity::Fairy::~Fairy()
{
    new entity::Fairy(*system, x+400, 200, 1000, 1000, 4, 0);
}

void entity::Fairy::update()
{
    //velocity.x=1;

    HostileB::update();

    if (count==10)
    {
        texture.loadFromFile("asset/texture/spritesheet1.png", sf::IntRect(10, 0, 48, 48));
    }
    else if (count==20)
    {
        texture.loadFromFile("asset/texture/spritesheet1.png", sf::IntRect(58, 0, 48, 48));
    }
    else if (count==30)
    {
        texture.loadFromFile("asset/texture/spritesheet1.png", sf::IntRect(106, 0, 48, 48));
    }
    else if (count==40)
    {
        texture.loadFromFile("asset/texture/spritesheet1.png", sf::IntRect(154, 0, 48, 48));
        count=0;
    }

    count++;
}

entity::Penguin::Penguin(System& system, float x, float y, int hp, int hpmax, int lvl)
: AnimateA(system, x, y, hp, hpmax, lvl)
{
    texture.loadFromFile("asset/texture/penguin.png");
    sprite.setTexture(texture);
    hitbox.height=64;
    hitbox.width=64;

    count=0;
}

entity::Penguin::~Penguin()
{

}

void entity::Penguin::update()
{
    AnimateA::update();

    velocity.x=-.5;
    sprite.setRotation(sprite.getRotation()+1);

    if (count==0)
    {
        velocity.y=-.5;
    }
    else if (count==100)
    {
        velocity.y=.5;
    }
    else if (count==200)
    {
        count=-1;
    }

    count++;
}

entity::Shop::Shop(System& system, float x, float y) : Entity(system, x, y)
{
    this->x=x;
    this->y=y;
    //map.allEntities.push_back(this);
    texture.loadFromFile("asset/texture/shop.png");
    texture1.loadFromFile("asset/texture/textbox.png");
    sprite.setTexture(texture);
    box1.setTexture(texture1);
    box1.setPosition(system.map.system->player.x-282, system.map.system->player.y+110);
}

void entity::Shop::addItem(Item* item, float price)
{
    item->setPrice(price);
    items.insert(item);
    std::cout << "Added " << item->getName() << " to the shop" << std::endl;
}

void entity::Shop::use()
{
    std::cout << "used the shop" << std::endl;
    //map.game->dialog=true;
    //map.game->onlyUpdate=this;
}

/***entity::HSpikeBall::HSpikeBall(Map& map, float x, float y, int hp, int hpmax) : Hostile(map, x, y, 100, 100)
{
    //map.canDamage.push_front(this);
    this->hp=hp;
    this->hpmax=hpmax;
    contactDamage=20;
    texture.loadFromFile("asset/texture/spike.png");
    sprite.setTexture(texture);
    hitbox.top=y;
    hitbox.left=x;
    hitbox.width=32.f;
    hitbox.height=32.f;
}

void entity::HSpikeBall::update(Map& map)
{
    for (std::list<Entity*>::iterator i = map.allEntities.begin(); i != map.allEntities.end(); i++)
    {
        if (!dynamic_cast<Projectile*>((*i)) == NULL)
        {
            Projectile* projectile = static_cast<Projectile*>((*i));
            if (projectile->shotType!=3)
            {
                if (sprite.getGlobalBounds().intersects(projectile->sprite.getGlobalBounds()))
                {
                    hp-=1;
                    std::cout << hp << std::endl;
                    delete *i;
                    i = map.allEntities.erase(i);
                }
            }
        }
        if (!dynamic_cast<Explosion*>((*i)) == NULL)
        {
            Explosion* explosion = static_cast<Explosion*>((*i));
            if (sprite.getGlobalBounds().intersects(explosion->sprite.getGlobalBounds()))
            {
                hp-=explosion->contactDamage;
                std::cout << hp << std::endl;
            }
        }
    }


    if (hp<0)
    {
        //die(map);
    }

    if (dir==0)
    {
        velocity.x=2.f;
    }
    else if (dir==1)
    {
        velocity.x=-2.f;
    }

    x+=velocity.x;
    y+=velocity.y;

    hitbox.top=y;
    hitbox.left=x;
    hitbox.width=32.f;
    hitbox.height=32.f;

    if (checkCollision(map, "none"))
    {
        collision=true;
        if (dir==0)
        {
            dir=1;
        }
        else if (dir==1)
        {
            dir=0;
        }
    }

    sprite.setPosition(x, y);
    //std::cout << std::to_string(x) + "," + std::to_string(y) + std::end;
}***/

/***bool HSpikeBall::checkCollision(Map& map, std::string direction)
{
    if (direction=="none")
    {
        for (int i=((x/32)-3); i<((x/32)+3); ++i)
        {
            for (int ii=((y/32)-3); ii<((y/32)+3); ++ii)
            {
                if (map.getSolid().GetTile(i, ii).GetGlobalBounds().intersects(hitbox))
                {
                    return true;
                }
            }
        }
    }
    else if (direction=="up")
    {
        hitbox.top=y-6.f;
        for (int i=((x/32)-3); i<((x/32)+3); ++i)
        {
            for (int ii=((y/32)-3); ii<((y/32)+3); ++ii)
            {
                if (map.getSolid().GetTile(i, ii).GetGlobalBounds().intersects(hitbox))
                {
                    hitbox.top=y;
                    return true;
                }
            }
        }
    }
    if (direction=="down")
    {
        hitbox.height=70.f;
        for (int i=((x/32)-3); i<((x/32)+3); ++i)
        {
            for (int ii=((y/32)-3); ii<((y/32)+3); ++ii)
            {
                if (map.getSolid().GetTile(i, ii).GetGlobalBounds().intersects(hitbox))
                {
                    hitbox.height=64.f;
                    return true;
                }
            }
        }
    }
    if (direction=="left")
    {
        hitbox.left=x-6.f;
        for (int i=((x/32)-3); i<((x/32)+3); ++i)
        {
            for (int ii=((y/32)-3); ii<((y/32)+3); ++ii)
            {
                if (map.getSolid().GetTile(i, ii).GetGlobalBounds().intersects(hitbox))
                {
                    hitbox.left=x;
                    return true;
                }
            }
        }
    }
    if (direction=="right")
    {
        hitbox.width=70.f;
        for (int i=((x/32)-3); i<((x/32)+3); ++i)
        {
            for (int ii=((y/32)-3); ii<((y/32)+3); ++ii)
            {
                if (map.getSolid().GetTile(i, ii).GetGlobalBounds().intersects(hitbox))
                {
                    hitbox.width=64.f;
                    return true;
                }
            }
        }
    }
}***/

/***entity::VSpikeBall::VSpikeBall(Map& map, float x, float y, int hp, int hpmax) : Hostile(map, x, y, 100, 100)
{
    //map.canDamage.push_front(this);
    this->hp=hp;
    this->hpmax=hpmax;
    contactDamage=20;
    texture.loadFromFile("asset/texture/spike.png");
    sprite.setTexture(texture);
    hitbox.top=y;
    hitbox.left=x;
    hitbox.width=32.f;
    hitbox.height=32.f;
}

void entity::VSpikeBall::update(Map& map)
{
    for (std::list<Entity*>::iterator i = map.allEntities.begin(); i != map.allEntities.end(); i++)
    {
        if (!dynamic_cast<Projectile*>((*i)) == NULL)
        {
            Projectile* projectile = static_cast<Projectile*>((*i));
            if (projectile->shotType!=3)
            {
                if (sprite.getGlobalBounds().intersects(projectile->sprite.getGlobalBounds()))
                {
                    hp-=1;
                    std::cout << hp << std::endl;
                    delete *i;
                    i = map.allEntities.erase(i);
                }
            }
        }
        if (!dynamic_cast<Explosion*>((*i)) == NULL)
        {
            Explosion* explosion = static_cast<Explosion*>((*i));
            if (sprite.getGlobalBounds().intersects(explosion->sprite.getGlobalBounds()))
            {
                hp-=explosion->contactDamage;
                std::cout << hp << std::endl;
            }
        }
    }

    if (hp<0)
    {
        //die(map);
    }

    if (dir==0)//down
    {
        velocity.y=4.f;
    }
    else if (dir==1)//up
    {
        velocity.y=-4.f;
    }

    x+=velocity.x;
    y+=velocity.y;

    hitbox.top=y;
    hitbox.left=x;
    hitbox.width=32.f;
    hitbox.height=32.f;

    if (checkCollision(map, "none"))
    {
        collision=true;
        if (dir==0)
        {
            dir=1;
        }
        else if (dir==1)
        {
            dir=0;
        }
    }

    sprite.setPosition(x, y);
    //std::cout << std::to_string(x) + "," + std::to_string(y) + std::end;
}***/

entity::Explosion::Explosion(System& system, float x, float y, int size) : HostileA(system, x, y, 0, 0, 0)
{
    lifespan=20;
    count=0;
    damageType=3;
    contactDamage=50;
    texture.loadFromFile("asset/texture/explosion.png", sf::IntRect(0, 0, 64, 64));
    sprite.setTexture(texture);
    sprite.scale(2.f*size, 2.f*size);
    //this->contactDamage=1;
}

void entity::Explosion::update()
{
    sprite.setPosition(x, y);
    count++;
    hitbox.top=y;
    hitbox.left=x;
    hitbox.width=128.f;
    hitbox.height=128.f;

    if (count==0)
    {
        texture.loadFromFile("asset/texture/explosion.png", sf::IntRect(0, 0, 64, 64));
        sprite.setTexture(texture);
    }
    if (count==2)
    {
        texture.loadFromFile("asset/texture/explosion.png", sf::IntRect(64, 0, 64, 64));
        sprite.setTexture(texture);
    }
    else if (count==4)
    {
        texture.loadFromFile("asset/texture/explosion.png", sf::IntRect(128, 0, 64, 64));
        sprite.setTexture(texture);
    }
    else if (count==6)
    {
        texture.loadFromFile("asset/texture/explosion.png", sf::IntRect(192, 0, 64, 64));
        sprite.setTexture(texture);
    }
    else if (count==8)
    {
        texture.loadFromFile("asset/texture/explosion.png", sf::IntRect(64, 0, 64, 64));
        sprite.setTexture(texture);
    }
    else if (count==10)
    {
        texture.loadFromFile("asset/texture/explosion.png", sf::IntRect(64, 64, 64, 64));
        sprite.setTexture(texture);
    }
    else if (count==12)
    {
        texture.loadFromFile("asset/texture/explosion.png", sf::IntRect(64, 128, 64, 64));
        sprite.setTexture(texture);
    }
    else if (count==14)
    {
        texture.loadFromFile("asset/texture/explosion.png", sf::IntRect(64, 192, 64, 64));
        sprite.setTexture(texture);
    }
    else if (count==16)
    {
        texture.loadFromFile("asset/texture/explosion.png", sf::IntRect(128, 0, 64, 64));
        sprite.setTexture(texture);
    }
    else if (count==18)
    {
        texture.loadFromFile("asset/texture/explosion.png", sf::IntRect(128, 64, 64, 64));
        sprite.setTexture(texture);
    }
    else if (count==20)
    {
        texture.loadFromFile("asset/texture/explosion.png", sf::IntRect(128, 128, 64, 64));
        sprite.setTexture(texture);
    }
    else if (count==22)
    {
        texture.loadFromFile("asset/texture/explosion.png", sf::IntRect(128, 192, 64, 64));
        sprite.setTexture(texture);
    }
    else if (count==24)
    {
        texture.loadFromFile("asset/texture/explosion.png", sf::IntRect(192, 0, 64, 64));
        sprite.setTexture(texture);
    }
    else if (count==26)
    {
        texture.loadFromFile("asset/texture/explosion.png", sf::IntRect(192, 64, 64, 64));
        sprite.setTexture(texture);
    }
    else if (count==28)
    {
        texture.loadFromFile("asset/texture/explosion.png", sf::IntRect(192, 128, 64, 64));
        sprite.setTexture(texture);
    }
    else if (count==30)
    {
        texture.loadFromFile("asset/texture/explosion.png", sf::IntRect(192, 192, 64, 64));
        sprite.setTexture(texture);
    }
}

entity::Cannon::Cannon(System& system, float x, float y, int type) : HostileA(system, x, y, 90, 90, 0), type(type)
{
    contactDamage=0;
    texture.loadFromFile("asset/texture/cannon.png");
    sprite.setTexture(texture);
    hitbox.height=sprite.getGlobalBounds().height;
    hitbox.width=sprite.getGlobalBounds().width;
}

double entity::Cannon::getAngle(float x, float y)
{
    return atan2f(y - this->y, x - this->x) * (180 / 3.14159265);
}

void entity::Cannon::update()
{
    HostileA::update();
    sprite.setPosition(x, y);
    count++;

    if (system->player.x>x-800 && system->player.x<x+800 && system->player.y>y-800 && system->player.y<y+800)
    {
        if (system->player.x<x) // left
        {
            dir=0;
            sprite.setOrigin({ sprite.getLocalBounds().width, 0 });
            sprite.setScale({ -1, 1 });

            if (type==0)
            {
                if (count==20 || count==40 || count==60)
                {
                    new EnemyProjectile(*system, x+32, y+20, 4, 180, 10, 0);
                }
            }
            else if (type==1)
            {
                if (count==20 || count==40 || count==60)
                {
                    new EnemyProjectile(*system, x+32, y+20, 5, 0, 10, 0);
                    new EnemyProjectile(*system, x+32, y+20, 5, 90, 10, 0);
                    new EnemyProjectile(*system, x+32, y+20, 5, 180, 10, 0);
                    new EnemyProjectile(*system, x+32, y+20, 5, 270, 10, 0);
                }
            }
            else if (type==2)
            {
                if (count==20)
                {
                    new EnemyProjectile(*system, x+32, y+20, 5, 180, 10, 0);
                    new EnemyProjectile(*system, x+32, y+20, 5.5, 180, 10, 0);
                    new EnemyProjectile(*system, x+32, y+20, 6., 180, 10, 0);
                    new EnemyProjectile(*system, x+32, y+20, 6.5, 180, 10, 0);
                }
            }
            else if (type==3)
            {
                if (count==20)
                {
                    new EnemyProjectile(*system, x+32, y+20, 9, 180, 10, 0);
                    new EnemyProjectile(*system, x+32, y+20, 9, 185, 10, 0);
                    new EnemyProjectile(*system, x+32, y+20, 9, 190, 10, 0);
                    new EnemyProjectile(*system, x+32, y+20, 9, 175, 10, 0);
                    new EnemyProjectile(*system, x+32, y+20, 9, 170, 10, 0);
                }
            }
            else if (type==4)
            {
                if (count==20)
                {
                    for (int i=0; i<360; i+=360/9)
                    {
                        new EnemyProjectile(*system, x+32, y+20, 6, i+getAngle(system->player.x, system->player.y), 10, 1);
                    }
                }
            }
        }
        else if (system->player.x>x) // right
        {
            dir=1;
            sprite.setOrigin({ 0, 0 });
            sprite.setScale({ 1, 1 });

            if (type==0)
            {
                if (count==20 || count==40 || count==60)
                {
                    new EnemyProjectile(*system, x+32, y+20, 4, 0, 10, 0);
                }
            }
            else if (type==1)
            {
                if (count==20 || count==40 || count==60)
                {
                    new EnemyProjectile(*system, x+32, y+20, 5, 0, 10, 0);
                    new EnemyProjectile(*system, x+32, y+20, 5, 90, 10, 0);
                    new EnemyProjectile(*system, x+32, y+20, 5, 180, 10, 0);
                    new EnemyProjectile(*system, x+32, y+20, 5, 270, 10, 0);
                }
            }
            else if (type==2)
            {
                if (count==20)
                {
                    new EnemyProjectile(*system, x+32, y+20, 5, 180, 10, 0);
                    new EnemyProjectile(*system, x+32, y+20, 5.5, 180, 10, 0);
                    new EnemyProjectile(*system, x+32, y+20, 6., 180, 10, 0);
                    new EnemyProjectile(*system, x+32, y+20, 6.5, 180, 10, 0);
                }
            }
            else if (type==3)
            {
                if (count==20)
                {
                    new EnemyProjectile(*system, x+32, y+20, 9, 0, 10, 0);
                    new EnemyProjectile(*system, x+32, y+20, 9, 5, 10, 0);
                    new EnemyProjectile(*system, x+32, y+20, 9, 10, 10, 0);
                    new EnemyProjectile(*system, x+32, y+20, 9, -5, 10, 0);
                    new EnemyProjectile(*system, x+32, y+20, 9, -10, 10, 0);
                }
            }
            else if (type==4)
            {
                if (count==20)
                {
                    for (int i=0; i<360; i+=360/9)
                    {
                        new EnemyProjectile(*system, x+32, y+20, 6, i+getAngle(system->player.x, system->player.y), 10, 1);
                    }
                }
            }
        }
    }

    if (type==0 && count==200)
    {
        count=0;
    }
    if (type==1 && count==200)
    {
        count=0;
    }
    if (type==2 && count==200)
    {
        count=0;
    }
    if (type==3 && count==400)
    {
        count=0;
    }
    if (type==4 && count==100)
    {
        count=0;
    }
}

/***entity::Sign::Sign(Map& map, float x, float y, std::string path, Game& game) : Entity(map, x, y), game(&game)
{
    texture.loadFromFile(path);
    sprite.setTexture(texture);
}

void entity::Sign::addString(std::string string)
{
    strings.push_front(string);
}

void entity::Sign::read()
{
    /***game->currentDialog = new Dialog(player);

    for (auto i=strings.rbegin(); i!=strings.rend(); i++)
    {
        game->currentDialog->addMessage(*i);
    }

    game->currentDialog->next();
    game->dialog=true;***/
//}

/***entity::Chest::Chest(Map& map, float x, float y, bool money, int amount, Item* item, int type) : money(money), amount(amount), Entity(map, x, y)
{
    this->item=item;

    switch(type)
    {
    case 0:
        texture.loadFromFile("asset/texture/chest.png", sf::IntRect(0, 0, 32, 32));
        break;
    }
    sprite.setTexture(texture);
}

void entity::Chest::update(Map& map)
{
    sprite.setPosition(x, y);
    if (empty)
    {
        if (count==10)
        {
            texture.loadFromFile("asset/texture/chest.png", sf::IntRect(0, 32, 32, 32));
        }
        else if (count==20)
        {
            texture.loadFromFile("asset/texture/chest.png", sf::IntRect(0, 64, 32, 32));
        }
        else if (count==30)
        {
            texture.loadFromFile("asset/texture/chest.png", sf::IntRect(0, 96, 32, 32));
        }
        sprite.setTexture(texture);
        if (count<=30)
        {
            count++;
        }
    }
}

void entity::Chest::open()
{
    /***if (!empty)
    {
        if (money)
        {
            player.mon+=amount;

            map.game->currentDialog = new Dialog(player);
            map.game->currentDialog->addMessage("You found $" + std::to_string(amount) + ".");
            map.game->currentDialog->next();
            map.game->dialog=true;
        }
        else if (!money)
        {
            map.game->inventory.insert(item);

            map.game->currentDialog = new Dialog(player);
            map.game->currentDialog->addMessage("You found a " + item->getName() + ".");
            map.game->currentDialog->next();
            map.game->dialog=true;
        }
        empty=true;
        count=0;
    }***/
//}

entity::Key::Key(System& system, float x, float y, int color) : Entity(system, x, y), color(color)
{
    switch(color)
    {
    case 0:
        texture.loadFromFile("asset/texture/key0.png");
        break;
    case 1:
        texture.loadFromFile("asset/texture/key1.png");
        break;
    case 2:
        texture.loadFromFile("asset/texture/key2.png");
        break;
    case 3:
        texture.loadFromFile("asset/texture/key3.png");
        break;
    case 4:
        texture.loadFromFile("asset/texture/key4.png");
        break;
    case 5:
        texture.loadFromFile("asset/texture/key5.png");
        break;
    }

    sprite.setTexture(texture);
    hitbox.height=sprite.getGlobalBounds().height;
    hitbox.width=sprite.getGlobalBounds().width;
}

void entity::Key::update()
{
    sprite.setPosition(x, y);

    if (sprite.getGlobalBounds().intersects(system->player.hitbox))
    {
        std::cout << "Collected a key" << std::endl;

        switch (color)
        {
        case 0:
            system->player.keys[0]=true;
            break;
        case 1:
            system->player.keys[1]=true;
            break;
        case 2:
            system->player.keys[2]=true;
            break;
        case 3:
            system->player.keys[3]=true;
            break;
        case 4:
            system->player.keys[4]=true;
            break;
        case 5:
            system->player.keys[5]=true;
            break;
        }

        dead = true;
    }
}

entity::SolidLock::SolidLock(System& system, float x, float y, float width, float height, int color) : Entity(system, x, y)
{
    //map.solidEntities.push_front(this);
    solid=true;
    testCloseProximity=true;

    this->color[0] = false;
    this->color[1] = false;
    this->color[2] = false;
    this->color[3] = false;
    this->color[4] = false;
    this->color[5] = false;

    switch(color)
    {
    case 0:
        this->color[0]=true;
        texture.loadFromFile("asset/texture/lock0.png");
        break;
    case 1:
        this->color[1]=true;
        texture.loadFromFile("asset/texture/lock1.png");
        break;
    case 2:
        this->color[2]=true;
        texture.loadFromFile("asset/texture/lock2.png");
        break;
    case 3:
        this->color[3]=true;
        texture.loadFromFile("asset/texture/lock3.png");
        break;
    case 4:
        this->color[4]=true;
        texture.loadFromFile("asset/texture/lock4.png");
        break;
    case 5:
        this->color[5]=true;
        texture.loadFromFile("asset/texture/lock5.png");
        break;
    }

    sprite.setTexture(texture);
    sprite.setScale(width, height);
}

void entity::SolidLock::update()
{
    sprite.setPosition(x-32, y);

    if (sprite.getGlobalBounds().intersects(system->player.hitbox))
    {
        for (int i=0; i!=6; i++)
        {
            if (system->player.keys[i] && color[i])
            {
                std::cout << "player has the key" << std::endl;
                system->player.keys[i]=false;
                dead=true;
            }
        }
    }

    sprite.setPosition(x+32, y);

    if (sprite.getGlobalBounds().intersects(system->player.hitbox))
    {
        for (int i=0; i!=6; i++)
        {
            if (system->player.keys[i] && color[i])
            {
                std::cout << "player has the key" << std::endl;
                system->player.keys[i]=false;
                dead = true;
            }
        }
    }

    sprite.setPosition(x, y);
}

entity::FallingPlatform::FallingPlatform(System& system, float x, float y, int type) : Entity(system, x, y), type(type)
{
    solid=true;
    testCloseProximity=true;

    respawnX=x;
    respawnY=y;

    top.left=x;
    top.top=y-30;

    switch(type)
    {
    case 0:
        texture.loadFromFile("asset/texture/fallingplatform.png");
        top.width=32;
        top.height=30;
        break;
    }

    sprite.setTexture(texture);
    hitbox.height=sprite.getGlobalBounds().height;
    hitbox.width=sprite.getGlobalBounds().width;
}

void entity::FallingPlatform::update()
{
    sprite.setPosition(x, y);

    if (system->player.hitbox.intersects(top) && counting==false)
    {
        counting=true;
    }

    if (counting)
    {
        count++;
    }

    if (falling)
    {
        y+=4;
        //count++;
        if (count==200)
        {
            x=respawnX;
            y=respawnY;
            falling=false;
            counting=false;
            count=0;
        }
    }
    else if (count==30)
    {
        falling=true;
        count=0;
    }
}
