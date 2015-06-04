#include "World.hpp"
#include "App.hpp"
#include "OnlineManager.hpp"

World::World(ah::Application& application, bool online)
: mApplication(application)
, mChunkManager(*this)
, mEntityManager(*this)
, mOnlineManager(App::instance().getOnlineManager())
, mChat(*this)
, mView(mApplication.getDefaultView())
, mOnline(online)
{
    if (mOnline)
    {
        mOnlineManager.setWorld(this);
    }
}

World::~World()
{
}

void World::handleEvent(sf::Event const& event)
{
    mEntityManager.handleEvent(event);
    mChat.handleEvent(event);
    sfh::handleZoom(event,mView,0.2f);
}

void World::update(sf::Time dt)
{
    if (isOnline())
    {
        mOnlineManager.handlePackets();
    }
    mEntityManager.update(dt);
    mChunkManager.update();
    mChat.update(dt);
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.setView(mView);

    mChunkManager.render(target,0);
    mChunkManager.render(target,1);

    target.draw(mEntityManager,states);

    mChunkManager.render(target,2);

    target.setView(target.getDefaultView());

    target.draw(mChat,states);
}

ah::Application& World::getApplication()
{
    return mApplication;
}

ChunkManager& World::getChunkManager()
{
    return mChunkManager;
}

EntityManager& World::getEntityManager()
{
    return mEntityManager;
}

OnlineManager& World::getOnlineManager()
{
    return mOnlineManager;
}

Chat& World::getChat()
{
    return mChat;
}

sf::View& World::getView()
{
    return mView;
}

bool World::isOnline()
{
    return mOnline;
}
