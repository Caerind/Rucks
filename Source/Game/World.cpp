#include "World.hpp"
#include "../Base/App.hpp"
#include "../Base/OnlineManager.hpp"

World::World(bool online)
: mChunkManager(*this)
, mObjectManager(*this)
, mOnlineManager(App::instance().getOnlineManager())
, mChat(*this)
, mView(App::instance().getDefaultView())
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
    mObjectManager.handleEvent(event);
    mChat.handleEvent(event);
    sfh::handleZoom(event,mView,0.2f);
}

void World::update(sf::Time dt)
{
    if (isOnline())
    {
        mOnlineManager.handlePackets();
    }

    mObjectManager.update(dt);
    mChunkManager.update();
    mChat.update(dt);

    sf::Vector2f mvt;
    if (getApplication().isActionActive("up") && !mChat.isWriting())
        mvt.y--;
    if (getApplication().isActionActive("down") && !mChat.isWriting())
        mvt.y++;
    if (getApplication().isActionActive("left") && !mChat.isWriting())
        mvt.x--;
    if (getApplication().isActionActive("right") && !mChat.isWriting())
        mvt.x++;
    mOnlineManager.sendPlayerUpdate(mvt,getApplication().getMousePositionView(mView));

    if (mObjectManager.getPlayer() != nullptr)
    {
        mView.setCenter(mObjectManager.getPlayer()->getPosition());
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2f m = getApplication().getMousePositionView(mView);
        sf::Vector2i c = ChunkManager::worldToChunk(m);
        sf::Vector2i t = ChunkManager::worldToTile(m);
        mOnlineManager.modifyChunk(c,t,0,800);
    }

}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.setView(mView);

    mChunkManager.render(target,0);
    mChunkManager.render(target,1);

    target.draw(mObjectManager,states);

    mChunkManager.render(target,2);

    target.setView(target.getDefaultView());

    target.draw(mChat,states);
}

ah::Application& World::getApplication()
{
    return App::instance();
}

ChunkManager& World::getChunkManager()
{
    return mChunkManager;
}

ObjectManager& World::getObjectManager()
{
    return mObjectManager;
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
