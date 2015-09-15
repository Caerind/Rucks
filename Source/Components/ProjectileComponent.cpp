#include "ProjectileComponent.hpp"
#include "../World.hpp"

ProjectileComponent::ProjectileComponent()
{
    mStricker = 0;
    mDistanceTraveled = 0.f;
}

std::string ProjectileComponent::getId()
{
    return "ProjectileComponent";
}

void ProjectileComponent::setStrickerId(std::size_t stricker)
{
    mStricker = stricker;
}

std::size_t ProjectileComponent::getStrickerId() const
{
    return mStricker;
}

es::Entity::Ptr ProjectileComponent::getStricker()
{
    return World::instance().getEntities().get(mStricker);
}

void ProjectileComponent::setType(ProjectileComponent::Type type)
{
    mType = type;
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

void ProjectileComponent::setDirection(sf::Vector2f const& direction)
{
    mDirection = direction;
	if (mDirection != sf::Vector2f())
	{
		mDirection = thor::unitVector<float>(mDirection);
	}
    if (hasParent())
    {
        if (mParent->hasComponent<TransformComponent>())
        {
            mParent->getComponent<TransformComponent>().setRotation(static_cast<float>(atan2(mDirection.y,mDirection.x) * 180 / 3.14159265) + 90.f);
        }
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

float ProjectileComponent::getDistanceTraveled() const
{
    return mDistanceTraveled;
}

bool ProjectileComponent::fallDown() const
{
    return mDistanceTraveled >= mRange;
}

/*

std::string ProjectileComponent::getTextureId(Type type)
{
    return "projectiles";
}

sf::Vector2f ProjectileComponent::getSize(Type type)
{
    return sf::Vector2f(8,8);
}

sf::Vector2i ProjectileComponent::getSheetSize(Type type)
{
    return sf::Vector2i(16,32);
}

sf::IntRect ProjectileComponent::getTextureRect(Type type)
{
    return sf::IntRect(type * 16, 0, 16, 32);
}

*/
