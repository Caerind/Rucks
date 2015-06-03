#include "Output.hpp"
#include "Server.hpp"

Output::Output()
{
}

void Output::init(Server* server)
{
    std::string logfile = "";
    if (server != nullptr)
    {
        logfile = server->getSettings().getString("logfile");
    }
    if (logfile == "")
    {
        logfile = "Assets/Log/server.log";
    }
    if(!open(logfile))
    {
        std::cout << "Error : Log file cannot be opened" << std::endl;
    }
}

bool Output::open(std::string const& filename)
{
    if (mFile.is_open())
        mFile.close();
    mFile.open(filename,std::ios::app);
    return mFile.is_open();
}

void Output::write(std::string const& emitter, std::string const& content)
{
    std::string realEmitter = emitter;
    if (emitter == "")
    {
        realEmitter = "[Server]";
    }

    std::string line;
    line += "[" + getTime() + "] ";
    line += realEmitter;
    line += " : ";
    line += content;

    std::cout << line << std::endl;
    if (mFile.is_open())
    {
        mFile << line << std::endl;
    }
}

std::string Output::getTime()
{
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    std::string timeFormat = "[%x][%X]";
    strftime(buffer,80,timeFormat.c_str(),timeinfo);
    return std::string(buffer);
}
