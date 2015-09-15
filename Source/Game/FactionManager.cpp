#include "FactionManager.hpp"

FactionManager::FactionManager()
{
}

void FactionManager::loadFromFile(std::string const& filename)
{

}

void FactionManager::saveToFile(std::string const& filename)
{

}

void FactionManager::create(int id)
{
    Faction faction;
    faction.setId(id);
    mFactions[id] = faction;
}

void FactionManager::remove(int id)
{
    auto itr = mFactions.find(id);
    if (itr != mFactions.end())
    {
        mFactions.erase(itr);
    }
}

Faction& FactionManager::get(int id)
{
    if (mFactions.find(id) != mFactions.end())
    {
        return mFactions[id];
    }
}

std::size_t FactionManager::getMemberCount(int id)
{
    if (mFactions.find(id) != mFactions.end())
    {
        return mFactions[id].getMemberCount();
    }
    else
    {
        return 0;
    }
}

void FactionManager::addMember(int id)
{
    if (mFactions.find(id) != mFactions.end())
    {
        return mFactions[id].addMember();
    }
}

void FactionManager::removeMember(int id)
{
    if (mFactions.find(id) != mFactions.end())
    {
        return mFactions[id].removeMember();
    }
}

bool FactionManager::isAlly(int id1, int id2)
{
    if (mFactions.find(id1) != mFactions.end())
    {
        return mFactions[id1].isAlly(id2);
    }
    else
    {
        return false;
    }
}

bool FactionManager::isEnemy(int id1, int id2)
{
    if (mFactions.find(id1) != mFactions.end())
    {
        return mFactions[id1].isEnemy(id2);
    }
    else
    {
        return false;
    }
}

bool FactionManager::isNeutral(int id1, int id2)
{
    if (mFactions.find(id1) != mFactions.end())
    {
        return mFactions[id1].isNeutral(id2);
    }
    else
    {
        return false;
    }
}
