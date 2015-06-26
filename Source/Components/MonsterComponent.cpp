#include "MonsterComponent.hpp"
#include "../World.hpp"

MonsterComponent::MonsterComponent(MonsterComponent::Type type)
{
    mType = type;
}

std::string MonsterComponent::getId()
{
    return "MonsterComponent";
}

std::string MonsterComponent::getTextureId(MonsterComponent::Type type)
{
    switch (type)
    {
        case MonsterComponent::Bat: return "bat"; break;
        case MonsterComponent::Bee: return "bee"; break;


    }
    return "";
}

void MonsterComponent::loadMonsterTextures()
{
    World::instance().getResources().loadTexture("bat","Assets/Textures/bat.png");
    World::instance().getResources().loadTexture("bee","Assets/Textures/bee.png");

    World::instance().getResources().getTexture("bat").setSmooth(true);
    World::instance().getResources().getTexture("bee").setSmooth(true);
}

void MonsterComponent::releaseMonsterTextures()
{
    World::instance().getResources().releaseTexture("bat");
    World::instance().getResources().releaseTexture("bee");
}
