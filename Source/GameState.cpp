#include "GameState.hpp"
#include "App.hpp"

GameState::GameState(ah::StateManager& manager) : ah::State(manager), mWorld(manager.getApplication(),true)
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
    {
        App::instance() << ah::to_string(App::instance().getOnlineManager().isLinked());
        App::instance() << ah::to_string(App::instance().getOnlineManager().isConnected());
        App::instance() << ah::to_string(App::instance().getOnlineManager().timedOut());

        toEnd();
    }

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
    mConnections["pause"] = getApplication().getCallbackSystem().connect("pause",[&](thor::ActionContext<std::string> context){toPause();});
    mConnections["writing"] = getApplication().getCallbackSystem().connect("writing",[&](thor::ActionContext<std::string> context){if (!mWorld.getChat().isWriting()) mWorld.getChat().write(true);});
    mConnections["sendMessage"] = getApplication().getCallbackSystem().connect("sendMessage",[&](thor::ActionContext<std::string> context){if (mWorld.getChat().isWriting()) mWorld.getChat().send();});

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
