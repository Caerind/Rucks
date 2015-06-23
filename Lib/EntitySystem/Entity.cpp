#include "Entity.hpp"

namespace es
{

std::size_t Entity::gIdCounter = 0;

Entity::Entity(EntityManager* manager, std::string const& name, std::size_t id)
: mManager(manager)
{
    if (id != 0)
    {
        mId = id;
    }
    else
    {
        mId = gIdCounter++;
    }
    mName = name;
    mType = "Entity";
    mTag = "Nothing";
}

bool Entity::hasComponent(std::string const& type)
{
    return mComponents.find(type) != mComponents.end();
}

bool Entity::hasComponents(ComponentFilter const& filter)
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

void Entity::removeAllComponents()
{
    mComponents.clear();
}

std::size_t Entity::getId() const
{
    return mId;
}

std::string Entity::getName() const
{
    return mName;
}

std::string Entity::getType() const
{
    return mType;
}

std::string Entity::getTag() const
{
    return mTag;
}

void Entity::setType(std::string const& type)
{
    mType = type;
}

void Entity::setTag(std::string const& tag)
{
    mTag = tag;
}

}
