#include "GameState.hpp"

GameState::GameState(ah::StateManager& manager) : ah::State(manager)
{
    mType = GameState::getID();
}

std::string GameState::getID()
{
    return "GameState";
}

bool GameState::handleEvent(sf::Event const& event)
{
    World::instance().handleEvent(event);
    return true;
}

bool GameState::update(sf::Time dt)
{
    World::instance().update(dt);
    return true;
}

void GameState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    World::instance().render(target);
}

void GameState::onActivate()
{
    World::instance().initialize();
}

void GameState::onDeactivate()
{
    World::instance().terminate();
}
