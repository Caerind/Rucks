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

sf::Vector2f MonsterComponent::getSize(MonsterComponent::Type type)
{
    switch (type)
    {
        case MonsterComponent::Bat: return sf::Vector2f(32,32); break;
        case MonsterComponent::Bee: return sf::Vector2f(32,32); break;


    }
    return sf::Vector2f(32,32);
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

sf::Vector2i MonsterComponent::getSheetSize(MonsterComponent::Type type)
{
    switch (type)
    {
        case MonsterComponent::Bat: return sf::Vector2i(32,32); break;
        case MonsterComponent::Bee: return sf::Vector2i(32,32); break;


    }
    return sf::Vector2i(32,32);
}

sf::FloatRect MonsterComponent::getCollisionBox(MonsterComponent::Type type)
{
    switch (type)
    {
        case MonsterComponent::Bat: return sf::FloatRect(0,10,10,10); break;
        case MonsterComponent::Bee: return sf::FloatRect(0,10,10,10); break;


    }
    return sf::FloatRect(0,10,10,10);
}

float MonsterComponent::getSpeed(MonsterComponent::Type type)
{
    return 100.f;
}

unsigned int MonsterComponent::getLife(MonsterComponent::Type type)
{
    return 100;
}

float MonsterComponent::getViewDistance(MonsterComponent::Type type)
{
    return 300.f;
}

float MonsterComponent::getOutOfView(MonsterComponent::Type type)
{
    return 500.f;
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
