#include "AIComponent.hpp"
#include "../World.hpp"

AIComponent::AIComponent(float view, float out, Type type)
{
    setViewDistance(view);
    setOutOfView(out);
    setType(type);
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

void AIComponent::setType(AIComponent::Type type)
{
    mType = type;
}

AIComponent::Type AIComponent::getType() const
{
    return mType;
}

bool AIComponent::isFighter() const
{
    return mType == AIComponent::Type::Fighter;
}

bool AIComponent::isPacific() const
{
    return mType == AIComponent::Type::Pacific;
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
                resetBoredTime();
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

void AIComponent::resetBoredTime()
{
    mBoredTime.restart();
}

sf::Time AIComponent::getBoredTime() const
{
    return mBoredTime.getElapsedTime();
}
