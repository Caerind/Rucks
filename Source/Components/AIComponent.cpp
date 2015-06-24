#include "AIComponent.hpp"
#include "../World.hpp"

AIComponent::AIComponent()
{
}

std::string AIComponent::getId()
{
    return "AIComponent";
}

es::ComponentFilter AIComponent::getTargetFilter()
{
    es::ComponentFilter filter;
    filter.push_back(TransformComponent::getId());
    filter.push_back(SpriteComponent::getId());
    filter.push_back(LifeComponent::getId());
    return filter;
}

void AIComponent::setTarget(es::Entity::Ptr target)
{
    mTarget = target;
    hasTarget();
}

es::Entity::Ptr AIComponent::getTarget()
{
    return mTarget;
}

bool AIComponent::hasTarget()
{
    if (mTarget != nullptr)
    {
        if (mTarget->hasComponents(getTargetFilter()) && mTarget->getId() != getIdAttachedTo())
        {
            es::Entity::Ptr e = World::instance().getEntities().get(getIdAttachedTo());
            sf::Vector2f ePos = e->getComponent<TransformComponent>().getPosition();
            sf::Vector2f tPos = mTarget->getComponent<TransformComponent>().getPosition();
            if (mTarget->getComponent<LifeComponent>().isAlive() && thor::length(ePos - tPos) < mOutOfView)
            {
                return true;
            }
            else
            {
                mTarget = nullptr;
            }
        }
        else
        {
            mTarget = nullptr;
        }
    }
    return false;
}

void AIComponent::setMonster(bool monster)
{
    mIsMonster = monster;
}

bool AIComponent::isMonster() const
{
    return mIsMonster;
}

void AIComponent::setFighter(bool fighter)
{
    mIsFighter = fighter;
}

bool AIComponent::isFighter() const
{
    return mIsFighter;
}

void AIComponent::setViewDistance(float distance)
{
    mViewDistance = distance;
}

float AIComponent::getViewDistance() const
{
    return mViewDistance;
}

void AIComponent::setOutOfView(float distance)
{
    mOutOfView = distance;
}

float AIComponent::getOutOfView() const
{
    return mOutOfView;
}
