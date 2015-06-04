#include "Chat.hpp"
#include "World.hpp"
#include "OnlineManager.hpp"

Chat::Chat(World& world) : mWorld(world)
{
    setPosition(0,550);

    mTextField = mContainer.create<sg::TextField>();
    mTextField->setSize(sf::Vector2f(300,35));
    mTextField->setPosition(1.f,-mTextField->getSize().y);
    mTextField->setFillColor(sf::Color(95,95,95,175));
    mTextField->setOutlineColor(sf::Color(0,0,0,175));
    mTextField->setOutlineThickness(1.f);
    mTextField->setFont(mWorld.getApplication().getFont("Assets/Fonts/sansation.ttf"));
    mTextField->setTextColor(sf::Color::White);
    mTextField->setCharacterSize(18);
    mTextField->setTextAlign(sg::TextField::Left);
    mTextField->setCallback([&](){},0);
    mTextField->setStringMaxSize(28);
    mTextField->getText().move(0,-8.f);

    mShape.setFillColor(sf::Color(95,95,95,175));
    mShape.setOutlineColor(sf::Color(0,0,0,175));
    mShape.setOutlineThickness(1.f);

    mWriting = false;
}

void Chat::handleEvent(sf::Event const& event)
{
    if (mWriting)
    {
        mContainer.update(event,mWorld.getApplication().getMousePosition());
    }
}

void Chat::update(sf::Time dt)
{
    if (mTexts.size() >= 1)
    {
        if (mTexts.front().second.getElapsedTime() > sf::seconds(10))
        {
            mTexts.erase(mTexts.begin());
            update();
        }
    }
}

void Chat::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    if (mWriting)
    {
        target.draw(mContainer,states);
    }
    if (mTexts.size() > 0)
    {
        target.draw(mShape,states);
    }
    for (unsigned int i = 0; i < mTexts.size(); i++)
    {
        target.draw(mTexts[i].first,states);
    }
}

void Chat::add(std::string const& username, std::string const& message)
{
    mTexts.push_back(std::make_pair<sf::Text,sf::Clock>(sf::Text(),sf::Clock()));
    mTexts.back().first.setFont(mWorld.getApplication().getFont("Assets/Fonts/sansation.ttf"));
    mTexts.back().first.setCharacterSize(18);
    if (username == "")
    {
        mTexts.back().first.setString(message);
    }
    else
    {
        mTexts.back().first.setString(username + " : " + message);
    }
    mTexts.back().first.setColor(sf::Color::White);

    if (mTexts.size() >= 5)
    {
        mTexts.erase(mTexts.begin());
    }

    update();
}

void Chat::write(bool writing)
{
    mWriting = writing;
    if (mWriting)
    {
        mTextField->setString("");
        mTextField->gainFocus();
    }
    update();
}

bool Chat::isWriting() const
{
    return mWriting;
}

void Chat::send()
{
    if (mTextField->getString() != "")
    {
        mWorld.getOnlineManager().sendMessage(mTextField->getString());
        mTextField->setString("");
        mTextField->lostFocus();
    }
    mWriting = false;
    update();
}

void Chat::update()
{
    float pos = 5.f;
    sf::Vector2f size = sf::Vector2f(300.f,15.f);

    if (mWriting)
    {
        pos += 46.f;
    }

    for (auto itr = mTexts.rbegin(); itr != mTexts.rend(); itr++)
    {
        pos += itr->first.getGlobalBounds().height;
        itr->first.setPosition(sf::Vector2f(5.f,-pos));
        pos += 10.f;
        size.y += itr->first.getGlobalBounds().height + 10.f;
        size.x = std::max(10.f + itr->first.getGlobalBounds().width,size.x);
    }

    mShape.setSize(size);
    mShape.setPosition(1,-pos);
}
