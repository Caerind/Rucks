#include "PreGameState.hpp"
#include "App.hpp"

PreGameState::PreGameState(ah::StateManager& manager) : ah::State(manager)
{
    mType = PreGameState::getID();

    auto loading = mContainer.create<sg::Box>();
    loading->setSize(sf::Vector2f(300,60));
    loading->setPosition(250,200);
    loading->setFillColor(sf::Color(127, 137, 168),0);
    loading->setFillColor(sf::Color(167, 179, 205),1);
    loading->setFont(getApplication().getFont("Assets/Fonts/aniron.ttf"));
    loading->setTextAlign(sg::Box::Center);
    loading->setTextColor(sf::Color::White);
    loading->setString("Play");
    loading->setCharacterSize(20);
    loading->setCallback([&](){toLoading();},0);

    auto menu = mContainer.create<sg::Box>();
    menu->setSize(sf::Vector2f(300,60));
    menu->setPosition(250,300);
    menu->setFillColor(sf::Color(127, 137, 168),0);
    menu->setFillColor(sf::Color(167, 179, 205),1);
    menu->setFont(getApplication().getFont("Assets/Fonts/aniron.ttf"));
    menu->setTextAlign(sg::Box::Center);
    menu->setTextColor(sf::Color::White);
    menu->setString("Back to Menu");
    menu->setCharacterSize(20);
    menu->setCallback([&](){toMenu();},0);
}

std::string PreGameState::getID()
{
    return "PreGameState";
}

bool PreGameState::handleEvent(sf::Event const& event)
{
    mContainer.update(event,getApplication().getMousePosition());
    return true;
}

bool PreGameState::update(sf::Time dt)
{
    mContainer.update();
    return true;
}

void PreGameState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mContainer);
}

void PreGameState::toLoading()
{
    requestClear();
    requestPush(LoadingState::getID());
}

void PreGameState::toMenu()
{
    requestClear();
    requestPush(MenuState::getID());
}
