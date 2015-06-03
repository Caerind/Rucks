#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>

#include <SFML/Network.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Thread.hpp>

#include "Peer.hpp"
#include "Settings.hpp"

#include "../Source/PacketType.hpp"

#include "../Aharos/Clock.hpp"
#include "../Aharos/String.hpp"

class Server
{
    public:
        Server();

        void start();
        void stop();
        bool isRunning() const;

        void sendToAll(sf::Packet& packet);
        void sendToPeer(sf::Packet& packet, unsigned int peerId);

        void handleCommand(std::string const& command);

        void broadcastMessage(std::string const& username, std::string const& message);
        void write(std::string const& username, std::string const& message);

    protected:
        void setListening(bool enable);

        void run();
        void update(sf::Time dt);

        void handlePackets();
        void handlePacket(sf::Packet& packet, Peer& peer, bool& detectedTimeout);

        void handleConnections();
        void handleDisconnections();

    protected:
        sf::Thread mThread;
        bool mRunning;

        sf::TcpListener mListener;
        bool mListeningState;

        Settings mSettings;

        std::size_t mMaxPlayers;
        std::size_t mPort;
        sf::Time mClientTimeoutTime;
        sf::Time mUpdateInterval;

        std::size_t mConnectedPlayers;

        std::vector<Peer::Ptr> mPeers;

        std::ofstream mFile;
};

#endif // SERVER_HPP
