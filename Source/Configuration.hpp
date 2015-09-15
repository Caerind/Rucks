#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include "../Aharos/Application/ActionTarget.hpp"

class Configuration
{
    public:
        static Configuration& instance();

        void initialize();
        void terminate();

        ah::ActionTarget::ActionMapPtr getPlayerInput();

    private:
        Configuration();
        ~Configuration();

        static Configuration mInstance;

        ah::ActionTarget::ActionMapPtr mPlayerInput;
};

#endif // CONFIGURATION_HPP
