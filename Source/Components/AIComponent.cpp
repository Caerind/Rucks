#include "AIComponent.hpp"
#include "../World.hpp"

AIComponent::AIComponent()
{
    mTarget = 0;
}

std::string AIComponent::getId()
{
    return "AIComponent";
}

bool AIComponent::setTargetId(std::size_t target)
{
    mTarget = target;
    return hasTarget();
}

std::size_t AIComponent::getTargetId() const
{
    return mTarget;
}

es::Entity::Ptr AIComponent::getTarget()
{
    return World::instance().getEntities().get(mTarget);
}

bool AIComponent::hasTarget()
{
    auto t = getTarget();
    if (t != nullptr)
    {
        es::ComponentFilter targetFilter;
        targetFilter.requires(FactionComponent::getId());
        targetFilter.requires(TransformComponent::getId());
        targetFilter.requires(StatComponent::getId());
        if (t->hasComponents(targetFilter) && hasParent())
        {
            sf::Vector2f ePos = mParent->getComponent<TransformComponent>().getPosition();
            sf::Vector2f tPos = t->getComponent<TransformComponent>().getPosition();
            if (t->getId() != mParent->getId() && t->getComponent<StatComponent>().isAlive() && thor::length(ePos - tPos) < mOutOfView && mParent->hasComponent<FactionComponent>())
            {
                if (mParent->getComponent<FactionComponent>().getFaction().isEnemy(t->getComponent<FactionComponent>().getFactionId()))
                {
                    return true;
                }
            }
            else
            {
                mTarget = 0;
            }
        }
        else
        {
            mTarget = 0;
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
