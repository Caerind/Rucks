#include "Source/App.hpp"

#include "Server/CommandHandler.hpp"
#include "Server/Output.hpp"
#include "Server/Server.hpp"

int main()
{
    #ifndef RUCKS_SERVER
        App::instance().run();
    #endif

    #ifdef RUCKS_SERVER
        App::instance().close();
        {
            Output out;
            Server server(&out);
            CommandHandler command(&server);

            std::string line;

            while (server.isRunning())
            {
                line.clear();
                std::getline(std::cin, line);
                command.handle(line);
            }
        }
    #endif

    return 0;
}
