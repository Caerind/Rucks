#include "LoadingState.hpp"
#include "../Base/App.hpp"
#include "../Base/OnlineManager.hpp"

LoadingState::LoadingState(ah::StateManager& manager) : ah::State(manager)
, mOnlineManager(App::instance().getOnlineManager())
{
    mType = LoadingState::getID();

    // Load Resources
    getApplication().getTexture("Assets/Textures/tileset.png");
    getApplication().getTexture("Assets/Textures/soldier1.png").setSmooth(true);

    mConnectingState = 0;

    mTimer = mContainer.create<sg::Timer>();
    mTimer->setSize(sf::Vector2f(600,50));
    mTimer->setPosition(100,400);
    mTimer->setFillColor(sf::Color(36, 44, 102));
    mTimer->getShapeTop().setFillColor(sf::Color(36, 44, 168));
    mTimer->restart(sf::seconds(10));
    mTimer->setCallback([&](){},0);

    mClock.restart();
}

std::string LoadingState::getID()
{
    return "LoadingState";
}

bool LoadingState::handleEvent(sf::Event const& event)
{
    mContainer.update(event,getApplication().getMousePosition());
    return true;
}

bool LoadingState::update(sf::Time dt)
{
    mContainer.update();

    if (mConnectingState == 0)
    {
        if (mOnlineManager.connect(getApplication().getData<std::string>("ip"),getApplication().getData<int>("port")))
        {
            mConnectingState++;
            mOnlineManager.sendLogin(getApplication().getData<std::string>("username"),"bla");
            mClock.restart();
        }
    }

    if (mConnectingState == 1)
    {
        mOnlineManager.handlePackets();

        if (mOnlineManager.isOk())
        {
            mConnectingState++;
            mClock.restart();
        }
    }
    if (mConnectingState == 2)
    {
        toGame();
    }

    if (mConnectingState < 2 && mClock.getElapsedTime() > sf::seconds(10))
    {
        App::instance().getOnlineManager().disconnect();
        toEnd();
    }

    return true;
}

void LoadingState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mContainer,states);
}

void LoadingState::toGame()
{
    requestClear();
    requestPush(GameState::getID());
}

void LoadingState::toEnd()
{
    requestClear();
    requestPush(EndState::getID());
}
