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
    (*mPlayerInput)["spell1"] = thor::Action(sf::Keyboard::Num1,thor::Action::PressOnce);
    (*mPlayerInput)["spell2"] = thor::Action(sf::Keyboard::Num2,thor::Action::PressOnce);
    (*mPlayerInput)["spell3"] = thor::Action(sf::Keyboard::Num3,thor::Action::PressOnce);
    (*mPlayerInput)["spell4"] = thor::Action(sf::Keyboard::Num4,thor::Action::PressOnce);
    (*mPlayerInput)["spell5"] = thor::Action(sf::Keyboard::Num5,thor::Action::PressOnce);
}

void Configuration::terminate()
{
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
