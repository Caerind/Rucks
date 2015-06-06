#ifndef ONLINEMANAGER_HPP
#define ONLINEMANAGER_HPP

#include <SFML/Network.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>

#include "../../Lib/Sfml-Helper/Packet.hpp"
#include "PacketType.hpp"
#include "Friend.hpp"

class World;

class OnlineManager
{
    public:
        OnlineManager();
        ~OnlineManager();

        void setWorld(World* world);

        bool connect(sf::IpAddress ip, int port);
        void disconnect();
        bool isLinked(); // Return if we are connected to the server
        bool isConnected(); // Return if we are connected as player
        sf::Time getTimeSinceLastPacket();
        bool timedOut();
        void resetTimeSinceLastPacket();
        bool isOk(); // Return if all is ok
        std::string getUsername();

        void sendPing();
        void sendLogin(std::string const& username, std::string const& password);
        void sendDisconnection();
        void sendMessage(std::string const& message);
        void askChunk(sf::Vector2i chunkPos);
        void modifyChunk(sf::Vector2i chunkPos, sf::Vector2i tilePos, unsigned int layer, unsigned int id);
        void sendPlayerUpdate(sf::Vector2f mvt, sf::Vector2f lookAt);

        void handlePackets();

    protected:
        void clientJoined(sf::Packet& packet);
        void clientLeft(sf::Packet& packet);
        void serverStopped(sf::Packet& packet);
        void receiveMessage(sf::Packet& packet);
        void receiveChunk(sf::Packet& packet);
        void modifyChunk(sf::Packet& packet);
        void objectAddition(sf::Packet& packet);
        void objectDeletion(sf::Packet& packet);
        void objectUpdate(sf::Packet& packet);

        void updateLinked(sf::Socket::Status status);

    protected:
        World* mWorld;
        sf::TcpSocket mSocket;
        bool mLinked;
        bool mConnected;
        sf::Clock mTimeSinceLastPacket;
        std::string mUsername;
        std::string mTempUsername;
        unsigned int mClientId;
        std::vector<Friend> mFriends;
};

#endif // ONLINEMANAGER_HPP
