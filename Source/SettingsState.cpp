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

    auto back = mContainer.create<sg::Box>();
    back->setSize(sf::Vector2f(300,60));
    back->setPosition(250,400);
    back->setTexture(getApplication().getTexture("Assets/Textures/gui.png"));
    back->setTextureRect(sf::IntRect(0,0,300,50),0);
    back->setTextureRect(sf::IntRect(0,50,300,50),1);
    back->setFont(getApplication().getFont("Assets/Fonts/aniron.ttf"));
    back->setTextAlign(sg::Box::Center);
    back->setTextColor(sf::Color::White);
    back->setString("Back to " + mLastState);
    back->setCharacterSize(20);
    back->setCallback([&](){backState();},0);
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
