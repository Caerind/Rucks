#include "World.hpp"

World World::mInstance;

World& World::instance()
{
    return mInstance;
}

void World::initialize()
{
    mOnline = false;
    mServer = false;
    // Load resources
}

void World::terminate()
{
    // Release resources
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
}

void World::update(sf::Time dt)
{
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}

ah::ResourceHolder& World::getResources()
{
    return mResources;
}

sf::View& World::getView()
{
    return mView;
}

bool World::isOnline() const
{
    return mOnline;
}

bool World::isServer() const
{
    return mServer;
}

World::World()
{

}

World::~World()
{

}
