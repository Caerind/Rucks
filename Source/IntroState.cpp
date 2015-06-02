#include "IntroState.hpp"
#include "App.hpp"

IntroState::IntroState(ah::StateManager& manager) : ah::State(manager)
{
    mType = IntroState::getID();

    auto timer = mContainer.create<sg::Timer>();
    timer->setSize(sf::Vector2f(600,50));
    timer->setPosition(100,400);
    timer->setFillColor(sf::Color(36, 44, 102));
    timer->getShapeTop().setFillColor(sf::Color(36, 44, 168));
    timer->restart(sf::seconds(3));
    timer->setCallback([&](){toMenu();},0);
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
    target.draw(mContainer);
}

void IntroState::toMenu()
{
    requestClear();
    requestPush(MenuState::getID());
}
