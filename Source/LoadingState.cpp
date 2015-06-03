#include "LoadingState.hpp"
#include "App.hpp"

LoadingState::LoadingState(ah::StateManager& manager) : ah::State(manager)
{
    mType = LoadingState::getID();

    auto timer = mContainer.create<sg::Timer>();
    timer->setSize(sf::Vector2f(600,50));
    timer->setPosition(100,400);
    timer->setFillColor(sf::Color(36, 44, 102));
    timer->setFont(getApplication().getFont("Assets/Fonts/sansation.ttf"));
    timer->setTextColor(sf::Color::White);
    timer->setCharacterSize(20);
    timer->getShapeTop().setFillColor(sf::Color(36, 44, 168));
    timer->restart(sf::seconds(1));
    timer->setCallback([&](){toGame();},0);
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
