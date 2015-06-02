#include "MenuState.hpp"
#include "App.hpp"

MenuState::MenuState(ah::StateManager& manager) : ah::State(manager)
{
    mType = MenuState::getID();

    auto pregame = mContainer.create<sg::Box>();
    pregame->setSize(sf::Vector2f(300,60));
    pregame->setPosition(250,200);
    pregame->setFillColor(sf::Color(127, 137, 168),0);
    pregame->setFillColor(sf::Color(167, 179, 205),1);
    pregame->setFont(getApplication().getFont("Assets/Fonts/aniron.ttf"));
    pregame->setTextAlign(sg::Box::Center);
    pregame->setTextColor(sf::Color::White);
    pregame->setString("Play");
    pregame->setCharacterSize(20);
    pregame->setCallback([&](){toPreGame();},0);

    auto settings = mContainer.create<sg::Box>();
    settings->setSize(sf::Vector2f(300,60));
    settings->setPosition(250,300);
    settings->setFillColor(sf::Color(127, 137, 168),0);
    settings->setFillColor(sf::Color(167, 179, 205),1);
    settings->setFont(getApplication().getFont("Assets/Fonts/aniron.ttf"));
    settings->setTextAlign(sg::Box::Center);
    settings->setTextColor(sf::Color::White);
    settings->setString("Settings");
    settings->setCharacterSize(20);
    settings->setCallback([&](){toSettings();},0);

    auto quit = mContainer.create<sg::Box>();
    quit->setSize(sf::Vector2f(300,60));
    quit->setPosition(250,400);
    quit->setFillColor(sf::Color(127, 137, 168),0);
    quit->setFillColor(sf::Color(167, 179, 205),1);
    quit->setFont(getApplication().getFont("Assets/Fonts/aniron.ttf"));
    quit->setTextAlign(sg::Box::Center);
    quit->setTextColor(sf::Color::White);
    quit->setString("Quit");
    quit->setCharacterSize(20);
    quit->setCallback([&](){quitGame();},0);
}

std::string MenuState::getID()
{
    return "MenuState";
}

bool MenuState::handleEvent(sf::Event const& event)
{
    mContainer.update(event,getApplication().getMousePosition());
    return true;
}

bool MenuState::update(sf::Time dt)
{
    mContainer.update();
    return true;
}

void MenuState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mContainer);
}

void MenuState::toPreGame()
{
    requestClear();
    requestPush(PreGameState::getID());
}

void MenuState::toSettings()
{
    requestPush(SettingsState::getID());
}

void MenuState::quitGame()
{
    requestClear();
    getApplication().close();
}
