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
    switch (type)
    {
        case MonsterComponent::Bat: return 100.f; break;
        case MonsterComponent::Bee: return 100.f; break;


    }
    return 100.f;
}

unsigned int MonsterComponent::getLife(MonsterComponent::Type type)
{
    switch (type)
    {
        case MonsterComponent::Bat: return 100; break;
        case MonsterComponent::Bee: return 100; break;


    }
    return 100;
}

float MonsterComponent::getViewDistance(MonsterComponent::Type type)
{
    switch (type)
    {
        case MonsterComponent::Bat: return 300.f; break;
        case MonsterComponent::Bee: return 300.f; break;


    }
    return 300.f;
}

float MonsterComponent::getOutOfView(MonsterComponent::Type type)
{
    switch (type)
    {
        case MonsterComponent::Bat: return 500.f; break;
        case MonsterComponent::Bee: return 500.f; break;


    }
    return 500.f;
}

float MonsterComponent::getRange(MonsterComponent::Type type)
{
    switch (type)
    {
        case MonsterComponent::Bat: return 50.f; break;
        case MonsterComponent::Bee: return 50.f; break;


    }
    return 50.f;
}

unsigned int MonsterComponent::getDamage(MonsterComponent::Type type)
{
    switch (type)
    {
        case MonsterComponent::Bat: return 5; break;
        case MonsterComponent::Bee: return 10; break;


    }
    return 5;
}

sf::Time MonsterComponent::getCooldown(MonsterComponent::Type type)
{
    return sf::seconds(0.3f);
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
