#include "Server.hpp"

Server::Server()
: mOutput()
, mThread(&Server::run,this)
, mRunning(false)
, mListener()
, mListeningState(false)
, mSettings()
, mConnectedPlayers(0)
, mPeers(1)
, mCommandHandler(*this)
{
    mOutput.init(this);

    mMaxPlayers = mSettings.getInt("maxplayers");
    mPort = mSettings.getInt("port");
    mClientTimeoutTime = sf::seconds(mSettings.getFloat("timeout"));
    mUpdateInterval = sf::seconds(mSettings.getFloat("update"));

    mListener.setBlocking(false);
    mPeers[0].reset(new Peer());

	mOutput.write("","Game Server Version 0.1");

	start();

	mCommandHandler.run();
}

void Server::start()
{
    mOutput.write("","Starting server...");

    mRunning = true;

    mThread.launch();

    mOutput.write("","Server started !");
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

    mOutput.write("","Server stopped !");
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

Settings& Server::getSettings()
{
    return mSettings;
}

Output& Server::getOutput()
{
    return mOutput;
}

void Server::list()
{
    connected();
    for (unsigned int i = 0; i < mConnectedPlayers; i++)
    {
        if (mPeers[i]->isConnected())
        {
            std::string str = " - " + mPeers[i]->getName();
            mOutput.write("",str);
        }
    }
}

void Server::connected()
{
    mOutput.write("","Players : " + ah::to_string(mConnectedPlayers) + " / " + ah::to_string(mMaxPlayers));
}

void Server::broadcastMessage(std::string const& username, std::string const& message)
{
    mOutput.write(username,message);
    sf::Packet mPacket;
    mPacket << Server2Client::Message << username << message;
    sendToAll(mPacket);
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

    // Ping
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

	std::cout << "Debugged !" << std::endl;

}
