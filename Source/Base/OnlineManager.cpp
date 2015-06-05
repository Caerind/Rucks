#include "OnlineManager.hpp"
#include "../Game/World.hpp"
#include "App.hpp"

OnlineManager::OnlineManager() : mWorld(nullptr)
{
    mClientId = 0;
    mSocket.setBlocking(false);
}

OnlineManager::~OnlineManager()
{
    disconnect();
}

void OnlineManager::setWorld(World* world)
{
    mWorld = world;
}

bool OnlineManager::connect(sf::IpAddress ip, int port)
{
    updateLinked(mSocket.connect(ip,port));
    mTimeSinceLastPacket.restart();
    return mLinked;
}

void OnlineManager::disconnect()
{
    mSocket.setBlocking(true);
    if (mLinked)
    {
        sf::Packet packet;
        packet << Client2Server::Disconnect;
        updateLinked(mSocket.send(packet));
    }
    mSocket.disconnect();
    mSocket.setBlocking(false);
    mClientId = 0;
}

bool OnlineManager::isLinked()
{
    return mLinked;
}

bool OnlineManager::isConnected()
{
    return mConnected;
}

sf::Time OnlineManager::getTimeSinceLastPacket()
{
    return mTimeSinceLastPacket.getElapsedTime();
}

bool OnlineManager::timedOut()
{
    return mTimeSinceLastPacket.getElapsedTime() > sf::seconds(3);
}

void OnlineManager::resetTimeSinceLastPacket()
{
    mTimeSinceLastPacket.restart();
}

bool OnlineManager::isOk()
{
    return (mLinked && mConnected && !timedOut());
}

std::string OnlineManager::getUsername()
{
    return mUsername;
}

void OnlineManager::handlePackets()
{
    if (mLinked)
    {
        sf::Packet packet;
        while (mSocket.receive(packet) == sf::Socket::Done)
        {
            mTimeSinceLastPacket.restart();
            sf::Int32 type;
            packet >> type;
            switch (type)
            {
                case Server2Client::None: break;
                case Server2Client::ClientJoined: clientJoined(packet); break;
                case Server2Client::ClientLeft: clientLeft(packet); break;
                case Server2Client::ServerStopped: serverStopped(packet); break;
                case Server2Client::Message: receiveMessage(packet); break;
                case Server2Client::SendChunk: receiveChunk(packet); break;
                case Server2Client::ModifyChunk: modifyChunk(packet); break;
                case Server2Client::ObjectAddition: objectAddition(packet); break;
                case Server2Client::ObjectDeletion: objectDeletion(packet); break;
                //case Server2Client::ObjectUpdate: objectUpdate(packet); break;
                default: break;
            }
        }
        sendPing();
    }
}

////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////

void OnlineManager::sendPing()
{
    if (mLinked)
    {
        sf::Packet packet;
        packet << Client2Server::None;
        updateLinked(mSocket.send(packet));
    }
}

void OnlineManager::sendLogin(std::string const& username, std::string const& password)
{
    if (mLinked)
    {
        sf::Packet packet;
        packet << Client2Server::Login << username << password;
        updateLinked(mSocket.send(packet));
        mTempUsername = username;
    }
}

void OnlineManager::sendDisconnection()
{
    if (mLinked)
    {
        sf::Packet packet;
        packet << Client2Server::Disconnect;
        updateLinked(mSocket.send(packet));
    }
}

void OnlineManager::sendMessage(std::string const& message)
{
    if (isOk())
    {
        sf::Packet packet;
        packet << Client2Server::Message << mUsername << message;
        updateLinked(mSocket.send(packet));
    }
}

void OnlineManager::askChunk(sf::Vector2i chunkPos)
{
    if (isOk())
    {
        sf::Packet packet;
        packet << Client2Server::AskChunk << chunkPos;
        updateLinked(mSocket.send(packet));
    }
}

void OnlineManager::modifyChunk(sf::Vector2i chunkPos, sf::Vector2i tilePos, unsigned int layer, unsigned int id)
{
    if (isOk())
    {
        sf::Packet packet;
        packet << Client2Server::ModifyChunk << chunkPos << tilePos << layer << id;
        updateLinked(mSocket.send(packet));
    }
}

void OnlineManager::sendPlayerUpdate(sf::Vector2f mvt, sf::Vector2f lookAt)
{
    if (isOk() && mWorld != nullptr)
    {
        if (mWorld->getObjectManager().getPlayer() != nullptr)
        {
            if (mWorld->getObjectManager().getPlayer()->isValid())
            {
                sf::Packet packet;
                packet << Client2Server::PlayerUpdate << Player::getTypeId();
                packet << mWorld->getObjectManager().getPlayer()->getId();
                packet << mvt << lookAt;
                updateLinked(mSocket.send(packet));
            }
        }
    }
}

////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////

void OnlineManager::clientJoined(sf::Packet& packet)
{
    std::string username = "";
    unsigned int clientId = 0;
    unsigned int objectId = 0;
    packet >> username >> clientId >> objectId;
    if (username == mTempUsername)
    {
        mUsername = mTempUsername;
        mTempUsername = "";
        mConnected = true;
        mClientId = clientId;
        if (mWorld != nullptr)
        {
            mWorld->getObjectManager().setPlayerId(objectId);
        }
    }
}

void OnlineManager::clientLeft(sf::Packet& packet)
{
    unsigned int clientId;
    packet >> clientId;
    if (mClientId == clientId)
    {
        mConnected = false;
        mLinked = false;
    }
}

void OnlineManager::serverStopped(sf::Packet& packet)
{
    mConnected = false;
    mLinked = false;
}

void OnlineManager::receiveMessage(sf::Packet& packet)
{
    std::string username;
    std::string message;
    packet >> username >> message;
    if (mWorld != nullptr)
    {
        mWorld->getChat().add(username,message);
    }
}

void OnlineManager::receiveChunk(sf::Packet& packet)
{
    if (mWorld != nullptr)
    {
        mWorld->getChunkManager().handleChunk(packet);
    }
}

void OnlineManager::modifyChunk(sf::Packet& packet)
{
    if (mWorld != nullptr)
    {
        mWorld->getChunkManager().handleChunkModification(packet);
    }
}

void OnlineManager::objectAddition(sf::Packet& packet)
{
    unsigned int id, typeId;
    sf::Vector2f pos, origin;
    std::string name, texture;
    sf::IntRect tRect;
    packet >> id >> typeId >> pos >> origin >> name >> texture >> tRect;
    if (mWorld != nullptr)
    {
        if (typeId == 1)
        {
            auto e = mWorld->getObjectManager().createEntity(id);
            unsigned int life, lifeMax;
            packet >> life >> lifeMax;
            e->setLife(life);
            e->setLifeMax(lifeMax);
        }
        else if (typeId == 2)
        {
            auto p = mWorld->getObjectManager().createPlayer(id);
            unsigned int life, lifeMax;
            packet >> life >> lifeMax;
            p->setLife(life);
            p->setLifeMax(lifeMax);
        }
        else
        {
            mWorld->getObjectManager().createGameObject(id);
        }

        auto go = mWorld->getObjectManager().getGameObject(id);
        go->setPosition(pos);
        go->setOrigin(origin);
        go->setName(name);
        go->setTexture(texture);
        go->setTextureRect(tRect);
    }
}

void OnlineManager::objectDeletion(sf::Packet& packet)
{
    unsigned int id;
    packet >> id;
    if (mWorld != nullptr)
    {
        mWorld->getObjectManager().remove(id);
    }
}

void OnlineManager::objectUpdate(sf::Packet& packet)
{
    unsigned int id;
    sf::Vector2f pos;
    sf::IntRect tRect;
    packet >> id >> pos >> tRect;
    if (mWorld != nullptr)
    {
        auto g = mWorld->getObjectManager().getGameObject(id);
        if (g != nullptr)
        {
            g->setPosition(pos);
            g->setTextureRect(tRect);
        }
    }
}


////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////


void OnlineManager::updateLinked(sf::Socket::Status status)
{
    mLinked = (status == sf::Socket::Done);
}
