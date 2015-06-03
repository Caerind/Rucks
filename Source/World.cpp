#include "World.hpp"

World::World(ah::Application& application) : mApplication(application)
{
}

World::~World()
{
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

bool World::isOnline()
{
    return true;
}

ah::Application& World::getApplication()
{
    return mApplication;
}
