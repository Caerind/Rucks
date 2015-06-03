#ifndef SERVER_HPP
#define SERVER_HPP

#include <vector>

#include <SFML/Network.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Thread.hpp>

#include "Message.hpp"
#include "Output.hpp"
#include "Peer.hpp"
#include "Settings.hpp"
#include "CommandHandler.hpp"

#include "../Source/PacketType.hpp"

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

        Settings& getSettings();
        Output& getOutput();

        void list();
        void connected();

        void broadcastMessage(std::string const& username, std::string const& message);

    protected:
        void setListening(bool enable);

        void run();
        void update(sf::Time dt);

        void handlePackets();
        void handlePacket(sf::Packet& packet, Peer& peer, bool& detectedTimeout);

        void handleConnections();
        void handleDisconnections();

    protected:
        Output mOutput;

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

        CommandHandler mCommandHandler;
};

#endif // SERVER_HPP
