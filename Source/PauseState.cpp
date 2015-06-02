#include "PauseState.hpp"
#include "App.hpp"

PauseState::PauseState(ah::StateManager& manager) : ah::State(manager)
{
    mType = PauseState::getID();
}

std::string PauseState::getID()
{
    return "PauseState";
}

bool PauseState::handleEvent(sf::Event const& event)
{
    return true;
}

bool PauseState::update(sf::Time dt)
{
    return true;
}

void PauseState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
}
