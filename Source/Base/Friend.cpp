#include "Friend.hpp"

Friend::Friend()
{
}

void Friend::setUsername(std::string const& username)
{
    mUsername = username;
}

std::string Friend::getUsername() const
{
    return mUsername;
}

void Friend::setClientId(unsigned int id)
{
    mClientId = id;
}

unsigned int Friend::getClientId() const
{
    return mClientId;
}

void Friend::setPlayerId(unsigned int id)
{
    mPlayerId = id;
}

unsigned int Friend::getPlayerId() const
{
    return mPlayerId;
}

