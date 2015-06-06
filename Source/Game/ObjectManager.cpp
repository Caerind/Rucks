#include "ObjectManager.hpp"
#include "World.hpp"

ObjectManager::ObjectManager(World& world) : mWorld(world)
{
}

GameObject::Ptr ObjectManager::createGameObject(unsigned int id)
{
    std::shared_ptr<GameObject> g = std::make_shared<GameObject>(mWorld);
    g->setId(id);
    mGameObjects.push_back(g);
    return g;
}

Entity::Ptr ObjectManager::createEntity(unsigned int id)
{
    std::shared_ptr<Entity> g = std::make_shared<Entity>(mWorld);
    g->setId(id);
    mGameObjects.push_back(g);
    mEntities.push_back(g);
    return g;
}

Player::Ptr ObjectManager::createPlayer(unsigned int id)
{
    std::shared_ptr<Player> g = std::make_shared<Player>(mWorld);
    g->setId(id);
    mGameObjects.push_back(g);
    mPlayers.push_back(g);
    return g;
}


void ObjectManager::handleEvent(sf::Event const& event)
{
    for (unsigned int i = 0; i < mGameObjects.size(); i++)
    {
        if (mGameObjects[i] != nullptr)
        {
            mGameObjects[i]->handleEvent(event);
        }
    }
}

void ObjectManager::update(sf::Time dt)
{
    mWorld.getApplication().setDebugInfo("Entities",ah::to_string(mGameObjects.size()));

    for (unsigned int i = 0; i < mGameObjects.size(); i++)
    {
        if (mGameObjects[i] != nullptr)
        {
            mGameObjects[i]->update(dt);
        }
    }

    std::sort(mGameObjects.begin(), mGameObjects.end(),[](GameObject::Ptr a, GameObject::Ptr b) -> bool { return a->getPosition().y < b->getPosition().y; });
}

void ObjectManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (unsigned int i = 0; i < mGameObjects.size(); i++)
    {
        if (mGameObjects[i] != nullptr)
        {
            target.draw(*mGameObjects[i],states);
        }
    }
}



void ObjectManager::setPlayerId(unsigned int id)
{
    mPlayerId = id;
}

unsigned int ObjectManager::getPlayerId() const
{
    return mPlayerId;
}

void ObjectManager::remove(unsigned int id)
{
    for (auto itr = mGameObjects.begin(); itr != mGameObjects.end(); )
	{
		if ((*itr)->getId() == id)
            itr = mGameObjects.erase(itr);
		else
			++itr;
	}

	for (auto itr = mEntities.begin(); itr != mEntities.end(); )
	{
		if ((*itr)->getId() == id)
            itr = mEntities.erase(itr);
		else
			++itr;
	}

	for (auto itr = mPlayers.begin(); itr != mPlayers.end(); )
	{
		if ((*itr)->getId() == id)
            itr = mPlayers.erase(itr);
		else
			++itr;
	}
}

GameObject::Ptr ObjectManager::getGameObject(unsigned int id)
{
    for (unsigned int i = 0; i < mGameObjects.size(); i++)
    {
        if (mGameObjects[i] != nullptr)
        {
            if (mGameObjects[i]->getId() == id)
            {
                return mGameObjects[i];
            }
        }
    }
    return nullptr;
}

Entity::Ptr ObjectManager::getEntity(unsigned int id)
{
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        if (mEntities[i] != nullptr)
        {
            if (mEntities[i]->getId() == id)
            {
                return mEntities[i];
            }
        }
    }
    return nullptr;
}

Player::Ptr ObjectManager::getPlayer(unsigned int id)
{
    for (unsigned int i = 0; i < mPlayers.size(); i++)
    {
        if (mPlayers[i] != nullptr)
        {
            if (mPlayers[i]->getId() == id)
            {
                return mPlayers[i];
            }
        }
    }
    return nullptr;
}

Player::Ptr ObjectManager::getPlayer()
{
    for (unsigned int i = 0; i < mPlayers.size(); i++)
    {
        if (mPlayers[i] != nullptr)
        {
            if (mPlayers[i]->getId() == mPlayerId)
            {
                return mPlayers[i];
            }
        }
    }
    return nullptr;
}
