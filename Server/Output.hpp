#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <ctime>
#include <iostream>
#include <string>
#include <fstream>
#include <string>

class Server;

class Output
{
    public:
        Output();

        void init(Server* server);
        void write(std::string const& emitter, std::string const& content);

        static std::string getTime();

    protected:
        bool open(std::string const& filename);

    protected:
        std::ofstream mFile;
};

#endif // OUTPUT_HPP
