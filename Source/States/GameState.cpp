#include "GameState.hpp"
#include "../Base/App.hpp"

GameState::GameState(ah::StateManager& manager) : ah::State(manager), mWorld(App::instance().getWorld())
{
    mType = GameState::getID();
}

std::string GameState::getID()
{
    return "GameState";
}

bool GameState::handleEvent(sf::Event const& event)
{
    mWorld.handleEvent(event);
    return true;
}

bool GameState::update(sf::Time dt)
{
    mWorld.update(dt);

    if (!App::instance().getOnlineManager().isOk())
        toEnd();

    return true;
}

void GameState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mWorld,states);
}

void GameState::onActivate()
{
    mConnections.clear();
    mConnections["pause"] = getApplication().getCallbackSystem().connect("pause",[&](tContext context){toPause();});
    mConnections["writing"] = getApplication().getCallbackSystem().connect("writing",[&](tContext context){if (!mWorld.getChat().isWriting()) mWorld.getChat().write(true);});
    mConnections["sendMessage"] = getApplication().getCallbackSystem().connect("sendMessage",[&](tContext context){if (mWorld.getChat().isWriting()) mWorld.getChat().send();});

    App::instance().getOnlineManager().resetTimeSinceLastPacket();
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

void GameState::toEnd()
{
    App::instance().getOnlineManager().disconnect();
    requestClear();
    requestPush(EndState::getID());
}
