#include "MenuState.hpp"
#include "../Base/App.hpp"

MenuState::MenuState(ah::StateManager& manager) : ah::State(manager)
{
    mType = MenuState::getID();

    mShape.setSize(static_cast<sf::Vector2f>(getApplication().getSize()));
    mShape.setTexture(&getApplication().getTexture("Assets/Textures/background.png"));

    mPregame = mContainer.create<sg::Box>();
    mPregame->setSize(sf::Vector2f(300,60));
    mPregame->setPosition(250,200);
    mPregame->setTexture(getApplication().getTexture("Assets/Textures/gui.png"));
    mPregame->setTextureRect(sf::IntRect(0,0,300,50),0);
    mPregame->setTextureRect(sf::IntRect(0,50,300,50),1);
    mPregame->setFont(getApplication().getFont("Assets/Fonts/aniron.ttf"));
    mPregame->setTextAlign(sg::Box::Center);
    mPregame->setTextColor(sf::Color::White);
    mPregame->setString("Play");
    mPregame->setCharacterSize(20);
    mPregame->setCallback([&](){toPreGame();},0);

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

    mQuit = mContainer.create<sg::Box>();
    mQuit->setSize(sf::Vector2f(300,60));
    mQuit->setPosition(250,400);
    mQuit->setTexture(getApplication().getTexture("Assets/Textures/gui.png"));
    mQuit->setTextureRect(sf::IntRect(0,0,300,50),0);
    mQuit->setTextureRect(sf::IntRect(0,50,300,50),1);
    mQuit->setFont(getApplication().getFont("Assets/Fonts/aniron.ttf"));
    mQuit->setTextAlign(sg::Box::Center);
    mQuit->setTextColor(sf::Color::White);
    mQuit->setString("Quit");
    mQuit->setCharacterSize(20);
    mQuit->setCallback([&](){quitGame();},0);
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
    target.draw(mShape,states);
    target.draw(mContainer,states);
}

void MenuState::onActivate()
{
    mPregame->setEnabled(true);
    mSettings->setEnabled(true);
    mQuit->setEnabled(true);
}

void MenuState::onDeactivate()
{
    mPregame->setEnabled(false);
    mSettings->setEnabled(false);
    mQuit->setEnabled(false);
}

void MenuState::toPreGame()
{
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
