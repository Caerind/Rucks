#include "PauseState.hpp"
#include "App.hpp"

PauseState::PauseState(ah::StateManager& manager) : ah::State(manager)
{
    mType = PauseState::getID();

    mShape.setSize(static_cast<sf::Vector2f>(getApplication().getSize()));
    mShape.setFillColor(sf::Color(35,35,35,150));

    mGame = mContainer.create<sg::Box>();
    mGame->setSize(sf::Vector2f(300,60));
    mGame->setPosition(250,200);
    mGame->setTexture(getApplication().getTexture("Assets/Textures/gui.png"));
    mGame->setTextureRect(sf::IntRect(0,0,300,50),0);
    mGame->setTextureRect(sf::IntRect(0,50,300,50),1);
    mGame->setFont(getApplication().getFont("Assets/Fonts/aniron.ttf"));
    mGame->setTextAlign(sg::Box::Center);
    mGame->setTextColor(sf::Color::White);
    mGame->setString("Resume");
    mGame->setCharacterSize(20);
    mGame->setCallback([&](){toGame();},0);

    mSettings = mContainer.create<sg::Box>();
    mSettings->setSize(sf::Vector2f(300,60));
    mSettings->setPosition(250,300);
    mSettings->setTexture(getApplication().getTexture("Assets/Textures/gui.png"));
    mSettings->setTextureRect(sf::IntRect(0,0,300,50),0);
    mSettings->setTextureRect(sf::IntRect(0,50,300,50),1);
    mSettings->setFont(getApplication().getFont("Assets/Fonts/aniron.ttf"));
    mSettings->setTextAlign(sg::Box::Center);
    mSettings->setTextColor(sf::Color::White);
    mSettings->setString("Settings");
    mSettings->setCharacterSize(20);
    mSettings->setCallback([&](){toSettings();},0);

    mMenu = mContainer.create<sg::Box>();
    mMenu->setSize(sf::Vector2f(300,60));
    mMenu->setPosition(250,400);
    mMenu->setTexture(getApplication().getTexture("Assets/Textures/gui.png"));
    mMenu->setTextureRect(sf::IntRect(0,0,300,50),0);
    mMenu->setTextureRect(sf::IntRect(0,50,300,50),1);
    mMenu->setFont(getApplication().getFont("Assets/Fonts/aniron.ttf"));
    mMenu->setTextAlign(sg::Box::Center);
    mMenu->setTextColor(sf::Color::White);
    mMenu->setString("Menu");
    mMenu->setCharacterSize(20);
    mMenu->setCallback([&](){toMenu();},0);
}

std::string PauseState::getID()
{
    return "PauseState";
}

bool PauseState::handleEvent(sf::Event const& event)
{
    mContainer.update(event,getApplication().getMousePosition());
    return false;
}

bool PauseState::update(sf::Time dt)
{
    mContainer.update();
    return true;
}

void PauseState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mShape,states);
    target.draw(mContainer,states);
}

void PauseState::onActivate()
{
    mGame->setEnabled(true);
    mSettings->setEnabled(true);
    mMenu->setEnabled(true);
}

void PauseState::onDeactivate()
{
    mGame->setEnabled(false);
    mSettings->setEnabled(false);
    mMenu->setEnabled(false);
}

void PauseState::toGame()
{
    requestPop();
}

void PauseState::toSettings()
{
    requestPush(SettingsState::getID());
}

void PauseState::toMenu()
{
    requestClear();
    requestPush(MenuState::getID());
}
