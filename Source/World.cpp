#include "World.hpp"

World World::mInstance;

World& World::instance()
{
    return mInstance;
}

void World::initialize()
{
    mIsOnline = false;
    mIsServer = false;

    // Load resources
    mResources.loadTexture("tileset","Assets/Textures/tileset.png");
}

void World::terminate()
{
    // Release resources
    mResources.releaseTexture("tileset");

    mChunks.clear();
}

bool World::loadFromFile(std::string const& filename)
{
    return true;
}

bool World::saveToFile(std::string const& filename)
{
    return true;
}

void World::handleEvent(sf::Event const& event)
{
    // Zoom
    if (event.type == sf::Event::MouseWheelScrolled && event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
    {
        if (event.mouseWheelScroll.delta < 1)
        {
            if (mView.getSize().x < 1024.f)
                mView.zoom(1.2f);
        }
        else
        {
            if (mView.getSize().x > 320.f)
                mView.zoom(0.8f);
        }
    }
}

void World::update(sf::Time dt)
{
    mChunks.update(mView);
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::View defaultView = target.getView();

    target.setView(mView);

    mChunks.draw(target, mView, 0);
    mChunks.draw(target, mView, 1);
    mChunks.draw(target, mView, 2);

    target.setView(defaultView);
}

ah::ResourceHolder& World::getResources()
{
    return mResources;
}

sf::View& World::getView()
{
    return mView;
}

ChunkManager& World::getChunks()
{
    return mChunks;
}

bool World::isOnline() const
{
    return mIsOnline;
}

bool World::isServer() const
{
    return mIsServer;
}

World::World()
{

}

World::~World()
{

}
