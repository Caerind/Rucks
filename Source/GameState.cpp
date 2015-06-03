#include "GameState.hpp"
#include "App.hpp"

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
    return true;
}

bool GameState::update(sf::Time dt)
{
    return true;
}

void GameState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
}

void GameState::onActivate()
{
    mConnections.clear();

    // Pause
    mConnections["pause"] = getApplication().getCallbackSystem().connect("pause",[&](thor::ActionContext<std::string> context){toPause();});
}

void GameState::onDeactivate()
{
    for (auto itr = mConnections.begin(); itr != mConnections.end(); itr++)
    {
        itr->second.disconnect();
    }
    mConnections.clear();
}

void GameState::toPause()
{
    requestPush(PauseState::getID());
}