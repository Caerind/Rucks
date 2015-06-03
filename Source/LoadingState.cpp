#include "LoadingState.hpp"
#include "App.hpp"

LoadingState::LoadingState(ah::StateManager& manager) : ah::State(manager)
{
    mType = LoadingState::getID();

    mTimer = mContainer.create<sg::Timer>();
    mTimer->setSize(sf::Vector2f(600,50));
    mTimer->setPosition(100,400);
    mTimer->setFillColor(sf::Color(36, 44, 102));
    mTimer->setFont(getApplication().getFont("Assets/Fonts/sansation.ttf"));
    mTimer->setTextColor(sf::Color::White);
    mTimer->setCharacterSize(20);
    mTimer->getShapeTop().setFillColor(sf::Color(36, 44, 168));
    mTimer->restart(sf::seconds(1));
    mTimer->setCallback([&](){toGame();},0);
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
