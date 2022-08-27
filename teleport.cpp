#include "include/teleport.hpp"

#include <iostream>

Teleport::Teleport(float x, float y, int destID, int locID, float destx, float desty, std::string texturePath, sf::RenderWindow& window, Map* map) : x(x), y(y), destID(destID), locID(locID), destx(destx), desty(desty)
{
    texture.loadFromFile(texturePath);
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    draw(window);
    map->teleports.insert(this);
}

void Teleport::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void Teleport::use()
{
    //map.allEntities.clear();
    /***map.changeMap(destID);
    player.x=destx;
    player.y=desty;
    player.respawnx=destx;
    player.respawny=desty;
    std::cout << "Used teleport from room " << locID << " to room " << destID << std::endl;
    map.initRoom();
    checkIfBad(map);***/
}

void Teleport::die(Map& map)
{
    map.teleports.erase(this);
    delete this;
}

void Teleport::checkIfBad(Map& map)
{
    //std::cout << "trying to delete bad teleports" << std::endl;
    for (auto& o : map.teleports)
    {
        Teleport* teleport = static_cast<Teleport*>(o);
        //std::cout << teleport->locID << std::endl;
        if (teleport->locID!=map.currentID)
        {
            //std::cout << "deleted bad teleport with locID " << teleport->locID << std::endl;
            teleport->die(map);
            //map.initRoom();
        }
    }
}
