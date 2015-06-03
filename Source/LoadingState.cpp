#include "LoadingState.hpp"
#include "App.hpp"
#include "OnlineManager.hpp"

LoadingState::LoadingState(ah::StateManager& manager) : ah::State(manager)
, mOnlineManager(App::instance().getOnlineManager())
{
    mType = LoadingState::getID();

    mConnectingState = 0;

    mTimer = mContainer.create<sg::Timer>();
    mTimer->setSize(sf::Vector2f(600,50));
    mTimer->setPosition(100,400);
    mTimer->setFillColor(sf::Color(36, 44, 102));
    mTimer->setFont(getApplication().getFont("Assets/Fonts/sansation.ttf"));
    mTimer->setTextColor(sf::Color::White);
    mTimer->setCharacterSize(20);
    mTimer->getShapeTop().setFillColor(sf::Color(36, 44, 168));
    mTimer->restart(sf::seconds(0.2));
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
        getApplication() << "Linking to localhost ...";
        if (mOnlineManager.connect("localhost",4567))
        {
            getApplication() << "Linked to localhost !";
            mConnectingState++;
            mOnlineManager.sendLogin("cmdu76","bla");
            mClock.restart();
        }
    }

    if (mConnectingState == 1)
    {
        mOnlineManager.handlePackets();

        if (mOnlineManager.isOk())
        {
            mConnectingState++;
            getApplication() << "Connecting to the game !";
        }
    }
    if (mConnectingState == 2)
    {
        toGame();
    }

    getApplication().setDebugInfo("Co",ah::to_string(mConnectingState));

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
