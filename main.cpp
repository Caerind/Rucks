#ifndef RUCKS_SERVER

#include "Source/App.hpp"

int main()
{
    App::instance().run();
    return 0;
}

#endif // RUCKS_SERVER

#ifdef RUCKS_SERVER

#include "Server/CommandHandler.hpp"
#include "Server/Output.hpp"
#include "Server/GameServer.hpp"

int main()
{
	Output out;
	GameServer server(&out);
	CommandHandler command(&server);
	
	std::string line;
	
	while (server.isRunning())
	{
		line.clear();
		std::getline(std::cin, line);
		command.handle(line);
	}
	
	return 0;
}

#endif // RUCKS_SERVER