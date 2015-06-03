#include "Server.hpp"

Server::Server()
: mThread(&Server::run,this)
, mRunning(false)
, mListener()
, mListeningState(false)
, mSettings()
, mConnectedPlayers(0)
, mPeers(1)
{
    mMaxPlayers = mSettings.getInt("maxplayers");
    mPort = mSettings.getInt("port");
    mClientTimeoutTime = sf::seconds(mSettings.getFloat("timeout"));
    mUpdateInterval = sf::seconds(mSettings.getFloat("update"));

    std::string logfile = mSettings.getString("logfile");
    if (logfile == "")
        logfile = "Assets/Log/server.log";
    mFile.open(logfile,std::ios::app);
    if(!mFile.is_open())
    {
        std::cout << "Error : Log file cannot be opened" << std::endl;
    }

    mListener.setBlocking(false);
    mPeers[0].reset(new Peer());

	write("","Game Server Version 0.1");

	start();

	std::string line;
    while (isRunning())
    {
        line.clear();
        std::getline(std::cin,line);
        handleCommand(line);
    }
}

void Server::start()
{
    write("","Starting server...");

    mRunning = true;

    mThread.launch();

    write("","Server started !");
}

void Server::stop()
{
    broadcastMessage("","Stopping server...");

    setListening(false);

    sf::Packet packet;
    packet << Server2Client::ServerStopped;
    sendToAll(packet);

    mRunning = false;

    mThread.wait();

    write("","Server stopped !");
}

bool Server::isRunning() const
{
    return mRunning;
}

void Server::sendToAll(sf::Packet& packet)
{
    for (std::size_t i = 0; i < mPeers.size(); i++)
    {
        if (mPeers[i]->isReady() && !mPeers[i]->hasTimedOut())
        {
            mPeers[i]->send(packet);
        }
    }
}

void Server::sendToPeer(sf::Packet& packet, unsigned int peerId)
{
    for (std::size_t i = 0; i < mPeers.size(); i++)
    {
        if (mPeers[i]->isReady() && mPeers[i]->getClientId() == peerId && !mPeers[i]->hasTimedOut())
        {
            mPeers[i]->send(packet);
        }
    }
}

void Server::handleCommand(std::string const& command)
{
    std::vector<std::string> args;
    std::stringstream ss(command);
    std::string arg;
    while (std::getline(ss,arg,' '))
    {
        args.push_back(arg);
    }

    if (args.size() == 0)
    {
        return;
    }
    if (args[0] == "stop")
    {
        stop();
    }
    else if (args[0] == "list")
    {
        write("","Players : " + ah::to_string(mConnectedPlayers) + " / " + ah::to_string(mMaxPlayers));
        for (unsigned int i = 0; i < mConnectedPlayers; i++)
        {
            if (mPeers[i]->isConnected())
            {
                std::string str = " - " + mPeers[i]->getName();
                write("",str);
            }
        }
    }
    else if (args[0] == "connected")
    {
        write("","Players : " + ah::to_string(mConnectedPlayers) + " / " + ah::to_string(mMaxPlayers));
    }
    else if (args[0] == "say")
    {
        std::string str;
        for (unsigned int i = 1; i < args.size(); i++)
        {
            str += args[i];
            if (i != args.size()-1)
            {
                str += " ";
            }
        }
        broadcastMessage("",str);
    }
    else if (args[0] == "help")
    {
        write("","help : See the list of commands");
        write("","stop : Stop the server");
        write("","list : See the list of players");
        write("","connected : See the number of connected players");
        write("","say : Say something as Server");
    }
}

void Server::broadcastMessage(std::string const& username, std::string const& message)
{
    write(username,message);
    sf::Packet mPacket;
    mPacket << Server2Client::Message << username << message;
    sendToAll(mPacket);
}

void Server::write(std::string const& username, std::string const& message)
{
    std::string e = (username == "") ? "[Server]" : username;
    std::string line = ah::getTime("[%x][%X]") + " " + e + " : " + message;
    std::cout << line << std::endl;
    if (mFile.is_open())
        mFile << line << std::endl;
}

void Server::setListening(bool enable)
{
    if (enable) // Check if it isn't already listening
	{
		if (!mListeningState)
        {
            mListeningState = (mListener.listen(mPort) == sf::TcpListener::Done);
        }
	}
	else
	{
		mListener.close();
		mListeningState = false;
	}
}

void Server::run()
{
    setListening(true);

    sf::Clock updateClock;

    while (isRunning())
    {
        handlePackets();
        handleConnections();

        if (updateClock.getElapsedTime() > mUpdateInterval)
        {
            update(mUpdateInterval);
            updateClock.restart();
        }

        sf::sleep(sf::milliseconds(100));
    }
}

void Server::update(sf::Time dt)
{

}

void Server::handlePackets()
{
    bool detectedTimeout = false;

	for (unsigned int i = 0; i < mConnectedPlayers; i++)
	{
		if (mPeers[i]->isReady())
        {
            sf::Packet packet;
            while (mPeers[i]->receive(packet) == sf::Socket::Done)
            {
                handlePacket(packet, *mPeers[i], detectedTimeout);
                packet.clear();
            }

            if (mPeers[i]->getLastPacketTime() > mClientTimeoutTime)
            {
                mPeers[i]->setTimedOut(true);
                detectedTimeout = true;
            }
        }
	}

	if (detectedTimeout)
		handleDisconnections();

    sf::Packet packet;
    packet << Server2Client::None;
    sendToAll(packet);
}

void Server::handlePacket(sf::Packet& packet, Peer& peer, bool& detectedTimeout)
{
    sf::Int32 packetType;
    packet >> packetType;

    switch (packetType)
    {
        case Client2Server::Login:
        {
            std::string username, password;
            packet >> username >> password;

            if (true)
            {
                peer.setName(username);
                sf::Packet newPacket;
                newPacket << Server2Client::ClientJoined << username << peer.getClientId() << peer.getClientId();
                sendToAll(newPacket);

                broadcastMessage("",username + " joined the game");
            }
        } break;

        case Client2Server::Disconnect:
        {
            peer.setTimedOut(true);
            detectedTimeout = true;
        } break;

        case Client2Server::Message:
        {
            std::string username, message;
            packet >> username >> message;
            broadcastMessage(username,message);
        } break;

        default: break;
    }
}

void Server::handleConnections()
{
    if (!mListeningState)
		return;

	if (mListener.accept(mPeers[mConnectedPlayers]->getSocket()) == sf::TcpListener::Done)
	{
		mPeers[mConnectedPlayers]->setReady(true);
		mConnectedPlayers++;

		if (mConnectedPlayers >= mMaxPlayers)
			setListening(false);
		else
			mPeers.push_back(Peer::Ptr(new Peer()));
	}
}

void Server::handleDisconnections()
{
    for (auto itr = mPeers.begin(); itr != mPeers.end(); )
	{
		if ((*itr)->hasTimedOut())
		{
			mConnectedPlayers--;

			sf::Packet packet;
            packet << Server2Client::ClientLeft << (*itr)->getClientId();
            sendToAll(packet);
            broadcastMessage("",std::string((*itr)->getName() + " left the game"));

			itr = mPeers.erase(itr);

			if (mConnectedPlayers < mMaxPlayers)
			{
				mPeers.push_back(Peer::Ptr(new Peer()));
				setListening(true);
			}
		}
		else
		{
			++itr;
		}
	}
}
