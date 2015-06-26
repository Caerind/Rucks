#include "Entity.hpp"

namespace es
{

std::size_t Entity::gIdCounter = 0;

Entity::Entity()
{
    mId = gIdCounter++;
}

bool Entity::hasComponent(std::string const& type) const
{
    return mComponents.find(type) != mComponents.end();
}

bool Entity::hasComponents(ComponentFilter const& filter) const
{
    for (unsigned int i = 0; i < filter.size(); i++)
    {
        if (!hasComponent(filter[i]))
        {
            return false;
        }
    }
    return true;
}

void Entity::removeComponents()
{
    mComponents.clear();
    if (hasManager())
    {
        mManager->updateEntity(mId,EntityManager::UpdateEntity::RemoveComponents);
    }
}

std::size_t Entity::getId() const
{
    return mId;
}

EntityManager* Entity::getManager() const
{
    return mManager;
}

bool Entity::hasManager() const
{
    return mManager != nullptr;
}

} // namespace es
