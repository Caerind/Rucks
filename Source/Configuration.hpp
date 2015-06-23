#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include "../Lib/Aharos/ActionTarget.hpp"

class Configuration
{
    public:
        static Configuration& instance();

        void initialize();
        void terminate();

        bool loadFromFile(std::string const& filename);
        bool saveToFile(std::string const& filename);

        ah::ActionTarget::ActionMapPtr getPlayerInput();

    private:
        Configuration();
        ~Configuration();

        static Configuration mInstance;

        ah::ActionTarget::ActionMapPtr mPlayerInput;
};

#endif // CONFIGURATION_HPP
