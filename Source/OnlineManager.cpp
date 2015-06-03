#include "OnlineManager.hpp"
#include "World.hpp"

OnlineManager::OnlineManager() : mWorld(nullptr)
{
}

void OnlineManager::setWorld(World* world)
{
    mWorld = world;
}

bool OnlineManager::connect()
{
    return true;
}

bool OnlineManager::isConnected()
{
    return true;
}


void OnlineManager::handlePacket()
{

}

void OnlineManager::askChunk(sf::Vector2i chunkPos)
{
    sf::Packet packet;
    //packet << PacketType::AskChunk;
    packet << chunkPos;
    //send
}

void OnlineManager::modifyChunk(sf::Vector2i chunkPos, sf::Vector2i tilePos, unsigned int layer, unsigned int id)
{
    sf::Packet packet;
    //packet << PacketType::ModifyChunk;
    packet << chunkPos << tilePos << layer << id;
    //send
}
