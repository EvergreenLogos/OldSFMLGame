#include "include/map.hpp"
#include <iostream>

#include "include/game.hpp"
#include "include/entity.hpp"

Tilemap::Tilemap(std::string mapPath) : map(mapPath)
{

}

Tilemap::~Tilemap()
{
    std::cout << "destroyed a tile map" << std::endl;
}

Map::Map(System& system) : system(&system)
{
    currentID=0;
    initRoom();
}

void Map::draw(sf::RenderWindow& window)
{
    //currentMap->map.ShowObjects();

    int w = ((system->game->screen->left+410)/32)-13;
    int x = ((system->game->screen->left+410)/32)+14;
    int y = ((system->game->screen->top+285)/32)-12;
    int z = ((system->game->screen->top+285)/32)+12;

    if (w<0)
    {
        w=0;
    }
    if (x>currentMap->map.GetWidth())
    {
        x=currentMap->map.GetWidth();
    }
    if (y<0)
    {
        y=0;
    }
    if (z>currentMap->map.GetHeight())
    {
        z=currentMap->map.GetHeight();
    }

    for (int i=w; i<x; i++)
    {
        for (int ii=y; ii<z; ii++)
        {
            window.draw(currentMap->map.GetLayer("nonsolid").GetTile(i, ii));
            window.draw(currentMap->map.GetLayer("nonsolid2").GetTile(i, ii));
            window.draw(currentMap->map.GetLayer("solid").GetTile(i, ii));
        }
    }
    //window.draw(currentMap->map);
}

tmx::TileMap& Map::getMap()
{
    return currentMap->map;
}

tmx::Layer& Map::getSolid()
{
    return currentMap->map.GetLayer("solid");
}

void Map::changeMap(int id)
{
    /***or (auto& o : this->canDamage)
    {
        canDamage.pop_front();
        std::cout << "destroyed a hostile" << std::endl;
    }
    //canDamage.clear();***/

    /***while (!canDamage.empty())
    {
        canDamage.pop_front();
    }***/

    /***while (!allEntities.empty())
    {
        allEntities.pop_front();
    }***/

    for (std::list<Entity*>::iterator i = allEntities.begin(); i != allEntities.end(); )
    {
        delete *i;
        i = allEntities.erase(i);
        ++i;
    }
    allEntities.clear();

    teleported=true;
    currentID=id;
    Tilemap* toBeDeleted = currentMap;
    //currentMap=NULL;
    currentMap=NULL;
    delete toBeDeleted;
    if (id==0)
    {
        currentMap = new Tilemap("map/a1.tmx");
    }
    else if (id==1)
    {
        currentMap = new Tilemap("map/1.tmx");
    }
    else if (id==2)
    {
        currentMap = new Tilemap("map/2.tmx");
    }
    else if (id==3)
    {
        currentMap = new Tilemap("map/3.tmx");
    }
    else if (id==4)
    {
        currentMap = new Tilemap("map/4.tmx");
    }
    else if (id==5)
    {
        currentMap = new Tilemap("map/5.tmx");
    }
    else if (id==6)
    {
        currentMap = new Tilemap("map/6.tmx");
    }
    else if (id==7)
    {
        currentMap = new Tilemap("map/7.tmx");
    }
    else if (id==8)
    {
        currentMap = new Tilemap("map/8.tmx");
    }
    else if (id==9)
    {
        currentMap = new Tilemap("map/9.tmx");
    }
    else if (id==10)
    {
        currentMap = new Tilemap("map/10.tmx");
    }
    else if (id==11)
    {
        currentMap = new Tilemap("map/11.tmx");
    }
    else if (id==12)
    {
        currentMap = new Tilemap("map/12.tmx");
    }
    else if (id==13)
    {
        currentMap = new Tilemap("map/13.tmx");
    }
    else if (id==14)
    {
        currentMap = new Tilemap("map/14.tmx");
    }
    else if (id==15)
    {
        currentMap = new Tilemap("map/15.tmx");
    }
    else if (id==16)
    {
        currentMap = new Tilemap("map/16.tmx");
    }
}

void Map::initRoom()
{
    if (currentID==0)
    {
        new entity::Fairy(*system, 400, 200, 1000, 1000, 4, 0);
        new entity::Penguin(*system, 8064, 352, 9999, 9999, 99);
        /***new entity::Key(*this, 160, 608, 2);
        new entity::Key(*this, 896, 608, 2);
        new Teleport(256.f, 992.f, 1, 0, 2048.f, 992.f, "asset/texture/door0.png", game->mWindow, this);
        new Teleport(960.f, 576.f, 10, 0, 192.f, 672.f, "asset/texture/door0.png", game->mWindow, this);
        entity::Sign* sign1 = new entity::Sign(*this, 320.f, 512.f, "asset/texture/sign.png", *game);
        sign1->addString("this is a sign");
        sign1->addString("sign message 2");
        new entity::Chest(*this, 1152.f, 608.f, false, 0, new item::AR15(), 0);
        new entity::Chest(*this, 1312.f, 800.f, true, 1000, NULL, 0);
        new entity::SolidLock(*this, 832, 480, 1, 2, 2);***/
    }/***
    else if (currentID==1)
    {
        new Teleport(1952.f, 992.f, 0, 1, 320.f, 992.f, "asset/texture/door0.png", game->mWindow, this);
        new Teleport(224.f, 1024.f, 2, 1, 2336.f, 1536.f, "asset/texture/door0.png", game->mWindow, this);
    }
    else if (currentID==2)
    {
        new Teleport(2464.f, 1504.f, 1, 2, 320.f, 1056.f, "asset/texture/door0.png", game->mWindow, this);
        new Teleport(1952.f, 1536.f, 3, 2, 288.f, 480.f, "asset/texture/door0.png", game->mWindow, this);
        new Teleport(192.f, 1536.f, 4, 2, 4672.f, 160.f, "asset/texture/door0.png", game->mWindow, this);
        new Teleport(544.f, 256.f, 7, 2, 704.f, 960.f, "asset/texture/door0.png", game->mWindow, this);
    }
    else if (currentID==3)
    {
        new Teleport(192.f, 480.f, 2, 3, 2048.f, 1536.f, "asset/texture/door0.png", game->mWindow, this);
    }
    else if (currentID==4)
    {
        new Teleport(4768.f, 128.f, 2, 4, 256.f, 1568.f, "asset/texture/door0.png", game->mWindow, this);
        new Teleport(192.f, 1920.f, 5, 4, 2240.f, 1600.f, "asset/texture/door0.png", game->mWindow, this);
        new Teleport(32.f, 256.f, 5, 4, 2400.f, 416.f, "asset/texture/door0.png", game->mWindow, this);
        new Teleport(1568.f, 416.f, 6, 4, 352.f, 2432.f, "asset/texture/door0.png", game->mWindow, this);
    }
    else if (currentID==5)
    {
        new Teleport(2336.f, 1600.f, 4, 5, 288.f, 1920.f, "asset/texture/door0.png", game->mWindow, this);
        new Teleport(2496.f, 416.f, 4, 5, 96.f, 256.f, "asset/texture/door0.png", game->mWindow, this);
        new Teleport(2368.f, 2336.f, 8, 5, 448.f, 1376.f, "asset/texture/door0.png", game->mWindow, this);
    }
    else if (currentID==6)
    {
        new Teleport(288.f, 2400.f, 4, 6, 1376.f, 416.f, "asset/texture/door0.png", game->mWindow, this);
        new Teleport(672.f, 832.f, 7, 6, 352.f, 768.f, "asset/texture/door0.png", game->mWindow, this);
    }
    else if (currentID==7)
    {
        new Teleport(256.f, 768.f, 6, 7, 736.f, 864.f, "asset/texture/door0.png", game->mWindow, this);
        new Teleport(608.f, 960.f, 2, 7, 448.f, 288.f, "asset/texture/door0.png", game->mWindow, this);
        new Teleport(864.f, 384.f, 9, 7, 224.f, 672.f, "asset/texture/door0.png", game->mWindow, this);
    }
    else if (currentID==8)
    {
        new Teleport(384.f, 1376.f, 5, 8, 2272.f, 2368.f, "asset/texture/door0.png", game->mWindow, this);
        new Teleport(512.f, 704.f, 5, 8, 2176.f, 1312.f, "asset/texture/door0.png", game->mWindow, this);
    }
    else if (currentID==9)
    {
        new Teleport(160.f, 672.f, 7, 9, 768.f, 416.f, "asset/texture/door0.png", game->mWindow, this);
        new Teleport(5600.f, 480.f, 10, 9, 192.f, 672.f, "asset/texture/door0.png", game->mWindow, this);
    }
    else if (currentID==10)
    {
        new Teleport(128.f, 672.f, 9, 10, 5504.f, 480.f, "asset/texture/door0.png", game->mWindow, this);
        new Teleport(3584.f, 896.f, 11, 10, 224.f, 416.f, "asset/texture/door0.png", game->mWindow, this);
        new Teleport(3424.f, 256.f, 12, 10, 320.f, 1952.f, "asset/texture/door0.png", game->mWindow, this);
        new entity::Hostile1(*this, 462, 448, 100, 100);
    }
    else if (currentID==11)
    {
        new Teleport(160.f, 416.f, 10, 11, 3488.f, 896.f, "asset/texture/door0.png", game->mWindow, this);
    }
    else if (currentID==12)
    {
        new Teleport(256.f, 1952.f, 10, 12, 3328.f, 288.f, "asset/texture/door0.png", game->mWindow, this);
        new Teleport(3488.f, 1184.f, 13, 12, 288.f, 1984.f, "asset/texture/door0.png", game->mWindow, this);
        new Teleport(3232.f, 576.f, 13, 12, 256.f, 512.f, "asset/texture/door0.png", game->mWindow, this);
        new Teleport(160, 960, 14, 12, 3392, 2944, "asset/texture/door0.png", game->mWindow, this);
        new entity::Cannon(*this, 864.f, 1952.f, 4);
    }
    else if (currentID==13)
    {
        new Teleport(224.f, 1984.f, 12, 13, 3392.f, 1216.f, "asset/texture/door0.png", game->mWindow, this);
        new Teleport(192.f, 512.f, 12, 13, 3136.f, 576.f, "asset/texture/door0.png", game->mWindow, this);
    }
    else if (currentID==14)
    {
        new Teleport(3520, 2944, 12, 14, 256, 960, "asset/texture/door0.png", game->mWindow, this);
        new Teleport(2880, 416, 15, 14, 224, 256, "asset/texture/door0.png", game->mWindow, this);
        new Teleport(1440, 1056, 16, 14, 384, 256, "asset/texture/door0.png", game->mWindow, this);
        new Teleport(384, 864, 16, 14, 1984, 544, "asset/texture/door0.png", game->mWindow, this);
        entity::Sign* sign1 = new entity::Sign(*this, 3328, 2976, "asset/texture/sign.png", *game);
        sign1->addString("Color Key Puzzle");
        new entity::Key(*this, 256, 1504, 0);
        new entity::SolidLock(*this, 2592, 1472, 2, 3, 0);
        new entity::Key(*this, 3456, 1504, 1);
        new entity::SolidLock(*this, 1376, 2656, 2, 3, 1);
        new entity::Key(*this, 736, 2912, 2);
        new entity::SolidLock(*this, 2080, 1312, 2, 3, 2);
        new entity::Key(*this, 96, 384, 3);
        new entity::SolidLock(*this, 3072, 288, 2, 6, 3);
        new entity::FallingPlatform(*this, 3136, 2976, 0);
        new entity::FallingPlatform(*this, 2592, 1056, 0);
        new entity::FallingPlatform(*this, 2624, 1056, 0);
        new entity::FallingPlatform(*this, 2880, 1056, 0);
        new entity::FallingPlatform(*this, 2912, 1056, 0);
        new entity::FallingPlatform(*this, 3232, 832, 0);
        new entity::FallingPlatform(*this, 3264, 832, 0);
        new entity::FallingPlatform(*this, 3360, 1024, 0);
        new entity::FallingPlatform(*this, 3456, 1024, 0);
        new entity::FallingPlatform(*this, 1600, 512, 0);
        new entity::FallingPlatform(*this, 1504, 512, 0);
        new entity::FallingPlatform(*this, 1408, 512, 0);
        new entity::FallingPlatform(*this, 1024, 480, 0);
        new entity::FallingPlatform(*this, 1056, 480, 0);
        new entity::FallingPlatform(*this, 1088, 480, 0);
        new entity::FallingPlatform(*this, 1120, 480, 0);
        new entity::FallingPlatform(*this, 1152, 480, 0);
        new entity::FallingPlatform(*this, 1184, 480, 0);
        new entity::FallingPlatform(*this, 3040, 1504, 0);
        new entity::FallingPlatform(*this, 3072, 1504, 0);
        new entity::FallingPlatform(*this, 3104, 1504, 0);
        new entity::FallingPlatform(*this, 3136, 1504, 0);
    }
    else if (currentID==15)
    {
        new Teleport(160, 256, 14, 15, 2994, 416, "asset/texture/door0.png", game->mWindow, this);
        new Teleport(3585, 192, 16, 15, 192, 640, "asset/texture/door0.png", game->mWindow, this);
        new entity::FallingPlatform(*this, 1888, 416, 0);
        new entity::FallingPlatform(*this, 1920, 416, 0);
        new entity::FallingPlatform(*this, 2240, 416, 0);
        new entity::FallingPlatform(*this, 2272, 416, 0);
        new entity::FallingPlatform(*this, 2304, 416, 0);
        new entity::FallingPlatform(*this, 2336, 416, 0);
        new entity::FallingPlatform(*this, 2720, 416, 0);
        new entity::FallingPlatform(*this, 2752, 416, 0);
        new entity::FallingPlatform(*this, 2912, 320, 0);
        new entity::FallingPlatform(*this, 2944, 320, 0);
        new entity::FallingPlatform(*this, 3040, 320, 0);
        new entity::FallingPlatform(*this, 3072, 320, 0);
    }
    else if (currentID==16)
    {
        new Teleport(128, 640, 15, 16, 3488, 192, "asset/texture/door0.png", game->mWindow, this);
        new Teleport(320, 256, 14, 16, 1504, 1056, "asset/texture/door0.png", game->mWindow, this);
        new Teleport(2080, 544, 14, 16, 448, 864, "asset/texture/door0.png", game->mWindow, this);
    }***/
}

void Map::removeBadTeleport()
{
    /***for (auto& o : this->teleports)
    {
        Teleport* teleport = static_cast<Teleport*>(o);
        std::cout << teleport->locID << std::endl;
        if (teleport->locID!=this->currentID)
        {
            std::cout << "deleted bad teleport with locID " << teleport->locID << std::endl;
            teleport->die(*this);
            //map.initRoom();
        }
    }***/
}
