#include "GameState.hpp"
#include "../../Lib/Aharos/Application.hpp"
#include "../World.hpp"

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
    target.draw(World::instance());
}

void GameState::onActivate()
{

}

void GameState::onDeactivate()
{

}
