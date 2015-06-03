#include "IntroState.hpp"
#include "App.hpp"

IntroState::IntroState(ah::StateManager& manager) : ah::State(manager)
{
    mType = IntroState::getID();

    mTimer = mContainer.create<sg::Timer>();
    mTimer->setSize(sf::Vector2f(600,50));
    mTimer->setPosition(100,400);
    mTimer->setFillColor(sf::Color(36, 44, 102));
    mTimer->getShapeTop().setFillColor(sf::Color(36, 44, 168));
    mTimer->restart(sf::seconds(0.3));
    mTimer->setCallback([&](){toMenu();},0);
}

std::string IntroState::getID()
{
    return "IntroState";
}

bool IntroState::handleEvent(sf::Event const& event)
{
    mContainer.update(event,getApplication().getMousePosition());
    return true;
}

bool IntroState::update(sf::Time dt)
{
    mContainer.update();
    return true;
}

void IntroState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mContainer,states);
}

void IntroState::toMenu()
{
    requestClear();
    requestPush(MenuState::getID());
}
