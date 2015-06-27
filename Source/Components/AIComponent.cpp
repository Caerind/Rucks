#include "AIComponent.hpp"

AIComponent::AIComponent()
{
    mTarget = nullptr;
}

std::string AIComponent::getId()
{
    return "AIComponent";
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
        es::ComponentFilter targetFilter;
        targetFilter.requires(TransformComponent::getId());
        targetFilter.requires(SpriteComponent::getId());
        targetFilter.requires(LifeComponent::getId());
        if (mTarget->hasComponents(targetFilter) && hasParent())
        {
            sf::Vector2f ePos = mParent->getComponent<TransformComponent>().getPosition();
            sf::Vector2f tPos = mTarget->getComponent<TransformComponent>().getPosition();
            if (mTarget->getId() != mParent->getId() && mTarget->getComponent<LifeComponent>().isAlive() && thor::length(ePos - tPos) < mOutOfView)
            {
                //resetBoredTime();
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
