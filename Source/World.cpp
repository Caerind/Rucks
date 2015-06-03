#include "World.hpp"
#include "App.hpp"
#include "OnlineManager.hpp"

World::World(ah::Application& application, bool online)
: mApplication(application)
, mChunkManager(*this)
, mEntityManager(*this)
, mOnlineManager(App::instance().getOnlineManager())
, mView(mApplication.getDefaultView())
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
}

void World::update(sf::Time dt)
{
    if (isOnline())
    {
        mOnlineManager.handlePacket();
    }
    mEntityManager.update(dt);
    mChunkManager.update();
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    mChunkManager.render(target,0);
    mChunkManager.render(target,1);

    target.draw(mEntityManager,states);

    mChunkManager.render(target,2);
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

sf::View& World::getView()
{
    return mView;
}

bool World::isOnline()
{
    return mOnline;
}
