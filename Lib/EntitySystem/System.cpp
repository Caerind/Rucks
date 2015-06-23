#include "System.hpp"

namespace es
{

System::System()
: mManager(nullptr)
{
}

System::~System()
{
}

std::string System::getId()
{
    return "System";
}

void System::add(Entity::Ptr e)
{
    mEntities.push_back(e);
}

void System::remove(Entity::Ptr e)
{
    mEntities.erase(std::remove_if(mEntities.begin(),
        mEntities.end(),
        [&](Entity::Ptr entity){return entity == e;}),
        mEntities.end());
}

void System::removeAll()
{
    mEntities.clear();
}

bool System::contains(Entity::Ptr e)
{
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        if (mEntities[i] == e)
        {
            return true;
        }
    }
    return false;
}

bool System::hasRequiredComponents(Entity::Ptr e)
{
    if (e != nullptr)
    {
        return e->hasComponents(mFilter);
    }
    return false;
}

System::EntityArray System::getEntities()
{
    return mEntities;
}

void System::setManager(EntityManager* manager)
{
    mManager = manager;
}

}
