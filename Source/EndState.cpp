#include "EndState.hpp"
#include "App.hpp"

EndState::EndState(ah::StateManager& manager) : ah::State(manager)
{
    mType = EndState::getID();

    mMenu = mContainer.create<sg::Box>();
    mMenu->setSize(sf::Vector2f(300,60));
    mMenu->setPosition(250,200);
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

std::string EndState::getID()
{
    return "EndState";
}

bool EndState::handleEvent(sf::Event const& event)
{
    mContainer.update(event,getApplication().getMousePosition());
    return true;
}

bool EndState::update(sf::Time dt)
{
    mContainer.update();
    return true;
}

void EndState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mContainer,states);
}

void EndState::toMenu()
{
    requestClear();
    requestPush(MenuState::getID());
}
