#include "OnlineManager.hpp"
#include "World.hpp"

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
    if (isOk())
    {
        sf::Packet packet;
        packet << Client2Server::Disconnect;
        updateLinked(mSocket.send(packet));
    }
    mSocket.disconnect();
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

bool OnlineManager::isOk()
{
    return (mLinked && mConnected && mTimeSinceLastPacket.getElapsedTime() < sf::seconds(3));
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
            std::cout << type << std::endl;
            switch (type)
            {
                case Server2Client::None: break;
                case Server2Client::ClientJoined: break;
                case Server2Client::ClientLeft: break;
                case Server2Client::ServerStopped: break;
                case Server2Client::Message: break;
                case Server2Client::SendChunk: break;
                case Server2Client::ModifyChunk: break;
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

////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////

void OnlineManager::clientJoined(sf::Packet& packet)
{
    std::string username = "";
    unsigned int clientId = 0;
    unsigned int entityId = 0;
    packet >> username >> clientId >> entityId;
    if (username == mTempUsername)
    {
        mUsername = mTempUsername;
        mTempUsername = "";
        mConnected = true;
        mClientId = clientId;
        if (mWorld != nullptr)
        {
            //mWorld->getPlayer()->setId(entityId);
        }
    }
    else
    {
        //mFriends.push_back(Friend(username,clientId,entityId));
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
    /*
    if (mFriends.contains(clientId))
    {
        remove(friend);
        remove(entity_linked_to_friend);
    }
    */
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
    if (username == "")
    {
        std::cout << message << std::endl;
    }
    else
    {
        std::cout << username << " : " << message << std::endl;
    }
    if (mWorld != nullptr)
    {
        //mWorld->getChat().write(username,message);

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


////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////


void OnlineManager::updateLinked(sf::Socket::Status status)
{
    mLinked = (status == sf::Socket::Done);
}
