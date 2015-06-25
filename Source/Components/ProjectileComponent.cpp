#include "ProjectileComponent.hpp"
#include "../World.hpp"

ProjectileComponent::ProjectileComponent(ProjectileComponent::Type type)
{
    setType(type);
}

std::string ProjectileComponent::getId()
{
    return "ProjectileComponent";
}

void ProjectileComponent::setType(ProjectileComponent::Type type)
{
    mType = type;
    es::Entity::Ptr e = World::instance().getEntities().get(getIdAttachedTo());
    if (e->hasComponent<SpriteComponent>())
    {
        // TODO (#3#): Set Projectile Texture
    }
}

ProjectileComponent::Type ProjectileComponent::getType() const
{
    return mType;
}

void ProjectileComponent::setRange(float range)
{
    mRange = range;
}

float ProjectileComponent::getRange() const
{
    return mRange;
}

void ProjectileComponent::setDamage(unsigned int damage)
{
    mDamage = damage;
}

unsigned int ProjectileComponent::getDamage() const
{
    return mDamage;
}

void ProjectileComponent::setSpeed(float speed)
{
    mSpeed = speed;
}

float ProjectileComponent::getSpeed() const
{
    return mSpeed;
}

void ProjectileComponent::setDirection(sf::Vector2f const& direction)
{
    mDirection = thor::unitVector<float>(direction);
    es::Entity::Ptr e = World::instance().getEntities().get(getIdAttachedTo());
    if (e->hasComponent<SpriteComponent>() && e->hasComponent<TransformComponent>())
    {
        // TODO (#3#): Update Angle
    }
}

sf::Vector2f ProjectileComponent::getDirection() const
{
    return mDirection;
}

void ProjectileComponent::addDistanceTraveled(float distance)
{
    mDistanceTraveled += distance;
}

void ProjectileComponent::addDistanceTraveled(sf::Vector2f const& movement)
{
    mDistanceTraveled += thor::length(movement);
}

bool ProjectileComponent::fallDown() const
{
    return mDistanceTraveled >= mRange;
}

std::string ProjectileComponent::getTextureId(Type type)
{
    return "projectiles";
}

sf::Vector2f ProjectileComponent::getSize(Type type)
{
    return sf::Vector2f(16,32);
}

sf::Vector2i ProjectileComponent::getSheetSize(Type type)
{
    return sf::Vector2i(16,32);
}

sf::IntRect ProjectileComponent::getTextureRect(Type type)
{
    return sf::IntRect(type * 16, 32, 16, 32);
}

void ProjectileComponent::loadProjectileTextures()
{
    World::instance().getResources().loadTexture("projectiles","Assets/Textures/projectiles.png");
    World::instance().getResources().getTexture("projectiles").setSmooth(true);
}

void ProjectileComponent::releaseProjectileTextures()
{
    World::instance().getResources().releaseTexture("projectiles");
}
