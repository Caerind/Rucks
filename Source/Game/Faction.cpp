#include "Faction.hpp"

Faction::Faction()
{
    mFactionId = 0;
    mName = "FactionLess";
    mMemberCount = 0;
}

void Faction::setId(int id)
{
    mFactionId = id;
}

int Faction::getId() const
{
    return mFactionId;
}

void Faction::setName(std::string const& name)
{
    mName = name;
}

std::string Faction::getName() const
{
    return mName;
}

bool Faction::isAlly(int id) const
{
    if (id == mFactionId)
    {
        return true;
    }
    for (std::size_t i = 0; i < mAllies.size(); i++)
    {
        if (mAllies[i] == id)
        {
            return true;
        }
    }
    return false;
}

bool Faction::isEnemy(int id) const
{
    for (std::size_t i = 0; i < mEnemies.size(); i++)
    {
        if (mEnemies[i] == id)
        {
            return true;
        }
    }
    return false;
}

bool Faction::isNeutral(int id) const
{
    return (!isAlly(id) && !isEnemy(id));
}

void Faction::addAlly(int id)
{
    mAllies.push_back(id);
    removeEnemy(id);
}

void Faction::addEnemy(int id)
{
    mEnemies.push_back(id);
    removeAlly(id);
}

void Faction::removeAlly(int id)
{
    for (std::size_t i = 0; i < mAllies.size(); i++)
    {
        if (mAllies[i] == id)
        {
            mAllies.erase(mAllies.begin() + i);
        }
    }
}

void Faction::removeEnemy(int id)
{
    for (std::size_t i = 0; i < mEnemies.size(); i++)
    {
        if (mEnemies[i] == id)
        {
            mEnemies.erase(mEnemies.begin() + i);
        }
    }
}

std::size_t Faction::getMemberCount() const
{
    if (mFactionId == 0)
    {
        return 0;
    }
    else
    {
        return mMemberCount;
    }
}

void Faction::addMember()
{
    mMemberCount++;
}

void Faction::removeMember()
{
    mMemberCount--;
}
