#include "CommandHandler.hpp"
#include "Server.hpp"

CommandHandler::CommandHandler(Server& server)
: mServer(server)
{
}

void CommandHandler::run()
{
    std::string line;

    while (mServer.isRunning())
    {
        line.clear();
        std::getline(std::cin, line);
        handle(line);
    }
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
    if (args.size() == 0)
    {
        return;
    }

    if (args[0] == "stop")
        handleStop(args);
    else if (args[0] == "list")
        handleList(args);
    else if (args[0] == "connected")
        handleConnected(args);
    else if (args[0] == "say")
        handleSay(args);
    else if (args[0] == "help")
        handleHelp(args);
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
    mServer.getOutput().write("",str);
    packet << Server2Client::Message << "" << str;
    mServer.sendToAll(packet);
}

void CommandHandler::handleHelp(Arguments args)
{
    mServer.getOutput().write("","help : See the list of commands");
    mServer.getOutput().write("","stop : Stop the server");
    mServer.getOutput().write("","list : See the list of players");
    mServer.getOutput().write("","connected : See the number of connected players");
    mServer.getOutput().write("","say : Say something as Server");
}
