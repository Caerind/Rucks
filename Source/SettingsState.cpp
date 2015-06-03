#include "SettingsState.hpp"
#include "App.hpp"

SettingsState::SettingsState(ah::StateManager& manager) : ah::State(manager)
{
    mType = SettingsState::getID();

    mLastState = mManager.getLastActiveStateType().substr(0,4);
    if (mLastState == "Paus")
        mLastState = "Game";

    mShape.setSize(static_cast<sf::Vector2f>(getApplication().getSize()));
    mShape.setFillColor(sf::Color(35,35,35,150));

    mBack = mContainer.create<sg::Box>();
    mBack->setSize(sf::Vector2f(300,60));
    mBack->setPosition(250,400);
    mBack->setTexture(getApplication().getTexture("Assets/Textures/gui.png"));
    mBack->setTextureRect(sf::IntRect(0,0,300,50),0);
    mBack->setTextureRect(sf::IntRect(0,50,300,50),1);
    mBack->setFont(getApplication().getFont("Assets/Fonts/aniron.ttf"));
    mBack->setTextAlign(sg::Box::Center);
    mBack->setTextColor(sf::Color::White);
    mBack->setString("Back to " + mLastState);
    mBack->setCharacterSize(20);
    mBack->setCallback([&](){backState();},0);
}

std::string SettingsState::getID()
{
    return "SettingsState";
}

bool SettingsState::handleEvent(sf::Event const& event)
{
    mContainer.update(event,getApplication().getMousePosition());
    return false;
}

bool SettingsState::update(sf::Time dt)
{
    mContainer.update();
    return true;
}

void SettingsState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mShape,states);
    target.draw(mContainer,states);
}

void SettingsState::backState()
{
    requestPop();
}
