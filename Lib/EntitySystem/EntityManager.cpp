#include "EntityManager.hpp"
#include "Entity.hpp"
#include "System.hpp"

namespace es
{

EntityManager::EntityManager()
{
}

Entity::Ptr EntityManager::create(std::string const& name)
{
    mEntities.push_back(std::make_shared<Entity>(this,name));
    update(mEntities.back()->getId());
    return mEntities.back();
}

Entity::Ptr EntityManager::create(std::size_t id, std::string const& name)
{
    if (!idExist(id))
    {
        mEntities.push_back(std::make_shared<Entity>(this,name,id));
    }
    else
    {
        mEntities.push_back(std::make_shared<Entity>(this,name));
    }
    update(mEntities.back()->getId());
    return mEntities.back();
}

Entity::Ptr EntityManager::get(std::size_t id)
{
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        if (mEntities[i]->getId() == id)
        {
            return mEntities[i];
        }
    }
    return nullptr;
}

Entity::Ptr EntityManager::getByName(std::string const& name)
{
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        if (mEntities[i]->getName() == name)
        {
            return mEntities[i];
        }
    }
    return nullptr;
}

EntityManager::EntityArray EntityManager::getByType(std::string const& type)
{
    EntityArray array;
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        if (mEntities[i]->getType() == type)
        {
            array.push_back(mEntities[i]);
        }
    }
    return array;
}

EntityManager::EntityArray EntityManager::getByTag(std::string const& tag)
{
    EntityArray array;
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        if (mEntities[i]->getTag() == tag)
        {
            array.push_back(mEntities[i]);
        }
    }
    return array;
}

EntityManager::EntityArray EntityManager::getByFilter(ComponentFilter const& filter)
{
    EntityArray array;
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        if (mEntities[i]->hasComponents(filter))
        {
            array.push_back(mEntities[i]);
        }
    }
    return array;
}

void EntityManager::remove(Entity::Ptr e)
{
    mEntities.erase(std::remove_if(mEntities.begin(),
        mEntities.end(),
        [&](Entity::Ptr entity){return entity == e;}),
        mEntities.end());
    for (auto itr = mSystems.begin(); itr != mSystems.end(); itr++)
    {
        if (itr->second->contains(e))
        {
            itr->second->remove(e);
        }
    }
}

void EntityManager::remove(std::size_t id)
{
    auto e = get(id);
    if (e != nullptr)
    {
        mEntities.erase(std::remove_if(mEntities.begin(),
            mEntities.end(),
            [&](Entity::Ptr entity){return entity->getId() == id;}),
            mEntities.end());
        for (auto itr = mSystems.begin(); itr != mSystems.end(); itr++)
        {
            if (itr->second->contains(e))
            {
                itr->second->remove(e);
            }
        }
    }
}

void EntityManager::removeByName(std::string const& name)
{
    EntityArray e;
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        if (mEntities[i]->getName() == name)
        {
            e.push_back(mEntities[i]);
        }
    }
    mEntities.erase(std::remove_if(mEntities.begin(),
        mEntities.end(),
        [&](Entity::Ptr entity){return entity->getName() == name;}),
        mEntities.end());
    for (unsigned int j = 0; j < e.size(); j++)
    {
        for (auto itr = mSystems.begin(); itr != mSystems.end(); itr++)
        {
            if (itr->second->contains(e[j]))
            {
                itr->second->remove(e[j]);
            }
        }
    }
}

void EntityManager::removeByType(std::string const& type)
{
    auto e = EntityManager::getByType(type);
    mEntities.erase(std::remove_if(mEntities.begin(),
        mEntities.end(),
        [&](Entity::Ptr entity){return entity->getType() == type;}),
        mEntities.end());
    for (unsigned int j = 0; j < e.size(); j++)
    {
        for (auto itr = mSystems.begin(); itr != mSystems.end(); itr++)
        {
            if (itr->second->contains(e[j]))
            {
                itr->second->remove(e[j]);
            }
        }
    }
}

void EntityManager::removeByTag(std::string const& tag)
{
    auto e = EntityManager::getByTag(tag);
    mEntities.erase(std::remove_if(mEntities.begin(),
        mEntities.end(),
        [&](Entity::Ptr entity){return entity->getTag() == tag;}),
        mEntities.end());
    for (unsigned int j = 0; j < e.size(); j++)
    {
        for (auto itr = mSystems.begin(); itr != mSystems.end(); itr++)
        {
            if (itr->second->contains(e[j]))
            {
                itr->second->remove(e[j]);
            }
        }
    }
}

void EntityManager::removeAll()
{
    removeAllSystems();
    mEntities.clear();
}

bool EntityManager::hasSystem(std::string const& type)
{
    return mSystems.find(type) != mSystems.end();
}

void EntityManager::removeAllSystems()
{
    mSystems.clear();
    updateAll();
}

std::size_t EntityManager::getEntitiesCount() const
{
    return mEntities.size();
}

bool EntityManager::idExist(std::size_t id) const
{
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        if (id == mEntities[i]->getId())
        {
            return true;
        }
    }
    return false;
}

void EntityManager::updateAll()
{
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        update(mEntities[i]->getId());
    }
}

void EntityManager::update(std::size_t id)
{
    Entity::Ptr e = get(id);
    for (auto itr = mSystems.begin(); itr != mSystems.end(); itr++)
    {
        if (!itr->second->contains(e) && itr->second->hasRequiredComponents(e))
        {
            itr->second->add(e);
        }
        if (itr->second->contains(e) && !itr->second->hasRequiredComponents(e))
        {
            itr->second->remove(e);
        }
    }
}

}
