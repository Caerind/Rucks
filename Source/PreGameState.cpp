#include "PreGameState.hpp"
#include "App.hpp"

PreGameState::PreGameState(ah::StateManager& manager) : ah::State(manager)
{
    mType = PreGameState::getID();

    mShape.setSize(static_cast<sf::Vector2f>(getApplication().getSize()));
    mShape.setFillColor(sf::Color(35,35,35,150));

    mAddress = mContainer.create<sg::TextField>();
    mAddress->setSize(sf::Vector2f(300,60));
    mAddress->setPosition(250,100);
    mAddress->setTexture(getApplication().getTexture("Assets/Textures/gui.png"));
    mAddress->setTextureRect(sf::IntRect(0,0,300,50),0);
    mAddress->setTextureRect(sf::IntRect(0,50,300,50),1);
    mAddress->setFont(getApplication().getFont("Assets/Fonts/aniron.ttf"));
    mAddress->setTextAlign(sg::TextField::Center);
    mAddress->setTextColor(sf::Color::White);
    mAddress->setString("Ip Address");
    if (getApplication().getData<std::string>("ip") != "")
        mAddress->setString(getApplication().getData<std::string>("ip"));
    mAddress->setCharacterSize(20);

    mUsername = mContainer.create<sg::TextField>();
    mUsername->setSize(sf::Vector2f(300,60));
    mUsername->setPosition(250,200);
    mUsername->setTexture(getApplication().getTexture("Assets/Textures/gui.png"));
    mUsername->setTextureRect(sf::IntRect(0,0,300,50),0);
    mUsername->setTextureRect(sf::IntRect(0,50,300,50),1);
    mUsername->setFont(getApplication().getFont("Assets/Fonts/aniron.ttf"));
    mUsername->setTextAlign(sg::TextField::Center);
    mUsername->setTextColor(sf::Color::White);
    mUsername->setString("Username");
    if (getApplication().getData<std::string>("username") != "")
        mUsername->setString(getApplication().getData<std::string>("username"));
    mUsername->setCharacterSize(20);

    mLoading = mContainer.create<sg::Box>();
    mLoading->setSize(sf::Vector2f(300,60));
    mLoading->setPosition(250,300);
    mLoading->setTexture(getApplication().getTexture("Assets/Textures/gui.png"));
    mLoading->setTextureRect(sf::IntRect(0,0,300,50),0);
    mLoading->setTextureRect(sf::IntRect(0,50,300,50),1);
    mLoading->setFont(getApplication().getFont("Assets/Fonts/aniron.ttf"));
    mLoading->setTextAlign(sg::Box::Center);
    mLoading->setTextColor(sf::Color::White);
    mLoading->setString("Play");
    mLoading->setCharacterSize(20);
    mLoading->setCallback([&](){toLoading();},0);

    mMenu = mContainer.create<sg::Box>();
    mMenu->setSize(sf::Vector2f(300,60));
    mMenu->setPosition(250,400);
    mMenu->setTexture(getApplication().getTexture("Assets/Textures/gui.png"));
    mMenu->setTextureRect(sf::IntRect(0,0,300,50),0);
    mMenu->setTextureRect(sf::IntRect(0,50,300,50),1);
    mMenu->setFont(getApplication().getFont("Assets/Fonts/aniron.ttf"));
    mMenu->setTextAlign(sg::Box::Center);
    mMenu->setTextColor(sf::Color::White);
    mMenu->setString("Back to Menu");
    mMenu->setCharacterSize(20);
    mMenu->setCallback([&](){toMenu();},0);
}

std::string PreGameState::getID()
{
    return "PreGameState";
}

bool PreGameState::handleEvent(sf::Event const& event)
{
    mContainer.update(event,getApplication().getMousePosition());
    return false;
}

bool PreGameState::update(sf::Time dt)
{
    mContainer.update();
    return true;
}

void PreGameState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mShape,states);
    target.draw(mContainer,states);
}

void PreGameState::toLoading()
{
    getApplication().setData("ip",mAddress->getString());
    getApplication().setData("username",mUsername->getString());

    requestClear();
    requestPush(LoadingState::getID());
}

void PreGameState::toMenu()
{
    requestClear();
    requestPush(MenuState::getID());
}
