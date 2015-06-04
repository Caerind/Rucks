#include "Chat.hpp"
#include "World.hpp"
#include "OnlineManager.hpp"

Chat::Chat(World& world) : mWorld(world)
{
    mTextField = mContainer.create<sg::TextField>();
    mTextField->setSize(sf::Vector2f(300,50));
    mTextField->setFillColor(sf::Color(95,95,95));
    mTextField->setFont(mWorld.getApplication().getFont("Assets/Fonts/aniron.ttf"));
    mTextField->setTextColor(sf::Color::White);
    mTextField->setCharacterSize(18);
    mTextField->setTextAlign(sg::TextField::Left);
    mTextField->setCallback([&](){},0);

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
    mTexts.back().first.setString(username + " : " + message);
    mTexts.back().first.setColor(sf::Color(175,175,175));

    if (mTexts.size() >= 5)
    {
        mTexts.erase(mTexts.begin());
        update();
    }
}

void Chat::write(bool writing)
{
    mWriting = writing;
    if (mWriting)
    {
        mTextField->setString("");
        mTextField->gainFocus();
        update();
    }
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
}

void Chat::update()
{

}
