#include "LoadingState.hpp"
#include "App.hpp"

LoadingState::LoadingState(ah::StateManager& manager) : ah::State(manager)
{
    mType = LoadingState::getID();
}

std::string LoadingState::getID()
{
    return "LoadingState";
}

bool LoadingState::handleEvent(sf::Event const& event)
{
    return true;
}

bool LoadingState::update(sf::Time dt)
{
    return true;
}

void LoadingState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
}
