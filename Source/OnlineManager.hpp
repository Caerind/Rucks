#ifndef ONLINEMANAGER_HPP
#define ONLINEMANAGER_HPP

#include <SFML/Network.hpp>
#include <SFML/System/Vector2.hpp>

#include "../Sfml-Helper/Packet.hpp"

class World;

class OnlineManager
{
    public:
        OnlineManager();
        void setWorld(World* world);

        bool connect();
        bool isConnected();


        void handlePacket();

        void askChunk(sf::Vector2i chunkPos);
        void modifyChunk(sf::Vector2i chunkPos, sf::Vector2i tilePos, unsigned int layer, unsigned int id);

    protected:
        World* mWorld;
};

#endif // ONLINEMANAGER_HPP
