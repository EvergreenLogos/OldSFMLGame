#pragma once

#include <SFML/Graphics.hpp>
#include <STP/TMXLoader.hpp>
#include <string>
#include <list>
#include <set>

class Entity;
class Teleport;
class Game;

//#include "entity.hpp"
//#include "teleport.hpp"
//#include "game.hpp"
//#include "player.hpp"
//#include "system.hpp"

class System;

class Tilemap
{
public:
    Tilemap(std::string mapPath);
    ~Tilemap();
    tmx::TileMap map;
};

class Map
{
private:

    int id;
public:
    Map(System& system);
    Game* game;
    System* system;
    //Player* player;
    void draw(sf::RenderWindow& window);
    tmx::TileMap& getMap();
    tmx::Layer& getSolid();
    void changeMap(int id);
    void initRoom();
    void removeBadTeleport();

    //tmx::TileMap* currentMap = &map0;
    Tilemap* currentMap = new Tilemap("map/1a.tmx");
    //tmx::TileMap* currentMap = &Tilemap("map/0.tmx").map;
    std::string mapPath = "map/test.tmx";
    int currentID;
    bool teleported=false;
    // = map.GetLayer("solid");
    //tmx::Layer nonsolid = map.GetLayer("nonsolid");

    //boost::ptr_list<Entity*> allEntities;

    std::list<Entity*> allEntities;
    std::list<Entity*> solidEntities;
    //std::set<Hostile*> canDamage;
    std::set<Teleport*> teleports;

private:
    tmx::Layer solid = currentMap->map.GetLayer("solid");
};
