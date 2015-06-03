#include "Source/App.hpp"

#include "Server/CommandHandler.hpp"
#include "Server/Server.hpp"

int main()
{
    #ifndef RUCKS_SERVER
        App::instance().run();
    #endif

    #ifdef RUCKS_SERVER
        App::instance().close();
        Server server;
    #endif

    return 0;
}
