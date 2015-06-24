#include "Configuration.hpp"

Configuration Configuration::mInstance;

Configuration& Configuration::instance()
{
    return mInstance;
}

void Configuration::initialize()
{
    (*mPlayerInput)["up"] = thor::Action(sf::Keyboard::Z,thor::Action::Hold);
    (*mPlayerInput)["left"] = thor::Action(sf::Keyboard::Q,thor::Action::Hold);
    (*mPlayerInput)["down"] = thor::Action(sf::Keyboard::S,thor::Action::Hold);
    (*mPlayerInput)["right"] = thor::Action(sf::Keyboard::D,thor::Action::Hold);
    (*mPlayerInput)["action"] = thor::Action(sf::Mouse::Left,thor::Action::PressOnce);
}

void Configuration::terminate()
{
}

bool Configuration::loadFromFile(std::string const& filename)
{
    return true;
}

bool Configuration::saveToFile(std::string const& filename)
{
    return true;
}

ah::ActionTarget::ActionMapPtr Configuration::getPlayerInput()
{
    return mPlayerInput;
}

Configuration::Configuration()
{
    mPlayerInput = std::make_shared<thor::ActionMap<std::string>>();
}

Configuration::~Configuration()
{
}
