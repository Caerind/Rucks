#include "CommandHandler.hpp"
#include "Server.hpp"

CommandHandler::CommandHandler(Server& server)
: mServer(server)
{
}

void CommandHandler::run()
{

}

CommandHandler::Arguments CommandHandler::splitArguments(std::string const& command)
{
    Arguments args;
    std::stringstream ss(command);
    std::string arg;
    while (std::getline(ss,arg,' '))
    {
        args.push_back(arg);
    }
    return args;
}

void CommandHandler::handle(std::string const& command)
{
    Arguments args = splitArguments(command);

    // Return if no arguments

}

void CommandHandler::handleStop(Arguments args)
{
    mServer.stop();
}

void CommandHandler::handleList(Arguments args)
{
    mServer.list();
}

void CommandHandler::handleConnected(Arguments args)
{
    mServer.connected();
}

void CommandHandler::handleSay(Arguments args)
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
    sf::Packet packet;
    mServer.write("",str);
    packet << Server2Client::Message << "" << str;
    mServer.sendToAll(packet);
}

void CommandHandler::handleHelp(Arguments args)
{
    mServer.write("","help : See the list of commands");
    mServer.write("","stop : Stop the server");
    mServer.write("","list : See the list of players");
    mServer.write("","connected : See the number of connected players");
    mServer.write("","say : Say something as Server");
}
